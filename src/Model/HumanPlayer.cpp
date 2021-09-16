#include "HumanPlayer.hpp"

//Classe enfant de "Player" permettant de créer des "joueurs humains"

HumanPlayer::HumanPlayer(string Name) : Player(Name) {}

Card *HumanPlayer::PlayCardFromHand(CardValueEnum LastValue, CardSymbolEnum LastSymbol) //Méthode permettant de jouer une carte de la main
{
    do
    {
        int Choice = ChosenValue();
        int Index = GetRealIndex(Choice);
        if (Choice == 0)
            return nullptr; // déclenche le fait de piocher une carte
        Card *HandCard = GetCardAtIndex(Index);
        if (HandCard == nullptr || !HandCard->CanBePlaced(LastValue, LastSymbol)) // si l'index entré ne correspond pas à une carte jouable, il doit entrer une nouvelle valeur
            View::ShowHumanCantPlayThatCard();
        else
        {
            RemoveCardAtIndex(Index);
            return HandCard; // la carte située à l'index entré est jouée
        }
    } while (true);
}
int HumanPlayer::ChosenValue() //Méthode permettant de récupérer et retourner le choix du joueur (si celui-ci est dans la tranche correcte des cartes de sa main)
{
    int Choice;
    int Maxindex;
    do
    {
        Maxindex = View::AskHumanWhatToPlay(&_ArrayHand); // Message console + récupère la valeur maximale qu'il peut entrer en fonction du contenu de sa main
        Choice = GetEnteredValue();
    } while (Choice <= -1 || Choice > Maxindex);
    return Choice;
}
int HumanPlayer::GetRealIndex(int ChosenCard) //Méthode permettant de récupérer le véritable index (celui entré par l'utilisateur, en ignorant les nullptr de sa main)
{
    int RealIndex = 0;
    for (int i = 0; i < DECK_SIZE; i++)
    {
        if (_ArrayHand.at(i) == nullptr)
            continue;
        RealIndex++;
        if (RealIndex == ChosenCard)
            return i;
    }
    return -1;
}
int HumanPlayer::GetEnteredValue() //Méthode permettant de récupérer la valeur entrée dans la console
{
    int Choice=0;
    cin >> Choice;
    if (cin.fail())
    {
        Choice = -1;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return Choice;
}
int HumanPlayer::ChoseColor() //Méthode permettant au joueur humain de choisir la couleur qu'il souhaite
{
    int Choice=0;
    do
    {
        View::WhichColorDoYouWant();
        Choice = GetEnteredValue();
    } while (Choice <= 0 || Choice > 4);
    return (Choice-1);
}