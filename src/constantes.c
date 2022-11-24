#ifndef _CONSTANTES_C_
#define _CONSTANTES_C_

// Formats J
#define FORMAT_1 1
// Formats I
#define FORMAT_2 2
#define FORMAT_3 3
#define FORMAT_4 4
// Formats R
#define FORMAT_5 5
#define FORMAT_6 6
#define FORMAT_7 7
#define FORMAT_8 8
#define FORMAT_9 9

#define FORMAT_1_INPUT "%s %d"                // from FORMAT OUTPUT 1 to 1
#define FORMAT_2_INPUT "%s $%d, $%d, %d"      // from FORMAT OUTPUT 2 to 3
#define FORMAT_3_INPUT "%s $%d, %d($%d)"      // from FORMAT OUTPUT 4 to 4
#define FORMAT_4_INPUT "%s $%d, %d"           // from FORMAT OUTPUT 5 to 6
#define FORMAT_5_INPUT "%s $%d, $%d, $%d"     // from FORMAT OUTPUT 7 to 9
#define FORMAT_6_INPUT "%s $%d, $%d"          // from FORMAT OUTPUT 10 to 10
#define FORMAT_7_INPUT "%s $%d"               // from FORMAT OUTPUT 11 to 11
#define FORMAT_8_INPUT "%s $%d"               // from FORMAT OUTPUT 12 to 12
#define FORMAT_9_INPUT "%s"                   // from FORMAT OUTPUT 13 to 13

#define FORMAT_1_OUTPUT "1"                   // FORMAT 1
#define FORMAT_2_OUTPUT "2 1 3"               // FORMAT 2
#define FORMAT_3_OUTPUT "1 2 3"               // FORMAT 2
#define FORMAT_4_OUTPUT "3 1 2"               // FORMAT 3
#define FORMAT_5_OUTPUT "1 0 2"               // FORMAT 4
#define FORMAT_6_OUTPUT "0 1 2"               // FORMAT 4
#define FORMAT_7_OUTPUT "2 3 1 0"             // FORMAT 5
#define FORMAT_8_OUTPUT "-1 2 1 3"            // FORMAT 5  // TODO: exception ici, le premier parametre est '0'+'1'
#define FORMAT_9_OUTPUT "0 2 1 3"             // FORMAT 5
#define FORMAT_10_OUTPUT "1 2 0 0"            // FORMAT 6
#define FORMAT_11_OUTPUT "0 0 1 0"            // FORMAT 7
#define FORMAT_12_OUTPUT "1 0 0 0"            // FORMAT 8
#define FORMAT_13_OUTPUT "0 0 0 0"            // FORMAT 9

#define OPCODE_FUNC_SIZE 6
#define PARAMETRES_REGISTRES_SIZE 5
#define FORMAT_I_IMMEDIATE_SIZE 16
#define FORMAT_J_TARGET_SIZE 26

#endif