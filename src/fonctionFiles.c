#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _FONCTION_FILES_C_
#define _FONCTION_FILES_C_

#include "../include/fonctionFiles.h"
#include "../include/utils.h"
#include "constantes.c"

#endif


int readLine(FILE *file, int size, char *line, Instruction *instruction, char *instructionHex) {
    char lineAnalyzed[size];
    char *checkError;

    printf("ici\n");

    if (file == NULL) {
        checkError = fgets(lineAnalyzed, size, stdin);
    } else {
        checkError = fgets(lineAnalyzed, size, file);
    }

    printf("ici : %s\n", checkError);

    replaceChar(lineAnalyzed, '\n', '\0');
    replaceChar(lineAnalyzed, '\r', '\0');
    replaceChar(lineAnalyzed, '#', '\0');
    strcpy(line, lineAnalyzed);

    /* Checking if the line is a comment or empty. */
    if (checkError == NULL || checkError[0] == '\0') {
        return 0;
    }

    printf("ici\n");

    analyseLine(lineAnalyzed, instruction);  // TODO: detecte pas quand c'est pas un opérateur valide
    getOutput(instruction, instructionHex);

    return 1;
}

void readInteractif(int registers[32]) {
    int isEnd = 0;

    while (!isEnd) {
        Instruction *instruction = (Instruction *) malloc(sizeof(Instruction));
        setError(instruction, NO_ERROR);

        char instructionHex[9], line[100];
        int resultat = readLine(NULL, 100, line, instruction, instructionHex);

        if (!resultat) {
            continue;
        }

        free(instruction);

        // printf("%s\n", line);
        printf("%s\n", instructionHex);

        int errorCode =  isError(instruction);

        if (errorCode) {
            printf("Erreur détéctée sur l'instruction !!\n");
            printf("Code d'erreur : %d\n", errorCode);
            showError(instruction);
        }

        char temp;
        temp = scanf("%c", &temp);
    }
}

void readAuto(FILE *progAsembleur, FILE *fichierAssemble, int registers[32]) {
    while (!feof(progAsembleur)) {
        Instruction *instruction = (Instruction *) malloc(sizeof(Instruction));
        setError(instruction, NO_ERROR);

        char instructionHex[9], line[100];
        int resultat = readLine(progAsembleur, 100, line, instruction, instructionHex);

        if (!resultat) {
            continue;
        }

        free(instruction);

        fprintf(fichierAssemble, "%s\n", instructionHex);
    }
}

void readPas(FILE *progAsembleur, int registers[32]) {
    while (!feof(progAsembleur)) {
        Instruction *instruction = (Instruction *) malloc(sizeof(Instruction));
        setError(instruction, NO_ERROR);

        char instructionHex[9], line[100];
        int resultat = readLine(progAsembleur, 100, line, instruction, instructionHex);

        if (!resultat) {
            continue;
        }

        free(instruction);

        printf("%s\n", line);
        printf("%s\n", instructionHex);

        int errorCode =  isError(instruction);

        if (errorCode) {
            printf("Erreur détéctée sur l'instruction !!\n");
            printf("Code d'erreur : %d\n", errorCode);
            showError(instruction);
        }

        char temp;
        temp = scanf("%c", &temp);
    }
}

void analyseLine(char *line, Instruction *instruction) {
    // on récupère toutes les infos de l'instruction
    setOperateurFromLine(line, instruction);
    setInfos(line, instruction);



    // setOperateurFormat(instruction);
    // if (!isError(instruction)) { // s'il n'y a pas d'erreur sur l'opérateur
    //     setNbParametersFromLine(instruction);  // si pas d'erreur sur l'opérateur alors pas d'erreur ici
    //     setParametersFromLine(line, instruction);

    //     if (!isError(instruction)) {  // s'il n'y a pas d'erreur sur les paramètres
    //         setOperateurOPcodeOrFunc(instruction);  // si pas d'erreur sur l'opérateur alors pas d'erreur ici
    //         setParametersOrderFromLine(instruction);  // si pas d'erreur sur l'opérateur alors pas d'erreur ici
    //     }
    // }
}

