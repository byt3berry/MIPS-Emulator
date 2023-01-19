ADDI $1, $0, 1  # terme u_n de fibonacci
ADDI $2, $0, 1  # terme u_(n+1) de fibonacci
ADDI $3, $0, 7  # terme final souhaité
ADDI $4, $0, 2  # terme actuel

ADD $8, $1, $2  # u_(n+2) = u_(n+1) + u_n
ADD $1, $0, $2  # u_n <- u_(n+1)
ADD $2, $0, $8  # u_(n+1) <- u_(n+2)
ADDI $4, $4, 1

BNE $3, $4, -5  # si on a le terme voulu
NOP

ADD $5, $0, $2  # on place le resultat dans $5

# EXPECTED_ASSEMBLY
# 20010001
# 20020001
# 20030007
# 20040002
# 00224020
# 00020820
# 00081020
# 20840001
# 1464FFFB
# 00000000
# 00022820

# EXPECTED_FINAL_STATE
# $01:8
# $02:13
# $03:7
# $04:7
# $05:13
# $08:13