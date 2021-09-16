#include "Card.hpp"

//Classe permettant de créer des Cartes
// Tableaux utilisés pour les getters
string _CardValueStr[NB_CARD] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "V", "D", "R", "Joker"};
string _CardSymbolStr[NB_SYMBOL] = {ROUGE "\3" RESET_COLOR, ROUGE "\4" RESET_COLOR, BLUE "\5" RESET_COLOR, BLUE "\6" RESET_COLOR};

Card::Card() {}              //Constructeur par défaut
Card::Card(int Val, int Sym) //constructeur avec 2 paramètres pour toutes les Cards sauf Joker
{
    this->_CardValue = CardValueEnum(Val);
    this->_CardSymbol = CardSymbolEnum(Sym);
}
Card::Card(int Val) //constructeur avec un seul argument pour le joker (ne nécessite pas de symbole)
{
    this->_CardValue = CardValueEnum(Val);
}
string Card::GetValue() //Permet de récupérer la valeur de la carte
{
    return _CardValueStr[_CardValue];
}
string Card::GetSymbol() //Permet de récupérer le symbole de la carte
{
    return _CardSymbolStr[_CardSymbol];
}
string Card::GetSymbolAtIndex(int Index) //Permet de récupérer le symbole de la carte selon l'index
{
    return _CardSymbolStr[Index];
}
string Card::GetValueAtIndex(int Index) //Permet de récupérer la valeur de la carte selon l'index
{
    return _CardValueStr[Index];
}
bool Card::CanBePlaced(CardValueEnum _LastValue, CardSymbolEnum _LastSymbol) //Vérifie si la carte peut être posée, à la suite d'une comparaison sur les valeurs de la dernière carte posée sur le tas
{
    if (_CardValue == _LastValue || _CardValue == Huit || _CardValue == Joker || _CardSymbol == _LastSymbol)
        return true;
    else
        return false;
}