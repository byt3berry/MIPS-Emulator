#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "read.h"
#include "analyse.h"
#include "utils.h"
#include "constantes.h"
#include "registers.h"
#include "memory.h"


int readLine(FILE *file, int size, char *line, Instruction *instruction, char *instructionHex) {
    char lineAnalyzed[size + 1];
    char *checkError;

    printf("line : %s\n", line);
    // printf("ici\n");

    if (file == NULL) {
        checkError = fgets(lineAnalyzed, size, stdin);
    } else {
        checkError = fgets(lineAnalyzed, size, file);
    }

    // printf("ici : %s\n", checkError);

    replaceChar(lineAnalyzed, '\n', '\0');
    replaceChar(lineAnalyzed, '\r', '\0');
    replaceChar(lineAnalyzed, '#', '\0');
    strcpy(line, lineAnalyzed);

    /*
 * On modifie la ligne pour qu'elle soit juste une liste de paramètres
 * ADDI $5, $0, 5 -> ADDI $5 $0 5
 */
    replaceChar(lineAnalyzed, '(', ' ');
    replaceChar(lineAnalyzed, ')', ' ');
    replaceChar(lineAnalyzed, ',', ' ');

    /* Si la ligne est nulle est ou un commentaire */
    if (checkError == NULL || checkError[0] == '\0') {
        return 0;
    }

    printf("%s\n", lineAnalyzed);

    analyseLine(lineAnalyzed, instruction);  // TODO: detecte pas quand c'est pas un opérateur valide
//    printInfos(instruction);
    executeInstruction(instruction);
    showRegistersStates();
    showMemoryStates();

    getOutput(instruction, instructionHex);
    printf("\n");

    return 1;
}

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

    analyseLine(line, instruction);
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
