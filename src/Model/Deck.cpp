#include "Deck.hpp"

//Classe permettant la création d'un objet "_Deck" qui est l'ensemble des cartes

int Myrandom(int i) { return std::rand() % i; } // random nécessaire à la méthode shuffle
Deck::Deck()                                    //constructeur sans paramètre qui va appeler la méthode Remplissage
{
    this->CreateArrayCard();
}
void Deck::CreateArrayCard() //Méthode permettant de créer un tableau de NB_SYMBOL * NB_CARD
{
    int Index = 0;
    for (int i = 0; i < NB_SYMBOL; i++)
    {
        for (int j = 0; j < NB_CARD; j++)
        {
            if (j != Joker)
                _DeckArray[Index] = Card(j, i);
            else //Spécial joker
                _DeckArray[Index] = Card(j);
            Index++;
        }
    }
    Shuffle();
}
void Deck::Shuffle() //permet de mélanger le _Deck selon un aléatoir
{
    srand(time(0));                                               // Fournit un seed semi-RNG (le temps) à rand()
    random_shuffle(_DeckArray.begin(), _DeckArray.end(), Myrandom); // mélange le _Deck grâce à rand(), srand(), et myrandom
}

Card *Deck::GetCardAtIndex(int Index) // permet de retourner une carte à un index
{
    return &(this->_DeckArray.at(Index));
}
int Deck::GetDeckSize() // permet de récupérer la taille du _Deck
{
    return this->_DeckArray.size();
}
