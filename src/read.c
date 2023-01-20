// Projet MIPS 2022-2023
// Auteurs : Cocagne_Strainovic

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "read.h"
#include "analyse.h"
#include "utils.h"
#include "constantes.h"
#include "registers.h"
#include "Instruction.h"


void readInteractif() {
    char line[LINES_LENGTHS_MAX];
    char *checkError = fgets(line, LINES_LENGTHS_MAX - 1, stdin);
    int isError = NO_ERROR;

    while (checkError != NULL && strcmp(line, "EXIT\n") != 0 && isError == NO_ERROR) {
        Instruction *instruction = (Instruction *) malloc(sizeof(Instruction));

        replaceChar(line, '\n', '\0');
        replaceChar(line, '\r', '\0');
        replaceChar(line, '#', '\0');

        if (line[0] == '\0') {
            continue;
        }

        analyseLine(line, instruction);

        if (isJumpOrBranch(instruction)) {
            setError(instruction, PAS_A_PAS);
        }

        isError = getError(instruction);  // erreur pendant l'assemblage

        if (!isError) {
            setOutput(instruction);
            printf("%08X\n", getOutput(instruction));

            executeInstruction(instruction);
            incrementPC(1);
        }

        isError = getError(instruction);  // erreur pendant l'execution

        free(instruction);

        printf("\n");

        if (!isError) {
            checkError = fgets(line, LINES_LENGTHS_MAX - 1, stdin);
        }
    }
}

void readAuto(FILE *progAsembleur, FILE *fichierAssemble, FILE *fichierFinal) {
    Instruction *instructions[LINES_NUMBER_MAX] = {0};

    int isError = getAllInstructionsInFile(progAsembleur, instructions, 0);

    if (isError) return;

    assemble(fichierAssemble, instructions, -1);
    execute(instructions, -1, 0);
    writeFinalStateRegisters(fichierFinal);
    showRegistersStates();
    freeAll(instructions);
}

void readPas(FILE *progAsembleur) {
    Instruction *instructions[LINES_NUMBER_MAX] = {0};
    int isError = getAllInstructionsInFile(progAsembleur, instructions, 0);

    if (isError) return;

    assemble(NULL, instructions, -1);

    int isEndUser = 0;
    int isEndFile = 0;

    while (!isEndUser && !isEndFile) {
        isEndFile = execute(instructions, 0, 1);

        char temp[50];
        getchar();
        int check = scanf("%[^\n]", temp);
        if (check != 0 && strcmp(temp, "EXIT") == 0) {
            isEndUser = 1;
        }
    }
}

int getAllInstructionsInFile(FILE *file, Instruction *instructions[LINES_NUMBER_MAX], int index) {
    while (!feof(file)) {
        Instruction *instruction = (Instruction *) malloc(sizeof(Instruction));
        setError(instruction, 0);
        char line[LINES_LENGTHS_MAX];
        char *checkError = fgets(line, LINES_LENGTHS_MAX - 1, file);
        int isError;

        replaceChar(line, '\n', '\0');
        replaceChar(line, '\r', '\0');
        replaceChar(line, '#', '\0');

        /* Si la ligne est nulle est ou un commentaire */
        if (checkError == NULL || checkError[0] == '\0') {
            index--;
        } else {
            isError = analyseLine(line, instruction);
            instructions[index] = instruction;
        }

        if (isError) {  // s'il y a une erreur dans l'instruction
            return isError;
        } else {
            index++;
        }
    }

    return 0;
}

void assemble(FILE *fichierAssemble, Instruction *instructions[LINES_NUMBER_MAX], int index) {
    for (int i = 0; i < LINES_NUMBER_MAX && instructions[i] != NULL; i++) {
        if (index != -1 && i != index) {
            continue;
        }

        setOutput(instructions[i]);

        if (fichierAssemble != NULL) {
            fprintf(fichierAssemble, "%08X\n", getOutput(instructions[i]));
        }

    }
}

int execute(Instruction *instructions[LINES_NUMBER_MAX], int index, int verboseMode) {
    int PCvalue;
    getValueFromRegister(PC, &PCvalue);
    PCvalue /= 4;
    int isError = NO_ERROR;

    while (PCvalue < LINES_NUMBER_MAX && instructions[PCvalue] != NULL && isError == NO_ERROR) {
        // si l'instruction est un jump ou un branch, il aura accès à l'instruction suivante pour le delay slot
        nextInstruction = instructions[PCvalue + 1];
        executeInstruction(instructions[PCvalue]);
        isError = getError(instructions[PCvalue]);
        nextInstruction = NULL;

        if (isJumpOrBranch(instructions[PCvalue])) {
            isError += getError(instructions[PCvalue + 1]);
        }

        if (verboseMode) {
            printf("%s\n", getLine(instructions[PCvalue]));
            printf("%08X\n", getOutput(instructions[PCvalue]));

            if (isJumpOrBranch(instructions[PCvalue])) {
                printf("DelaySlot :\n");
                printf("    %s\n", getLine(instructions[PCvalue + 1]));
                printf("    %08X\n", getOutput(instructions[PCvalue + 1]));
            }
            printf("\n");

            showRegistersStates();
        }


        incrementPC(1);
        getValueFromRegister(PC, &PCvalue);
        PCvalue /= 4;

        if (index == 0) {
            return 0;
        }
    }

    return 1;
}

void freeAll(Instruction *instructions[LINES_NUMBER_MAX]) {
    for (int i = 0; i < LINES_NUMBER_MAX && instructions[i] != 0; i++) {
        free(instructions[i]);
    }
}
