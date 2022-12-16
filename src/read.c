#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "read.h"
#include "analyse.h"
#include "execute.h"
#include "utils.h"
#include "constantes.h"


int readLine(FILE *file, int *registers, int size, char *line, Instruction *instruction, char *instructionHex) {
    char lineAnalyzed[size + 1];
    char *checkError;

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

    analyseLine(lineAnalyzed, instruction);  // TODO: detecte pas quand c'est pas un opérateur valide
    execute(instruction, registers);

    getOutput(instruction, instructionHex);

    return 1;
}

void readInteractif(int *registers) {
    int isEnd = 0;

    while (!isEnd) {
        Instruction *instruction = (Instruction *) malloc(sizeof(Instruction));
        setError(instruction, NO_ERROR);

        char instructionHex[9], line[100];
        int resultat = readLine(NULL, registers, 100, line, instruction, instructionHex);

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

void readAuto(FILE *progAsembleur, FILE *fichierAssemble, int *registers) {
    while (!feof(progAsembleur)) {
        Instruction *instruction = (Instruction *) malloc(sizeof(Instruction));
        setError(instruction, NO_ERROR);

        char instructionHex[9], line[100];
        int resultat = readLine(progAsembleur, registers, 100, line, instruction, instructionHex);

        if (!resultat) {
            continue;
        }

//        printInfos(instruction);

        free(instruction);

        fprintf(fichierAssemble, "%s\n", instructionHex);

//        break;
    }
}

void readPas(FILE *progAsembleur, int *registers) {
    while (!feof(progAsembleur)) {
        Instruction *instruction = (Instruction *) malloc(sizeof(Instruction));
        setError(instruction, NO_ERROR);

        char instructionHex[9], line[100];
        int resultat = readLine(progAsembleur, registers, 100, line, instruction, instructionHex);

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