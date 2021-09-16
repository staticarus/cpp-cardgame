#pragma once

//Constantes utilisées dans le projet, celles-ci servent a minimiser les valeurs a changer dans le programme

#define DECK_SIZE 56    //permet de "remplacer" toutes les mentions "DECK_SIZE" par 56 lors de la compilation
#define HAND_SIZE 7     //permet de "remplacer" toutes les mentions "HAND_SIZE" par 7 lors de la compilation
#define PLAYER_AMOUNT 4 //permet de "remplacer" toutes les mentions "PLAYER_AMOUNT" par 4 lors de la compilation
#define NB_CARD 14      //permet de "remplacer" toutes les mentions "NB_CARD" par 14 lors de la compilation
#define NB_SYMBOL 4     //permet de "remplacer" toutes les mentions "NB_SYMBOl" par 4 lors de la compilation
#define WIN_SCORE 500    //permet de "remplacer" toutes les mentions "WIN_SCORE" par 500 lors de la compilation

// Permet l'affichage de couleurs dans la console

#define RESET_COLOR   "\033[0m" // Reset la couleur
#define ROUGE     "\033[1m\033[31m"  //Rouge
#define BLUE "\033[1m\033[34m" //Bleu utilisé  à la place du noir pour s'afficher correctement sur un fond noir