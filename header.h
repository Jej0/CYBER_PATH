#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<unistd.h>
#include <termios.h>

//tester sur windows #include<windows.h>


#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define NOMBRE_TOUR 5
// #define DEBUG

typedef struct {
  int coor_x;
  int coor_y;
} Coor;

typedef struct {
  //num du joueur 1 2 3 4
  int num;
  Coor coor;
} Joueur;

typedef struct {
  int num;
  Coor coor;
} Cible;


char **CreationGrille(int ligne, int colonne);

void RemplirTab(char **tab, int ligne, int colonne, Joueur joueur_tab[4], Cible cible_tab[18]);