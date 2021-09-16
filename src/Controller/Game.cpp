#include "Game.hpp"

//Classe permettant de gérer la partie

Game::~Game() //destructeur de la classe game afin de supprimer les objets "Players" créés par le mot-clé new
{
    for (int i = 0; i < PLAYER_AMOUNT; i++)
        delete this->_PlayerArray[i];
    //cout << "Suppression des joueurs..." << endl;
}
void Game::LaunchGame(int HumanPlayerAmount) //Méthode permettant de lancer les différentes méthodes nécessaires au déroulement de la partie
{
    _DBCtrl.SendDataToTableGames(); // Insertion de la partie en cours (ID + DateTime) dans la table 'Games'
    CreatePlayers(HumanPlayerAmount);
    do
    {
        FillDraw();
        FillHands();
        FirstCardOnHeap();
        View::GameStart();
        Turn();
        ResetTheRound();
    } while (!EndOfGame());
    View::EndOfGameDisplay(GetWinner());
}
void Game::CreatePlayers(int HumanPlayerAmount) //Méthode qui crée les joueurs, avec une main vide
{
    for (int i = 0; i < PLAYER_AMOUNT; i++)
    {
        if (i < HumanPlayerAmount)
            this->_PlayerArray[i] = new HumanPlayer("Joueur " + to_string(i + 1));
        else
            this->_PlayerArray[i] = new ComputerPlayer("Joueur " + to_string(i + 1));
    }
    _DBCtrl.SendDataToTablePlayers(&_PlayerArray); // Insertion des joueurs dans la table 'Players' (si pas déjà présents)
}
void Game::FillDraw() //Méthode qui crée la pioche à partir d'un modèle (classe Deck) qui est lui même mélangé avant cela
{
    this->_DrawArray = {0};
    for (int i = 0; i < _Deck.GetDeckSize(); i++)
        _DrawArray[i] = _Deck.GetCardAtIndex(i);
}
void Game::FillHands() // Méthode qui distribue les 7 premières cartes de la pioche, et ce pour chaque joueur
{
    for (_CurrentPlayer = 0; _CurrentPlayer < PLAYER_AMOUNT; _CurrentPlayer++)
    {
        for (int j = 0; j < HAND_SIZE; j++)
            _PlayerArray.at(_CurrentPlayer)->AddCardInHand(GetLastCardOnDraw());
    }
    _CurrentPlayer = 0;
}
void Game::FirstCardOnHeap() //Méthode qui place la première carte (différente du joker) sur le tas
{
    for (int i = 0; i < DECK_SIZE; i++)
    {
        Card *HeapCard = this->_DrawArray.at((DECK_SIZE - 1) - i);
        if (HeapCard == nullptr)
            continue;
        AddCardOnHeap(HeapCard);
        _DrawArray.at((DECK_SIZE - 1) - i) = nullptr;
        if (HeapCard->_CardValue != Joker)
            return;
    }
}
void Game::AddCardOnHeap(Card *HeapCard) //Méthode qui ajoute une carte sur le tas
{
    for (int i = 0; i < DECK_SIZE; i++)
    {
        if (_HeapArray.at(i) == nullptr)
        {
            _HeapArray.at(i) = HeapCard;
            if (!(HeapCard->_CardValue == Joker)) //il fallait entourer de parenthèses pour que le ! fonctionne correctement
                ChangeLastCardData(HeapCard->_CardValue, HeapCard->_CardSymbol);
            else
                _LastValue = Undefined;
            return;
        }
    }
}
void MySleep(int sleepMs) //Exécute une légère attente entre chaque tour de joueur
{
    #ifdef __linux__
        usleep(sleepMs * 1000);   // usleep takes sleep time in us (1 millionth of a second)
    #endif
    #ifdef _WIN32
        Sleep(sleepMs);
    #endif
}
void Game::Turn() //Gestion des tours de la partie jusqu'à ce qu'une main soit vide
{
    _CurrentPlayer--;
    do
    {
        //mySleep(500); // désactivé le temps de debug
        NextPlayer();
        PlayOneCardFromHand();
    } while (!EndOfRound());
    View::EndOfRoundDisplay(&_PlayerArray);
}
void Game::NextPlayer() //Permet de passer au joueur suivant qu'importe le sens du tour
{
    if (_TurnIsClockwise)
    {
        if (_CurrentPlayer == 3)
            _CurrentPlayer = 0;
        else
            _CurrentPlayer++;
    }
    else
    {
        if (_CurrentPlayer == 0)
            _CurrentPlayer = 3;
        else
            _CurrentPlayer--;
    }
}
void Game::PlayOneCardFromHand() //Méthode pour jouer une carte de la main du joueur actuel
{
    Card *HandCard = nullptr;
    View::ShowTurnDetails(&_HeapArray, &_DrawArray, Card::GetValueAtIndex(_LastValue), Card::GetSymbolAtIndex(_LastSymbol), &_PlayerArray, &_CurrentPlayer);
    HandCard = _PlayerArray.at(_CurrentPlayer)->PlayCardFromHand(_LastValue, _LastSymbol);
    if (HandCard == nullptr)
        DrawCard();
    else
    {
        View::ShowChosenCard(HandCard);
        AddCardOnHeap(HandCard);
        GameRules(HandCard);
        _DBCtrl.SendDataToTableCards(_CurrentPlayer, HandCard); // Insertion de la carte jouée depuis la main dans la table 'Cards'
    }
}
void Game::ChangeLastCardData(CardValueEnum ValueLastCardPlayed, CardSymbolEnum SymbolLastCardPlayed) //Actualise la valeur et le symbole de la dernière carte jouée
{
    this->_LastValue = ValueLastCardPlayed;
    this->_LastSymbol = SymbolLastCardPlayed;
}
void Game::GameRules(Card *Card) //Méthode permettant d'appliquer les règles selon la valeur de la carte jouée
{
    CardValueEnum CardValue = Card->_CardValue;
    switch (CardValue)
    {
    case As:
        RevertTurn();
        View::ShowEffect(CardValue);
        break;
    case Deux:
        DealCards(2);
        View::ShowEffect(CardValue);
        break;
    case Huit:
        ChangeColor(_PlayerArray.at(_CurrentPlayer)->ChoseColor());
        View::ShowEffect(CardValue);
        break;
    case Dix:
        SamePlayer();
        View::ShowEffect(CardValue);
        break;
    case Valet:
        NextPlayer();
        View::ShowEffect(CardValue);
        break;
    case Joker:
        DealCards(4);
        View::ShowEffect(CardValue);
        break;
    default:
        break;
    }
}
void Game::SamePlayer() //Méthode permettant de faire rejouer le même joueur
{
    _TurnIsClockwise = !_TurnIsClockwise;
    NextPlayer();
    _TurnIsClockwise = !_TurnIsClockwise;
}
void Game::ChangeColor(int ChosenColor) //Méthode permettant de changer la couleur choisie
{
    _LastSymbol = CardSymbolEnum(ChosenColor);
}
void Game::RevertTurn() //Méthode permettant de changer le sens du tour
{
    _TurnIsClockwise = !_TurnIsClockwise;
}
void Game::DealCards(int Amount) //Méthode permettant de donner un nombre de cartes précis au joueur suivant
{
    NextPlayer();
    for (int i = 0; i < Amount; i++)
        _PlayerArray.at(_CurrentPlayer)->AddCardInHand(GetLastCardOnDraw());
    _TurnIsClockwise = !_TurnIsClockwise;
    NextPlayer();
    _TurnIsClockwise = !_TurnIsClockwise;
}
void Game::DrawCard() //Méthode permettant de piocher une carte et de la jouer si elle peut être posée
{
    Card *Card = GetLastCardOnDraw();
    View::ShowDrawACard(_PlayerArray.at(_CurrentPlayer)->GetPlayerName(), Card);
    if (Card->CanBePlaced(_LastValue, _LastSymbol))
    {
        AddCardOnHeap(Card);
        _DBCtrl.SendDataToTableCards(_CurrentPlayer, Card); // Insertion de la carte piochée depuis le deck (si jouée) dans la table 'Cards'
        GameRules(Card);
    }
    else
        _PlayerArray.at(_CurrentPlayer)->AddCardInHand(Card);
}
Card *Game::GetLastCardOnDraw() //Méthode permettant de récupérer la carte du dessus de la pioche
{
    Card *DealCard;
    if (DrawIsEmpty())
        RefillDraw();
    for (int i = DECK_SIZE - 1; i >= 0; i--)
    {
        DealCard = this->_DrawArray[i];
        if (DealCard != nullptr)
        {
            _DrawArray[i] = nullptr;
            return DealCard;
        }
    }
    return nullptr;
}
bool Game::DrawIsEmpty() //Méthode permettant de vérifier si la pioche est vide
{
    for (int i = 0; i < DECK_SIZE; i++)
    {
        if (_DrawArray.at(i) != nullptr)
            return false;
    }
    return true;
}
void Game::RefillDraw() //Méthode permettant de remplir la pioche quand celle-ci est vide
{
    _DrawArray.swap(_HeapArray); // contenu du tas -> pioche, et inversément
    int Index;
    for (Index = (DECK_SIZE - 1); Index >= 0; Index--) // on commence à la fin du _Deck
    {
        if (_DrawArray.at(Index) != nullptr)
        {                                            // jusqu'à trouver la dernière carte jouée
            _HeapArray.at(0) = _DrawArray.at(Index); // on la pose sur le tas
            _DrawArray.at(Index) = nullptr;          // et on la supprime de la pioche
            break;
        }
    }
    ShuffleDraw(Index); //on mélange la pioche (sans toucher aux nullptr)
    View::ShowRefill();
}
int MyRandom(int i) { return std::rand() % i; } //Méthode permettant de générer un random, utilisé par ShuffleDraw()
void Game::ShuffleDraw(int Index)               //Méthode permettant de mélanger la pioche
{
    srand(time(0));
    random_shuffle(&_DrawArray.at(0), &_DrawArray.at(Index), MyRandom); //Mélange la pioche de 0 (inclus) jusqu'à index (non inclus)
    View::ShowCards(&_DrawArray);                                       //Afin de démontrer le refill et le shuffle sur la pioche
}
bool Game::EndOfRound() //Méthode permettant de vérifier si on a atteint la fin d'un round
{
    if (_PlayerArray.at(_CurrentPlayer)->GetIfHandIsEmpty())
    {
        CalculateScore();
        return true;
    }
    else
        return false;
}
void Game::CalculateScore() //Méthode permettant le calcul des scores de chaque joueur
{
    for (_CurrentPlayer = 0; _CurrentPlayer < PLAYER_AMOUNT; _CurrentPlayer++) // pour chaque joueur
        _PlayerArray.at(_CurrentPlayer)->CalculatePlayerScore();               // Chaque joueur calcule son score
}
bool Game::EndOfGame() //Méthode permettant de vérifier si on a le score nécessaire pour mettre fin à la partie
{
    for (int i = 0; i < PLAYER_AMOUNT; i++)
    {
        if (_PlayerArray.at(i)->GetPlayerScore() >= WIN_SCORE)
        {
            _DBCtrl.SendDataToTableScores("Partie", &_PlayerArray); // 500 pts = envoi des scores + type "Partie"
            return true;
        }
    }
    _DBCtrl.SendDataToTableScores("Round", &_PlayerArray); // si pas de 500 pts, envoi des scores + type "Round"
    return false;
}
string Game::GetWinner() //Méthode permettant de retourner le gagnant de la partie
{
    Player *Winner = this->_PlayerArray.at(0);
    for (int i = 1; i < PLAYER_AMOUNT; i++)
    {
        if (this->_PlayerArray.at(i)->GetPlayerScore() < Winner->GetPlayerScore())
            Winner = this->_PlayerArray.at(i);
    }
    _DBCtrl.UpdateTablePlayersForWinner(Winner); // Met à jour la table 'Players' pour ajouter une victoire au joueur ayant remporté la partie
    return Winner->GetPlayerName();
}
void Game::ResetTheRound() //Méthode permettant de remettre à zéro ce qui doit l'être pour démarrer un autre round
{
    _CurrentPlayer = 0;
    _TurnIsClockwise = true;
    _HeapArray = {0};
    _DrawArray = {0};
    for (int i = 0; i < PLAYER_AMOUNT; i++)
        _PlayerArray.at(i)->ResetHand();
    _Deck.Shuffle();
}