#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _FONCTION_FILES_C_
#define _FONCTION_FILES_C_

#include "fonctionFiles.h"
#include "../include/utils.h"
#include "constantes.c"

#endif

// TODO: stocker les formats d'entrée et de sortie des instructions dans la structure Instruction
// TODO: implémenter la distinction entre les mnémoniques de registres et les registres
// TODO: ranger les fonctions dans des fichiers spécifiques
// TODO: savoir s'il faut implémenter les mnémoniques

int readLine(FILE *file, int size, char *line, Instruction *instruction, char *instructionHex) {
    char* checkError = fgets(line, size, file);

    /* Checking if the line is a comment or empty. */
    if (checkError == NULL || checkError[0] == '#' || checkError[0] == '\n') {
        return 0;
    }

    delLineFeed(line);
    analyseLine(line, instruction);
    getOutput(instruction, instructionHex);

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
    setOperateurFromLine(line, instruction);
    setOperateurFormat(instruction);
    if (!isError(instruction)) { // s'il n'y a pas d'erreur sur l'opérateur
        setNbParametersFromLine(instruction);  // si pas d'erreur sur l'opérateur alors pas d'erreur ici
        setParametersFromLine(line, instruction);

        if (!isError(instruction)) {  // s'il n'y a pas d'erreur sur les paramètres
            setOperateurOPcodeOrFunc(instruction);  // si pas d'erreur sur l'opérateur alors pas d'erreur ici
            setParametersOrderFromLine(instruction);  // si pas d'erreur sur l'opérateur alors pas d'erreur ici
        }
    }
}

void setOperateurFromLine(char *line, Instruction *instruction) {
    char operateur[8];  // stock l'adresse de début de l'opétateur
    char *tempOP = operateur;
    char *tempLine = line;

    while (*tempLine != ' ' && *tempLine != '\n') { // tant qu'il n'y a pas d'espace
        *tempOP = *tempLine;
        tempOP++;
        tempLine++;
    }
    *tempOP = '\0';

    toUpperCase(operateur);
    setOperateur(instruction, operateur);

    // return;
}

void setOperateurFormat(Instruction *instruction) {
    FILE *file = fopen("data//operateursFormat.txt", "r");
    int format = -1;

    while (!feof(file) && format == -1) {
        char line[15];
        char mot[8];
        int temp;

        char* checkError = fgets(line, 15, file);

        if (checkError == NULL) {
            continue;
        }

        sscanf(line, "%s %d", mot, &temp);

        if (strcmp(instruction->operateur, mot) == 0) {
            format = temp;
        }
    }

    fclose(file);

    if (format == -1) {  // si l'opérateur n'existe pas on transforme l'instruction en NOP
        setNOP(instruction);
        setError(instruction, BAD_OPERATEUR);
    } else {
        setFormat(instruction, format);
    }
}

void setNbParametersFromLine(Instruction *instruction) {
    FILE *file = fopen("data/operateursNbParameters.txt", "r");
    int nbParameters = -1;

    while (!feof(file) && nbParameters == -1) {
        char line[15];
        char mot[8];
        int temp;

        fgets(line, 15, file);
        sscanf(line, "%s %d", mot, &temp);

        if (strcmp(instruction->operateur, mot) == 0) {
            nbParameters = temp;
        }
    }

    fclose(file);
    setNbParameters(instruction, nbParameters);
}

