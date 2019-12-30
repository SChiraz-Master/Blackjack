//Blackjack V2.0
//--------------
//Created by SChiraz on 01/12/2018

//Blackjack V3.0
//--------------
//Modified by SChiraz on 15/12/2018

#pragma once
#include "Card.h"
#include <vector>
#include <algorithm>
#include <random>
#include <cstdlib> 
#include <ctime>
#include <iostream>

class Deck
{
	vector <Card> TheDeck;
	SDL_Renderer *Renderer;

public:
	Deck(SDL_Renderer *MyRenderer);
	~Deck();

	Card GetTopDeck();
	vector <Card> GetDeck();
	void DeckUpdate(int);
};