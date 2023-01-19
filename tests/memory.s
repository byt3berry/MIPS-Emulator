# On va échanger les valeurs de 2 registres en passant par la mémoire

ADDI $t1, $zero, 42  # premier registre à inverser
ADDI $t2, $zero, 69  # deuxième registre à inverser

LUI $1, 0x7D0  # on stockera les 2 nombres avec cette base

# On enregistre dans la mémoire
SW $t1, 0($1)
SW $t2, 4($1)

# On récupère dans la mémoire
LW $t1, 4($1)
LW $t2, 0($1)

# EXPECTED_ASSEMBLY
# 2009002A
# 200A0045
# 3C0107D0
# AC290000
# AC2A0004
# 8C290004
# 8C2A0000

# EXPECTED_FINAL_STATE
# $01:0x7D00000
# $09:69
# $10:42