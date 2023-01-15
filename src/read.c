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

    while (checkError != NULL && strcmp(line, "EXIT\n") != 0) {
        Instruction *instruction = (Instruction *) malloc(sizeof(Instruction));

        replaceChar(line, '\n', '\0');
        replaceChar(line, '\r', '\0');
        replaceChar(line, '#', '\0');

        if (line[0] == '\0') {
            continue;
        }

        int isError = analyseLine(line, instruction);

        if (!isError) {
            int instructionAssemble;
            getOutput(instruction, &instructionAssemble);
            printf("%08X\n", instructionAssemble);

            executeInstruction(instruction);
            incrementPC(1);
        }

        free(instruction);

        printf("\n");
        checkError = fgets(line, LINES_LENGTHS_MAX - 1, stdin);
    }
}

void readAuto(FILE *progAsembleur, FILE *fichierAssemble, FILE *fichierFinal) {
    Instruction *instructions[LINES_NUMBER_MAX] = {0};

    int isError = getAllInstructionsInFile(progAsembleur, instructions, 0);

    if (!isError) {
        assemble(fichierAssemble, instructions, -1);
        execute(instructions, -1);
        writeFinalStateRegisters(fichierFinal);
        freeAll(instructions);
    }
}

void readPas(FILE *progAsembleur) {
    Instruction *instructions[LINES_NUMBER_MAX] = {0};
    getAllInstructionsInFile(progAsembleur, instructions, 0);

    int index = 0;
    int isEndUser = 0;
    int isEndFile = 0;

    while (!isEndUser && !isEndFile) {
        assemble(NULL, instructions, index);
        isEndFile = execute(instructions, 0);

        char temp[50];
        getchar();
        int check = scanf("%[^\n]", temp);
        if (check != 0 && strcmp(temp, "EXIT") == 0) {
            isEndUser = 1;
        }
    }
}

// TODO : A refractoriser
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
            isError = analyseLine(line, instruction);  // TODO: detecte pas quand c'est pas un opérateur valide
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

        int instructionAssemble;
        getOutput(instructions[i], &instructionAssemble);  // TODO: stocker l'output dans la struct ?

        if (fichierAssemble == NULL) {
            printf("%08X\n", instructionAssemble);
        } else {
            fprintf(fichierAssemble, "%08X\n", instructionAssemble);
        }

    }
}

int execute(Instruction *instructions[LINES_NUMBER_MAX], int index) {
    int PCvalue;
    getValueFromRegister(PC, &PCvalue);
    PCvalue /= 4;

    while (PCvalue < LINES_NUMBER_MAX && instructions[PCvalue] != NULL) {
        printf("%s\n", instructions[PCvalue]->line);
        nextInstruction = instructions[PCvalue + 1];
        executeInstruction(instructions[PCvalue]);
        nextInstruction = NULL;

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