void setParametersFromLine(char *line, Instruction *instruction) {
    char formatInput[20];
    int format = instruction->format;

    if (format == FORMAT_1) {
            copyStrings(FORMAT_1_INPUT, formatInput);
    } else if (FORMAT_2 <= format && format <= FORMAT_3) {
            copyStrings(FORMAT_2_INPUT, formatInput);
    } else if (format == FORMAT_4) {
            copyStrings(FORMAT_3_INPUT, formatInput);
    } else if (FORMAT_5 <= format && format <= FORMAT_6) {
            copyStrings(FORMAT_4_INPUT, formatInput);
    } else if (FORMAT_7 <= format && format <= FORMAT_8) {
            copyStrings(FORMAT_5_INPUT, formatInput);
    }else if (format == FORMAT_9) {
            copyStrings(FORMAT_6_INPUT, formatInput);
    } else if (format == FORMAT_10) {
            copyStrings(FORMAT_7_INPUT, formatInput);
    } else if (format == FORMAT_11) {
            copyStrings(FORMAT_8_INPUT, formatInput);
    } else if (format == FORMAT_12) {
            copyStrings(FORMAT_9_INPUT, formatInput);
    } else if (format == FORMAT_13){
            copyStrings(FORMAT_10_INPUT, formatInput);
    }

    char temp[8];
    int parameters[4];
    /*
    Dans les types I, J, et R les instructions recoivent au maximum 3 paramètres
    Dans le type R, le code binaire contient 4 paramètres : rd, rs, rt et sa
    Mais un des 4 sera nul (le paramètre dépend de l'instruction)
    On ne donne donc pas de valeur à parametre[3] qui sera forcément nul
    */

    int nbParameters = sscanf(line, formatInput, temp, &parameters[0], &parameters[1], &parameters[2]);
    
    // TODO: faire une fonction void checkRegisterExistence(instruction, parametre) qui set une erreur si le registre n'existe pas (si besoin)

    if (instruction->nbParameters != nbParameters -1) { // si on récupère un mauvais nombre de paramètres
        setNOP(instruction);
        setError(instruction, BAD_NBPARAMETERS);
    }else {
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

void setOperateurOPcodeOrFunc(Instruction *instruction) {
    FILE *file = fopen("data/operateursOPcodeFunc.txt", "r");
    int OPcodeOrFunc = -1;
    char mot[8];

    while (!feof(file) && OPcodeOrFunc == -1) {
        char line[15];
        int temp;

        char * checkError = fgets(line, 15, file);

        if (checkError == NULL) {
            continue;
        }

        sscanf(line, "%s %d", mot, &temp);

        if (strcmp(instruction->operateur, mot) == 0) {
            OPcodeOrFunc = temp;
        }
        
    }

    fclose(file);
    setOPcodeOrFunc(instruction, OPcodeOrFunc);
}

void setParametersOrderFromLine(Instruction *instruction) {
    char formatOutput[15];
    int parametersOrder[4];
    int format = instruction->format;

    // if (format == 1) {
    //     copyStrings(FORMAT_1_OUTPUT, formatOutput);
    // } else if (format == 2) {
    //     copyStrings(FORMAT_2_OUTPUT, formatOutput);
    // } else if (format == 3) {
    //     copyStrings(FORMAT_3_OUTPUT, formatOutput);
    // } else if (format == 4) {
    //     copyStrings(FORMAT_4_OUTPUT, formatOutput);
    // } else if (format == 5) {
    //     copyStrings(FORMAT_5_OUTPUT, formatOutput);
    // } else if (format == 6) {
    //     copyStrings(FORMAT_6_OUTPUT, formatOutput);
    // } else if (format == 7) {
    //     copyStrings(FORMAT_7_OUTPUT, formatOutput);
    // } else if (format == 8) {
    //     copyStrings(FORMAT_8_OUTPUT, formatOutput);
    // } else if (format == 9) {
    //     copyStrings(FORMAT_9_OUTPUT, formatOutput);
    // } else if (format == 10) {
    //     copyStrings(FORMAT_10_OUTPUT, formatOutput);
    // } else if (format == 11) {
    //     copyStrings(FORMAT_11_OUTPUT, formatOutput);
    // } else if (format == 12) {
    //     copyStrings(FORMAT_12_OUTPUT, formatOutput);
    // } else if (format == 13) {
    //     copyStrings(FORMAT_13_OUTPUT, formatOutput);
    // }

    switch (instruction->format) {
        case FORMAT_1:
            copyStrings(FORMAT_1_OUTPUT, formatOutput);
            break;
        case FORMAT_2:
            copyStrings(FORMAT_2_OUTPUT, formatOutput);
            break;
        case FORMAT_3:
            copyStrings(FORMAT_3_OUTPUT, formatOutput);
            break;
        case FORMAT_4:
            copyStrings(FORMAT_4_OUTPUT, formatOutput);
            break;
        case FORMAT_5:
            copyStrings(FORMAT_5_OUTPUT, formatOutput);
            break;
        case FORMAT_6:
            copyStrings(FORMAT_6_OUTPUT, formatOutput);
            break;
        case FORMAT_7:
            copyStrings(FORMAT_7_OUTPUT, formatOutput);
            break;
        case FORMAT_8:
            copyStrings(FORMAT_8_OUTPUT, formatOutput);
            break;
        case FORMAT_9:
            copyStrings(FORMAT_9_OUTPUT, formatOutput);
            break;
        case FORMAT_10:
            copyStrings(FORMAT_10_OUTPUT, formatOutput);
            break;
        case FORMAT_11:
            copyStrings(FORMAT_11_OUTPUT, formatOutput);
            break;
        case FORMAT_12:
            copyStrings(FORMAT_12_OUTPUT, formatOutput);
            break;
        case FORMAT_13:
            copyStrings(FORMAT_13_OUTPUT, formatOutput);
            break;
    }

    if (instruction->format == FORMAT_1) {
        sscanf(formatOutput, "%d", &parametersOrder[0]);
    } else if (FORMAT_2 <= instruction->format && instruction->format <= FORMAT_6) {
        sscanf(formatOutput, "%d %d %d", &parametersOrder[0], &parametersOrder[1], &parametersOrder[2]);
    } else {
        sscanf(formatOutput, "%d %d %d %d", &parametersOrder[0], &parametersOrder[1], &parametersOrder[2], &parametersOrder[3]);
    }

    setParametersOrder(instruction, parametersOrder);
}

void checkRegisterExistence(Instruction *instruction, int parameter) {
    if (parameter < 0 || 31 <= parameter) {
        setError(instruction, BAD_REGISTER);
    }
}