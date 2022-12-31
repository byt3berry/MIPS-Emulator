#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "read.h"
#include "analyse.h"
#include "utils.h"
#include "constantes.h"
#include "registers.h"


// TODO : mode interactif à finir
void readInteractif() {
    Instruction *instructionsToAssemble[LINES_NUMBER_MAX] = {0};
    Instruction *instructionsToExecute[LINES_NUMBER_MAX] = {0};
    int assembled[LINES_NUMBER_MAX] = {0};

    int index = 0;
    int isEnd = 0;

    while (!isEnd) {
        getAllInstructions(NULL, instructionsToAssemble, index);
        assemble(NULL, instructionsToAssemble, assembled, index);

        disassemble(assembled, instructionsToExecute, index);
        execute(instructionsToExecute, index);

        char temp[50] = {0};
        if (*fgets(temp, 50, stdin) != '\n') {
            isEnd = 1;
        }
    }

    freeAll(instructionsToAssemble);
    freeAll(instructionsToExecute);
}

void readAuto(FILE *progAsembleur, FILE *fichierAssemble, FILE *fichierFinal) {
    Instruction *instructionsToAssemble[LINES_NUMBER_MAX] = {0};
    Instruction *instructionsToExecute[LINES_NUMBER_MAX] = {0};
    int assembled[LINES_NUMBER_MAX] = {0};

    getAllInstructions(progAsembleur, instructionsToAssemble, 0);
    assemble(fichierAssemble, instructionsToAssemble, assembled, -1);

    disassemble(assembled, instructionsToExecute, -1);
//    execute(instructionsToExecute, -1);
//    showRegistersStates();
//    writeFinalStateRegisters(fichierFinal);
    freeAll(instructionsToAssemble);
    freeAll(instructionsToExecute);
}

// TODO : mode pas à pas à finir
void readPas(FILE *progAsembleur) {
    Instruction *instructionsToAssemble[LINES_NUMBER_MAX] = {0};
    Instruction *instructionsToExecute[LINES_NUMBER_MAX] = {0};
    int assembled[LINES_NUMBER_MAX] = {0};
    getAllInstructions(progAsembleur, instructionsToAssemble, 0);

    int index = 0;
    int isEnd = 0;

    while (!isEnd) {
        assemble(NULL, instructionsToAssemble, assembled, index);

        disassemble(assembled, instructionsToExecute, index);
        execute(instructionsToExecute, index);

        char temp[50] = {0};
        char *check = fgets(temp, 1, stdin);  // TODO: faire un truc pour passer à l'instruction suivante
        if (*check != '\n') {
            isEnd = 1;
        }
    }
}

// TODO : A refractoriser
int getAllInstructions(FILE *file, Instruction *instructions[LINES_NUMBER_MAX], int index) {
    if (file == NULL) {
        Instruction *instruction = (Instruction *) malloc(sizeof(Instruction));
        char line[LINES_LENGTHS_MAX];
        char *checkError;

        checkError = fgets(line, LINES_LENGTHS_MAX - 1, stdin);

        replaceChar(line, '\n', '\0');
        replaceChar(line, '\r', '\0');
        replaceChar(line, '#', '\0');

        /* Si la ligne est nulle est ou un commentaire */
        if (checkError == NULL || checkError[0] == '\0') {
            return -1;
        }

        analyseLine(line, instruction);  // TODO: detecte pas quand c'est pas un opérateur valide
        instructions[index] = instruction;
    } else {
        while (!feof(file)) {
            Instruction *instruction = (Instruction *) malloc(sizeof(Instruction));
            setError(instruction, 0);
//            printf("error0 : %d\n", instruction->error);
            char line[LINES_LENGTHS_MAX];
            char *checkError = fgets(line, LINES_LENGTHS_MAX - 1, file);


            replaceChar(line, '\n', '\0');
            replaceChar(line, '\r', '\0');
            replaceChar(line, '#', '\0');

//            printf("%s\n", line);

            /* Si la ligne est nulle est ou un commentaire */
            if (checkError == NULL || checkError[0] == '\0') {
//                printf("skip : %s\n", line);
                index--;
            } else {
//                printf("accepted : %s\n", line);
                analyseLine(line, instruction);  // TODO: detecte pas quand c'est pas un opérateur valide
//                printInfos(instruction);
//                printf("\n");
                instructions[index] = instruction;
            }

            index++;
        }
    }

    return 0;
}

void assemble(FILE *fichierAssemble, Instruction *instructions[LINES_NUMBER_MAX], int *assembled, int index) {
    for (int i = 0; i < LINES_NUMBER_MAX; i++) {
        if (index != -1 && i != index) {
            continue;
        }

        if (instructions[i] == 0) {
            assembled[i] = -1;
            continue;
        }

        int instructionAssemble;
//        printInfos(instructions[i]);
        getOutput(instructions[i], &instructionAssemble);

        if (fichierAssemble == NULL) {
            printf("hex : %08X\n", instructionAssemble);
        } else {
            fprintf(fichierAssemble, "%08X\n", instructionAssemble);
        }

        if (assembled != NULL) {
            assembled[i] = instructionAssemble;
        }

        printf("%08X\n", instructionAssemble);
    }
    printf("\n");
}

void disassemble(int *assembled, Instruction *instructions[LINES_NUMBER_MAX], int index) {
    for (int i = 0; i < LINES_NUMBER_MAX && assembled[i] != -1; i++) {
        if (index != -1 && i != index) {
            continue;
        }

        Instruction *instruction = (Instruction *) malloc(sizeof(Instruction));
        setError(instruction, 0);
        printf("%08X\n", assembled[i]);
        analyseHex(assembled[i], instruction);
        printInfos(instruction);
        printf("\n");

        instructions[i] = instruction;
    }
}

void execute(Instruction *instructions[LINES_NUMBER_MAX], int index) {
    int PCvalue;
    getValueFromRegister(PC, &PCvalue);
    PCvalue /= 4;

    while (PCvalue < LINES_NUMBER_MAX && instructions[PCvalue] != 0) {
        if (index != -1 && PCvalue != index) {
            continue;
        }

        executeInstruction(instructions[PCvalue]);
        incrementPC(1);
        getValueFromRegister(PC, &PCvalue);
        PCvalue /= 4;

//        break;
    }
}

void freeAll(Instruction *instructions[LINES_NUMBER_MAX]) {
    for (int i = 0; i < LINES_NUMBER_MAX && instructions[i] != 0; i++) {
        free(instructions[i]);
    }
}
