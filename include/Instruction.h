typedef struct {
    char* operateur;
    int format;
    char* OPcodeOrFunc;
    int nbParametres;
    int parametres[4];
    int parametresOrder[4];
} Instruction;

void setOperateur(Instruction*, char*);
void setFormat(Instruction*, int);
void setOPcodeOrFunc(Instruction*, char*);
void setNbParametres(Instruction*, int);
void setParametres(Instruction*, int*);
void setParametresOrder(Instruction*, int*);
void setOutput(Instruction*);
void printInfos(Instruction*);