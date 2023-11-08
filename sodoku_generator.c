#include "header.h"


void tovide(int SodokuMatrice[SIZE][SIZE]){
    for (int i = 0; i < SIZE; i++){
        for (int j = 0; j < SIZE; j++){
            SodokuMatrice[i][j]=VIDE;
        } 
    }
}

void printMatrix(int matrice[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", matrice[i][j]);
        }
        printf("\n");
    }
}



//char nom[],int level
void create(char *folderName) {
    // Nom du dossier à créer ou vérifier
    char currentPath[1024];
    char folderPath[1024]; // Utilisez un tableau plutôt qu'un pointeur

    // Obtenir le chemin actuel du répertoire de travail
    if (_getcwd(currentPath, sizeof(currentPath)) != NULL) {
        // Concaténer le chemin actuel avec le nom du dossier
        snprintf(folderPath, sizeof(folderPath), "%s\\%s", currentPath, folderName);

        // Vérifier si le dossier existe
        if (_access(folderPath, 0) == -1) {
            // Le dossier n'existe pas, donc on le crée
            if (_mkdir(folderPath) == 0) {
                printf("Dossier créé avec succès : %s\n", folderPath);
                // Créer le fichier "data.csv" dans le dossier
                char csvPath[1024];
                snprintf(csvPath, sizeof(csvPath), "%s\\data.csv", folderPath);
                FILE *f = fopen(csvPath, "w");
                if (f != NULL) {
                    fprintf(f, "ID;NOM;AGE;LEVEL;MAIL;PAYS;VILLE;RECORD\n");
                    fclose(f);
                    printf("Fichier 'data.csv' créé avec succès dans : %s\n", folderPath);
                } else {
                    printf("Échec de la création du fichier 'data.csv' dans : %s\n", folderPath);
                }
            } else {
                printf("Échec de la création du dossier : %s\n", folderPath);
            }
        } else {
            printf("Le dossier existe déjà : %s\n", folderPath);
        }
    } else {
        printf("Erreur lors de l'obtention du répertoire de travail.\n");
    }
}




void savedatas(GameInfo jeu){
    FILE * f = fopen("sodoku_doc/data.csv","a");

    fprintf(f,"%d;%s;%d;%s;%s;%s;%s;%d\n",jeu.id,jeu.name,jeu.age,jeu._level,jeu.mail,jeu.pays,jeu.ville,-1);

    fclose(f);
}

//save id
int id_in_data(){
    GameInfo jeu;
    int current;
    jeu.id = -1;
    FILE * f = fopen("sodoku_doc/data.csv","r");
    char data[150];
    while (fgets(data, sizeof(data),f)!= NULL) {
        sscanf(data, "%d;%*[^;];%*d;%*[^;];%*[^;];%*[^;];%*[^;]", &current);
        if (current> jeu.id)
        {
            jeu.id = current;
        }   
    }
    fclose(f);
    return jeu.id+1;
}



void saveGameInfo(const char *folderPath, const GameInfo *gameInfo,int SodokuMatrice[SIZE][SIZE]) {
    char filePath[256];
    snprintf(filePath, sizeof(filePath), "%s/%s.txt", folderPath, gameInfo->name);
    FILE *file = fopen(filePath, "w");
    
    if (file) {
        fprintf(file, "ID : %d\n", gameInfo->id);
        fprintf(file, "Nom : %s\n", gameInfo->name);
        fprintf(file, "_Level_ : %s\n", gameInfo->_level);
        fprintf(file, "Mail : %s\n", gameInfo->mail);
        fprintf(file, "Pays : %s\n", gameInfo->pays);
        fprintf(file, "Ville : %s\n", gameInfo->ville);
        fprintf(file, "Âge : %d\n", gameInfo->age);
        fprintf(file, "Level : %d\n", gameInfo->level);
        fprintf(file, "Partie : %d\n", gameInfo->partie);
        fprintf(file, "Points : %d\n", gameInfo->points);
        fprintf(file, "Record : %d\n", gameInfo->record);
        for (int i = 0; i < SIZE; i++) {;
            for (int j = 0; j < SIZE; j++) {
                fprintf(file, "[%d][%d] : %d\n",i,j, gameInfo->matrice[i][j]);
            }
        }
        //save solution
        for (int i = 0; i < SIZE; i++) {;
            for (int j = 0; j < SIZE; j++) {
                fprintf(file, "solution[%d][%d] : %d\n",i,j, SodokuMatrice[i][j]);
            }
        }
        // Écrivez d'autres informations spécifiques à la partie ici
        fclose(file);
    } else {
        printf("Erreur lors de l'ouverture du fichier pour enregistrement.\n");
    }
}

