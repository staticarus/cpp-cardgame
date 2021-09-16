#include "DatabaseController.hpp"

/* Affichages console ------------------------------- */

/* Affichage console pour la Requête 1 (scores par ordre croissant et par date) */
static int callbackScores(void *data, int argc, char **argv, char **azColName){
    int i;
    if(data) // ajout d'une condition pour éviter le "(null): " au début de chaque réponse/callback
        fprintf(stderr, "%s: ", (const char*)data);
    
    int loop = 0;
    for(i = 0; i<argc; i++){
            // Cette boucle permet d'organiser la syntaxe console au fil des callback qui sont reçus pour la Requête SQL 1
        if (loop == 4)
            loop = 1;
        else
            loop++;

        switch (loop)
        {
        case 1:
            printf("%s (", argv[i] ? argv[i] : "NULL");
            break;
        case 2:
            printf("Partie %s) - ", argv[i] ? argv[i] : "NULL");
            break;
        case 3:
            printf("Joueur %s, ", argv[i] ? argv[i] : "NULL");
            break;
        case 4:
            printf("%s points", argv[i] ? argv[i] : "NULL");
            break;
        default:
            break;
        }

    }
    
    printf("\n");
    return 0;
}

/* Affichage console pour la Requête 2 (nombre de victoires pour chaque joueur) */
static int callbackWins(void *data, int argc, char **argv, char **azColName){
    int i;
    if(data) // ajout d'une condition pour éviter le "(null): " au début de chaque réponse
        fprintf(stderr, "%s: ", (const char*)data);
    
    int loop = 0;
    for(i = 0; i<argc; i++){
            // Cette boucle permet d'organiser la syntaxe console au fil des callback qui sont reçus pour la Requête SQL 2
        if (loop == 2)
            loop = 1;
        else
            loop++;

        switch (loop)
        {
        case 1:
            printf("%s : ", argv[i] ? argv[i] : "NULL");
            break;
        case 2:
            printf("%s victoire(s)", argv[i] ? argv[i] : "NULL");
            break;
        default:
            break;
        }
    }
    
    printf("\n");
    return 0;
}

/* Affichage console pour la Requête 3 (liste des cartes, nombre de fois jouées, et taux) */
static int callbackCardsPlayed(void *data, int argc, char **argv, char **azColName){
    int i;
    if(data) // ajout d'une condition pour éviter le "(null): " au début de chaque réponse
        fprintf(stderr, "%s: ", (const char*)data);
    
    int loop = 0;
    string cardvalue = "";
    for(i = 0; i<argc; i++){
            // Cette boucle permet d'organiser la syntaxe console au fil des callback qui sont reçus pour la Requête SQL 3
        if (loop == 3)
            loop = 1;
        else
            loop++;

        switch (loop)
        {
        case 1:
            
            printf("La carte : %s ", argv[i] ? argv[i] : "NULL");
            break;
        case 2:
            printf("a ete jouee %s fois ", argv[i] ? argv[i] : "NULL");
            break;
        case 3:
            printf("et son taux est de %s pourcent ", argv[i] ? argv[i] : "NULL");
            break;
        default:
            break;
        }
    }
    
    printf("\n");
    return 0;
}

/* Constructeur et actions de base ------------------ */

DatabaseController::DatabaseController()
{
    int OpeningCode = OpenDatabase(); // reçoit un code réponse
    if (OpeningCode) // autre que 0 = erreur
        cerr << "Erreur durant l'ouverture de la DB, code : " << OpeningCode << endl;
    else // si 0 = réussite
        cout << "DB ouverte avec succes, code : " << OpeningCode << endl;
    CreateTableGames();
    CreateTablePlayers();
    CreateTableScores();
    CreateTableCards();
    CloseDatabase();    // création des tables et fermeture ensuite (car c'est à faire manuellement)
}

int DatabaseController::OpenDatabase() // Ouverture de la base de données, et renvoie un code réponse
{
    return (sqlite3_open("./sqlite3/parties.db", &_DB)); // retourne 0 si succès, 1 si échec
}

void DatabaseController::CloseDatabase() // Fermeture de la base de données
{
    sqlite3_close(_DB);
}

/* Création des tables ------------------------------ */

