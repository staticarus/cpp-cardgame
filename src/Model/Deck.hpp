#pragma once

#include "Card.hpp"
#include <random>    // random_shuffle example
#include <algorithm> // std::random_shuffle
#include <ctime>     // std::time
#include <cstdlib>   // std::rand, std::srand

using namespace std;

class Deck
{
private:
    array<Card, DECK_SIZE> _DeckArray; // "container library array"
    void CreateArrayCard();

public:
    Deck();
    Card *GetCardAtIndex(int Index);
    int GetDeckSize();
    void Shuffle();
};