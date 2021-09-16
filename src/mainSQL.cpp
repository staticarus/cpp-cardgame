
/* CE PROGRAMME SERT UNIQUEMENT A LANCER LES REQUETES SQL POUR L'ETAPE 10, 
IL NE GERE PAS DU TOUT LE JEU */

#include <iostream>
#include "./Controller/DatabaseController.hpp"
#include "./sqlite3/sqlite3.h"
#include "./View/View.hpp"
using namespace std;

int main() {
    DatabaseController DBCtrl;  // Contrôleur de la DB
    View::DisplayLine();
    DBCtrl.SqlQueryScores();    // Requête scores croissants par partie/date
    View::DisplayLine();
    DBCtrl.SqlQueryWins();      // Requête nombre de victoire par joueur
    View::DisplayLine();
    DBCtrl.SqlQueryCardsPlayed();   // Requête liste des cartes, nombre de fois jouées, et taux
    return 0;
}