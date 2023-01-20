// Projet MIPS 2022-2023
// Auteurs : Cocagne_Strainovic

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "analyse.h"
#include "utils.h"
#include "constantes.h"


int analyseLine(char *line, Instruction *instruction) {
    // on récupère toutes les infos de l'instruction
    setLine(instruction, line);
    line = formatLine(line);
    setOperateurFromLine(line, instruction);

    FILE *file = fopen("data//data.txt", "r");
    char operateur[10], format[3], OPcodeOrFunc[10], nbParameters[10], inputFormat[20], parametersOrder[15], executeFunction[5], executeParameters[15];
    int isFound = 0;

    // On cherche la bonne ligne sur laquelle récupérer les infos sur l'opérateur
    while (!feof(file) && !isFound) {
        char lineTested[200];
        char *checkError = fgets(lineTested, 200, file);
        replaceChar(lineTested, '\n', '\0');

        if (checkError[0] == '#' || checkError[0] == '\0') {
            continue;
        }

        sscanf(lineTested, "%s ; %s ; %s ; %s ; %s ; %s ; %s ; %s ;", operateur, format, OPcodeOrFunc, nbParameters, inputFormat, parametersOrder, executeFunction, executeParameters);

        if (strcmp(getOperateur(instruction), operateur) == 0) {
            isFound = 1;
        }
    }
    fclose(file);

    if (isFound == 0) {  // si on ne trouve pas l'opérateur dans la liste, pas besoin de continuer
        setError(instruction, BAD_OPERATEUR);
        return getError(instruction);
    }

    /*
     * Dans le fichier, on a remplacé les espaces par des +
     * Car avec sscanf, la lecture s'arrête à chaque espace
     * Donc il faut supprimer tous ces +
     */
    replaceChar(inputFormat, '+', ' ');
    replaceChar(parametersOrder, '+', ' ');
    replaceChar(executeParameters, '+', ' ');

    setOperateurFormat(format, instruction);

    if (!getError(instruction)) { // s'il n'y a pas d'erreur sur l'opérateur
        setOperateurOPcodeOrFunc(OPcodeOrFunc, instruction);
        setNbParametersFromLine(nbParameters, instruction);
        setParametersFromLine(line, inputFormat, instruction);
        if (!getError(instruction)) {  // s'il n'y a pas d'erreur sur les paramètres
            setParametersOrderFromLine(parametersOrder, instruction);
            setExecuteFunctionFromLine(executeFunction, instruction);
            setExecuteParametersFromLine(executeParameters, instruction);
        }
    }

    return getError(instruction);
}

char *formatLine(char *line) {
    // Pour simplifier la lecture, on remplace les caractères gênants par des espaces
    replaceChar(line, '(', ' ');
    replaceChar(line, ')', ' ');
    replaceChar(line, ',', ' ');

    // On supprime aussi tous les espaces en début de ligne
    while (*line == ' ') {
        line++;
    }

    return line;
}

/**
 * It takes a line of code, and extracts the operator from it
 * 
 * @param line the line of the file we're reading
 * @param instruction the instruction to set the operator to
 */
void setOperateurFromLine(char *line, Instruction *instruction) {
    char operateur[8];  // stock l'adresse de début de l'opétateur
    char *tempOP = operateur;
    char *tempLine = line;
    int index = 0;

    while (*tempLine != '\0' && *tempLine != ' ' && *tempLine != '$') { // tant qu'il n'y a pas d'espace, de retour à la ligne ou de dollars
        *tempOP = *tempLine;
        tempOP++;
        tempLine++;
        index++;
    }
    *tempOP = '\0';

    addChar(line, index, ' ');
    toUpperCase(operateur);
    setOperateur(instruction, operateur);
}

void setOperateurFormat(char *formatChar, Instruction *instruction) {
    int formatInt = (int) strtol(formatChar, NULL, 10);
    setFormat(instruction, formatInt);
}

void setOperateurOPcodeOrFunc(char *OPcodeOrFuncChar, Instruction *instruction) {
    int OPcodeOrFuncInt = (int) strtol(OPcodeOrFuncChar, NULL, 10);
    setOPcodeOrFunc(instruction, OPcodeOrFuncInt);
}

void setNbParametersFromLine(char *nbParametersChar, Instruction *instruction) {
    int nbParametersInt = (int) strtol(nbParametersChar, NULL, 10);
    setNbParameters(instruction, nbParametersInt);
}

/**
 * It takes a line of code, an input format, and an instruction, and sets the parameters of the
 * instruction based on the line of code and the input format
 * 
 * @param line the line of the instruction
 * @param inputFormat the format of the line to be read
 * @param instruction the instruction to set the parameters of
 */
