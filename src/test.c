#include <stdio.h>


int test(void) {
    /*
    FILE* file = fopen("testtt.txt", "r");

    while(!feof(file)){
        char *mot;
        // fgets(mot, 20, file);
        // int len = sizeof(mot);
        // printf("%s\n", mot);
        
        fscanf(file, "%c", mot);
        printf("%s\n", mot);

        
        for (int i = 0; i < len-1; i++) {
            printf("%d %d \n", i, mot[i]);
        }
        break;
        
    }
    */
    char* mot = "abcdef";

    for (int i = 0; i < 6; i++) {
        printf("%c\n", *mot);
        mot++;
    }

    return 0;
}
