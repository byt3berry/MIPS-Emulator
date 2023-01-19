# Projet MIPS 2022-2023
# Auteurs : Cocagne_Strainovic

# Dans ce fichier nous allons coder un programme qui va compter le nombre de caractères 's'
# dans la chaine de caractères "l'esisar fait mips"
# Puisque nous n'avons pas les labels et les directives
# Nous allons mettre le code ASCII des lettres une à une dans la mémoire

ADDI $1, $zero, 108
SW $1, 0($zero)  # on stock 'l'

ADDI $1, $zero, 0x27
SW $1, 4($zero)  # on stock "'"

ADDI $1, $zero, 101
SW $1, 8($zero)  # on stock 'e'

ADDI $1, $zero, 115
SW $1, 12($zero)  # on stock 's'

ADDI $1, $zero, 0x69
SW $1, 16($zero)  # on stock 'i'

ADDI $1, $zero, 115
SW $1, 20($zero)  # on stock 's'

ADDI $1, $zero, 97
SW $1, 24($zero)  # on stock 'a'

ADDI $1, $zero, 0x72
SW $1, 28($zero)  # on stock 'r'

ADDI $1, $zero, 32
SW $1, 32($zero)  # on stock ' '

ADDI $1, $zero, 102
SW $1, 36($zero)  # on stock 'f'

ADDI $1, $zero, 0x61
SW $1, 40($zero)  # on stock 'a'

ADDI $1, $zero, 105
SW $1, 44($zero)  # on stock 'i'

ADDI $1, $zero, 116
SW $1, 48($zero)  # on stock 't'

ADDI $1, $zero, 0x20
SW $1, 52($zero)  # on stock ' '

ADDI $1, $zero, 109
SW $1, 56($zero)  # on stock 'm'

ADDI $1, $zero, 105
SW $1, 60($zero)  # on stock 'i'

ADDI $1, $zero, 0x70
SW $1, 64($zero)  # on stock 'p'

ADDI $1, $zero, 115
SW $1, 68($zero)  # on stock 's'

ADDI $1, $zero, 0
SW $1, 72($zero)  # on stock '\0'

ADDI $2, $zero, 0  # $2 stock le resultat
ADD $3, $zero, $0  # $3 stock l'adresse de début de la chaine
ADDI $4, $zero, 115  # $4 stock le code ASCII de 's'

LW $5, 0($3)  # $5 stock le code ASCII à l'adresse $3

BEQ $5, $zero, 5  # si on est à la fin de la chaine on arrete
NOP

BNE $4, $5, 2  # si les codes ASCII sont différent on passe à la lettre suivante
NOP

ADDI $2, $2, 1

J 41  # on retourne au début de la 'boucle'
ADDI $3, $3, 4  # on saute à l'adresse suivante

# EXPECTED_ASSEMBLY
# 2001006C
# AC010000
# 20010027
# AC010004
# 20010065
# AC010008
# 20010073
# AC01000C
# 20010069
# AC010010
# 20010073
# AC010014
# 20010061
# AC010018
# 20010072
# AC01001C
# 20010020
# AC010020
# 20010066
# AC010024
# 20010061
# AC010028
# 20010069
# AC01002C
# 20010074
# AC010030
# 20010020
# AC010034
# 2001006D
# AC010038
# 20010069
# AC01003C
# 20010070
# AC010040
# 20010073
# AC010044
# 20010000
# AC010048
# 20020000
# 00001820
# 20040073
# 8C650000
# 10A00005
# 00000000
# 14850002
# 00000000
# 20420001
# 08000029
# 20630004

# EXPECTED_FINAL_STATE
# $01:0
# $02:3
# $03:76
# $04:115
# $05:0
