# CADIC BERNARD
ADDI $8, $0, 2000 # 1er valeur arbitraire
LUI $9, 1911 # (=0x777) 2e valeur arbitraire (0x777 << 16 = 0x7770000)

ADDI $29, $29, -4 # Sommet pile -4
SW $8, 0($29) # On place $t0 au sommet de la pile
SW $9, 4($29) # On place $t1 au sommet de la pile + 4 octets

LW $8, 4($29) # On récupère 0x7770000 ($t1) dans $t0
LW $9, 0($29) # On récupère 2000 ($t0) dans $t1

ADDI $29, $29, 4 # On revient au sommet de la pile

# EXPECTED_ASSEMBLY
# 200807D0
# 3C090777
# 23BDFFFC
# AFA80000
# AFA90004
# 8FA80004
# 8FA90000
# 23BD0004

# EXPECTED_FINAL_STATE
# $08:0x07770000
# $09:0x000007D0
# $29:0