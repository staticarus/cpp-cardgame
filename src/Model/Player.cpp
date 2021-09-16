#include "Player.hpp"

//Classe Parent permettant la création et la gestion des joueurs

Player::Player() //constructeur par défaut
{
}
Player::Player(string PlayerName) //constructeur personnalisé prenant un string "Playername"
{
    this->_PlayerName = PlayerName;
    this->_ArrayHand = {0};
    this->_Score = 0;
}
string Player::GetPlayerName() const //Méthode permettant de retourner le nom du joueur
{
    return this->_PlayerName;
}
int Player::GetPlayerScore() const //Méthode permettant de retourner le score du joueur
{
    return this->_Score;
}
void Player::CalculatePlayerScore() //Méthode permettant de calculer le score du joueur
{
    for (int i = 0; i < DECK_SIZE; i++) // on parcourt la main
    {
        if (_ArrayHand.at(i) == nullptr)
            continue;
        Card *CurrentCard = _ArrayHand.at(i);       // on reçoit la carte
        this->AddScore(ScoreValueOf(CurrentCard)); // on calcule sa valeur
    }
}
void Player::AddScore(int i) //Méthode permettant d'ajouter le score
{
    this->_Score += i;
}
int Player::ScoreValueOf(Card *Card) //Méthode permettant de retourner les points de la carte selon sa valeur
{
    switch (Card->_CardValue)
    {
    case Joker:
        return 50;
    case Roi:
        return 10;
    case Dame:
        return 10;
    case Valet:
        return 20;
    case Dix:
        return 10;
    case Neuf:
        return 9;
    case Huit:
        return 50;
    case Sept:
        return 7;
    case Six:
        return 6;
    case Cinq:
        return 5;
    case Quatre:
        return 4;
    case Trois:
        return 3;
    case Deux:
        return 20;
    case As:
        return 20;
    default:
        return 0;
        break;
    }
}
array<Card *, DECK_SIZE> *Player::GetHandArray() //Méthode permettant de récupérer la main du joueur
{
    return &_ArrayHand;
}
void Player::AddCardInHand(Card *Card) //Méthode permettant d'ajouter une carte dans la main d'un joueur au premier nullptr croisé
{
    for (int i = 0; i < DECK_SIZE; i++)
    {
        if (this->_ArrayHand[i] == nullptr)
        {
            this->_ArrayHand[i] = Card;
            return;
        }
    }
}
bool Player::GetIfHandIsEmpty() //Méthode permettant de savoir si la main d'un joueur est vide ou non
{
    for (int i = 0; i < _ArrayHand.size(); i++)
    {
        if (_ArrayHand.at(i) != nullptr)
            return false;
    }
    return true;
}
void Player::ResetHand() //Méthode permettant de remettre a nullptr le tableau entier contenant les cartes de la main d'un joueur
{
    _ArrayHand = {0};
}
Card *Player::GetCardAtIndex(int Index) //Méthode permettant de retourner la carte située à un index précis
{
    return (_ArrayHand.at(Index));
}
void Player::RemoveCardAtIndex(int Index) //Méthode permettant permet de retirer une carte de la main située à un index précis
{
    _ArrayHand.at(Index) = nullptr;
}
