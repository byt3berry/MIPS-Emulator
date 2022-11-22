#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _FONCTION_FILES_C_
#define _FONCTION_FILES_C_
#include "../include/fonctionFiles.h"
#include "constantes.c"
#include "../include/utils.h"
#endif


// TODO: voir pour utiliser strcmp de string.h à la place de areStringsEqual

void readLine(FILE* file, char* line, int size) {
        fgets(line, size, file);
}

void read(FILE* file, int registres[32]) {
    while(!feof(file)) {
        //printf("ici\n");
        char line[50];
        readLine(file, line, 50);
        printf("%s\n", line);
        Instruction* instruction = (Instruction*) malloc(sizeof(Instruction));
        analyseLine(line, instruction);
        printInfos(instruction);
        printf("\n");

        //break;
    }
}

void analyseLine(char* line, Instruction* instruction) {
    // on récupère l'instruction
    setOperateurFromLine(line, instruction);
    setOperateurFormat(instruction);
    //setOperateurOPcodeOrFunc(instruction);
    //setParametersFromLine(line, instruction);
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
    int format = -1;
    
    while(!feof(file) && format == -1) {
        char line[15];
        char mot[8];
        char temp[2];

        fgets(line, 15, file);
        sscanf(line, "%s %s", mot, temp);

        if (areStringsEqual(instruction->operateur, mot)) {
            if (areStringsEqual(temp, "R\0")) {
                format = FORMAT_R;
            } else if (areStringsEqual(temp, "I\0")) {
                format = FORMAT_I;
            } else if (areStringsEqual(temp, "J\0")) {
                format = FORMAT_J;
            }
        }
    }

    fclose(file);
    setFormat(instruction, format);
}

void setParametersFromLine(char* line, Instruction* instruction) {
    switch (instruction->format) {
        case FORMAT_R:
            setParametersFromLineR(line, instruction);
            break;
        case FORMAT_I:
            setParametersFromLineI(line, instruction);
            break;
        case FORMAT_J:
            setParametersFromLineJ(line, instruction);
            break;
    }
}

void setParametersFromLineR(char* line, Instruction* instruction){
    char temp[8];
    int r1, r2, r3;

    sscanf(line, FORMAT_R_STR, temp, &r1, &r2, &r3);
    setParametres(instruction, r1);
    setParametres(instruction, r2);
    setParametres(instruction, r3);
}

void setParametersFromLineI(char* line, Instruction* instruction){
    char temp[8];
    int r1, r2, r3;

    sscanf(line, FORMAT_I_STR, temp, &r1, &r2, &r3);
    setParametres(instruction, r1);
    setParametres(instruction, r2);
    setParametres(instruction, r3);
}

void setParametersFromLineJ(char* line, Instruction* instruction){
    char temp[8];
    int r1;

    sscanf(line, FORMAT_J_STR, temp, &r1);
    setParametres(instruction, r1);
}

void setOperateurOPcodeOrFunc(Instruction* instruction) {
    FILE * file = fopen("../data/operateursOPcodeFunc2.txt", "r");
    char OPcodeOrFunc[7];
    char mot[8];

    while(!feof(file) && !areStringsEqual(instruction->operateur, mot)) {
        char line[20];

        fgets(line, 20, file);
        sscanf(line, "%s %s", mot, OPcodeOrFunc);
    } 

    fclose(file);
    setOPcodeOrFunc(instruction, OPcodeOrFunc);
}