int loadGameInfo(const char *folderPath, const char *gameName, GameInfo *gameInfo,int SodokuMatrice[SIZE][SIZE]) {
    char filePath[256];
    snprintf(filePath, sizeof(filePath), "%s/%s.txt", folderPath, gameName);
    FILE *file = fopen(filePath, "r");
    
    if (file) {
        fscanf(file, "ID : %d\n",&gameInfo->id);
        fscanf(file, "Nom : %s\n", gameInfo->name);
        fscanf(file, "_Level_ : %s\n", gameInfo->_level);
        fscanf(file, "Mail : %s\n", gameInfo->mail);
        fscanf(file, "Pays : %s\n", gameInfo->pays);
        fscanf(file, "Ville : %s\n", gameInfo->ville);
        fscanf(file, "Âge : %d\n", &gameInfo->age);
        fscanf(file, "Level : %d\n", &gameInfo->level);
        fscanf(file, "Partie : %d\n", &gameInfo->partie);
        fscanf(file, "Points : %d\n", &gameInfo->points);
        fscanf(file, "Record : %d\n", &gameInfo->record);
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                fscanf(file, "[%d][%d] : %d\n",&i,&j,&gameInfo->matrice[i][j]);
            }
        }

        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                fscanf(file, "solution[%d][%d] : %d\n",&i,&j,&SodokuMatrice[i][j]);
            }
        }
        // Lisez d'autres informations spécifiques à la partie ici
        fclose(file);
        return 1;  // La lecture a réussi
    } else {
        printf("Erreur lors de l'ouverture du fichier pour chargement.\n");
        return 0;  // La lecture a échoué
    }
}

void game(GameInfo jeu,int SodokuMatrice[SIZE][SIZE]){
    DWORD startTime = GetTickCount();
    int temps;
    


    PIL *back = createPIL();
    back = enPIL(back,jeu);
    int i,j,value;
    while (!solution(jeu))
    {
        system("cls");//update
        PrintSodoku(jeu);
        //PrintSodoku(SodokuMatrice);
        // À chaque itération de la boucle de jeu :
        DWORD currentTime = GetTickCount();
        temps = currentTime - startTime;
        printf("Temps ecoule : %u secondes\n", temps/1000);
        //printf("enter position x :\n");
        print_generique("enter position x 0 pour fermer :\n",1);
        scanf("%d",&i);
        if (i==0)
        {
            print_generique("A plus :-)",1);
            Sleep(1500);
            saveGameInfo("sodoku_doc", &jeu,SodokuMatrice);
            exit(1);
        }
        
        //printf("enter position y :\n");
        print_generique("enter position y :\n",1);
        scanf("%d",&j);
        print_generique("value",1);
        printf("[%d][%d]",i,j);
        scanf("%d",&value);
        
        if (value == 0)
        {
            if (!isEmptyPIL(back))
            {
                back = dePIL(back,&jeu);
            }
            
        }
        
        else if (value ==-1){
            if (jeu.points>=3*POINT){
                print_generique("la solution a value",1);
                printf("[%d][%d] est %d\n",i,j,SodokuMatrice[i-1][j-1]);
                jeu.points = jeu.points-3*POINT;
                Sleep(1000);
            }
            else
            {
                print_generique("Desole vous n'avez pas assey de points :( ",1);
                Sleep(1000);
            }  
        }
        
        else if (IsSodoku(jeu.matrice,i-1,j-1,value)){
            jeu.matrice[i-1][j-1]=value;
            jeu.points = jeu.points+POINT;
            saveGameInfo("sodoku_doc", &jeu,SodokuMatrice);

            back = enPIL(back,jeu);
        }
        else
        {
            //printf("this value not a sodoku solution\n");
            print_generique("cette valeur n'est pas valide pour cette case :| \n",1);
            Sleep(1000);
        }
        

        Sleep(100);
        
        
    }
    free(back);
    
    if(jeu.record==-1){
        jeu.record = temps;
    }
    else
    {
        if (temps<jeu.record)
        {
            jeu.record = temps;
        }
        
    }
    


    system("cls");
    print_generique("Bravo !!! vous avez gagne la partie :) \n",0);
    tovide(SodokuMatrice);
    GenerateDagonaleBlocks(SodokuMatrice);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            jeu.matrice[i][j] = SodokuMatrice[i][j];
        }
    }
    grillenonresolu(&jeu);
    jeu.partie=jeu.partie+1;
    saveGameInfo("sodoku_doc", &jeu,SodokuMatrice);
    game(jeu,SodokuMatrice);

}

