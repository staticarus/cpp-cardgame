#include "ComputerPlayer.hpp"

//Classe enfant de "Player" permettant la création de joueurs ordinateurs

ComputerPlayer::ComputerPlayer(string Name) : Player(Name) {} //constructeur personnalisé appelant le constructeur du parent en lui passant un nom

Card *ComputerPlayer::PlayCardFromHand(CardValueEnum _LastValue, CardSymbolEnum _LastSymbol) //méthode retournant une carte de la main 
{                                                                                          //pouvant être placée sur le tas    
    Card *HandCard;
    for (int i = 0; i < DECK_SIZE; i++)
    {
        HandCard = GetCardAtIndex(i);
        if (HandCard == nullptr || !HandCard->CanBePlaced(_LastValue, _LastSymbol))
            continue;
        RemoveCardAtIndex(i);
        return HandCard;
    }
    return nullptr;
}
int ComputerPlayer::ChoseColor() //méthode permettant de changer la couleur aléatoirement
{
    srand(time(0));
    int randomNumber = rand() % 4;
    cout << "Valeur que j'ai choisi : " << randomNumber << endl;
    return randomNumber;
}