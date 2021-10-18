#pragma once

#include <iostream>
#include <string>
#include <time.h>
#include <cstdlib>
#include <ctime>
#include <Windows.h>
#include <vector>

void login();
void game();
void playerCard();
void dealerCard();
void printSum();
void printHand();
int playerSum();
int dealerSum();

bool userResult{};
bool passResult{};

int playerCurrency = 100;
std::vector <int> playerHand;
bool playerTurn = true;
bool playerWin = false;


int dealerCurrency = 100;
std::vector <int> dealerHand;
bool dealerTurn = false;
bool dealerWin = false;

char aceInput{};
char input{};
int count{};
int betInput{};
int betWin{};

bool stopPlaying = false;