void game_free(GameInfo jeu,int SodokuMatrice[SIZE][SIZE]){


    int i,j,value;
    while (!solution(jeu))
    {
        system("cls");//update
        PrintSodoku(jeu);
        //printf("enter position x :\n");
        print_generique("enter position x :\n",1);
        scanf("%d",&i);
        //printf("enter position y :\n");
        print_generique("enter position y :\n",1);
        scanf("%d",&j);
        print_generique("value",1);
        printf("[%d][%d]",i,j);
        scanf("%d",&value);
        if (value == 0)
        {
            exit(1);
        }
        
        else if (value ==-1){
            print_generique("la solution a value ",1);
            printf("[%d][%d] est %d\n",i,j,SodokuMatrice[i-1][j-1]);
            Sleep(1000);
        }
        
        else if (IsSodoku(jeu.matrice,i-1,j-1,value)){
            jeu.matrice[i-1][j-1]=value;
        }
        else
        {
            //printf("this value not a sodoku solution\n");
            print_generique("cette valeur n'est pas valide pour cette case :|\n",1);
            Sleep(1000);
        }
        
        //PrintSodoku(SodokuMatrice);

        Sleep(100);   
    }
    system("cls");
    print_generique("Bravo !!! vous avez gagne \n",0);
    tovide(SodokuMatrice);
    GenerateDagonaleBlocks(SodokuMatrice);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            jeu.matrice[i][j] = SodokuMatrice[i][j];
        }
    }
    grillenonresolu(&jeu);
    game_free(jeu,SodokuMatrice);

}

