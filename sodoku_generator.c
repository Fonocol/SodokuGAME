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

    fprintf(f,"%d;%s;%d;%s;%s;%s;%s;%d\n",jeu.id,jeu.name,jeu.age,jeu._level,jeu.mail,jeu.pays,jeu.ville,jeu.record);

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
    snprintf(filePath, sizeof(filePath), "%s/%s", folderPath, gameInfo->name);
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
        fprintf(file, "currenttime : %d\n", gameInfo->currenttime);
        fprintf(file, "tempsmoyen : %d\n", gameInfo->tempsmoyen);
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

        //save matricenonmodif
        for (int i = 0; i < SIZE; i++) {;
            for (int j = 0; j < SIZE; j++) {
                fprintf(file, "NomModifMatrice[%d][%d] : %d\n",i,j, gameInfo->matricenonmodif[i][j]);
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
    snprintf(filePath, sizeof(filePath), "%s/%s", folderPath, gameName);
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
        fscanf(file, "currenttime : %d\n", &gameInfo->currenttime);
        fscanf(file, "tempsmoyen : %d\n", &gameInfo->tempsmoyen);
        //matrice
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                fscanf(file, "[%d][%d] : %d\n",&i,&j,&gameInfo->matrice[i][j]);
            }
        }
        //solution
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                fscanf(file, "solution[%d][%d] : %d\n",&i,&j,&SodokuMatrice[i][j]);
            }
        }
        // matrice nonModif
        //matricenonmodif
        for (int i = 0; i < SIZE; i++) {;
            for (int j = 0; j < SIZE; j++) {
                fscanf(file, "NomModifMatrice[%d][%d] : %d\n",&i,&j, &gameInfo->matricenonmodif[i][j]);
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
    char phrases[11][15] = {
        "Concentration!",
        "Vous reussirez",
        "Avancez bien! ",
        "Perseverez!   ",
        "Resolvez-le!  ",
        "Succes proche!",
        "Ne lachez pas!",
        "Toujours plus!",
        "Determination!",
        "Victoire sure!",
    };
    DWORD startTime = GetTickCount();
    DWORD currentTime = GetTickCount();
    
    int temps;
    


    PIL *back = createPIL();
    int back_time=0;
    back = enPIL(back,jeu);
    int i=-2,j=-2,value=-1;
    while (!solution(jeu))
    {
        
        //PrintSodoku(SodokuMatrice);
        // À chaque itération de la boucle de jeu :
        startTime = GetTickCount();
        
        system("cls");//update
        afficher_en_Damier(jeu,i-1,j-1,value,phrases);

        //printf("enter position x :\n");    
        do
        {
            print_generique("enter position x 0 pour fermer :\n",1);
            scanf("%d",&i);
        } while (i<0 || i>10);
        
 
        if (i==0)
        {
            print_generique("A plus :-)",1);
            Sleep(1500);
            saveGameInfo("sodoku_doc", &jeu,SodokuMatrice);
            exit(1);
        }
        
        //printf("enter position y :\n");
        do
        {
            print_generique("enter position y 0 pour ouvrir les statistiques:\n",1);
            scanf("%d",&j);
        } while (j<0 || j>10);
        if (j==0)
        {
            char* fichier = "sodoku_doc/data.csv";
            if (fichier)
            {
                // Utilisation de la commande système pour ouvrir le fichier
                // Pour Windows
                char commande[100];
                snprintf(commande, sizeof(commande), "start %s", fichier);
                system(commande);
                //value=-1;
            }
            value=-1;
        }else
        {
            do
            {
                print_generique("value",1);
                printf("[%d][%d]\n",i,j);
                scanf("%d",&value);
            } while (value<-2 || value>10);
        }
        
        


        //non modif value
        if (value >0 && jeu.matricenonmodif[i-1][j-1] != 0)
        {
            value =jeu.matricenonmodif[i-1][j-1];
        }

        else if (value == 0)
        {
            if (!isEmptyPIL(back))
            {
                back_time = jeu.currenttime;
                back = dePIL(back,&jeu);
                jeu.currenttime = back_time;
            }
            //value =-1;
            
        }
        
        else if (value ==-2){
            if (jeu.points>=3*POINT){
                if (jeu.matrice[i-1][j-1] == 0)
                {
                    jeu.matrice[i-1][j-1]=SodokuMatrice[i-1][j-1];
                    jeu.points = jeu.points-3*POINT;
                    value =SodokuMatrice[i-1][j-1];
                    Sleep(500);
                }else
                {
                    print_generique("cette case est deja valide !",1);
                    Sleep(1000);
                }
                
            }
            else
            {
                print_generique("Desole vous n'avez pas assey de points |_(o o)_|",1);
                Sleep(1000);
            }  
        }
        
        else if ( value >0 && IsSodoku(jeu.matrice,i-1,j-1,value)){
            if (jeu.matrice[i-1][j-1]=value == VIDE)
            {
                jeu.points = jeu.points+POINT;
            }
            jeu.matrice[i-1][j-1]=value;
            

            back = enPIL(back,jeu);
        }
        else
        {
            //printf("this value not a sodoku solution\n");
            //print_generique("cette valeur n'est pas valide pour cette case :| \n",1);
            //system("cls");
            //Sleep(100);
            //afficher_en_Damier(jeu,i-1,j-1,value);
            //Sleep(3000);
        }
        

        Sleep(100);
        //save data
        currentTime = GetTickCount();
        temps = currentTime - startTime;
        jeu.currenttime = jeu.currenttime + (temps/1000);
        saveGameInfo("sodoku_doc", &jeu,SodokuMatrice);
        
       
 
    }

    system("cls");
    afficher_en_Damier(jeu,i-1,j-1,value,phrases);
    Sleep(500);

    free(back);
    //ajustement du record
    if(jeu.record==-1){
        jeu.record = (jeu.currenttime);
        savedatas(jeu);
    }
    else
    {
        if ((jeu.currenttime)<jeu.record)
        {
            jeu.record = (jeu.currenttime);
        }
        savedatas(jeu);
        
    }
    


    system("cls");
    print_generique("Bravo !!! vous avez gagne la partie |_(00)_| \n",0);
    tovide(SodokuMatrice);
    GenerateDagonaleBlocks(SodokuMatrice);
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            jeu.matrice[i][j] = SodokuMatrice[i][j];
        }
    }
    grillenonresolu(&jeu);
    //calcul temps moyen
    jeu.tempsmoyen  = (jeu.tempsmoyen*(jeu.partie-1) + (jeu.currenttime))/jeu.partie;
    jeu.partie=jeu.partie+1;
    
    jeu.currenttime = 0;
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

