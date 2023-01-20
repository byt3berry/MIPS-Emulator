// Projet MIPS 2022-2023
// Auteurs : Cocagne_Strainovic

#ifndef CONSTANTES_C_
#define CONSTANTES_C_


/* * * * * * * * * * *  */
/* INSTRUCTIONS FORMATS */

// Formats J
#define FORMAT_1  1
// Formats I
#define FORMAT_2  2
#define FORMAT_3  3
#define FORMAT_4  4
#define FORMAT_5  5
#define FORMAT_6  6
// Formats R
#define FORMAT_7  7
#define FORMAT_8  8
#define FORMAT_9  9
#define FORMAT_10 10
#define FORMAT_11 11
#define FORMAT_12 12

/* INSTRUCTIONS FORMATS */
/* * * * * * * * * * *  */


/* * * * * * * * * * * * * * */
/* * * * * * SIZES * * * * * */

#define OPCODE_FUNC_SIZE 6
#define I_IMMEDIATE_SIZE 16
#define J_TARGET_SIZE    26
#define REGISTER_SIZE    5
#define BINARY_CODE_SIZE 32

/* * * * * * SIZES * * * * * */
/* * * * * * * * * * * * * * */


/* * * * * *  * * * * * * */
/* * * * * ERRORS * * * * */

#define NO_ERROR         0
#define BAD_OPERATEUR    1
#define BAD_NBPARAMETERS 2
#define BAD_REGISTER     3
#define OVERFLOW_PARAM   4
#define BAD_ADDRESS      5
#define DIVISION_BY_ZERO 6
#define PAS_A_PAS        7

/* * * * * ERRORS * * * * */
/* * * * * *  * * * * * * */


/* * * * * * */
/* REGISTERS */
#define HI 32
#define LO 33
#define PC 34
/* REGISTERS */
/* * * * * * */

/*
 * On pourra stocker 300 adresses différentes dans la mémoire
 * La mémoire ne fait donc pas 4Go
 * Mais 300 adresses nous semble parfaitement sufissant pour notre utilisation
 */
#define MEMORY_SIZE 300
#define LINES_LENGTHS_MAX 300  // les lignes récupérées devront faire maximum 300 caractères
#define LINES_NUMBER_MAX 500  // le programme devra contenir maximum 500 instructions

#endif
