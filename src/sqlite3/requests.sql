/* Pense-bête et tests pour la partie SQL du projet */

/* Suppressions */

DROP TABLE Games;
DROP TABLE Players;
DROP TABLE Scores;
DROP TABLE Cards;

PRAGMA foreign_keys = ON;   /* à ajouter à chaque runtime */
PRAGMA foreign_keys;        /* permet de tester si les FOREIGN KEYS sont activées ou non */

/* Création des tables */

PRAGMA foreign_keys = ON;
CREATE TABLE IF NOT EXISTS Games(
    GAMEID      INTEGER    NOT NULL PRIMARY KEY AUTOINCREMENT,
    DATETIME    TEXT       NOT NULL
);
CREATE TABLE IF NOT EXISTS Players(
    PLAYERID    INTEGER         NOT NULL PRIMARY KEY AUTOINCREMENT,
    NAME        VARCHAR(10)     NOT NULL,
    WINS        INTEGER         DEFAULT 0
);
CREATE TABLE IF NOT EXISTS Scores(
    SCOREID     INTEGER         NOT NULL PRIMARY KEY AUTOINCREMENT,
    GAMEID      INTEGER         NOT NULL,
    TYPE        VARCHAR(10)     NOT NULL,
    PLAYERID    INTEGER         NOT NULL,
    SCORE       INTEGER         NOT NULL,
    FOREIGN KEY(GAMEID) REFERENCES Games(GAMEID),
    FOREIGN KEY(PLAYERID) REFERENCES Players(PLAYERID)
);
CREATE TABLE IF NOT EXISTS Cards(
    CARDID      INTEGER         NOT NULL PRIMARY KEY AUTOINCREMENT,
    GAMEID      INTEGER         NOT NULL,
    VALUE       VARCHAR(15)     NOT NULL,
    PLAYERID    INTEGER         NOT NULL,
    FOREIGN KEY(GAMEID) REFERENCES Games(GAMEID),
    FOREIGN KEY(PLAYERID) REFERENCES Players(PLAYERID)
);

/* Insertions */

INSERT INTO Games(DATETIME) VALUES /* 13:13 , 15:13 (local modifie le now, il ne s'ajoute pas à la suite) */
(
    (datetime('now','localtime'))
);

/* Pas de recopie des joueurs si ils existent */
INSERT INTO Players(NAME) 
SELECT ("Joueur1")
WHERE NOT EXISTS(SELECT 1 FROM Players WHERE NAME = "Joueur1");
INSERT INTO Players(NAME) 
SELECT ("Joueur2")
WHERE NOT EXISTS(SELECT 1 FROM Players WHERE NAME = "Joueur2");
INSERT INTO Players(NAME) 
SELECT ("Joueur3")
WHERE NOT EXISTS(SELECT 1 FROM Players WHERE NAME = "Joueur3");
INSERT INTO Players(NAME) 
SELECT ("Joueur4")
WHERE NOT EXISTS(SELECT 1 FROM Players WHERE NAME = "Joueur4");

/* Gagnant */
UPDATE Players
SET WINS = WINS + 1
WHERE NAME = "Joueur3"; /* variable donnée en paramètre une fois implémenté en C++ */

INSERT INTO Cards(GAMEID, VALUE, PLAYERID) VALUES /* MAX permet de trouver la valeur maximale de l'autoincrement de l'autre table, c-à-d à chaque fois la partie (Game) actuelle */
(
    (SELECT MAX(GAMEID) FROM Games), 
    "10♥",
    (SELECT PLAYERID FROM Players WHERE NAME = "Joueur4")
);


/* ---------------------------------------- tests requêtes */
SELECT * FROM Scores
WHERE TYPE = "Partie"
ORDER BY GAMEID ASC, SCORE ASC
/*--- autre test */
SELECT Games.DATETIME, Players.NAME, Scores.SCORE 
FROM Games, Players, Scores
WHERE TYPE = "Partie"
ORDER BY DATETIME ASC, SCORE ASC

/*--- REQUETE NUMERO 1 FINALE ---*/
SELECT Games.DATETIME, Scores.GAMEID, Scores.PLAYERID, Scores.SCORE
FROM Scores
INNER JOIN Games ON Scores.GAMEID = Games.GAMEID
WHERE Scores.TYPE="Partie"
ORDER BY DATETIME ASC, SCORE ASC

