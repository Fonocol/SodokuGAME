#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <windows.h> 
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

//le répertoire de travail actuel.
#ifdef _WIN32
#include <direct.h>
#define GetCurrentDir(buffer, drive, length) getcwd(buffer, length)
#else
#include <unistd.h>
#define GetCurrentDir getdcwd
#endif

#define VIDE 0
#define SIZE 9
#define POINT 5

typedef enum LEVEL{
    easy,
    medium,
    difficult,
}LEVEL;
    
typedef struct GameInfo{
    int id;
    char name[50];
    char _level[10];
    char mail[50];
    char ville[15];
    char pays[15];
    int age;
    int matrice[SIZE][SIZE];
    int partie;
    int points;
    LEVEL level;
    int record;
    // Ajoutez d'autres informations spécifiques à la partie ici
} GameInfo;

typedef struct Element {
    GameInfo jeu;
    struct Element *next;
}Element;

typedef struct PIL {
    Element *front;
}PIL;


void PrintSodoku(GameInfo gameInfo);
bool IsSodoku(int SodokuMatrice[SIZE][SIZE],int ligne, int colone,int element);
bool SodokuSolution(int SodokuMatrice[SIZE][SIZE]);
bool solution(GameInfo jeu);
void GenerateDagonaleBlocks(int SodokuMatrice[SIZE][SIZE]);
void grillenonresolu(GameInfo *jeu);
void print_generique(char bravo_message[],int index);


// Fonction pour créer une nouvelle pile
PIL* createPIL();
// Fonction pour vérifier si la pile est vide
int isEmptyPIL(PIL* pil);
// Fonction pour ajouter un élément à la pile 
PIL* enPIL(PIL* pil, GameInfo item);
// Fonction pour retirer un élément de la pile 
PIL* dePIL(PIL* pil,GameInfo *item);

void tovide(int SodokuMatrice[SIZE][SIZE]);
void printMatrix(int matrice[SIZE][SIZE]);
void afficher_en_Damier(GameInfo gameinfo,int line,int col,int val);
void create(char *folderName);
int id_in_data();
void saveGameInfo(const char *folderPath, const GameInfo *gameInfo,int SodokuMatrice[SIZE][SIZE]);
int loadGameInfo(const char *folderPath, const char *gameName, GameInfo *gameInfo,int SodokuMatrice[SIZE][SIZE]);
void game(GameInfo jeu,int SodokuMatrice[SIZE][SIZE]);
void game_free(GameInfo jeu,int SodokuMatrice[SIZE][SIZE]);
void run(int sodokumatrice[SIZE][SIZE],char *folderName);