#pragma once

#include <chrono>
#include <thread>
#include "../View/View.hpp"
#include "../Model/Card.hpp"
#include "../Model/ComputerPlayer.hpp"
#include "../Model/HumanPlayer.hpp"
#include "../Model/Deck.hpp"
#include "../sqlite3/sqlite3.h" // Base de données (librairie SQL)
#include "DatabaseController.hpp"

#ifdef __linux__
#include <unistd.h>
#endif
#ifdef _WIN32
#include <windows.h>
#endif

class Game
{

public:
  ~Game();
  void LaunchGame(int AmountHumanPlayer);

private:
  array<Player *, PLAYER_AMOUNT> _PlayerArray = {0};
  array<Card *, DECK_SIZE> _DrawArray = {0};
  array<Card *, DECK_SIZE> _HeapArray = {0};
  bool _TurnIsClockwise = true;
  int _CurrentPlayer = 0;
  Deck _Deck;
  DatabaseController _DBCtrl;
  CardSymbolEnum _LastSymbol;
  CardValueEnum _LastValue;

  void CreatePlayers(int HumanPlayerAmount);
  void FillDraw();
  void FillHands();
  void FirstCardOnHeap();
  void Turn();
  void NextPlayer();
  void ClockwiseTurn();
  void CounterClockwiseTurn();

  void PlayOneCardFromHand();
  void AddCardOnHeap(Card *HeapCard);
  void GameRules(Card *Card);
  void ChangeLastCardData(CardValueEnum ValueLastCardPlay, CardSymbolEnum SymbolLastCardPlay);
  void DrawCard();
  Card *GetLastCardOnDraw();

  bool DrawIsEmpty();
  void RefillDraw();
  void ShuffleDraw(int Index);
  
  void ChangeColor(int ChoosenColor);
  void RevertTurn();
  void DealCards(int Amount);
  void SkipPlayer();
  void SamePlayer();

  bool EndOfRound();
  void CalculateScore();
  void ResetTheRound();
  bool EndOfGame();
  string GetWinner();
};