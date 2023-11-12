#include "header.h"


void PrintSodoku(GameInfo gameInfo){
    printf("-------------------------------------------------------------\n");
    for (int i = -1; i < SIZE; i++){
        for (int j = -1; j < SIZE; j++){
            if (i==-1){
                printf("||%d|||",j+1);
            }
            else{
                if (j==-1){
                    printf("||%d|||",i+1);
                }
                else{
                    if (gameInfo.matrice[i][j]==VIDE){
                        printf("  x  |");
                    }
                    else{
                        printf("  %d  |",gameInfo.matrice[i][j]);
                    }
                }
            }  
        }
        printf("\n");
        printf("-------------------------------------------------------------\n");
    }
    printf("A tout moment vous pouvez obtenir de l'aide en entrant -1 ou\nretour en entrant 0 sur value\n");
    //printf("Nom: %s\n",gameInfo.name);
    //printf("Age: %d Ans\n",gameInfo.age);
    printf("Level : %s \n",gameInfo._level);
    printf("Partie: %d \n",gameInfo.partie);
    printf("Points: %d \n",gameInfo.points);
    printf("-------------------------------------------------------------\n");
}

bool region(int SodokuMatrice[SIZE][SIZE],int ligne,int colone,int element){
    int StartLigne = ligne - ligne%3;
    int StartColone = colone - colone%3;

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (SodokuMatrice[i+StartLigne][j+StartColone]== element){
                return true;
            }  
        }
    }
    return false;
}

void afficher_en_Damier(GameInfo gameinfo,int line,int col,int val,char phrases[11][15]){
    char ph[14];
    strcpy(ph,phrases[rand()%9]);
    printf("\033[47m\033[31m            SODOKU            \033[0m\n");
    printf("\033[47m\033[31m        %s        \033[0m\n",ph);
    //printf("\033[0m\n"); // Réinitialiser la couleur après la ligne 1


    for (int i = -1; i < SIZE; i++) {
        for (int j = -1; j < SIZE; j++) {
            if (i==-1)
            {
                printf(" %d ",j+1);
            }
            else
            {
                if (j==-1)
                {
                    printf(" %d ",i+1);
                }
                else
                {
                    // Alterner les couleurs en fonction de la somme des indices
                    if ((i + j) % 2 == 0) {
                        // Case de couleur claire avec caractère noir
                        if (gameinfo.matrice[i][j]==0)
                        {
                            printf("\033[47m   ");
                        }else if (gameinfo.matrice[i][j]!=0)
                        {
                            if (gameinfo.matrice[i][j]==val)
                            {
                                if (i==line || j==col)
                                {
                                    printf("\033[47m\033[31m %d ",gameinfo.matrice[i][j]);
                                }else if (((line-line%3)==(i - i%3) && (col-col%3)==(j - j%3)) &&  region(gameinfo.matrice,line,col,val))  //cette condition montre que les variables col line i et j sont dans la mm region
                                {
                                    printf("\033[47m\033[31m %d ",gameinfo.matrice[i][j]);
                                }
                                else
                                {
                                    printf("\033[47m\033[32m %d ",gameinfo.matrice[i][j]);
                                }

                            }else
                            {
                                printf("\033[47m\033[32m %d ",gameinfo.matrice[i][j]);
                            }
                            
                            
                            //printf("\033[47m\033[32m %d ",gameinfo.matrice[i][j]);
                        }
                        
                    } 
                    else {
                        if (gameinfo.matrice[i][j]==0)
                        {
                            printf("\033[40m   ");
                        }else if (gameinfo.matrice[i][j]!=0)
                        {
                            if (gameinfo.matrice[i][j]==val)
                            {
                                if (i==line || j==col)
                                {
                                    printf("\033[40m\033[31m %d ",gameinfo.matrice[i][j]);
                                }else if (((line-line%3)==(i - i%3) && (col-col%3)==(j - j%3)) &&  region(gameinfo.matrice,line,col,val))  //cette condition montre que les variables col line i et j sont dans la mm region
                                {
                                    printf("\033[40m\033[31m %d ",gameinfo.matrice[i][j]);
                                }
                                else
                                {
                                    printf("\033[40m\033[32m %d ",gameinfo.matrice[i][j]);
                                }
                                

                            }else
                            {
                                printf("\033[40m\033[32m %d ",gameinfo.matrice[i][j]);
                            }

                        }
                    }
                }
                
                
            }
            

        }
        printf("\033[0m\n"); // Réinitialiser la couleur après chaque ligne
    }
    printf("\033[47m\033[31m            SODOKU            \033[0m\n");
    printf("A tout moment vous pouvez obtenir\nde l'aide en entrant -1 ou\nretour en entrant 0 sur value\n");
    printf("Level : %s \n",gameinfo._level);
    printf("Partie: %d \n",gameinfo.partie);
    printf("Points: %d \n",gameinfo.points);
}

