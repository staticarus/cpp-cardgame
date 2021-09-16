#pragma once

#include "Player.hpp"

class ComputerPlayer : public Player
{
public:
    ComputerPlayer(string Name);

    Card *PlayCardFromHand(CardValueEnum _LastValue, CardSymbolEnum _LastSymbol);
    int ChoseColor();
};