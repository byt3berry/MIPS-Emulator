#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "read.h"
#include "analyse.h"
#include "utils.h"
#include "constantes.h"
#include "registers.h"


void readInteractif() {
    Instruction *instructions[LINES_NUMBER_MAX] = {0};
    int index = 0;
    int isEnd = 0;

    while (!isEnd) {
        getAllInstructions(NULL, instructions, index);
        assemble(NULL, instructions, index);
        execute(instructions, index);

        char temp[50] = {0};
        if (*fgets(temp, 50, stdin) != '\n') {
            isEnd = 1;
        }
    }
}

void readAuto(FILE *progAsembleur, FILE *fichierAssemble, FILE *fichierFinal) {
    Instruction *instructions[LINES_NUMBER_MAX] = {0};
    getAllInstructions(progAsembleur, instructions, 0);
    assemble(fichierAssemble, instructions, -1);

    execute(instructions, -1);
    showRegistersStates();
    writeFinalStateRegisters(fichierFinal);
    freeAll(instructions);
}

void readPas(FILE *progAsembleur) {
    Instruction *instructions[LINES_NUMBER_MAX] = {0};
    getAllInstructions(progAsembleur, instructions, 0);

    int index = 0;
    int isEnd = 0;

    while (!isEnd) {
        assemble(NULL, instructions, index);
        execute(instructions, index);

        char temp[50] = {0};
        char *check = fgets(temp, 1, stdin);  // TODO: faire un truc pour passer à l'instruction suivante
        if (*check != '\n') {
            isEnd = 1;
        }
        printf("iciii %d\n", (int) temp[0]);
    }
}

void getAllInstructions(FILE *file, Instruction *instructions[LINES_NUMBER_MAX], int index) {
    Instruction *instruction = (Instruction *) malloc(sizeof(Instruction));
    char line[LINES_LENGTHS_MAX];
    char *checkError;

    if (file == NULL) {
        checkError = fgets(line, LINES_LENGTHS_MAX - 1, stdin);
    } else if (feof(file)) {
        printf("ici\n");
        return;
    } else {
        checkError = fgets(line, LINES_LENGTHS_MAX - 1, file);
    }


    replaceChar(line, '\n', '\0');
    replaceChar(line, '\r', '\0');
    replaceChar(line, '#', '\0');

    /* Si la ligne est nulle est ou un commentaire */
    if (checkError == NULL || checkError[0] == '\0') {
        return getAllInstructions(file, instructions, index);
    }

    analyseLine(line, instruction);  // TODO: detecte pas quand c'est pas un opérateur valide
    instructions[index] = instruction;

    if (file == NULL) {
        return;
    }

    return getAllInstructions(file, instructions, index + 1);

}

void assemble(FILE *fichierAssemble, Instruction *instructions[LINES_NUMBER_MAX], int index) {
    for (int i = 0; i < LINES_NUMBER_MAX && instructions[i] != 0; i++) {
        if (index != -1 && i != index) {
            continue;
        }

        char instructionHex[9];
        getOutput(instructions[i], instructionHex);

        if (fichierAssemble == NULL) {
            printf("%s\n", instructionHex);
        } else {
            fprintf(fichierAssemble, "%s\n", instructionHex);
        }
    }
}

void execute(Instruction *instructions[LINES_NUMBER_MAX], int index) {
    int PCvalue;
    getValueFromRegister(PC, &PCvalue);
    PCvalue /= 4;

    while(PCvalue < LINES_NUMBER_MAX && instructions[PCvalue] != 0) {
        if (index != -1 && PCvalue != index) {
            continue;
        }

        executeInstruction(instructions[PCvalue]);
        incrementPC(1);
        getValueFromRegister(PC, &PCvalue);
        PCvalue /= 4;

//        break;
    }
}

void freeAll(Instruction *instructions[LINES_NUMBER_MAX]) {
    for (int i = 0; i < LINES_NUMBER_MAX && instructions[i] != 0; i++) {
        free(instructions[i]);
    }
}
