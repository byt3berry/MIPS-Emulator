#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "read.h"
#include "analyse.h"
#include "utils.h"
#include "constantes.h"
#include "registers.h"
#include "Instruction.h"


// TODO : mode interactif à finir
void readInteractif() {
    Instruction *instructions[LINES_NUMBER_MAX] = {0};

    int index = 0;
    int isEnd = 0;

    while (!isEnd) {
        getAllInstructions(NULL, instructions, index);
        assemble(NULL, instructions, index);
        index++;

        char temp[50];
        getchar();
        int check = scanf("%[^\n]", temp);
        if (check != 0 && strcmp(temp, "EXIT") == 0) {
            isEnd = 1;
        }
    }

    freeAll(instructions);
}

void readAuto(FILE *progAsembleur, FILE *fichierAssemble, FILE *fichierFinal) {
    Instruction *instructions[LINES_NUMBER_MAX] = {0};

    getAllInstructions(progAsembleur, instructions, 0);

    assemble(fichierAssemble, instructions, -1);
    execute(instructions, -1);
//    showRegistersStates();
    writeFinalStateRegisters(fichierFinal);
    freeAll(instructions);
}

// TODO : mode pas à pas à finir
void readPas(FILE *progAsembleur) {
    Instruction *instructions[LINES_NUMBER_MAX] = {0};
    getAllInstructions(progAsembleur, instructions, 0);

    int index = 0;
    int isEndUser = 0;
    int isEndFile = 0;

    while (!isEndUser && !isEndFile) {
        printf("%s\n", instructions[index]->line);
        assemble(NULL, instructions, index);
        isEndFile = execute(instructions, 0);
//        showRegistersStates();

        char temp[50];
        getchar();
        int check = scanf("%[^\n]", temp);
        if (check != 0) {
            isEndUser = 1;
        }
    }
}

// TODO : A refractoriser
int getAllInstructions(FILE *file, Instruction *instructions[LINES_NUMBER_MAX], int index) {
    if (file == NULL) {
        Instruction *instruction = (Instruction *) malloc(sizeof(Instruction));
        char line[LINES_LENGTHS_MAX];
        char *checkError;

        getchar();
        checkError = fgets(line, LINES_LENGTHS_MAX - 1, stdin);

        replaceChar(line, '\n', '\0');
        replaceChar(line, '\r', '\0');
        replaceChar(line, '#', '\0');

        /* Si la ligne est nulle est ou un commentaire */
        if (checkError == NULL || checkError[0] == '\0') {
            return -1;
        }

        analyseLine(line, instruction);  // TODO: detecte pas quand c'est pas un opérateur valide
        instructions[index] = instruction;
    } else {
        while (!feof(file)) {
            Instruction *instruction = (Instruction *) malloc(sizeof(Instruction));
            setError(instruction, 0);
//            printf("error0 : %d\n", instruction->error);
            char line[LINES_LENGTHS_MAX];
            char *checkError = fgets(line, LINES_LENGTHS_MAX - 1, file);

            replaceChar(line, '\n', '\0');
            replaceChar(line, '\r', '\0');
            replaceChar(line, '#', '\0');

//            printf("%s\n", line);

            /* Si la ligne est nulle est ou un commentaire */
            if (checkError == NULL || checkError[0] == '\0') {
//                printf("skip : %s\n", line);
                index--;
            } else {
//                printf("accepted : %s\n", line);
                analyseLine(line, instruction);  // TODO: detecte pas quand c'est pas un opérateur valide
//                printInfos(instruction);
//                printf("\n");
                instructions[index] = instruction;
            }

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
//        printInfos(instructions[i]);
        getOutput(instructions[i], &instructionAssemble);

        if (fichierAssemble == NULL) {
            printf("hex : %08X\n", instructionAssemble);
        } else {
            fprintf(fichierAssemble, "%08X\n", instructionAssemble);
        }

        printf("%08X\n", instructionAssemble);
    }
}

int execute(Instruction *instructions[LINES_NUMBER_MAX], int index) {
    int PCvalue;
    getValueFromRegister(PC, &PCvalue);
    printf("PC value : %d\n", PCvalue);
    PCvalue /= 4;

    while (PCvalue < LINES_NUMBER_MAX && instructions[PCvalue] != NULL) {
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