void run(int sodokumatrice[SIZE][SIZE],char *folderName) {
    int partie;
    //printf("Pour jouer une exhibition, entrez 0. Pour jouer une partie, entrez 1 : ");
    print_generique("Pour jouer une exhibition entrez(0); Pour jouer une partie entrez (1)\npour consulter l'aide et la documentation entrez -1 : ",1);
    scanf("%d", &partie);

    if (partie == 0) {
        // Code pour lancer un jeu simple
        GameInfo gameInfo;
        strcpy(gameInfo.name , "NONE");
        gameInfo.age = 0;
        gameInfo.points = 0;
        gameInfo.partie = 0;
        gameInfo.level = rand()%3;
        GenerateDagonaleBlocks(sodokumatrice);
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                gameInfo.matrice[i][j] = sodokumatrice[i][j];
            }
        }
        grillenonresolu(&gameInfo);
        game_free(gameInfo,sodokumatrice);
    } else if(partie == 1) {
        //printf("0 pour continuer une partie, 1 pour créer une nouvelle partie : ");
        print_generique("0 pour continuer une partie, 1 pour creer une nouvelle partie : ",1);
        scanf("%d", &partie);

        if (partie == 0) {

            char gameName[50];
            //printf("Entrez le nom de la partie que vous souhaitez continuer : ");
            print_generique("Entrez le nom de la partie que vous souhaitez continuer : ",1);
            scanf("%s", gameName);
            
            GameInfo gameInfo;
            if (loadGameInfo("sodoku_doc", gameName, &gameInfo,sodokumatrice)) {
                printf("Chargement reussi : Nom : %s, Âge : %d\n,Matrice %s", gameInfo.name, gameInfo.age);
                //printMatrix(gameInfo.matrice);
                game(gameInfo,sodokumatrice);

                // Ajoutez le code pour continuer la partie ici
            } else {
                printf("Chargement de la partie échoué.\n");
            }
        } else {
            // Code pour créer une nouvelle partie
            GameInfo gameInfo;
            //id generation
            gameInfo.id = id_in_data();
            //printf("Entrez votre nom : ");
            print_generique("Entrez votre nom : ",1);
            scanf("%s", gameInfo.name);
            //printf("Entrez votre âge : ");
            print_generique("Entrez votre age : ",1);
            scanf("%d", &gameInfo.age);
            //printf("Entrez votre level entre 0 et 2 : ");
            print_generique("Entrez votre adresse mail : ",1);
            scanf("%s", gameInfo.mail);
            print_generique("Entrez votre pays : ",1);
            scanf("%s", gameInfo.pays);
            print_generique("Entrez votre ville : ",1);
            scanf("%s", gameInfo.ville);
            print_generique("Entrez votre level: 0=Easy 1=Medium 2=Difficult : ",1);
            scanf("%d", &gameInfo.level);
            switch (gameInfo.level)
            {
            case 0:
                strcpy(gameInfo._level,"Easy");
                break;
            case 1:
                strcpy(gameInfo._level,"Medium");
                break;
            case 2:
                strcpy(gameInfo._level,"Difficult");
                break;
            default:
                strcpy(gameInfo._level,"NONE");
                break;
            }
            gameInfo.partie =1;
            gameInfo.points = 0;
            gameInfo.record = -1;
            GenerateDagonaleBlocks(sodokumatrice);
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++) {
                    gameInfo.matrice[i][j] = sodokumatrice[i][j];
                }
            }
            grillenonresolu(&gameInfo);
            
            
            saveGameInfo("sodoku_doc", &gameInfo,sodokumatrice);
            savedatas(gameInfo);
            printf("Nouvelle partie creee : Nom : %s, age : %d\n", gameInfo.name, gameInfo.age);
            game(gameInfo,sodokumatrice);
        }
    }else
    {
        //fonction pour la documentation
        printf("==> Description \nLe jeu Sodoku est un casse-tete numerique populaire qui se joue sur une grille de 9x9 cases,\ndivisee en neuf sous-grilles de 3x3 cases. L'objectif du jeu est de remplir toutes les cases\n de la grille avec des chiffres de 1 a 9 de maniere a ce que chaque ligne, chaque colonne et\n chaque sous-grille de 3x3 ne contienne jamais deux fois le meme chiffre. En d'autres termes,\n chaque chiffre de 1 a 9 doit apparaitre une seule fois dans chaque ligne, chaque colonne \net chaque sous-grille.\nLe jeu commence generalement avec quelques chiffres deja places dans la grille, formant un\n puzzle initial. Le joueur doit ensuite utiliser la logique et l'elimination pour determiner\n quels chiffres doivent etre places dans les cases vides pour resoudre le puzzle. Le jeu Sodoku\n est un defi de reflexion et de resolution de problemes qui repose sur la logique et la perspicacite.\n==> Les objectifs du jeu Sodoku sont les suivants :\n1. Remplir la grille de 9x9 avec des chiffres de 1 a 9 de maniere a respecter les regles\nde non-repetition dans les lignes, les colonnes et les sous-grilles.\n2. Resoudre le puzzle en determinant les chiffres manquants de maniere logique, sans deviner.\n3. Completer la grille de maniere efficace en minimisant le nombre d'erreurs.\n4. Ameliorer ses competences en resolution de problemes et en logique pour resoudre des Sodokus\nde niveaux de difficulte croissants.\n");

        run(sodokumatrice,folderName);
    }
    
}
