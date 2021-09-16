#pragma once

#include "../sqlite3/sqlite3.h" // Base de données (librairie SQL)
#include <iostream>
#include <array>
#include "../Model/Const.hpp"
#include "../Model/Player.hpp"

using namespace std;


class DatabaseController {

    private:
    sqlite3 * _DB;
    char * _ErrorMsg = 0;

    public:
    DatabaseController(); // Constructeur qui ouvre la DB et crée les tables si non présentes
    int OpenDatabase(); // Ouverture
    void CloseDatabase(); // Fermeture

    /* Création des tables ------------------------------ */
    void CreateTableGames(); // Création de la table stockant les parties et leur date
    void CreateTablePlayers(); // Création de la table stockant les joueurs et leur nom (avec vérification pour éviter les doublons si nom déjà existant)
    void CreateTableScores(); // Création de la table stockant les scores de chaque round et partie
    void CreateTableCards(); // Création de la table stockant les cartes jouées par chaque joueur

    /* Envoi des données -------------------------------- */
    void SendDataToTableGames(); // Insertion d'une nouvelle partie (ID + DateTime)
    void SendDataToTablePlayers(array<Player *, PLAYER_AMOUNT> * PlayerArray);
    void SendDataToTableScores(string Type, array<Player *, PLAYER_AMOUNT> * PlayerArray); // Envoi de données vers la table des scores
    void SendDataToTableCards(int Player, Card * Card); // Envoi de données vers la table des cartes jouées
    
    void UpdateTablePlayersForWinner(Player * Winner);

    /* Requêtes SQL ------------------------------------- */
    void SqlQueryScores(); // scores par ordre croissant sur la date et l'heure du jeu 
    void SqlQueryWins(); // nombre de parties gagnées par chaque joueur 
    void SqlQueryCardsPlayed(); // combien de fois chaque carte a été jouée et son taux de jeu

    /* Utilitaires -------------------------------------- */
    string CastCardForSQL(Card * Card); // Permet de convertir nos '\3' en format textuel (car SQLite ne lit pas nos '.getSymbol()' de la classe 'Card')
                                        // Pas de conversion vers '♥' etc. car à ce moment-là c'est la console windows qui ne sait pas les lire... :(
};
