#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _ANALYSE_H_
#define _ANALYSE_H_

#include "../include/analyse.h"

#endif

#include "../include/utils.h"
#include "constantes.c"


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

        replaceChar(line, '\n', '\0');


        /* 
         * On modifie la linge pour qu'elle soit juste une liste de paramètres
         * ADDI $5, $0, 5 -> ADDI $5 $0 5
        */
        replaceChar(line, '(', ' ');
        replaceChar(line, ')', ' ');
        replaceChar(line, ',', ' ');

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
    On ne donne donc pas de valeur à parameters[3] qui sera forcément nul
    */

    char temp[8];
    int parameters[4];
    int nbParameters = sscanf(line, inputFormat, temp, &parameters[0], &parameters[1], &parameters[2]);
    
    if (instruction->nbParameters != nbParameters -1) { // si on récupère un mauvais nombre de paramètres
        setNOP(instruction);
        setError(instruction, BAD_NBPARAMETERS);
    } else {
        int format = instruction->format;

        if (format == 5 || format == 6 || format == 11 || format == 12) {
            // si le paramètre 1 est un registre
            checkRegisterExistence(instruction, parameters[0]);
        } else if (format == 2 || format == 3 || format == 9 || format == 10) {
            // si les paramètres 1 et 2 sont des registres
            checkRegisterExistence(instruction, parameters[0]);
            checkRegisterExistence(instruction, parameters[1]);
        } else if (format == 4) {
            // si les paramètres 1 et 3 sont des registres
            checkRegisterExistence(instruction, parameters[0]);
            checkRegisterExistence(instruction, parameters[2]);
        }
    }

    if (!isError(instruction)) {
        setParameters(instruction, parameters);
    }
}

void setParametersOrderFromLine(char *parametersOrderChar, Instruction *instruction) {
    int parametersOrderInt[4];
    sscanf(parametersOrderChar, "%d %d %d %d", &parametersOrderInt[0], &parametersOrderInt[1], &parametersOrderInt[2], &parametersOrderInt[3]);
    setParametersOrder(instruction, parametersOrderInt);
}

void checkRegisterExistence(Instruction *instruction, int parameter) {
    if (parameter < 0 || 31 < parameter) {
        setError(instruction, BAD_REGISTER);
    }
}