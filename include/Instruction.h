typedef struct {
    char* operateur;
    int formatInput;
    int formatOutput;
    char* OPcodeOrFunc;
    int nbParametres;
    int parametres[4];
} Instruction;

void setOperateur(Instruction*, char*);
void setFormat(Instruction*, int);
void setOPcodeOrFunc(Instruction*, char*);
void setNbParametres(Instruction*, int);
void setParametres(Instruction*, int*);
void setOutput(Instruction*);
void printInfos(Instruction*);