void DatabaseController::CreateTableGames() // Création de la table stockant les scores
{
    /* Le const permet la conversion de string literal (appelé constant par le compilateur) vers char * (requis pour la méthode du dessous) */
    /* les backslash sont requis pour assemblage correct des strings (répartis sur plusieurs lignes pour plus de clarté */
    const char * SQLRequest = 
                        "PRAGMA foreign_keys = ON;" \
                        "CREATE TABLE IF NOT EXISTS Games(" \
                            "GAMEID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT," \
                            "DATETIME TEXT  NOT NULL" \
                        ");";
    int OpeningCode = sqlite3_exec(_DB, SQLRequest, NULL, 0, &_ErrorMsg); // Demande d'exécuter la requête sur notre base de données, sans arguments supplémentaires
    if(OpeningCode)
    { // Si le code renvoyé par l'exécution est différent de 0 = erreur
        cout << "Erreur lors de la creation de la table 'Games' : " << _ErrorMsg << endl;
        sqlite3_free(_ErrorMsg);
    }
    else
        cout << "Creation de la table 'Games' reussie" << endl;
}

void DatabaseController::CreateTablePlayers() // Création de la table stockant les joueurs
{
    /* Le const permet la conversion de string literal (appelé constant par le compilateur) vers char * (requis pour la méthode du dessous) */
    /* les backslash sont requis pour assemblage correct des strings (répartis sur plusieurs lignes pour plus de clarté */
    const char * SQLRequest = 
                        "PRAGMA foreign_keys = ON;" \
                        "CREATE TABLE IF NOT EXISTS Players(" \
                            "PLAYERID INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT," \
                            "NAME VARCHAR(10) NOT NULL," \
                            "WINS INTEGER DEFAULT 0" \
                        ");";
    int OpeningCode = sqlite3_exec(_DB, SQLRequest, NULL, 0, &_ErrorMsg); // Demande d'exécuter la requête sur notre base de données, sans arguments supplémentaires
    if(OpeningCode)
    { // Si le code renvoyé par l'exécution est différent de 0 = erreur
        cout << "Erreur lors de la creation de la table 'Players' : " << _ErrorMsg << endl;
        sqlite3_free(_ErrorMsg);
    }
    else
        cout << "Creation de la table 'Players' reussie" << endl;
}

void DatabaseController::CreateTableScores() // Création de la table stockant les scores
{
    /* Le const permet la conversion de string literal (appelé constant par le compilateur) vers char * (requis pour la méthode du dessous) */
    /* les backslash sont requis pour assemblage correct des strings (répartis sur plusieurs lignes pour plus de clarté */
    const char * SQLRequest = 
                        "PRAGMA foreign_keys = ON;" \
                        "CREATE TABLE IF NOT EXISTS Scores(" \
                            "SCOREID INTEGER    NOT NULL PRIMARY KEY AUTOINCREMENT," \
                            "GAMEID INTEGER     NOT NULL," \
                            "TYPE VARCHAR(10)   NOT NULL," \
                            "PLAYERID INTEGER NOT NULL," \
                            "SCORE INTEGER    NOT NULL," \
                            "FOREIGN KEY(GAMEID) REFERENCES Games(GAMEID)," \
                            "FOREIGN KEY(PLAYERID) REFERENCES Players(PLAYERID)" \
                        ");";
    int OpeningCode = sqlite3_exec(_DB, SQLRequest, NULL, 0, &_ErrorMsg); // Demande d'exécuter la requête sur notre base de données, sans arguments supplémentaires
    if(OpeningCode)
    { // Si le code renvoyé par l'exécution est différent de 0 = erreur
        cout << "Erreur lors de la creation de la table 'Scores' : " << _ErrorMsg << endl;
        sqlite3_free(_ErrorMsg);
    }
    else
        cout << "Creation de la table 'Scores' reussie" << endl;
}

