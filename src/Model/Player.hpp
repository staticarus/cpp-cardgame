#pragma once

#include "Card.hpp"
#include "Deck.hpp"

class Player
{
protected:
    string _PlayerName;
    int _Score;
    array<Card *, DECK_SIZE> _ArrayHand;

    Player();
    Player(string PlayerName);

    Card *GetCardAtIndex(int Index);
    void RemoveCardAtIndex(int Index);

public:
    string GetPlayerName() const;
    int GetPlayerScore() const;
    void CalculatePlayerScore();
    void AddCardInHand(Card *Card);
    array<Card *, DECK_SIZE> *GetHandArray();
    virtual Card *PlayCardFromHand(CardValueEnum LastValue, CardSymbolEnum LastSymbol) = 0;
    virtual int ChoseColor() = 0;
    bool GetIfHandIsEmpty();
    void ResetHand();

private:
    void AddScore(int i);
    int ScoreValueOf(Card *Card);
};