typedef struct {
    char *operateur;
    int format;
    int OPcodeOrFunc;
    int nbParametres;
    int parametres[4];
    int parametresOrder[4];
} Instruction;

void setOperateur(Instruction *, char *);

void setFormat(Instruction *, int);

void setOPcodeOrFunc(Instruction *, int);

void setNbParametres(Instruction *, int);

void setParametres(Instruction *, int *);

void setParametresOrder(Instruction *, int *);

void setOutputFull(Instruction *, char *);

void setOutputR(Instruction *, char *);

void setOutputI(Instruction *, char *);

void setOutputJ(Instruction *, char *);

void setOutput(Instruction *);

void printInfos(Instruction *);