bool IsSodoku(int SodokuMatrice[SIZE][SIZE],int ligne, int colone,int element){

    for (int col = 0; col < SIZE; col++){
        if (SodokuMatrice[ligne][col] == element){
            return false;
        }  
    }

    for (int _ligne = 0; _ligne < SIZE; _ligne++){
        if (SodokuMatrice[_ligne][colone] == element){
            return false;
        }
    }

    /*if (ligne == colone){
        for (int i = 0; i < SIZE; i++){
            if (SodokuMatrice[i][i]==element){
                return false;
            }
        }
    }*/
    
    
    int StartLigne = ligne - ligne%3;
    int StartColone = colone - colone%3;

    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++){
            if (SodokuMatrice[i+StartLigne][j+StartColone]== element){
                return false;
            }  
        } 
    }
    return true;
}

bool SodokuSolution(int SodokuMatrice[SIZE][SIZE]){
    int ligne;
    int colone;
    bool IsEmpty = false;

    for (ligne = 0; ligne < SIZE; ligne++){
        for ( colone = 0; colone < SIZE; colone++){
            if (SodokuMatrice[ligne][colone]==0)
            {
                IsEmpty = true;
                break;
            }
        }
        if (IsEmpty){
            break;
        }   
    }

    if (!IsEmpty){
        return true;
    }
    
    for (int element = 1; element <= SIZE; element++){
        if (IsSodoku(SodokuMatrice,ligne,colone,element)){
            SodokuMatrice[ligne][colone] = element;

            if (SodokuSolution(SodokuMatrice)){
                return true;
            }

            SodokuMatrice[ligne][colone] = VIDE;
        }
    }
    return false;


}



void GenerateDagonaleBlocks(int SodokuMatrice[SIZE][SIZE]){
    for (int i = 0; i < SIZE; i+=3){
        for (int element = 1; element <= SIZE; element++){
            do{
                int _ligne = rand()%3 +i;
                int _colone = rand()%3+i;
                if (SodokuMatrice[_ligne][_colone]==0 && IsSodoku(SodokuMatrice,_ligne,_colone,element)){
                    SodokuMatrice[_ligne][_colone] = element;
                    break;
                }
            } while (1);
        }
    }
    SodokuSolution(SodokuMatrice);
}

void grillenonresolu(GameInfo *jeu){  //grillenonresolu(int SodokuMatrice[SIZE][SIZE],LEVEL dificulty){
    //srand(time(NULL));

    int nombre_de_zero=0;
    if (jeu->level==easy)
    {
        //nombre_de_zero = 0.06*SIZE*SIZE;
        nombre_de_zero= 1 + 3*(1-exp(-jeu->partie/3));// 5-30
        /*if (nombre_de_zero >= 29)
        {
            jeu->level= medium;
            jeu->partie = 1;
        }*/
    }
    else if (jeu->level==medium)
    {
        nombre_de_zero =  30+ 20*(1-exp(-jeu->partie/3)); // 30-50
        /*if (nombre_de_zero >= 49)
        {
            jeu->level= difficult;
            jeu->partie = 1;
        }*/
        
    }
    else if (jeu->level==difficult)
    {
        nombre_de_zero =  45 + 15*(1-exp(-jeu->partie/3)); //45-60
    }
    else{
        nombre_de_zero = 0.5*SIZE*SIZE;
    }

    for (int i = 0; i < nombre_de_zero; i++)
    {
        do
        {
            int ligne = rand()% SIZE;
            int col = rand()% SIZE;
            if (jeu->matrice[ligne][col] != VIDE)
            {
                jeu->matrice[ligne][col] = VIDE;
                break;
            }
        } while (1);
        
    }
    
}

bool solution(GameInfo jeu){
    bool issolution = true;
    int element;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            element = jeu.matrice[i][j];
            if (element==0)
            {
                issolution = false;
                break;
            }
        }
        if(!issolution){
            break;
        } 
    }
    if (issolution)
    {
        return true;
    }
    else
    {
        return false;
    }
    

}
void print_generique(char bravo_message[],int index) {
    
    int message_length = strlen(bravo_message);
    
    for (int i = 0; i < message_length; i++) {
        printf("%c", bravo_message[i]);
        Sleep(100);
    }
    if (index==0)
    {
        Sleep(120);
        printf("loading ");
        for (int i = 0; i < 3; i++)
        {
            printf(".");
            Sleep(1500);
        }
        printf("\n");
    }  
}



// file pour le retour 

PIL* createPIL() {
    PIL* pil = (PIL*)malloc(sizeof(PIL));
    if (pil == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire.\n");
        exit(1);
    }
    pil->front = NULL;
    return pil;
}

// Fonction pour vérifier si la file est pleine
int isEmptyPIL(PIL* pil) {
    return (pil->front == NULL);
}



// Fonction pour ajouter un élément à la file (enqueue)
PIL* enPIL(PIL* pil, GameInfo item) {
    Element *New = (Element*)malloc(sizeof(Element));
    New->jeu = item;
    New->next = NULL;

    if (isEmptyPIL(pil))
    {
        pil->front = New;
    }
    else
    {
        Element* current = pil->front;
        New->next = current;
        pil->front = New;
    }
    return pil;   
}

// Fonction pour retirer un élément de la file (dequeue)
PIL* dePIL(PIL* pil,GameInfo *item) {
    Element *front = pil->front;
    *item = front->jeu;
    
    pil->front = front->next;
    //free(front);
    return pil;
}