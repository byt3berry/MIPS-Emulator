#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _FONCTION_FILES_C_
#define _FONCTION_FILES_C_

#include "../include/fonctionFiles.h"
#include "constantes.c"
#include "../include/utils.h"

#endif

void readLine(FILE *file, char *line, int size) {
    fgets(line, size, file);
}

void read(FILE *progAsembleur, FILE *fichierAssemble, int registres[32]) {
    while (!feof(progAsembleur)) {
        // printf("ici\n");
        char line[50];
        readLine(progAsembleur, line, 50);
        Instruction *instruction = (Instruction *) malloc(sizeof(Instruction));
        analyseLine(line, instruction);
//        printInfos(instruction);

        char instructionBin[33], instructionHex[9];
        setOutputFull(instruction, instructionBin);
        binToHex(instructionBin, instructionHex);

        write(fichierAssemble, instructionHex);
//        printf("%s\n", outputBin);
//        printf("%s\n", outputHex);

//        printf("\n");

        free(instruction);

        // break;
    }
}

void read(FILE *progAsembleur, int registres[32]) {
    while (!feof(progAsembleur)) {
        // printf("ici\n");
        char line[50];
        readLine(progAsembleur, line, 50);
        Instruction *instruction = (Instruction *) malloc(sizeof(Instruction));
        analyseLine(line, instruction);
        //printInfos(instruction);

        char instructionBin[33], instructionHex[9];
        setOutputFull(instruction, instructionBin);
        binToHex(instructionBin, instructionHex);
        printf("%s\n", line);
        printf("%s\n", instructionHex);

//        printf("%s\n", outputBin);
//        printf("%s\n", outputHex);

        free(instruction);

        char *temp;
        scanf("%s\n", temp);

        // break;
    }
}

void write(FILE *file, char *instructionHex) {
    fprintf(file, "%s\n", instructionHex);
}

void analyseLine(char *line, Instruction *instruction) {
    // on récupère l'instruction
    setOperateurFromLine(line, instruction);
    setOperateurFormat(instruction);
    setNbParametersFromLine(instruction);
    setParametersFromLine(line, instruction);
    setOperateurOPcodeOrFunc(instruction);
    setParametersOrderFromLine(instruction);
}

void setNbParametersFromLine(Instruction *instruction) {
    FILE *file = fopen("../data/operateursNbParametres.txt", "r");
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
        case FORMAT_9:
            copyStrings(FORMAT_5_INPUT, formatInput);
            break;
        case FORMAT_10:
            copyStrings(FORMAT_6_INPUT, formatInput);
            break;
        case FORMAT_11:
            copyStrings(FORMAT_7_INPUT, formatInput);
            break;
        case FORMAT_12:
            copyStrings(FORMAT_8_INPUT, formatInput);
            break;
        case FORMAT_13:
            copyStrings(FORMAT_9_INPUT, formatInput);
            break;
    }

    char temp[8];
    int parametres[4];
    sscanf(line, formatInput, temp, &parametres[0], &parametres[1], &parametres[2], &parametres[3]);
    setParametres(instruction, parametres);
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

    switch (instruction->format) {
        case FORMAT_1:
            sscanf(formatOutput, "%d", &parametresOrder[0]);
            break;
        case FORMAT_2:
        case FORMAT_3:
        case FORMAT_4:
        case FORMAT_5:
        case FORMAT_6:
            sscanf(formatOutput, "%d %d %d", &parametresOrder[0], &parametresOrder[1], &parametresOrder[2]);
            break;
        default:
            sscanf(formatOutput, "%d %d %d %d", &parametresOrder[0], &parametresOrder[1], &parametresOrder[2], &parametresOrder[3]);
            break;
    }

    setParametresOrder(instruction, parametresOrder);
}

void getFormatStr(char *output, Instruction *instruction) {
    FILE *file = fopen("../data/instructionsFormatStr.txt", "r");

    char operateur[30];
    copyStrings(instruction->operateur, operateur);
    int isFound = 0;

    while (!feof(file) && !isFound) {
        char operateurFound[10], temp[20], line[30];

        fgets(line, 30, file);
        sscanf(line, "%s %s", operateurFound, temp);
        printf("temp : %s\n", temp);

        if (!strcmp(operateur, operateurFound)) {
            copyStrings(line, output);
            isFound = 1;
        }
    }

    fclose(file);
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

    setOperateur(instruction, operateur);
}

void setOperateurFormat(Instruction *instruction) {
    FILE *file = fopen("../data/operateursFormat2.txt", "r");
    int formatInput = -1;

    while (!feof(file) && formatInput == -1) {
        char line[15];
        char mot[8];
        int temp;

        fgets(line, 15, file);
        sscanf(line, "%s %d", mot, &temp);

        if (!strcmp(instruction->operateur, mot)) {
            formatInput = temp;
        }
    }

    fclose(file);
    setFormat(instruction, formatInput);
}

void setOperateurOPcodeOrFunc(Instruction *instruction) {
    FILE *file = fopen("../data/operateursOPcodeFunc3.txt", "r");
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
