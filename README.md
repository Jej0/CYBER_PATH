# Cyber Path: Procedural Tactical Engine

[English Version](#english-version) | [Version Française](#version-française)

---

<a name="english-version"></a>
### Cyber Path: Procedural Tactical Engine

Cyber Path is a terminal based puzzle game featuring a procedural engine where robots must navigate a grid to reach targets. The core challenge lies in the sliding physics. Robots move in a straight line until they hit an obstacle like a wall or another robot.

### How to compile and execute the game

Ensure you have a C compiler gcc and make installed on your system.

### Optional Step

Installer make et gcc: 'apt install gcc' 'apt install make':

### Step 1 Download

Download the complete source files from the GitHub repository.

### Step 2 Compilation

Use the provided Makefile to compile the source files.
Command: make exec

### Step 3 Execution

Execute the generated binary to start the game.
Command: ./exec

Note: This project is optimized for Unix based systems to handle terminal rendering correctly.

### How does it work

The engine is built on two main pillars.

1 Procedural Generation gen.c: The game dynamically creates a balanced grid ensuring targets and obstacles are placed to allow solvable but challenging puzzles.
2 Game Logic main.c: Implements a structured game loop that manages real time player input collision detection and score tracking.

The project utilizes dynamic memory allocation for the grid system ensuring a scalable environment size while maintaining a low memory footprint.

### Technical Stack

Programming Language: C.
Architecture: Modular design with a dedicated header system.
Tools: GCC, Make, Git.

### Authors

Lucien Boyer
Axel Atagan
Adou Humblot

---

<a name="version-française"></a>
# CYBER_PATH

Jeu Cyber Path réalisé pour le projet d'informatique de fin de Pré-ing1. Le but est de déplacer des robots pour rejoindre une cible définie aléatoirement en un minimum de mouvements. Les robots glissent ils ne s'arrêtent que lorsqu'ils rencontrent un obstacle.

### Comment faire pour que le programme compile et qu'il s'exécute

### Etape Facultative

Installer make et gcc: 'apt install gcc' 'apt install make':

### Etape 1 Téléchargement

Téléchargez l'intégralité des fichiers sources depuis le dépôt GitHub.

### Etape 2 Compilation

Sous Linux ouvrez un terminal dans le répertoire du projet et entrez la commande: make exec.

### Etape 3 Lancement du jeu

Lancez l'exécutable généré avec la commande suivante: ./exec.

### Comment ça fonctionne

Le jeu repose sur un moteur procédural développé en C qui génère une grille de jeu différente à chaque partie.

1 Génération gen.c: Le programme alloue dynamiquement la mémoire pour la grille et place intelligemment les murs les joueurs et les cibles pour garantir la jouabilité.
2 Logique de Jeu main.c: Gère les tours le calcul des points et les collisions. Un mouvement n'est comptabilisé que si le robot parcourt une distance en ligne droite jusqu'à un obstacle.

### Ce que l'on a utilisé

Langage : C.
Bibliothèques : stdio.h, stdlib.h, string.h, time.h, unistd.h, termios.h.
Outils : Makefile pour l'automatisation de la compilation.

### Auteurs

Lucien Boyer
Axel Atagan
Adou Humblot
