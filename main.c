#include "header.h"

int main(){
    
    
    srand(time(NULL));
    char *folderName = "sodoku_doc";
    create(folderName);

    
    
    int SodokuMatrice[SIZE][SIZE]={VIDE};
    int SodokuMatriceresolue[SIZE][SIZE]={VIDE};

    //lance le jeu
    //system("cls");//update
    //print_generique("Bienvenue dans le jeu de sudoku developpe dans le cadre du projet tutore Ing1 Info!\n",0);
    //system("cls");

    run(SodokuMatrice,folderName);

    return 0 ;
}