void DatabaseController::CreateTableCards() // Création de la table stockant les cartes jouées
{
    /* Le const permet la conversion de string literal (appelé constant par le compilateur) vers char * (requis pour la méthode du dessous) */
    /* les backslash sont requis pour assemblage correct des strings (répartis sur plusieurs lignes pour plus de clarté */
    const char * SQLRequest = 
                        "PRAGMA foreign_keys = ON;" \
                        "CREATE TABLE IF NOT EXISTS Cards(" \
                            "CARDID INTEGER     NOT NULL PRIMARY KEY AUTOINCREMENT," \
                            "GAMEID INTEGER     NOT NULL," \
                            "VALUE VARCHAR(15)  NOT NULL," \
                            "PLAYERID INTEGER NOT NULL," \
                            "FOREIGN KEY(GAMEID) REFERENCES Games(GAMEID)," \
                            "FOREIGN KEY(PLAYERID) REFERENCES Players(PLAYERID)" \
                        ");";
    int OpeningCode = sqlite3_exec(_DB, SQLRequest, NULL, 0, &_ErrorMsg); // Demande d'exécuter la requête sur notre base de données, sans arguments supplémentaires
    if(OpeningCode) 
    { // Si le code renvoyé par l'exécution est différent de 0 = erreur
        cout << "Erreur lors de la creation de la table 'Cards' : " << _ErrorMsg << endl;
        sqlite3_free(_ErrorMsg);
    }
    else
        cout << "Creation de la table 'Cards' reussie" << endl;
}

/* Envoi des données -------------------------------- */

void DatabaseController::SendDataToTableGames() // Envoi de données vers la table 'Games'
{
    int OpeningCode = OpenDatabase(); // Ouverture de la DB et réception d'un code
    if (OpeningCode)
        cerr << "Erreur durant l'ouverture de la DB, code : " << OpeningCode << endl;
    char SQLRequest[256]; // Sert à stocker la requête
    sprintf(SQLRequest, "INSERT INTO Games(DATETIME) VALUES (datetime('now','localtime'))"); // DateTime actuel converti à l'heure locale
    OpeningCode = sqlite3_exec(_DB, SQLRequest, NULL, 0, &_ErrorMsg); // Envoi de la requête, réception d'un code réponse
    if (OpeningCode) {
        cout << "Erreur lors de l'insertion dans la table 'Games' : " << _ErrorMsg << endl;
        sqlite3_free(_ErrorMsg);
    } else cout << "Insertion d'une nouvelle partie dans la table 'Games' reussie" << endl;
    CloseDatabase();
}

void DatabaseController::SendDataToTablePlayers(array<Player *, PLAYER_AMOUNT> * PlayerArray)
{
    int OpeningCode = OpenDatabase(); // Ouverture de la DB et réception d'un code
    if (OpeningCode)
        cerr << "Erreur durant l'ouverture de la DB, code : " << OpeningCode << endl;
    char SQLRequest[256]; // Sert à stocker la requête
    for (int index = 0; index < PLAYER_AMOUNT; index++) // Pour chaque joueur 
    {
        sprintf(SQLRequest,
            "INSERT INTO Players(NAME) SELECT ('%s') "\
            "WHERE NOT EXISTS(SELECT 1 FROM Players WHERE NAME = '%s');", // On l'enregistre seulement si son nom n'est pas déjà présent dans la table
            (*PlayerArray).at(index)->GetPlayerName().c_str(),
            (*PlayerArray).at(index)->GetPlayerName().c_str()
            );
        OpeningCode = sqlite3_exec(_DB, SQLRequest, NULL, 0, &_ErrorMsg); // Envoi de la requête, réception d'un code réponse
        if (OpeningCode) {
            cout << "Erreur lors de l'insertion dans la table 'Players' : " << _ErrorMsg << endl;
            sqlite3_free(_ErrorMsg);
        }
    }
    
}

void DatabaseController::SendDataToTableScores(string type, array<Player *, PLAYER_AMOUNT> * PlayerArray) // Envoi de données vers la table des scores
{
    int OpeningCode = OpenDatabase(); // Ouverture de la DB et réception d'un code
    if (OpeningCode)
        cerr << "Erreur durant l'ouverture de la DB, code : " << OpeningCode << endl;
    char SQLRequest[256]; // il faut que ce soit un tableau, le pointeur ne fonctionne pas avec sprintf
    // !!! il faut un %s pour la donnée en string ET un .c_str() sur la data (même si c'est déjà un string)... idkwhy
    // pour un int, on utilise %d sur sprintf
    for (int index = 0; index < PLAYER_AMOUNT; index++) // Pour chaque joueur
    {
        sprintf(SQLRequest,
            "INSERT INTO Scores(GAMEID, TYPE, PLAYERID, SCORE) VALUES "\
            "((SELECT MAX(GAMEID) FROM Games),'%s',(SELECT PLAYERID FROM Players WHERE NAME = '%s'),%d)", // envoi de la partie actuelle, de son nom et de son score
            type.c_str(),
            (*PlayerArray).at(index)->GetPlayerName().c_str(),
            (*PlayerArray).at(index)->GetPlayerScore());
        OpeningCode = sqlite3_exec(_DB, SQLRequest, NULL, 0, &_ErrorMsg); // Envoi de la requête, réception d'un code réponse
        if (OpeningCode) {
            cout << "Erreur lors de l'insertion dans la table 'Scores' : " << _ErrorMsg << endl;
            sqlite3_free(_ErrorMsg);
        } /*else cout << "Insertion dans la table 'Scores' reussie" << endl;*/
    }
    

    CloseDatabase();
}

