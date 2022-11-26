#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _FONCTION_FILES_C_
#define _FONCTION_FILES_C_

#include "../include/fonctionFiles.h"
#include "../include/utils.h"
#include "constantes.c"

#endif

// TODO: stocker les formats d'entrée et de sortie des instructions dans la structure Instruction

int readLine(FILE *file, int size, char *line, Instruction *instruction, char *instructionHex) {
    fgets(line, size, file);

    /* Checking if the line is a comment or empty. */
    if (line[0] == '#' || line[0] == '\n') {
        return 0;
    }

    delLineFeed(line);
    analyseLine(line, instruction);
    getOutput(instruction, instructionHex);

    return 1;
}

void readAuto(FILE *progAsembleur, FILE *fichierAssemble, FILE *fichierFinal, int registres[32]) {
    while (!feof(progAsembleur)) {
        Instruction *instruction = (Instruction *) malloc(sizeof(Instruction));

        char instructionHex[9], line[50];
        int resultat = readLine(progAsembleur, 50, line, instruction, instructionHex);

        if (!resultat) {
            continue;
        }

        free(instruction);

        fprintf(fichierAssemble, "%s\n", instructionHex);

        // break;
    }
}

void readPas(FILE *progAsembleur, int registres[32]) {
    while (!feof(progAsembleur)) {
        Instruction *instruction = (Instruction *) malloc(sizeof(Instruction));

        char instructionHex[9], line[50];
        int resultat = readLine(progAsembleur, 50, line, instruction, instructionHex);

        if (!resultat) {
            continue;
        }

        free(instruction);

        printf("%s\n", line);
        printf("%s\n", instructionHex);

        char temp;
        scanf("%c", &temp);

        // break;
    }
}

void analyseLine(char *line, Instruction *instruction) {
    // on récupère toutes les infos de l'instruction
    setOperateurFromLine(line, instruction);
    setOperateurFormat(instruction);
    setNbParametersFromLine(instruction);
    setParametersFromLine(line, instruction);
    setOperateurOPcodeOrFunc(instruction);
    setParametersOrderFromLine(instruction);
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
}

void setOperateurFormat(Instruction *instruction) {
    FILE *file = fopen("data//operateursFormat.txt", "r");
    int format = -1;
    // printf("%s,\n", instruction->operateur);


    while (!feof(file) && format == -1) {
        char line[15];
        char mot[8];
        int temp;

        fgets(line, 15, file);
        sscanf(line, "%s %d", mot, &temp);

        if (strcmp(instruction->operateur, mot) == 0) {
            format = temp;
        }
    }

    fclose(file);
    setFormat(instruction, format);
}

void setNbParametersFromLine(Instruction *instruction) {
    FILE *file = fopen("data/operateursNbParametres.txt", "r");
    int nbParametres = -1;

    while (!feof(file) && nbParametres == -1) {
        char line[15];
        char mot[8];
        int temp;

        fgets(line, 15, file);
        sscanf(line, "%s %d", mot, &temp);

        if (strcmp(instruction->operateur, mot) == 0) {
            nbParametres = temp;
        }
    }

    fclose(file);
    setNbParametres(instruction, nbParametres);
}

void setParametersFromLine(char *line, Instruction *instruction) {
    char formatInput[20];
    // int format = instruction->format;

    // if (format == FORMAT_1) {
    //         copyStrings(FORMAT_1_INPUT, formatInput);
    // } else if (FORMAT_2 <= format || format <= FORMAT_3) {
    //         copyStrings(FORMAT_2_INPUT, formatInput);
    // } else if (format == FORMAT_4) {
    //         copyStrings(FORMAT_3_INPUT, formatInput);
    // } else if (FORMAT_5 <= format || format <= FORMAT_6) {
    //         copyStrings(FORMAT_4_INPUT, formatInput);
    // } else if (FORMAT_7 <= format || format <= FORMAT_9) {
    //         copyStrings(FORMAT_5_INPUT, formatInput);
    // } else if (format == FORMAT_10) {
    //         copyStrings(FORMAT_6_INPUT, formatInput);
    // } else if (format == FORMAT_11) {
    //         copyStrings(FORMAT_7_INPUT, formatInput);
    // } else if (format == FORMAT_12) {
    //         copyStrings(FORMAT_8_INPUT, formatInput);
    // } else if (format == FORMAT_13){
    //         copyStrings(FORMAT_9_INPUT, formatInput);
    // }

    switch (instruction->format) {
        case FORMAT_1:
            copyStrings(FORMAT_1_INPUT, formatInput);
            break;
        case FORMAT_2:
        case FORMAT_3:
            copyStrings(FORMAT_2_INPUT, formatInput);
            break;
        case FORMAT_4:
            copyStrings(FORMAT_3_INPUT, formatInput);
            break;
        case FORMAT_5:
        case FORMAT_6:
            copyStrings(FORMAT_4_INPUT, formatInput);
            break;
        case FORMAT_7:
        case FORMAT_8:
            copyStrings(FORMAT_5_INPUT, formatInput);
            break;
        case FORMAT_9:
            copyStrings(FORMAT_6_INPUT, formatInput);
            break;
        case FORMAT_10:
            copyStrings(FORMAT_7_INPUT, formatInput);
            break;
        case FORMAT_11:
            copyStrings(FORMAT_8_INPUT, formatInput);
            break;
        case FORMAT_12:
            copyStrings(FORMAT_9_INPUT, formatInput);
            break;
        case FORMAT_13:
            copyStrings(FORMAT_10_INPUT, formatInput);
            break;
    }

    char temp[8];
    int parametres[4];
    sscanf(line, formatInput, temp, &parametres[0], &parametres[1], &parametres[2], &parametres[3]);
    setParametres(instruction, parametres);
}

void setOperateurOPcodeOrFunc(Instruction *instruction) {
    FILE *file = fopen("data/operateursOPcodeFunc.txt", "r");
    int OPcodeOrFunc;
    char mot[8];

    do {
        char line[20];

        fgets(line, 20, file);
        sscanf(line, "%s %d", mot, &OPcodeOrFunc);
    } while (!feof(file) && strcmp(instruction->operateur, mot) != 0);

    fclose(file);
    setOPcodeOrFunc(instruction, OPcodeOrFunc);
}

void setParametersOrderFromLine(Instruction *instruction) {
    char formatOutput[15];
    int parametresOrder[4];

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
        sscanf(formatOutput, "%d", &parametresOrder[0]);
    } else if (FORMAT_2 <= instruction->format && instruction->format <= FORMAT_6) {
        sscanf(formatOutput, "%d %d %d", &parametresOrder[0], &parametresOrder[1], &parametresOrder[2]);
    } else {
        sscanf(formatOutput, "%d %d %d %d", &parametresOrder[0], &parametresOrder[1], &parametresOrder[2], &parametresOrder[3]);
    }

    setParametresOrder(instruction, parametresOrder);
}
