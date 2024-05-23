#include "header.h"

char **CreationGrille(int ligne, int colonne) {

  // attribution dynamique du tableau de pointeur
  char **tab = NULL;
  tab = calloc(ligne, sizeof(char *));
  if (tab == NULL) {
    exit(1);
  }

  // atribution dynamique des tableau dans le tableau de pointeur
  for (int i = 0; i < ligne; i++) {

    tab[i] = calloc(colonne, sizeof(char));
    if (tab[i] == NULL) {
      exit(1);
    }
  }

  for (int i = 0; i < ligne; i++) {

    for (int j = 0; j < colonne; j++) {

      tab[i][j] = '0';
    }
  }

  return tab;
}

void GenererMur(int *mur1, int *mur2, int debut, int fin) {
  // genere deux murs aléatoirement sur chaque côté et verifier les condition pour le placer
  do {
    *mur1 = rand() % (fin - debut + 1) + debut;
    *mur2 = rand() % (fin - debut + 1) + debut;
    //printf("%d %d\n", *mur1, *mur2);
    //regenere si le murs sont generer sur les cases joueurs ou sont aux meme ccoordonée
  } while (*mur1 % 2 != 0 || *mur2 % 2 != 0 || *mur1 == *mur2);
  //printf("fin\n");
}


void GenererJoueur(int *coor_x, int *coor_y, int longueur, int largeur) {
  //genere un joueur aléatoirement et verifier les condition pour le placer
  do {
    *coor_x = (rand() % longueur) +1;
    *coor_y = (rand() % largeur) +1;
    //printf("%d %d\n", *coor_x, *coor_y);
    //Regenere si les joueurs sont generere sur des cases murs ou on les meme coordonées
  } while (*coor_x % 2 == 0 || *coor_y % 2 == 0);
  //printf("fin\n");
}

void GenererCible(int *coor_x, int *coor_y, int longueur, int largeur) {
  //genere une cible aléatoirement et verifier qu'elle est sur les cases impaires
  do {
    *coor_x = (rand() % longueur)+3;
    *coor_y = (rand() % largeur) + 3;
    //printf("%d %d\n", *coor_x, *coor_y);
  } while (*coor_x % 2 == 0 || *coor_y % 2 == 0);
  //printf("fin\n");
}

