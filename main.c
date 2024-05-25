#include "header.h"


void nettoyerCache() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
}

void libererTableau2D(char **tab, int ligne) {
    // Libérer chaque ligne du tableau
    for (int i = 0; i < ligne; i++) {
        free(tab[i]);
    }
    // Libérer le tableau de pointeurs
    free(tab);
}

void intialisationJeu(int *difficulte, int* nbr_joueur) {
  *difficulte = -1;
  *nbr_joueur = -1;

  int test;
  do {
    printf("Entrez le nombre de joueurs: ");

    test = scanf("%d", nbr_joueur);
    //printf(",entrer %d\n", *nbr_joueur);
    if (*nbr_joueur <= 1 || test != 1) {
      printf("entrer un nombre supérieur à 1\n");
      nettoyerCache();
    }
// si tout se passe bien retourne 1 sinon retourne 0 donc recommence la boucle
  } while (*nbr_joueur <= 1 || test != 1);

  nettoyerCache();



  do {
    printf("Entrez difficulté entre 1 et 4 (1 : 2 mintues, 2 : 1 minutes, 3 : 30 secondes , 4 : 15 secondes): ");

    test = scanf("%d", difficulte);

    if (*difficulte < 1 || *difficulte > 4 || test != 1) {
      printf("entrez un nombre supérieur à 1 et inférieur à 4 (1 : 2 mintues, 2 : 1 minutes, 3 : 30 secondes , 4 : 15 secondes)\n");
      nettoyerCache();
    }
    // si tout se passe bien retourne 1 sinon retourne 0 donc recommence la boucle
  } while (*difficulte < 1 || *difficulte > 4 || test != 1);

  nettoyerCache();

}

void choisirJoueurCible(Joueur* tabJoueur, Cible* tabCible, int *joueur_aleatoire, int* cible_aleatoire) {

  *joueur_aleatoire = rand() % 4;
  //robots aleatoire entre 0 et 4 = 4 robots
  *cible_aleatoire = rand() % 18;
  //cible aleatoire entre 0 et 17 = 18 cibles

}


void AfficheTab(char **tab, int ligne, int colonne, char joueur, char cible, int compteur) {
  printf("TOUR %d/%d\n\n", compteur, NOMBRE_TOUR);
  for (int i = 0; i < ligne; i++) {

    for (int j = 0; j < colonne; j++) {

      switch (tab[i][j]) {
        case '0':
          printf("* ");
          break;
        case 'I':
          printf("  ");
          break;
        default:
          if (tab[i][j] == joueur) {
            printf(ANSI_COLOR_RED "%c " ANSI_COLOR_RESET, tab[i][j]);
            //mettre en couleur rouge le robot et le joueur de cette manche
          } else if (tab[i][j] == cible) {
            printf(ANSI_COLOR_GREEN "%c " ANSI_COLOR_RESET, tab[i][j]);
            //mettre en couleur vert la cible de cette manche
          } else {
            printf("%c ", tab[i][j]);

          }

      }
    }
    printf("\n");
  }
}

