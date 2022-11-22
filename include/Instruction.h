typedef struct {
    char* operateur;
    int format;
    char* OPcodeOrFunc;
    int nbParametres;
    int parametres[3]; // les numéros des registres
} Instruction;

void setOperateur(Instruction*, char*);
void setFormat(Instruction*, int);
void setOPcodeOrFunc(Instruction*, char*);
void setParametres(Instruction*, int);

void printInfos(Instruction*);
char* fromIntToCharOPcodeFormat(int);
int isNext(Instruction*);