void printSudokuLogo(int val) {
    system("cls");

    printf("\n\033[0;96m");
    printf("                   +-----------------------------+\n");
    printf("                   |                             |\n");
    printf("                   |           SUDOKU            |\n");
    printf("                   |                             |\n");
    printf("                   +-----------------------------+\n");
    printf("\033[0m");

    printf("\n\n\n");
    if(val ==1){
        printf("                   +-----------------------------+\n");
        printf("                   |                             |\n");
        printf("                   |      0. Charger Partie      |\n");
        printf("                   |      1. Nouvelle Partie     |\n");
        printf("                   |      2. Quitter             |\n");
        printf("                   |                             |\n");
        printf("                   +-----------------------------+\n");
        printf("\n\033[0;34mChoisissez une option (0-2) : \033[0m");
    }else
    {

        printf("      +-----------------------------------------------+\n");
        printf("      |                                               |\n");
        printf("      |      0. jouer une exhibition                  |\n");
        printf("      |      1. jouer une partie                      |\n");
        printf("      |      2. consulter l'aide et la documentation  |\n");
        printf("      |      3. Quitter                               |\n");
        printf("      |                                               |\n");
        printf("      +-----------------------------------------------+\n");

        printf("\n\033[0;34mChoisissez une option (0-3) : \033[0m");
    }
    
}

