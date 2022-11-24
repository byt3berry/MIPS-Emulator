#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _FONCTION_FILES_C_
#define _FONCTION_FILES_C_
#include "../include/fonctionFiles.h"
#include "constantes.c"
#include "../include/utils.h"
#endif

void readLine(FILE* file, char* line, int size) {
        fgets(line, size, file);
}

void read(FILE* file, int registres[32]) {
    while(!feof(file)) {
        // printf("ici\n");
        char line[50];
        readLine(file, line, 50);
        printf("%s\n", line);
        Instruction* instruction = (Instruction*) malloc(sizeof(Instruction));
        analyseLine(line, instruction);
        printInfos(instruction);
        printf("\n");

        free(instruction);

        //break;
    }
}

void analyseLine(char* line, Instruction* instruction) {
    // on récupère l'instruction
    setOperateurFromLine(line, instruction);
    setOperateurFormat(instruction);
    // setNbParametersFromLine(instruction);
    // setParametersFromLine(line, instruction);
    // setOperateurOPcodeOrFunc(instruction);
}

void setNbParametersFromLine(Instruction* instruction) {
    FILE * file = fopen("../data/operateursNbParametres.txt", "r");
    int nbParametres = -1;


    while(!feof(file) && nbParametres == -1) {
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

void setParametersFromLine(char* line, Instruction* instruction) {
    char formatInput[20];

    switch(instruction->format) {
        case FORMAT_1:
            copyStrings(FORMAT_1_INPUT, formatInput);
            break;
        case FORMAT_2:
            copyStrings(FORMAT_2_INPUT, formatInput);
            break;
        case FORMAT_3:
            copyStrings(FORMAT_3_INPUT, formatInput);
            break;
        case FORMAT_4:
            copyStrings(FORMAT_4_INPUT, formatInput);
            break;
        case FORMAT_5:
            copyStrings(FORMAT_5_INPUT, formatInput);
            break;
        case FORMAT_6:
            copyStrings(FORMAT_6_INPUT, formatInput);
            break;
        case FORMAT_7:
            copyStrings(FORMAT_7_INPUT, formatInput);
            break;
        case FORMAT_9:
            copyStrings(FORMAT_9_INPUT, formatInput);
            break;
    }

    printf("%s\n", formatInput);

    char temp[8];
    int parametres[4];
    sscanf(line, formatInput, temp, &parametres[0], &parametres[1], &parametres[2], &parametres[3]);
    setParametres(instruction, parametres);

void setParametresOrder(Instruction *instruction) {
    char formatOutput[15];

    switch (instruction->format) {
        case FORMAT_1:
        case FORMAT_2:
        case FORMAT_3:
        case FORMAT_4:
        case FORMAT_5:
        case FORMAT_6:
        case FORMAT_7:
        case FORMAT_8:
        case FORMAT_9:

    }
}

void getFormatStr(char* output, Instruction* instruction) {
    FILE * file = fopen("../data/instructionsFormatStr.txt", "r");

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

void setOperateurFromLine(char* line, Instruction* instruction){
    char operateur[8];  // stock l'adresse de début de l'opétateur
    char* temp = operateur;
    while (*line != ' ' && *line != '\n') { // tant qu'il n'y a pas d'espace
        *temp = *line;
        temp++;
        line++;
    }
    *temp = '\0';

    setOperateur(instruction, operateur);
}

void setOperateurFormat(Instruction* instruction) {
    FILE * file = fopen("../data/operateursFormat.txt", "r");
    int formatInput = -1;
    
    while(!feof(file) && formatInput == -1) {
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

void setOperateurOPcodeOrFunc(Instruction* instruction) {
    FILE * file = fopen("../data/operateursOPcodeFunc2.txt", "r");
    char OPcodeOrFunc[7];
    char mot[8];


    while(!feof(file) && !!strcmp(instruction->operateur, mot)) {
        char line[20];

        fgets(line, 20, file);
        sscanf(line, "%s %s", mot, OPcodeOrFunc);
    }

    fclose(file);
    setOPcodeOrFunc(instruction, OPcodeOrFunc);
}
