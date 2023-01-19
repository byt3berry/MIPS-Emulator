ADDI $1, $0, 2
# $1 = 2

ROTR $2, $1, 2
# $2 = -2³¹ 

ADDI $3, $2, 1
SUB $3, $0, $3
# $3 = 2³¹ - 1

SUB $4, $0, $1
# $4 = -2

# Overflows sur ADD : positif, négatif
ADD $5, $3, $1
ADD $6, $4, $2

# Overflow sur ADDI : positif, négatif
ADDI $7, $3, 1
ADDI $8, $2, -1

# Overflow sur SUB
SUB $9, $3, $4
SUB $10, $2, $1


# EXPECTED_ASSEMBLY
# 20010002
# 00211082
# 20430001
# 00031822
# 00012022
# 00612820
# 00823020
# 20670001
# 2048FFFF
# 00644822
# 00415022

# EXPECTED_FINAL_STATE
# $01:2
# $02:-2147483648
# $03:2147483647
# $04:-2
# $05:0
# $06:0
# $07:0
# $08:0
# $09:0
# $10:0