void DatabaseController::SendDataToTableCards(int Player, Card * Card) // Envoi de données vers la table des cartes jouées
{
    int OpeningCode = OpenDatabase(); // Ouverture de la DB et réception d'un code
    if (OpeningCode)
        cerr << "Erreur durant l'ouverture de la DB, code : " << OpeningCode << endl;
    char SQLRequest[256]; // Sert à stocker la requête

    string SqlCard = CastCardForSQL(Card); // travaille les données car SQL ne lit pas les symboles de cartes en \3 et compagnie

    sprintf(SQLRequest,
            "INSERT INTO Cards(GAMEID, VALUE, PLAYERID) VALUES "\
            "((SELECT MAX(GAMEID) FROM Games),'%s',(SELECT PLAYERID FROM Players WHERE NAME = 'Joueur %d'))", // envoi de la partie actuelle, de la carte et du joueur actuel
            SqlCard.c_str(),
            (Player+1)
            );
    OpeningCode = sqlite3_exec(_DB, SQLRequest, NULL, 0, &_ErrorMsg); // Envoi de la requête, réception d'un code réponse
    if (OpeningCode) {
        cout << "Erreur lors de l'insertion dans la table 'Cards' : " << _ErrorMsg << endl;
        sqlite3_free(_ErrorMsg);
    }
    CloseDatabase();
}

void DatabaseController::UpdateTablePlayersForWinner(Player * Winner) // Met à jour la table 'Players' pour incrémenter le nombre de victoires du gagnant
{
    int OpeningCode = OpenDatabase(); // Ouverture de la DB et réception d'un code
    if (OpeningCode)
        cerr << "Erreur durant l'ouverture de la DB, code : " << OpeningCode << endl;
    char SQLRequest[256];

    sprintf(SQLRequest, 
            "UPDATE Players SET Wins = WINS + 1 WHERE NAME = '%s';",
            Winner->GetPlayerName().c_str());

    OpeningCode = sqlite3_exec(_DB, SQLRequest, NULL, 0, &_ErrorMsg); // Envoi de la requête, réception d'un code réponse
    if (OpeningCode) {
        cout << "Erreur lors de l'insertion dans la table 'Games' : " << _ErrorMsg << endl;
        sqlite3_free(_ErrorMsg);
    } else cout << "Mise a jour des victoires dans la table 'Games' reussie" << endl;
    CloseDatabase();
}

/* Requêtes SQL ------------------------------------- */

void DatabaseController::SqlQueryScores() // Ouvre la DB, exécute une requête SQL via sqlite3_exec. L'un des paramètres est une méthode callback qui renvoie les résultats un à un
{
    int OpeningCode = OpenDatabase();
    if (OpeningCode)
        cerr << "Erreur durant l'ouverture de la DB, code : " << OpeningCode << endl;
    // Requête SQL sur deux tables avec un INNER JOIN (Games pour la date, et Scores pour le reste) et un try sur les scores de fin de partie uniquement (on ignore les rounds)
    string SQLRequest = "SELECT Games.DATETIME, Scores.GAMEID, Scores.PLAYERID, Scores.SCORE FROM Scores INNER JOIN Games ON Scores.GAMEID = Games.GAMEID WHERE Scores.TYPE='Partie' ORDER BY DATETIME ASC, SCORE ASC";
    OpeningCode = sqlite3_exec(_DB, SQLRequest.c_str(), callbackScores, 0, &_ErrorMsg); // le callback se charge d'envoyer en console chaque réponse, avec une syntaxe adaptée à cette requête en particulier
    if (OpeningCode)
    {
        cerr << "Erreur durant la requête scores : " << _ErrorMsg << endl;
        sqlite3_free(_ErrorMsg);
    }
    else
        cout << "Query 1 (ascending scores by Game/Date) done" << endl;
}

