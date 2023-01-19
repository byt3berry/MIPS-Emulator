# Dans ce fichier nous allons compter le nombre de puissances de 2 dans un nombre
# Exemple dans 1234 = 0b10011010010 le résultat est 5 car il y a 5 fois le chiffre 1 dans sa verison binaire
# Pour cela nous allons utiliser ROTR, AND et une boucle

ADDI $1, $zero, 1234  # le nombre à tester
ADDI $2, $0, 31  # le nombre d'itérations restantes
ADDI $3, $zero, 0  # le résulat
ADDI $4, $0, 1  # valeur utile pour le AND

AND $5, $1, $4  # on récupère le premier bit de $1
BNE $5, $4, 2  # si le bit ne vaut pas 1 on passe au bit suivant
NOP

ADDI $3, $3, 1

ROTR $1, $1, 1

BGTZ $2, -6
ADDI $2, $2, -1


# EXPECTED_ASSEMBLY
# 200104D2
# 2002001F
# 20030000
# 20040001
# 00242824
# 14A40002
# 00000000
# 20630001
# 00210842
# 1C40FFFA
# 2042FFFF

# EXPECTED_FINAL_STATE
# $01:1234
# $02:-1
# $03:5
# $04:1
# $05:0