void DeplacerRobot(char** tab, Joueur joueur_tab[], int robot, char mouvement, int ligne, int colonne, char *cache, Cible cible_tab[],int *compteur_chemin ) {
  //printf("test mov %c", mouvement);
  //97 -> 114
// 4 cas possibles : haut, bas, gauche, droite = z q s d
  switch (mouvement) {
    case 'q':

      if (tab[joueur_tab[robot].coor.coor_x][joueur_tab[robot].coor.coor_y-1] == 'M' ||
        (tab[joueur_tab[robot].coor.coor_x][joueur_tab[robot].coor.coor_y-2] >= 49 &&
        tab[joueur_tab[robot].coor.coor_x][joueur_tab[robot].coor.coor_y-2] <= 52))// robot/joueur de cette manche peut pas aller sur un mur et un autre joueur
      {
        printf("Vous ne pouvez pas aller dans cette direction\n");
        break;
        }

// cache position stock element dans un tableau qui stock la structure des donnee de la cible
      if (*cache >= 0) {
        tab[joueur_tab[robot].coor.coor_x][joueur_tab[robot].coor.coor_y] = cible_tab[*cache].num;
        *cache = -1;
      } else {
        tab[joueur_tab[robot].coor.coor_x][joueur_tab[robot].coor.coor_y] = '0';
      }

      //printf("q=gauche\n");
      //boucle sur toute les cases dans la direction voulu
      for (int i = joueur_tab[robot].coor.coor_y-1; i >= 0; i--) {

        //cherche un Mur sur une case mur
        if (tab[joueur_tab[robot].coor.coor_x][i] == 'M') {
          

          // if (joueur_tab[robot].coor.coor_y == i+1) {
          //   break;  
          // }
        // si il rencontre un mur il va a la case "*"juste après i+1
          
          if (*compteur_chemin < 0) {
            printf("vous avez fais trop de déplacment\n");
            break;
          } else {
            *compteur_chemin -=1;
          }


          if (tab[joueur_tab[robot].coor.coor_x][i+1] != '0') {
            *cache = tab[joueur_tab[robot].coor.coor_x][i+1]-97;
            // si coordonne ou robot vas different de 0 alors on met le robot dans la case de la cible, cache = position du robot a la place de la cible -97 car ASCI = cible
          }

          tab[joueur_tab[robot].coor.coor_x][i+1] = joueur_tab[robot].num;
          // tab[joueur_tab[robot].coor.coor_x][joueur_tab[robot].coor.coor_y] = '0';
            joueur_tab[robot].coor.coor_y = i+1;
            break;

          if (*compteur_chemin < 0) {
            printf("vous avez fais trop de déplacment\n");
            break;
          } else {
            *compteur_chemin -=1;
          }


        } else if (tab[joueur_tab[robot].coor.coor_x][i] > 48 && tab[joueur_tab[robot].coor.coor_x][i] < 53) {
          // if (joueur_tab[robot].coor.coor_y == i+2) {
          //   break;
          // }
// si robot rencontre un joueur il va a la case "*" juste après = i+2
          
          if (*compteur_chemin < 0) {
            printf("vous avez fais trop de déplacment\n");
            break;
          } else {
            *compteur_chemin -= 1;
          }
          //reduit de 1 chaque deplacement restants

          if (tab[joueur_tab[robot].coor.coor_x][i+2] != '0') {
            *cache = tab[joueur_tab[robot].coor.coor_x][i+2]-97;
            // si coordonne ou robot vas different de 0 alors on met le robot dans la case de la cible, cache = position du robot a la place de la cible -97 car ASCI = cible
          } else {
            *cache = -1;
          }
          tab[joueur_tab[robot].coor.coor_x][i+2] = joueur_tab[robot].num;


            // tab[joueur_tab[robot].coor.coor_x][joueur_tab[robot].coor.coor_y] = '0';

            joueur_tab[robot].coor.coor_y = i+2;
          break;
        }
      }
    break;

    case 'd':


      if (tab[joueur_tab[robot].coor.coor_x][joueur_tab[robot].coor.coor_y+1] == 'M' ||
        (tab[joueur_tab[robot].coor.coor_x][joueur_tab[robot].coor.coor_y+2] >= 49 &&
        tab[joueur_tab[robot].coor.coor_x][joueur_tab[robot].coor.coor_y+2] <= 52))  // // robot/joueur de cette manche peut pas aller sur un mur et un autre joueur
      {
        printf("Vous ne pouvez pas aller dans cette direction\n");
        break;
        }

      if (*cache >= 0) {
        // tab[cible_tab[*cache].coor.coor_x][cible_tab[*cache].coor.coor_y] = cible_tab[*cache].num;
        tab[joueur_tab[robot].coor.coor_x][joueur_tab[robot].coor.coor_y] = cible_tab[*cache].num;
        *cache = -1;
      } else {
        tab[joueur_tab[robot].coor.coor_x][joueur_tab[robot].coor.coor_y] = '0';
      }

      //printf("d=droite\n");
      for (int i = joueur_tab[robot].coor.coor_y+1; i <= colonne-1; i++) {

        if (tab[joueur_tab[robot].coor.coor_x][i] == 'M') {

          //if( joueur_tab[robot].coor.coor_y == i-1) {
            //break;
          //}
          // si il rencontre un mur il va a la case "*"juste avant i-1
          if (*compteur_chemin < 0) {
            printf("vous avez fais trop de déplacment\n");
            break;
          } else {
            *compteur_chemin -=1;
          }

          if (tab[joueur_tab[robot].coor.coor_x][i-1] != '0') {
            *cache = tab[joueur_tab[robot].coor.coor_x][i-1]-97;
          }
          // si coordonne ou robot vas different de 0 alors on met le robot dans la case de la cible, cache = position du robot a la place de la cible -97 car ASCI = cible
          

          tab[joueur_tab[robot].coor.coor_x][i-1] = joueur_tab[robot].num;
          // tab[joueur_tab[robot].coor.coor_x][joueur_tab[robot].coor.coor_y] = '0';
            joueur_tab[robot].coor.coor_y = i-1;
            break;

        } else if (tab[joueur_tab[robot].coor.coor_x][i] > 48 && tab[joueur_tab[robot].coor.coor_x][i] < 53) {
          //if (joueur_tab[robot].coor.coor_y == i-2) {
            //break;
          //}
          // si robot rencontre un joueur il va a la case "*" juste avant = i-2

          if (*compteur_chemin < 0) {
            printf("vous avez fais trop de déplacment\n");
            break;
          } else {
            *compteur_chemin -=1;
          }

          if (tab[joueur_tab[robot].coor.coor_x][i-2] != '0') {
            *cache = tab[joueur_tab[robot].coor.coor_x][i-2]-97;
             // si coordonne ou robot vas different de 0 alors on met le robot dans la case de la cible, cache = position du robot a la place de la cible -97 car ASCI = cible
          }
          tab[joueur_tab[robot].coor.coor_x][i-2] = joueur_tab[robot].num;
          // tab[joueur_tab[robot].coor.coor_x][joueur_tab[robot].coor.coor_y] = '0';
            joueur_tab[robot].coor.coor_y = i-2;
          break;
        }
      }
    break;

    case 'z':

      if (tab[joueur_tab[robot].coor.coor_x-1][joueur_tab[robot].coor.coor_y] == 'M' ||
        (tab[joueur_tab[robot].coor.coor_x-2][joueur_tab[robot].coor.coor_y] >= 49 &&
        tab[joueur_tab[robot].coor.coor_x-2][joueur_tab[robot].coor.coor_y] <= 52))// robot/joueur de cette manche peut pas aller sur un mur et un autre joueur 
      {
        printf("Vous ne pouvez pas aller dans cette direction\n");
        break;
        }

      if (*cache >= 0) {
        // tab[cible_tab[*cache].coor.coor_x][cible_tab[*cache].coor.coor_y] = cible_tab[*cache].num;

        tab[joueur_tab[robot].coor.coor_x][joueur_tab[robot].coor.coor_y] = cible_tab[*cache].num;

        *cache = -1;
      } else {
        tab[joueur_tab[robot].coor.coor_x][joueur_tab[robot].coor.coor_y] = '0';
      }
      //printf("z=haut\n");

      for (int i = joueur_tab[robot].coor.coor_x-1; i >= 0; i--) {

        if (tab[i][joueur_tab[robot].coor.coor_y] == 'M') {

          //if( joueur_tab[robot].coor.coor_x == i+1) {
            //break;
          //}
          // si il rencontre un mur il va a la case "*"juste après i+1


          if (*compteur_chemin < 0) {
            printf("vous avez fais trop de déplacment\n");
            break;
          } else {
            *compteur_chemin -=1;
          }

          if (tab[i+1][joueur_tab[robot].coor.coor_y] != '0') {
            *cache = tab[i+1][joueur_tab[robot].coor.coor_y]-97;
             // si coordonne ou robot vas different de 0 alors on met le robot dans la case de la cible, cache = position du robot a la place de la cible -97 car ASCI = cible
          }

          tab[i+1][joueur_tab[robot].coor.coor_y] = joueur_tab[robot].num;
          // tab[joueur_tab[robot].coor.coor_x][joueur_tab[robot].coor.coor_y] = '0';
            joueur_tab[robot].coor.coor_x = i+1;
            break;

        } else if (tab[i][joueur_tab[robot].coor.coor_y]> 48 && tab[i][joueur_tab[robot].coor.coor_y] < 53) {
          //if (joueur_tab[robot].coor.coor_y == i+2) {
          //break;
        //}
          // si robot rencontre un joueur il va a la case "*" juste après = i+2

          if (*compteur_chemin < 0) {
            printf("vous avez fais trop de déplacment\n");
            break;
          } else {
            *compteur_chemin -=1;
          }



          if (tab[i+2][joueur_tab[robot].coor.coor_y] != '0') {
            *cache = tab[i+2][joueur_tab[robot].coor.coor_y]-97;
          }
            tab[i+2][joueur_tab[robot].coor.coor_y] = joueur_tab[robot].num;
          // tab[joueur_tab[robot].coor.coor_x][joueur_tab[robot].coor.coor_y] = '0';
            joueur_tab[robot].coor.coor_x = i+2;
          break;
        }
      }
    break;

    case 's':

      if (tab[joueur_tab[robot].coor.coor_x+1][joueur_tab[robot].coor.coor_y] == 'M' ||
        (tab[joueur_tab[robot].coor.coor_x+2][joueur_tab[robot].coor.coor_y] >= 49 &&
        tab[joueur_tab[robot].coor.coor_x+2][joueur_tab[robot].coor.coor_y] <= 52))// robot/joueur de cette manche peut pas aller sur un mur et un autre joueur 
      {
        printf("Vous ne pouvez pas aller dans cette direction\n");
        break;
        }

      if (*cache >= 0) {
        // tab[cible_tab[*cache].coor.coor_x][cible_tab[*cache].coor.coor_y] = cible_tab[*cache].num;
        tab[joueur_tab[robot].coor.coor_x][joueur_tab[robot].coor.coor_y] = cible_tab[*cache].num;
        *cache = -1;
      } else {
        tab[joueur_tab[robot].coor.coor_x][joueur_tab[robot].coor.coor_y] = '0';
      }
      //printf("s=bas\n");

      for (int i = joueur_tab[robot].coor.coor_x+1; i <= ligne-1; i++) {

        if (tab[i][joueur_tab[robot].coor.coor_y] == 'M') {

          //if( joueur_tab[robot].coor.coor_x == i-1) {
          //break;
        //}
          // si il rencontre un mur il va a la case "*"juste avant i-1

          if (*compteur_chemin < 0) {
            printf("vous avez fais trop de déplacment\n");
            break;
          } else {
            *compteur_chemin -=1;
          }

          if (tab[i-1][joueur_tab[robot].coor.coor_y] != '0') {
            *cache = tab[i-1][joueur_tab[robot].coor.coor_y]-97;
             // si coordonne ou robot vas different de 0 alors on met le robot dans la case de la cible, cache = position du robot a la place de la cible -97 car ASCI = cible
          }

          tab[i-1][joueur_tab[robot].coor.coor_y] = joueur_tab[robot].num;

            joueur_tab[robot].coor.coor_x = i-1;
            break;

        } else if (tab[i][joueur_tab[robot].coor.coor_y]> 48 && tab[i][joueur_tab[robot].coor.coor_y] < 53) {
          //if (joueur_tab[robot].coor.coor_y == i-2) {
          //break;
        //}
          // si robot rencontre un joueur il va a la case "*" juste avant = i-2

          if (*compteur_chemin < 0) {
            printf("vous avez fais trop de déplacment\n");
            break;
          } else {
            *compteur_chemin -=1;
          }


          if (tab[i-2][joueur_tab[robot].coor.coor_y] != '0') {
            *cache = tab[i-2][joueur_tab[robot].coor.coor_y]-97;
             // si coordonne ou robot vas different de 0 alors on met le robot dans la case de la cible, cache = position du robot a la place de la cible -97 car ASCI = cible
          }
            tab[i-2][joueur_tab[robot].coor.coor_y] = joueur_tab[robot].num;
          // tab[joueur_tab[robot].coor.coor_x][joueur_tab[robot].coor.coor_y] = '0';
            joueur_tab[robot].coor.coor_x = i-2;
          break;
        }
      }
    break;
  }


}


