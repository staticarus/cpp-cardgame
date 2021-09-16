#pragma once

#include <iostream>
#include <array>
#include "../Model/Deck.hpp"
#include "../Model/Card.hpp"
#include "../Model/Const.hpp"
#include "../Model/Player.hpp"
#include "../Model/HumanPlayer.hpp"
#include "../Model/Const.hpp"
using namespace std;

class View
{

public:
    
    static void ShowCards(array<Card *, DECK_SIZE> *ArrayForDisplay);
    static void DisplayLine();
    static void ShowDraw(array<Card *, DECK_SIZE> *ArrayForDisplay);
    static void ShowHeap(array<Card *, DECK_SIZE> *ArrayForDisplay);
    static void ShowHands(array<Player *, PLAYER_AMOUNT> *PlayerArray, int *CurrentPlayer);
    static void ShowChosenCard(Card *ChosenCard);
    static void ShowCurrentValueAndColor(string *value, string *color);
    static void ShowTurnDetails(array<Card *, DECK_SIZE> *HeapArray, array<Card *, DECK_SIZE> *DrawArray, string Value, string Color, 
                                array<Player *, PLAYER_AMOUNT> *PlayerArray, int *CurrentPlayer);
    static void ShowPlayerCantPlay(array<Player *, PLAYER_AMOUNT> *PlayerArray, int *CurrentPlayer);
    static void GameStart();
    static void EndOfRoundDisplay(array<Player *, PLAYER_AMOUNT> *PlayerArray);
    static void EndOfGameDisplay(string PlayerName);
    static void ShowRefill();
    static void ShowEffect(CardValueEnum Value);
    static void ShowDrawACard(string Player, Card *Card);
    static void ShowHumanPlayerCards(array<Card *, DECK_SIZE> *ArrayForDisplay); // affichage spécial pour la main
    static int AskHumanWhatToPlay(array<Card *, DECK_SIZE> *ArrayForDisplay);    // message qui lui demande ce qu'il veut jouer
    static void ShowAskHumanWhatToPlay(int StartIndex, int EndIndex);            // affiche la range ("chosir de x à y")
    static void ShowHumanCantPlayThatCard();
    static void WhichColorDoYouWant();
    static void ShowDoYouWantToLeave();
};