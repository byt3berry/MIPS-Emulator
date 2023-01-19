ADDI $1, $0, 2
# $1 = 2

ROTR $2, $1, 2
# $2 = -2³¹ 

ADDI $3, $2, 1
SUB $3, $0, $3
# $3 = 2³¹ - 1

SUB $4, $0, $1
# $4 = -2

# Overflows on ADD: positive, negative
ADD $5, $3, $1
ADD $6, $4, $2

# Overflow on ADDI
ADDI $7, $3, 1
ADDI $8, $2, -1

# Overflow on SUB
SUB $9, $3, $4
SUB $10, $2, $1