void DatabaseController::SqlQueryWins() // Ouvre la DB, exécute une requête SQL via sqlite3_exec. L'un des paramètres est une méthode callback qui renvoie les résultats un à un
{
    int OpeningCode = OpenDatabase();
    if (OpeningCode)
        cerr << "Erreur durant l'ouverture de la DB, code : " << OpeningCode << endl;
    // Requête SQL sur la table joueur pour lister tous les joueurs et leurs nombres de victoires respectifs
    string SQLRequest = "SELECT NAME, WINS FROM Players";
    OpeningCode = sqlite3_exec(_DB, SQLRequest.c_str(), callbackWins, 0, &_ErrorMsg); // le callback se charge d'envoyer en console chaque réponse, avec une syntaxe adaptée à cette requête en particulier
    if (OpeningCode)
    {
        cerr << "Erreur durant la requête wins : " << _ErrorMsg << endl;
        sqlite3_free(_ErrorMsg);
    }
    else
        cout << "Query 2 (players wins) done" << endl;
}

void DatabaseController::SqlQueryCardsPlayed() // Ouvre la DB, exécute une requête SQL via sqlite3_exec. L'un des paramètres est une méthode callback qui renvoie les résultats un à un
{
    int OpeningCode = OpenDatabase();
    if (OpeningCode)
        cerr << "Erreur durant l'ouverture de la DB, code : " << OpeningCode << endl;
    // Requête SQL pour lister toutes les cartes joueurs (en regroupant les doublons, donc 56 entrées au total) ainsi que le nombre d'occurence pour chaque carte, et le taux (occurence divisée par nombre de partie), le tout trié par ordre alphabétique
    string SQLRequest = "SELECT VALUE, COUNT(VALUE) AS MONTANT, (COUNT(VALUE)/MAX(Games.GAMEID)) AS TAUX FROM Cards, Games GROUP BY VALUE ORDER BY VALUE ASC";
    OpeningCode = sqlite3_exec(_DB, SQLRequest.c_str(), callbackCardsPlayed, 0, &_ErrorMsg); // le callback se charge d'envoyer en console chaque réponse, avec une syntaxe adaptée à cette requête en particulier
    if (OpeningCode)
    {
        cerr << "Erreur durant la requête cards played : " << _ErrorMsg << endl;
        sqlite3_free(_ErrorMsg);
    }
    else {
        cout << "Query 3 (cards played) done" << endl;
        cout << "\n Probleme d'encodage sur la console pour la lecture des 4 symboles de cartes, donc nous les avons ecrits sous format textuel pour la DB et la requete console.\n\n" << endl;
    }
}


/* Utilitaires -------------------------------------- */

string DatabaseController::CastCardForSQL(Card * Card)
{
    /* Pourquoi cette méthode : les \3, \4, \5, \6 utilisés par notre classe 'Card' ne
        fonctionnent pas avec le SQL et donnent des caractères illisibles dans la DB.
    
        Si à la place je les indique en code alt ici (♥,♦,♣,♠) c'est durant les requêtes
        SQL en console qu'ils ne sont plus lisibles...
        (Sur SQLite Explorer de VSCode tout va bien : aucun problème d'encodage)
        
        Par mesure de facilité, j'ai donc indiqué les valeurs en format texte pour la DB et les requêtes console. */
    
    string WholeCard = "Cast Error";
    if ((*Card)._CardValue == Joker) {
        WholeCard = (*Card).GetValue(); // Si Joker on n'envoie que la Valeur
        return WholeCard;
    } else { // Sinon on envoie la valeur + un symbole précis (les \3,\4,\5,\6 de notre classe Card ne fonctionnent pas)
        switch ((*Card)._CardSymbol)
        {
        case Coeur:
            WholeCard = ((*Card).GetValue() + /*"♥"*/ " de Coeur"); // symboles ascii finalement commentés, car ils n'étaient pas reconnus par la console windows (pour SQLite c'était OK)
            return WholeCard;
        case Carreau:
            WholeCard = ((*Card).GetValue() + /*"♦"*/ " de Carreau");
            return WholeCard;
        case Trefle:
            WholeCard = ((*Card).GetValue() + /*"♣"*/ " de Trefle");
            return WholeCard;
        case Pique:
            WholeCard = ((*Card).GetValue() + /*"♠"*/ " de Pique");
            return WholeCard;
        default:
            break;
        }
    }
    return WholeCard; // Retourne "Cast Error" si erreur quelque part
}

