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
#define FORMAT_13 13

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
#define OVERFLOW         4

/* * * * * ERRORS * * * * */
/* * * * * *  * * * * * * */


/* * * * * * * * * * */
/* EXECUTE FUNCTIONS */
#define JUMP       0
#define BRANCH     1
#define SHIFT_LEFT 2
#define ADD        3
#define LOGICAL    4
#define MOVE_FROM  5
#define ROTATE     6
#define DIVIDE     7
#define MULTIPLY   8
#define MEMORY     9

/* EXECUTE FUNCTIONS */
/* * * * * * * * * * */


/* * * * * * */
/* REGISTERS */
#define HI 32
#define LO 33
#define PC 34
/* REGISTERS */
/* * * * * * */

#define MEMORY_SIZE 5
#define LINES_LENGTHS_MAX 100
#define LINES_NUMBER_MAX 100

#endif
