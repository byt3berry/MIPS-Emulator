void WriteInfile(char*){
    File* fichier;
    f = fopen("fichier.txt", "w");

    if(f==NULL){
        printf("ca marche pas zebi le fichier il existe pas");
        exit(1);
    }
     else if(f==!NULL){
        fputs(char*, fichier);
        fclose(fichier);
    }
    return(0);
}