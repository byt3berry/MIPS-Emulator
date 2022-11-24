typedef struct {
    char operateur[8];
    int format;
    char OPcodeOrFunc[6];
    int nbParametres;
    int parametres[4];
} Instruction;

void setOperateur(Instruction*, char*);
void setFormat(Instruction*, int);
void setOPcodeOrFunc(Instruction*, char*);
void setNbParametres(Instruction*, int);
void setParametres(Instruction*, int*);

void printInfos(Instruction*);
char* fromIntToCharOPcodeFormat(int);
int isNext(Instruction*);