void setParametersFromLine(char *line, char *inputFormat, Instruction *instruction) {
    /*
    Dans les types I, J, et R les instructions recoivent au maximum 3 paramètres
    Dans le type R, le code binaire contient 4 paramètres : rd, rs, rt et sa
    Mais un des 4 sera nul (le paramètre nul dépend de l'instruction)
    On ne donne donc pas de valeur à parameters[4] qui sera forcément nul
    Mais parameters[4] sera utile plus tard donc on le garde pour éviter une condition en plus
    */

    char strParameters[4][100] = {0};
    int intParameters[4] = {0};
    int nbParameters = sscanf(line, inputFormat, strParameters[0], strParameters[1], strParameters[2], strParameters[3]);

    if (nbParameters - 1 != getNbParameters(instruction)) { // si on récupère un mauvais nombre de paramètres
        setError(instruction, BAD_NBPARAMETERS);
    } else {
        int format = getFormat(instruction);

        if (format == FORMAT_1) {
            // si le paramètre 1 est un immédiat
            formatParameter(strParameters[1], &intParameters[0]);
        } else if (format == FORMAT_2 || format == FORMAT_3 || format == FORMAT_8 || format == FORMAT_9) {
            // si les paramètres 1 et 2 sont des registres et 3 est un immédiat
            checkRegisterExistence(instruction, strParameters[1], &intParameters[0]);
            checkRegisterExistence(instruction, strParameters[2], &intParameters[1]);
            formatParameter(strParameters[3], &intParameters[2]);
        } else if (format == FORMAT_4) {
            // si les paramètres 1 et 3 sont des registres et 2 est un immédiat
            checkRegisterExistence(instruction, strParameters[1], &intParameters[0]);
            formatParameter(strParameters[2], &intParameters[1]);
            checkRegisterExistence(instruction, strParameters[3], &intParameters[2]);
        } else if (format == FORMAT_5 || format == FORMAT_6) {
            // si le paramètre 1 est un registre et 2 est un immédiat
            checkRegisterExistence(instruction, strParameters[1], &intParameters[0]);
            formatParameter(strParameters[2], &intParameters[1]);
        } else if (format == FORMAT_7) {
            // si les paramètres 1, 2 et 3 sont des registres
            checkRegisterExistence(instruction, strParameters[1], &intParameters[0]);
            checkRegisterExistence(instruction, strParameters[2], &intParameters[1]);
            checkRegisterExistence(instruction, strParameters[3], &intParameters[2]);
        } else if (format == FORMAT_10) {
            // si les paramètres 1 et 2 sont des registres
            checkRegisterExistence(instruction, strParameters[1], &intParameters[0]);
            checkRegisterExistence(instruction, strParameters[2], &intParameters[1]);
        } else if (format == FORMAT_11 || format == FORMAT_12) {
            // si le paramètre 1 est un registre
            checkRegisterExistence(instruction, strParameters[1], &intParameters[0]);
        }
    }

    if (!getError(instruction)) {
        setParameters(instruction, intParameters);
    }
}

void setParametersOrderFromLine(char *parametersOrderChar, Instruction *instruction) {
    int parametersOrderInt[4];
    char *ptr = parametersOrderChar;

    for (int i = 0; i < 4; i++) {
        parametersOrderInt[i] = (int) strtol(ptr, &ptr, 10);
    }

    setParametersOrder(instruction, parametersOrderInt);
}

void setExecuteFunctionFromLine(char *executeFunctionChar, Instruction *instruction) {
    int executeFunctionInt = (int) strtol(executeFunctionChar, NULL, 10);
    setExecuteFunction(instruction, executeFunctionInt);
}

void setExecuteParametersFromLine(char *executeParametersChar, Instruction *instruction) {
    int executeParametersInt[5];
    char *ptr = executeParametersChar;

    for (int i = 0; i < 5; i++) {
        executeParametersInt[i] = (int) strtol(ptr, &ptr, 10);
    }

    setExecuteParameters(instruction, executeParametersInt);
}

void formatParameter(char *strParameter, int *intParameter) {
    int base;
    int offset = 0; // utile seulement pour convertir depuis binaire
    if (strParameter[0] == '0' && strParameter[1] == 'x') {  // récuperation d'un nomber écrit en hexadécimal
        base = 16;
    } else if (strParameter[0] == '0' && strParameter[1] == 'b') {  // récuperation d'un nomber écrit en binaire
        base = 2;
        offset = 2;
    } else {  // récuperation d'un nomber écrit en décimal
        base = 10;
    }
    *intParameter = (int) strtol(strParameter + offset, NULL, base);
}

void checkRegisterExistence(Instruction *instruction, char *strParameter, int *intParameter) {
    toLowerCase(strParameter);

    if ('a' <= strParameter[0] && strParameter[0] <= 'z') {
        *intParameter = findRegisterNumber(strParameter);
    } else {
        *intParameter = (int) strtol(strParameter, NULL, 10);
    }

    if (*intParameter < 0 || 31 < *intParameter) {
        setError(instruction, BAD_REGISTER);
    }
}

int findRegisterNumber(char *mnemonic) {
    FILE *file = fopen("data/registers.txt", "r");
    int output = -1;
    int nbLine = 0;

    while (!feof(file) && output == -1) {
        char line[10];
        char *checkError = fgets(line, 10, file);
        replaceChar(line, '\n', '\0');

        if (checkError[0] == '#' || checkError[0] == '\n') {
            continue;
        }

        if (strcmp(mnemonic, line) == 0) {
            output = nbLine;
        }

        nbLine++;
    }

    return output;
}
