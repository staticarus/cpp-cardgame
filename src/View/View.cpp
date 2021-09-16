#include "View.hpp"

void View::GameStart() //Vue affichant le début de la partie
{
    cout << "\n==== Debut de la partie ====\n"
         << endl;
}
void View::ShowCards(array<Card *, DECK_SIZE> *ArrayForDisplay) //Permet d'afficher à l'écran toutes les cartes présentes dans le tableau qu'on lui passe
{
    for (int i = 0; i < DECK_SIZE; i++)
    {
        if ((*ArrayForDisplay).at(i) != nullptr)
        {
            if ((*ArrayForDisplay).at(i)->_CardValue == Joker)
                cout << (*ArrayForDisplay).at(i)->GetValue().c_str() << "  "; //Affichage du joker
            else
                cout << (*ArrayForDisplay).at(i)->GetValue().c_str()
                     << (*ArrayForDisplay).at(i)->GetSymbol().c_str() << "  ";
        }
        else
            continue;
    }
    cout << endl;
}
void View::DisplayLine() //Vue affichant une ligne afin de séparer les informations
{
    cout << "\n----------------------------------------------------------------------\n"
         << endl;
}
void View::ShowDraw(array<Card *, DECK_SIZE> *ArrayForDisplay) //Vue affichant la pioche
{
    cout << "- Pioche : ";
    ShowCards(ArrayForDisplay);
}
void View::ShowHeap(array<Card *, DECK_SIZE> *ArrayForDisplay) //Vue affichant le tas
{
    cout << "- Tas : ";
    ShowCards(ArrayForDisplay);
}
void View::ShowHands(array<Player *, PLAYER_AMOUNT> *PlayerArray, int *CurrentPlayer) //Vue affichant la main des joueurs
{
    for (int i = 0; i < PLAYER_AMOUNT; i++)
    {
        if (i == (*CurrentPlayer)) // Si joueur actuel on met un chevron pour faire jouli
            cout << "> " << (*PlayerArray).at(i)->GetPlayerName().c_str() << " : ";
        else
            cout << "- " << (*PlayerArray).at(i)->GetPlayerName().c_str() << " : ";
        if (i == (*CurrentPlayer) && typeid(*PlayerArray->at(i)).name() == typeid(HumanPlayer).name()) // si joueur actuel est humain on appelle un affichage spécial
            ShowHumanPlayerCards((*PlayerArray).at(i)->GetHandArray());                                // affichage joueur humain (avec les index avant chaque carte)
        else                                                                                           // sinon affichage normal
            ShowCards((*PlayerArray).at(i)->GetHandArray());                                           // affichage joueur computer (juste les cartes, sans index)
    }
}
void View::ShowChosenCard(Card *ChosenCard) //Vue affichant la carte choisie
{
    if (ChosenCard->_CardValue == Joker)
        cout << "\n**** Carte choisie : " << ChosenCard->GetValue().c_str() << "\n";
    else
        cout << "\n**** Carte choisie : " << ChosenCard->GetValue().c_str() << ChosenCard->GetSymbol().c_str() << "\n";
}
void View::ShowCurrentValueAndColor(string *Value, string *Color) //Vue affichant La valeur et le symbole de la dernière carte posée
{
    cout << "- Valeur courante : " << *Value << ", Couleur courante : " << *Color << "\n\n";
}
void View::ShowTurnDetails(array<Card *, DECK_SIZE> *HeapArray, array<Card *, DECK_SIZE> *DrawArray, string Value, string Color,
                           array<Player *, PLAYER_AMOUNT> *PlayerArray, int *CurrentPlayer) //Vue affichant les détails d'un tour
{
    DisplayLine();
    ShowHeap(HeapArray);
    ShowDraw(DrawArray);
    ShowCurrentValueAndColor(&Value, &Color);
    ShowHands(PlayerArray, CurrentPlayer);
}
void View::ShowPlayerCantPlay(array<Player *, PLAYER_AMOUNT> *PlayerArray, int *CurrentPlayer) //Vue affichée lorsqu'un joueur ne sait pas jouer
{
    DisplayLine();
    cout << "\n-> Le " << (*PlayerArray).at(*CurrentPlayer)->GetPlayerName().c_str() << " ne peut jouer aucune carte :(\n"
         << endl;
}
void View::EndOfRoundDisplay(array<Player *, PLAYER_AMOUNT> *PlayerArray) //Vue affichant la fin d'un round et la liste des points actuels de chaque joueur
{
    cout << "\n==== Une main est vide, fin du round ====\n"
         << endl;
    for (int i = 0; i < PLAYER_AMOUNT; i++)
    {
        cout << "- " << (*PlayerArray).at(i)->GetPlayerName().c_str() << " : ";
        cout << (*PlayerArray).at(i)->GetPlayerScore() << " points" << endl;
    }
    cout << "Appuyer sur une touche pour continuer..." << endl;
    cin.ignore();
    cout << endl;
}
void View::ShowRefill() //Vue affichant un message lorsque le tas est utilisé pour reformer la pioche
{
    cout << "La pioche était vide, le tas a ete melange pour la recreer." << endl;
}
void View::ShowEffect(CardValueEnum Value) //Vue affichant les effets qui ont été appliqués selon la carte spéciale jouée
{
    switch (Value)
    {
    case As:
        cout << "**** Effet : changement de sens pour les tours\n";
        break;
    case Deux:
        cout << "**** Attaque : 2 cartes pour le joueur suivant\n";
        break;
    case Huit:
        cout << "**** Effet : changement de couleur\n";
        break;
    case Dix:
        cout << "**** Effet : le joueur actuel rejoue\n";
        break;
    case Valet:
        cout << "**** Effet : le prochain joueur passe son tour\n";
        break;
    case Joker:
        cout << "**** Attaque : 4 cartes pour le joueur suivant\n";
        break;
    default:
        break;
    }
}
void View::ShowDrawACard(string Player, Card *Card) //Vue affichant la carte piochée par un joueur n'ayant rien de jouable en main
{
    cout << "Le " << Player << " ne peut pas jouer de carte, il pioche : ";
    if (Card->_CardValue == Joker)
        cout << Card->GetValue().c_str() << endl;
    else
        cout << Card->GetValue().c_str() << Card->GetSymbol().c_str() << endl;
}
void View::EndOfGameDisplay(string PlayerName) //Vue affichant la fin de la partie et le gagnant final
{
    cout << "Fin de la partie, le " << PlayerName.c_str() << " a gagne." << endl;
    //cout << "Appuyer sur une touche pour continuer." << endl;
}
void View::ShowHumanPlayerCards(array<Card *, DECK_SIZE> *ArrayForDisplay) //Vue affichant la main du joueur humain (avec les indices pour chaque carte)
{                                                                          // appelé par 'Showhands()' [ligne 49] si le joueur actuel est Humain
    int Maxindex = 0;
    for (int i = 0; i < DECK_SIZE; i++) // on parcourt la main
    {
        if ((*ArrayForDisplay).at(i) == nullptr) // nullptr = on ignore
            continue;
        else // si une carte est présente
        {
            Maxindex++; // = 1, 2, 3, ... on incrémente l'index à la carte pour l'afficher
            if ((*ArrayForDisplay).at(i)->_CardValue == Joker)
                cout << "(" << Maxindex << ")" << (*ArrayForDisplay).at(i)->GetValue().c_str() << "  "; // example (1)Joker
            else
                cout << "(" << Maxindex << ")" << (*ArrayForDisplay).at(i)->GetValue().c_str()
                     << (*ArrayForDisplay).at(i)->GetSymbol().c_str() << "  "; // example (2)8♥
        }
    }
    cout << endl;
}