void run(int sodokumatrice[SIZE][SIZE],char *folderName) {
    char phrases[11][15] = {
        "Concentration!",
        "Vous reussirez",
        "Avancez bien! ",
        "Perseverez!   ",
        "Resolvez-le!  ",
        "Succes proche!",
        "Ne lachez pas!",
        "Toujours plus!",
        "Determination!",
        "Victoire sure!",
    };
    tovide(sodokumatrice);
    int partie;
    //printf("Pour jouer une exhibition, entrez 0. Pour jouer une partie, entrez 1 : ");
    printSudokuLogo(0);
    //print_generique("Pour jouer une exhibition entrez(0); Pour jouer une partie entrez (1)\npour consulter l'aide et la documentation entrez -1 : ",1);
    scanf("%d", &partie);

    if (partie == 0) {
        // Code pour lancer un jeu simple
        GameInfo gameInfo;
        strcpy(gameInfo.name , "NONE");
        gameInfo.age = 0;
        gameInfo.points = 0;
        gameInfo.partie = 0;
        gameInfo.record = -1;
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
        //print_generique("0 pour continuer une partie, 1 pour creer une nouvelle partie : ",1);
        printSudokuLogo(1);
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
        } else if(partie == 1) {
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
            gameInfo.tempsmoyen = 0;
            gameInfo.currenttime = 0;
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
        else
        {
            print_generique("A plus :-)",1);
            exit(1);
        }
    }else if(partie ==2)
    {
        //fonction pour la documentation
        //aide237france.txt
        print_generique("\n==> Les objectifs du jeu Sodoku sont les suivants :\n  1. Remplir la grille de 9x9 avec des chiffres de 1 a 9 de maniere a respecter les regles\n  de non-repetition dans les lignes, les colonnes et les sous-grilles.\n  2. Resoudre le puzzle en determinant les chiffres manquants de maniere logique, sans deviner.\n  3. Completer la grille de maniere efficace en minimisant le nombre d'erreurs.\n  4. Ameliorer ses competences en resolution de problemes et en logique pour resoudre des Sodokus\n  de niveaux de difficulte croissants.\n",1);
        char gameName[] = "AideSUdoku";
        GameInfo gameInfo;
        if (loadGameInfo("sodoku_doc", gameName, &gameInfo,sodokumatrice)) {
            
            printf("\n");
            print_generique("1)essayons d'entrer la valeur 6\na la case [5][8]\n",1);
            gameInfo.matrice[4][7]=6;
            afficher_en_Damier(gameInfo,4,7,6,phrases);
            print_generique("toutes les contraintes du sodoku\netant verivier la valeur 6 est bien \nvalable pour[5][8]\n",1);
            printf("\n");
            print_generique("2)essayons d'entrer la valeur 8\na la case [7][7]\n",1);
            gameInfo.matrice[6][6]=8;
            afficher_en_Damier(gameInfo,6,6,8,phrases);
            printf("\n");
            gameInfo.matrice[6][6]=0;
            print_generique("ici les condition de sodoku en\nligne et en colone ne sont pas respecter \ndonc 8 est invalide pour cette cellule\n",1);
            printf("\n");
            print_generique("3)essayons d'entrer la valeur 1 a\nla case [2][2]\n",1);
            gameInfo.matrice[1][1]=1;
            afficher_en_Damier(gameInfo,1,1,1,phrases);
            printf("\n");
            gameInfo.matrice[1][1]=0;
            print_generique("ici les condition de sodoku en \nligne en colone et dans la region ne sont \npas respecter donc 1 est invalide pour \ncette cellule\n",1);
            
            printf("\n");
            print_generique("4)apres avoir mis les valeur en\nrestant fidele aux regles du sodoku on a\n",1);
            gameInfo.matrice[1][1] = 1;
            gameInfo.matrice[8][3] = 8;
            gameInfo.matrice[8][4] = 2;
            gameInfo.matrice[8][5] = 9;
            gameInfo.matrice[6][2] = 7;
            gameInfo.matrice[6][3] = 6;
            gameInfo.matrice[6][4] = 3;
            gameInfo.matrice[6][5] = 1;
            gameInfo.matrice[0][0] = 8;
            gameInfo.matrice[0][1] = 2;
            gameInfo.matrice[0][2] = 4;
            gameInfo.matrice[5][3] = 9;
            gameInfo.matrice[5][5] = 3;
            gameInfo.matrice[5][6] = 2;
            afficher_en_Damier(gameInfo,1,1,-1,phrases);
        } else {
            printf("le Chargement de l'aide a echoue\n");
        }
        printf("\n");       
        run(sodokumatrice,folderName);
    }
    else
    {
        print_generique("A plus :-)",1);
        exit(1);
    }
    
    
}