void RemplirTab(char **tab, int ligne, int colonne, Joueur joueur_tab[4], Cible cible_tab[18]) {
  // rempli le tableau vierge avec les murs des extremites et les case mur vide
  for (int i = 0; i < ligne; i++) {

    for (int j = 0; j < colonne; j++) {

      if (i % 2 == 0) {

        tab[i][j] = 'I';
      }

      if (j % 2 == 0) {

        tab[i][j] = 'I';
      }

      if (i == 0 || i == ligne - 1) {
        tab[i][j] = 'M';
      }

      if (j == 0 || j == colonne - 1) {
        tab[i][j] = 'M';
      }
    }
  }

  int mur1;
  int mur2;
  //choisire les coordonnées valides pour les murs des cotés
  GenererMur(&mur1, &mur2, 1, colonne - 2);

  // Place 2 murs sur les extremités
  tab[1][mur1] = 'M'; // MUR DU HAUT
  tab[1][mur2] = 'M'; // MUR DU HAUR

  GenererMur(&mur1, &mur2, 1, colonne - 2);
  tab[ligne - 2][mur1] = 'M'; // MUR DU BAS
  tab[ligne - 2][mur2] = 'M'; // MUR DU BAS

  GenererMur(&mur1, &mur2, 1, ligne - 2);
  tab[mur1][1] = 'M'; // MUR GAUCHE
  tab[mur2][1] = 'M'; // MUR GAUCHE

  GenererMur(&mur1, &mur2, 1, ligne - 2);
  tab[mur1][colonne - 2] = 'M'; // MUR DROITE
  tab[mur2][colonne - 2] = 'M'; // MUR DROITE


  Joueur joueur_liste[4];

  int coor_x;
  int coor_y;

  //GENERER 4 ROBOTS ET LEUR POSITIONS
  for (int i = 0; i < 4; i++) {

    do {
      GenererJoueur(&coor_x, &coor_y, ligne - 2, colonne - 2);
    } while (tab[coor_x][coor_y] >= 49 && tab[coor_x][coor_y] <= 52);
    // regenerer robot tant que la case est déja occupé par autre un robot 
    tab[coor_x][coor_y] = 49+i;
      joueur_liste[i].coor.coor_x = coor_x;
      joueur_liste[i].coor.coor_y = coor_y;
      joueur_liste[i].num = 49+i;

  }

  Cible cible_liste[18];

  //GENERE 18 CIBLES lettre de a jusqu'a r
  for (int i = 0; i < 18; i++){

    do {
      GenererCible(&coor_x, &coor_y, ligne - 5, colonne - 5);
    } while 
      (
      (tab[coor_x][coor_y] >= 97 && tab[coor_x][coor_y] <= 122)
      || ((tab[coor_x][coor_y] >=49 && tab[coor_x][coor_y] <= 52)
      //regenere cible tant que cible est pas sur cible ou robot ou cible a cote d une autre cible
      // diagonale en bas a droite
      || (tab[coor_x + 2][coor_y + 2] >= 97 && tab[coor_x + 2][coor_y + 2] <= 122)
      // en bas
      || (tab[coor_x + 2][coor_y] >= 97 && tab[coor_x + 2][coor_y] <= 122)
      // en bas a gauche
      || (tab[coor_x + 2][coor_y -2] >= 97 && tab[coor_x + 2][coor_y - 2] <= 122)
      // diagonale en haut a gauche
      || (tab[coor_x - 2][coor_y - 2] >= 97 && tab[coor_x - 2][coor_y - 2] <= 122)
      // a gauche
      || (tab[coor_x][coor_y - 2] >= 97 && tab[coor_x][coor_y - 2] <= 122)
      //en haut
      || (tab[coor_x - 2 ][coor_y] >= 97 && tab[coor_x - 2][coor_y] <= 122)
      // en haut a droite
      || (tab[coor_x-2 ][coor_y +2] >= 97 && tab[coor_x - 2][coor_y + 2] <= 122)
      //a droite 
      || (tab[coor_x][coor_y +2] >= 97 && tab[coor_x][coor_y + 2] <= 122)
      ));

      //ecrit dans le tableau de jeu la cible
      tab[coor_x][coor_y] = 97+i;

    //ajoute ses coordonées et son caractère dans le tableau d'info des cible
      cible_liste[i].coor.coor_x = coor_x;
      cible_liste[i].coor.coor_y = coor_y;
      cible_liste[i].num = 97+i;

    // choisis un coté random pour générer les murs autour de la cible
    int random = rand() % 4;
    // placer les 3 murs autour des cibles 
    switch (random) {
      case 0 :
        //en haut a gauche
        tab[coor_x - 1][coor_y] = 'M';
        tab[coor_x][coor_y - 1] = 'M';
        tab[coor_x -1][coor_y - 1] = 'M';
      break;
      case 1 :
      //en haut a droite
      tab[coor_x - 1][coor_y] = 'M';
      tab[coor_x][coor_y + 1] = 'M';
      tab[coor_x -1][coor_y + 1] = 'M';
      break;
      case 2 :
      // en bas a droite
        tab[coor_x + 1][coor_y] = 'M';
        tab[coor_x][coor_y + 1] = 'M';
        tab[coor_x +1][coor_y + 1] = 'M';
      break;
      case 3:
      //en bas a gauche
        tab[coor_x + 1][coor_y] = 'M';
        tab[coor_x][coor_y - 1] = 'M';
        tab[coor_x + 1][coor_y - 1] = 'M';
      break;

    }


  }

  //afecte les valeurs des tableaux locaux aux tableaux en paramètre pour pouvoir les utiliser dans le main
  for (int i = 0; i < 4; i++) {
    joueur_tab[i] = joueur_liste[i];

  } 

  for (int i = 0; i < 18; i++) {
    cible_tab[i] = cible_liste[i];

  } 


}


