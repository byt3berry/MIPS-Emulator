typedef struct {
    char* operateur;
    int format;
    char* OPcodeOrFunc;
    int nbParametres;
//    int parametre1, parametre2, parametre3, parametre4; // les registres ou immédiats
    int parametres[4];
} Instruction;

void setOperateur(Instruction*, char*);
void setFormat(Instruction*, int);
void setOPcodeOrFunc(Instruction*, char*);
void setNbParametres(Instruction*, int);
void setParametres(Instruction*, int*);
//void setParametres(Instruction*, int, int, int, int);

void printInfos(Instruction*);
char* fromIntToCharOPcodeFormat(int);
int isNext(Instruction*);
