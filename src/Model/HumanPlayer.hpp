#pragma once

#include "Player.hpp"
#include <climits>
#include "../View/View.hpp"

class HumanPlayer : public Player
{
public:
    HumanPlayer(string Name);

    Card *PlayCardFromHand(CardValueEnum LastValue, CardSymbolEnum LastSymbol);

    int ChosenValue();
    int GetRealIndex(int ChooseCard);
    int ChoseColor();
    int GetEnteredValue();
};