/*--- REQUETE NUMERO 2 FINALE ---*/
SELECT NAME, WINS AS VICTOIRES
FROM Players

/*--- REQUETE NUMERO 3 FINALE ---*/
SELECT VALUE, COUNT(VALUE) AS MONTANT, (COUNT(VALUE)/MAX(Games.GAMEID)) AS TAUX
FROM Cards, Games
GROUP BY VALUE
ORDER BY VALUE ASC

/*--- REQUETE NB MOYEN DE ROUND ---*/
/* attention les décimales ne sont pas présentes */
SELECT COUNT(TYPE)/4 as nombreRound, 
        COUNT(DISTINCT GAMEID)as nombrePartie, 
        (COUNT(TYPE)/4)/(COUNT(DISTINCT GAMEID)) as moyenne 
FROM Scores

/*--- REQUETE CARTE MOINS JOUEE ---*/
SELECT VALUE, COUNT(VALUE) AS MONTANT
FROM Cards
GROUP BY VALUE
ORDER BY MONTANT ASC LIMIT 1

/*--- REQUETE CARTE PLUS JOUEE PAR JOUEUR PAR PARTIE ---*/
/*Il faut - la partie + le joueur + la carte GROUP BY */
SELECT GameID, PlayerID, VALUE, COUNT(VALUE) as Occurrences
FROM Cards
GROUP BY GAMEID, PLAYERID
ORDER BY Occurrences, GAMEID, PLAYERID


SELECT GAMEID, PlayerID, VALUE, COUNT(VALUE)
FROM (SELECT GAMEID, PlayerID, VALUE, MIN(ValueCount)
      FROM (SELECT GAMEID, PlayerID, VALUE, Count(VALUE) as ValueCount
            FROM Cards
            GROUP BY GAMEID, PlayerID, VALUE) SelectWithCount
      GROUP BY GAMEID, PlayerID, VALUE
      ORDER BY GAMEID, PlayerID, ValueCount ASC) OrderedValue
GROUP BY GAMEID, PlayerID
ORDER BY GAMEID, PlayerID
/* ------ */

CREATE TABLE IF NOT EXISTS TEST(
    ID      INTEGER    NOT NULL PRIMARY KEY AUTOINCREMENT,
    TYPE        VARCHAR(10)     NOT NULL
);

INSERT INTO TEST(TYPE) VALUES
("Round"),("Round"),("Round"),("Round"),
("Round"),("Round"),("Round"),("Round"),
("Round"),("Round"),("Round"),("Round"),
("Round"),("Round"),("Round"),("Round"),
("Round"),("Round"),("Round"),("Round"),
("Partie"),("Partie"),("Partie"),("Partie");

SELECT TYPE, COUNT(TYPE)/4
FROM TEST
GROUP BY TYPE
ORDER BY TYPE ASC

SELECT TYPE, 
        COUNT(TYPE), 
        SUM(CASE WHEN TYPE = "Partie" THEN 1 ELSE 0 END) NbOfParties,
        SUM(CASE WHEN TYPE = "Round" THEN 1 ELSE 0 END) NbOfRounds,
        (
            (
                SUM(CASE WHEN TYPE = "Partie" THEN 1 ELSE 0 END) 
                + SUM(CASE WHEN TYPE = "Round" THEN 1 ELSE 0 END)
            ) / SUM(CASE WHEN TYPE = "Partie" THEN 1 ELSE 0 END) 
        ) NbRoundsMoyen,
        AVG()
FROM TEST

SELECT TYPE, 
        COUNT(TYPE),
        SUM(CASE WHEN TYPE = "Partie" THEN 1 ELSE 0 END) AS test1,
        (
            (
                COUNT(TYPE)
            ) / SUM(CASE WHEN TYPE = "Partie" THEN 1 ELSE 0 END) 
        ) NbRoundsMoyen,
        /*ROUND(COUNT(TYPE) / SUM(CASE WHEN TYPE = "Partie" THEN 1 ELSE 0 END) , 4) AS test2,*/
        ROUND(36/10),
        ROUND(36/10,1),
        ROUND((36/10),2),
        ROUND(2.45875, 3)
FROM TEST