int View::AskHumanWhatToPlay(array<Card *, DECK_SIZE> *ArrayForDisplay) //Permet de savoir le nbre de carte que possède un joueur
{
    int Maxindex = 0;
    for (int i = 0; i < DECK_SIZE; i++)
    {
        if ((*ArrayForDisplay).at(i) == nullptr)
            continue;
        else
            Maxindex++;
    }
    ShowAskHumanWhatToPlay(1, Maxindex);
    return Maxindex;
}
void View::ShowAskHumanWhatToPlay(int StartIndex, int EndIndex) //Vue permettant de demander au joueur d'entrer une valeur comprise dans la suite de cartes de sa main
{
    if (StartIndex != EndIndex)
        cout << "Votre choix (entre " << StartIndex << " et " << EndIndex;
    else
        cout << "Dernière carte, " << StartIndex;

    cout << ", 0 pour ne pas jouer) : ";
}
void View::ShowHumanCantPlayThatCard() //Vue qui s'affiche quand une carte choisie est injouable
{
    cout << "Impossible de jouer cette carte :(" << endl;
}
void View::WhichColorDoYouWant() //Vue demandant quelle couleur le joueur veut appliquer après avoir joué un '8'
{
    cout << "Choix de la couleur  : (1 = Coeur, 2 = Carreau, 3 = Trefle, 4 = Pique) :";
}
void View::ShowDoYouWantToLeave() //Vue qui permet de demander au joueur s'il souhaite quitter le jeu ou non, à la fin d'une partie
{
    cout << "Voulez-vous continuer a jouer ? " << endl;
    cout << "Pour continuer appuyez sur 1, pour quitter appuyez sur 0 : ";
}