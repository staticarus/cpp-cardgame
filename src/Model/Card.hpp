#pragma once

#include "Enumerator.hpp"
#include "Const.hpp"
#include <iostream>
#include <array>

using namespace std;

class Card
{
public:
    CardValueEnum _CardValue;
    CardSymbolEnum _CardSymbol;

    Card();
    Card(int Val, int Sym); // Constructeur "normal"
    Card(int Val); // Constructeur pour le Joker

    bool CanBePlaced(CardValueEnum _LastValue, CardSymbolEnum _LastSymbol); // ChangeLastCardData retirés d'ici car c'est déjà géré par AddCardOnHeap et cela foirait les valeurs
    string GetValue();
    string GetSymbol();
    static string GetSymbolAtIndex(int Index);
    static string GetValueAtIndex(int Index);
};