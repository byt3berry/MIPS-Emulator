#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _FONCTION_FILES_C_
#define _FONCTION_FILES_C_

#include "../include/fonctionFiles2.h"
#include "../include/utils.h"
#include "constantes.c"

#endif

// TODO: stocker les formats d'entrée et de sortie des instructions dans la structure Instruction
// TODO: implémenter la distinction entre les mnémoniques de registres et les registres
// TODO: ranger les fonctions dans des fichiers spécifiques
// TODO: savoir s'il faut implémenter les mnémoniques
// TODO: verifier que les erreurs soient bien checkées pour le nouveau code

int readLine(FILE *file, int size, char *line, Instruction *instruction, char *instructionHex) {
    char* checkError = fgets(line, size, file);

    /* Checking if the line is a comment or empty. */
    if (checkError == NULL || checkError[0] == '#' || checkError[0] == '\n') {
        return 0;
    }

    // delLineFeed(line);
    replace(line, '\n', '\0');
    replace(line, '#', '\0');
    analyseLine(line, instruction);
    // printf("analyse finie\n");
    // getOutput(instruction, instructionHex);

    return 1;
}

void readAuto(FILE *progAsembleur, FILE *fichierAssemble, int registers[32]) {
    while (!feof(progAsembleur)) {
        Instruction *instruction = (Instruction *) malloc(sizeof(Instruction));
        setError(instruction, NO_ERROR);

        char instructionHex[9], line[50];
        int resultat = readLine(progAsembleur, 50, line, instruction, instructionHex);

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

        char instructionHex[9], line[50];
        int resultat = readLine(progAsembleur, 50, line, instruction, instructionHex);

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
    // printf("%s\n", line);
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
    // printf("entrée\n");
    
    while(!feof(file) && !isFound) {
        // printf("iciiii\n");
        char lineTested[100];
        char* checkError = fgets(lineTested, 100, file);
        // printf("%s", lineTested);

        if (checkError[0] == '#') {
            continue;
        }

        // printf("%s\n", lineTested);
        replace(line, '\n', '\0');

        char operateur[10], format[3], OPcodeOrFunc[10], nbParameters[10], inputFormat[20], orderParameters[10];
        sscanf(lineTested, "%s ; %s ; %s ; %s ; %s ; %s ;", operateur, format, OPcodeOrFunc, nbParameters, inputFormat, orderParameters);

        replace(inputFormat, '+', ' ');
        replace(orderParameters, '+', ' ');

        // printf("operateur : %s\n", operateur);
        // printf("format : %s\n", format);
        // printf("OPcodeOrFunc : %s\n", OPcodeOrFunc);
        // printf("nbParametres : %s\n", nbParametres);
        // printf("format_input : %s\n", inputFormat);
        // printf("orderParametres : %s\n", orderParametres);

        // printf("\n\n");

        if (strcmp(instruction->operateur, operateur) == 0) {
            isFound = 1;

            printf("operateur : %s\n", operateur);
            printf("format : %s\n", format);
            printf("OPcodeOrFunc : %s\n", OPcodeOrFunc);
            printf("nbParameters : %s\n", nbParameters);
            printf("format_input : %s\n", inputFormat);
            printf("orderParameters : %s\n", orderParameters);
            printf("\n");

            setOperateurFormat(format, instruction);
            setOperateurOPcodeOrFunc(OPcodeOrFunc, instruction);
            setNbParametersFromLine(nbParameters, instruction);
            setParametersFromLine(line, inputFormat, instruction);
            // setParametersOrderFromLine(orderParameters, instruction);

            printInfos(instruction);
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
    char temp[8];
    int parameters[4];
    /*
    Dans les types I, J, et R les instructions recoivent au maximum 3 paramètres
    Dans le type R, le code binaire contient 4 paramètres : rd, rs, rt et sa
    Mais un des 4 sera nul (le paramètre dépend de l'instruction)
    On ne donne donc pas de valeur à parametre[3] qui sera forcément nul
    */

    printf("iciiiii : %s\n", inputFormat);

    int nbParameters = sscanf(line, inputFormat, temp, &parameters[0], &parameters[1], &parameters[2]);
    
    // TODO: faire une fonction void checkRegisterExistence(instruction, parametre) qui set une erreur si le registre n'existe pas (si besoin)

    if (instruction->nbParameters != nbParameters -1) { // si on récupère un mauvais nombre de paramètres
        setNOP(instruction);
        setError(instruction, BAD_NBPARAMETERS);
    } else {
        switch (instruction->format) {
            case 5:
            case 6:
            case 11:
            case 12:
                checkRegisterExistence(instruction, parameters[0]);
                break;
            case 2:
            case 3:
            case 9:
            case 10:
                checkRegisterExistence(instruction, parameters[0]);
                checkRegisterExistence(instruction, parameters[1]);
                break;
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