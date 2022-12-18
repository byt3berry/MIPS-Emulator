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
    int isEnd = 0;

    while (!isEnd) {
        Instruction *instruction = (Instruction *) malloc(sizeof(Instruction));
        setError(instruction, NO_ERROR);

        char instructionHex[9], line[100];
        int resultat = readLine(NULL, 100, line, instruction, instructionHex);

        if (!resultat) {
            continue;
        }

        int errorCode = isError(instruction);

        if (errorCode) {
            printf("Erreur détéctée sur l'instruction !!\n");
            printf("Code d'erreur : %d\n", errorCode);
            showError(instruction);
        }

        free(instruction);

        // printf("%s\n", line);
//        printInfos(instruction);
        printf("%s\n", instructionHex);


        char temp;
        temp = scanf("%c", &temp);
    }
}

void readAuto(FILE *progAsembleur, FILE *fichierAssemble, FILE *fichierFinal) {
    Instruction *instructions[LINES_NUMBER_MAX] = {0};
    getAllInstructions(progAsembleur, instructions, 0);
    assemble(fichierAssemble, instructions, -1);

//    for (int i = 0; instructions[i] != 0; i++) {
////        printf("%d : %s\n", i + 1, instructions[i]->line);
//        printInfos(instructions[i]);
//        printf("\n");
//    }

    execute(instructions, -1);
    showRegistersStates();
    writeFinalStateRegisters(fichierFinal);
    freeAll(instructions);
}

void readPas(FILE *progAsembleur) {
    while (!feof(progAsembleur)) {
        Instruction *instruction = (Instruction *) malloc(sizeof(Instruction));
        setError(instruction, NO_ERROR);

        char instructionHex[9], line[100];
        int resultat = readLine(progAsembleur, 100, line, instruction, instructionHex);

        if (!resultat) {
            continue;
        }

        printf("%s\n", line);

        int errorCode = isError(instruction);

        if (errorCode) {
            printf("Erreur détéctée sur l'instruction !!\n");
            printf("Code d'erreur : %d\n", errorCode);
            showError(instruction);
        } else {
            printf("%s\n", instructionHex);
        }

        free(instruction);

        char temp[50];
        if (*fgets(temp, 50, stdin) != '\n') {
            break;
        }
    }
}

void getAllInstructions(FILE *file, Instruction *instructions[LINES_NUMBER_MAX], int index) {
    if (feof(file)) {
        return;
    }

    Instruction *instruction = (Instruction *) malloc(sizeof(Instruction));
    char line[LINES_LENGTHS_MAX];
    char *checkError;

    if (file == NULL) {
        checkError = fgets(line, LINES_LENGTHS_MAX - 1, stdin);
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
        printf("PC : %d\n", PCvalue);
        if (index != -1 && PCvalue != index) {
            printf("iciiiiiii\n");
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