void AfficherPoint(int liste_point[], int nbr_joueur) {

  for (int i = 0; i < nbr_joueur; i++) {
    printf(" Joueur %d : %d point\n", i+1, liste_point[i]);
  }
}

void DeroulementPartie(int difficulte, int  temps, int nbr_joueur, char** tab, Joueur* joueur_tab, Cible cible_tab[18], int ligne, int colonne, int liste_vrai_joueur[],int liste_point_joueur[], int compteur) {

  //system("clear");
  
    //Declaration variable aléatoire
  int joueur_aleatoire;
  int cible_aleatoire;
  
    //choisir une cible seulement si il n'y a pas de joueur dessus
  do {choisirJoueurCible(joueur_tab, cible_tab, &joueur_aleatoire, &cible_aleatoire);
     } while (tab[cible_tab[cible_aleatoire].coor.coor_x][cible_tab[cible_aleatoire].coor.coor_y] > 48 &&
            tab[cible_tab[cible_aleatoire].coor.coor_x][cible_tab[cible_aleatoire].coor.coor_y] < 53);
  
  
    printf("Le robot est : %c\nLa cible est %c\n", joueur_tab[joueur_aleatoire].num, cible_tab[cible_aleatoire].num);
  printf("Vous avez %d secondes ( difficulté %d)\n", temps, difficulte);
  AfficheTab(tab, ligne, colonne, joueur_tab[joueur_aleatoire].num, cible_tab[cible_aleatoire].num, compteur);
  
  sleep(temps);
  //met le programme en pause pendant la duree n=temps
  
  tcflush(STDIN_FILENO, TCIFLUSH);
    //tcflush = efface donne non transmise et donne non lu,
    //STDIN_FILENO : Lire le fichier buffer entree et STDOUT_FILENO : Lire le fichier buffer sortie TCIFLUSH:effacer tout le buffer entree recu pas lu
  system("clear");
  // cacher tout le jeu 
  
  
  //boucle pour entrer le déplacement des chaques joueurs
  for(int i =1; i<nbr_joueur+1;i++) {

    int test;
    do {
      printf("joueur N°%d, entrez le nombre de déplacements necessaire pour arriver au robot:\n", i);


      test = scanf("%d", &liste_vrai_joueur[i-1]);
      if (liste_vrai_joueur[i-1] <= 0 || test != 1) {
        printf("Nombre de déplacement invalide, recommencez\n");
        nettoyerCache();

      }

    } while (liste_vrai_joueur[i-1] <= 0 || test != 1);

    nettoyerCache();

  }

  // for(int i = 0; i< nbr_joueur; i++) {
  //   printf("%d\n",liste_vrai_joueur[i]);
  // }

  //cherche le joueur qui a mit le plus petit déplacements dans la liste 
  int plus_petit_joueur = 0;
  int plus_petit = liste_vrai_joueur[plus_petit_joueur];
  for(int i = 1; i<nbr_joueur; i++){
    if (plus_petit > liste_vrai_joueur[i]) {
      plus_petit = liste_vrai_joueur[i];
      plus_petit_joueur = i;
    }
  }

  int plus_petit_chemin = liste_vrai_joueur[plus_petit_joueur];
// initialise plus petit chemin = plus petit nombre de déplacement du joueur plus petit
  printf("plus petit chemin est en %d deplacement\n", plus_petit);

  AfficheTab(tab, ligne, colonne, joueur_tab[joueur_aleatoire].num, cible_tab[cible_aleatoire].num, compteur);

  printf("Joueur N°%d, tracer le chemin que vous avez trouvé pour atteindre la cible (haut : z, droite : d, bas : s, gauche : q) \n", plus_petit_joueur+1);

  //déclare les variables
  char mouvement;
  char cache = -1;


  //lance la boucle de la partie
  while(1) {

    int test;
    do {
      printf("Entrez votre déplacement :\n");
      test = scanf("%c", &mouvement);

      if ((mouvement != 'z' && mouvement != 'q' && mouvement != 's' && mouvement != 'd') || test != 1) {
printf("Mauvais déplacment\n");
        // peut pas faire autre mouvement que z q s d
        nettoyerCache();
        
      }
    } while((mouvement != 'z' && mouvement != 'q' && mouvement != 's' && mouvement != 'd') || test != 1);
    // peut pas faire autre mouvement que z q s d

    nettoyerCache();

    DeplacerRobot(tab, joueur_tab ,joueur_aleatoire , mouvement, ligne, colonne, &cache, cible_tab, &plus_petit_chemin);

    //si le cache est égale à la cible a atteindre 
    if (cache+97 == cible_tab[cible_aleatoire].num) {

      if(plus_petit_chemin == 0) {
        printf("Vous avez atteint la cible avec le nombre de mouvement que vous avez indiquez, vous gagnez 2 points !\n");
        liste_point_joueur[plus_petit_joueur] += 2;
        // arrive a la cible avec le nombre de deplacement dit => +2 points au joueur 
        AfficherPoint(liste_point_joueur, nbr_joueur);
        break;
      } else if (plus_petit_chemin > 0){
          liste_point_joueur[plus_petit_joueur] -= 1;
        printf("Vous avez atteint la cible mais il vous reste des mouvements non utilisé ! Vous perdez 1 point !\n");
        // arrive a la cible avant le nombre de deplacement dit => -1 point au joueur
        AfficherPoint(liste_point_joueur,  nbr_joueur);
        break;
      }
      //si la cible n'est pas atteinte
    } else if (plus_petit_chemin <= 0) {
      //ajoute 1 points a tout les joueurs
      for (int i =0; i<nbr_joueur; i++) {
        if (i != plus_petit_joueur) {
          liste_point_joueur[i] +=1;
        }
      }
        printf("Vous n'avez pas atteint la cible ! Tout les autres joueurs gagnent 1 point !\n");
        break;
      //AfficherPoint(liste_point_joueur, nbr_joueur);
    }

    AfficheTab(tab, ligne, colonne, joueur_tab[joueur_aleatoire].num, cible_tab[cible_aleatoire].num, compteur);
    printf("DEPLACEMENT RESTANT : %d\n", plus_petit_chemin);
  }


}

