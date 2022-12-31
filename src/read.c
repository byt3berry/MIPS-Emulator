#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "read.h"
#include "analyse.h"
#include "utils.h"
#include "constantes.h"
#include "registers.h"


// TODO : mode interactif à finir
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
//    printf("ici0\n");
    getAllInstructions(progAsembleur, instructions, 0);

    int index = 0;
    int isEnd = 0;

//    printf("ici1\n");
    while (!isEnd) {
        assemble(NULL, instructions, index);
//        printf("ici2\n");
        execute(instructions, index);
//        printf("ici3\n");

        char temp[50] = {0};
        char *check = fgets(temp, 1, stdin);  // TODO: faire un truc pour passer à l'instruction suivante
        if (*check != '\n') {
            isEnd = 1;
        }
//        printf("iciii %d\n", (int) temp[0]);
    }
}

// TODO : A refractoriser
int getAllInstructions(FILE *file, Instruction *instructions[LINES_NUMBER_MAX], int index) {
    if (file == NULL) {
        Instruction *instruction = (Instruction *) malloc(sizeof(Instruction));
        char line[LINES_LENGTHS_MAX];
        char *checkError;

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
            char line[LINES_LENGTHS_MAX];
            char *checkError = fgets(line, LINES_LENGTHS_MAX - 1, file);

            replaceChar(line, '\n', '\0');
            replaceChar(line, '\r', '\0');
            replaceChar(line, '#', '\0');

//            printf("%s\n", line);

            /* Si la ligne est nulle est ou un commentaire */
            if (checkError == NULL || checkError[0] == '\0') {
                index--;
            } else {
                analyseLine(line, instruction);  // TODO: detecte pas quand c'est pas un opérateur valide
                instructions[index] = instruction;
            }

            index++;
        }
    }

    return 0;
}

void assemble(FILE *fichierAssemble, Instruction *instructions[LINES_NUMBER_MAX], int index) {
    for (int i = 0; i < LINES_NUMBER_MAX && instructions[i] != 0; i++) {
        if (index != -1 && i != index) {
            continue;
        }

        int instructionAssemble;
        getOutput(instructions[i], &instructionAssemble);

        if (fichierAssemble == NULL) {
            printf("hex : %08X\n", instructionAssemble);
        } else {
            fprintf(fichierAssemble, "%08X\n", instructionAssemble);
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