void setInfos(char *line, Instruction *instruction) {
    FILE * file = fopen("data/data.txt", "r");
    int isFound = 0;
    
    while(!feof(file) && !isFound) {
        char lineTested[100];
        char* checkError = fgets(lineTested, 100, file);

        if (checkError[0] == '#') {
            continue;
        }

        replaceChar(line, '(', ' ');
        replaceChar(line, ')', ' ');
        replaceChar(line, '\n', '\0');
        removeChar(line, ',');

        char operateur[10], format[3], OPcodeOrFunc[10], nbParameters[10], inputFormat[20], orderParameters[10];
        sscanf(lineTested, "%s ; %s ; %s ; %s ; %s ; %s ;", operateur, format, OPcodeOrFunc, nbParameters, inputFormat, orderParameters);

        replaceChar(inputFormat, '+', ' ');
        replaceChar(orderParameters, '+', ' ');

        if (strcmp(instruction->operateur, operateur) == 0) {
            isFound = 1;

            setOperateurFormat(format, instruction);
            setOperateurOPcodeOrFunc(OPcodeOrFunc, instruction);
            setNbParametersFromLine(nbParameters, instruction);
            setParametersFromLine(line, inputFormat, instruction);
            setParametersOrderFromLine(orderParameters, instruction);
        }
        
    }
}

void setOperateurFromLine(char *line, Instruction *instruction) {
    char operateur[8];  // stock l'adresse de début de l'opétateur
    char *tempOP = operateur;
    char *tempLine = line;

    while (*tempLine != ' ' && *tempLine != '\n') { // tant qu'il n'y a pas d'espace ou de retour à la ligne
        *tempOP = *tempLine;
        tempOP++;
        tempLine++;
    }
    *tempOP = '\0';

    toUpperCase(operateur);
    setOperateur(instruction, operateur);
}

void setOperateurFormat(char *formatChar, Instruction *instruction) {
    int formatInt;
    sscanf(formatChar, "%d", &formatInt);
    setFormat(instruction, formatInt);
}

void setOperateurOPcodeOrFunc(char *OPcodeOrFuncChar, Instruction *instruction) {
    int OPcodeOrFuncInt;
    sscanf(OPcodeOrFuncChar, "%d", &OPcodeOrFuncInt);
    setOPcodeOrFunc(instruction, OPcodeOrFuncInt);
}

void setNbParametersFromLine(char *nbParametersChar, Instruction *instruction) {
    int nbParametersInt;
    sscanf(nbParametersChar, "%d", &nbParametersInt);
    setNbParameters(instruction, nbParametersInt);
}

void setParametersFromLine(char *line, char *inputFormat, Instruction *instruction) {
    /*
    Dans les types I, J, et R les instructions recoivent au maximum 3 paramètres
    Dans le type R, le code binaire contient 4 paramètres : rd, rs, rt et sa
    Mais un des 4 sera nul (le paramètre dépend de l'instruction)
    On ne donne donc pas de valeur à parametre[3] qui sera forcément nul
    */

    char temp[8];
    int parameters[4];
    int nbParameters = sscanf(line, inputFormat, temp, &parameters[0], &parameters[1], &parameters[2]);
    
    if (instruction->nbParameters != nbParameters -1) { // si on récupère un mauvais nombre de paramètres
        setNOP(instruction);
        setError(instruction, BAD_NBPARAMETERS);
    } else {
        switch (instruction->format) {
            // si le paramètre 1 est un registre
            case 5:
            case 6:
            case 11:
            case 12:
                checkRegisterExistence(instruction, parameters[0]);
                break;
            // si les paramètres 1 et 2 sont des registres
            case 2:
            case 3:
            case 9:
            case 10:
                checkRegisterExistence(instruction, parameters[0]);
                checkRegisterExistence(instruction, parameters[1]);
                break;
            // si les paramètres 1 et 3 sont des registres
            case 4:
                checkRegisterExistence(instruction, parameters[0]);
                checkRegisterExistence(instruction, parameters[2]);
                break;
            // si les paramètres 1, 2 et 3 sont des registres
            case 7:
            case 8:
                checkRegisterExistence(instruction, parameters[0]);
                checkRegisterExistence(instruction, parameters[1]);
                checkRegisterExistence(instruction, parameters[2]);
                break;
        }
    }

    if (!isError(instruction)) {
        setParameters(instruction, parameters);
    }
}

void setParametersOrderFromLine(char *orderParametresChar, Instruction *instruction) {
    int orderParametresInt[4];
    sscanf(orderParametresChar, "%d %d %d %d", &orderParametresInt[0], &orderParametresInt[1], &orderParametresInt[2], &orderParametresInt[3]);
    setParametersOrder(instruction, orderParametresInt);
}

void checkRegisterExistence(Instruction *instruction, int parameter) {
    if (parameter < 0 || 31 <= parameter) {
        setError(instruction, BAD_REGISTER);
    }
}