int main() {

  srand(time(NULL));

  //CRETION TABLEAU
  // taille de tableau généré aléatoirement entre 15 et 20 pour lignes et
  // colones et ligne entre 15 et 20
  int ligne = (rand() % 6) + 15;
  int colonne = (rand() % 6) + 15;

  ligne = ligne * 2 + 1;
  colonne = colonne * 2 + 1;
  // nombre de côtés du tableau * 2 + 1 car cela compte egalement la ou le joueur peut aller = case mais aussi les murs = des espaces donc 2 fois plus de cotés + 1 
  
  char **tab;
  tab = CreationGrille(ligne, colonne);

  Joueur joueur_tab[4];
  Cible cible_tab[18];
  // tableau de 4 element = 4 joueurs
  // tableau de 18 element = 18 robots
  RemplirTab(tab, ligne, colonne, joueur_tab, cible_tab);



//printf("info %d\n",joueur_tab[2].coor.coor_x);

  // LANCER LE JEU
  int difficulte;
  int nbr_joueur;
  int temps;



  intialisationJeu( &difficulte, &nbr_joueur);

  switch (difficulte) {
    case 1:
    temps = 120;
    break;
    case 2:
    temps = 60;
    break;
    case 3:
    temps = 30;
    break;
    case 4:
    temps = 15;
    break;
  }
// choix entre 2min, 1min, 30s, 15s

  //Déclaration
  int liste_vrai_joueur[nbr_joueur];
  int liste_point_joueur[nbr_joueur];
  for (int i = 0; i<nbr_joueur; i++) {
    liste_point_joueur[i] = 0;
  }
  int compteur = 1;

  //boucle qui tourne jusqu'a un certain nombre de tour
  while(compteur <= NOMBRE_TOUR) {
  DeroulementPartie(difficulte, temps, nbr_joueur, tab, joueur_tab, cible_tab, ligne, colonne, liste_vrai_joueur, liste_point_joueur, compteur);
    compteur += 1;

    printf("Prochain tour dans 5 seconde\n");
      sleep(5);
    tcflush(STDIN_FILENO, TCIFLUSH);
    //tcflush = efface donne non transmise et donne non lu,
    //STDIN_FILENO : Lire le fichier buffer entree et STDOUT_FILENO : Lire le fichier buffer sortie TCIFLUSH:effacer tout le buffer entree recu pas lu
      system("clear"); //efface ce qu'il ya d'afficher sur le terminal
  }


  //une fois tout les tours fait, afficher les points et désigner le gagnant
  AfficherPoint( liste_point_joueur, nbr_joueur);


  //chercher le joueur avec le plus de point dans la liste des points des joueurs
  int joueur_gagnant = 0;
  int max_point = liste_point_joueur[joueur_gagnant];
  for (int i = 1; i<nbr_joueur; i++) {
    if (liste_point_joueur[i] > max_point) {
      max_point = liste_point_joueur[i];
      joueur_gagnant = i;
    }
  }

  printf("Le gagnant est le joueur %d avec %d points\n", joueur_gagnant+1, max_point);
// NEW
  libererTableau2D(tab, ligne);

}
