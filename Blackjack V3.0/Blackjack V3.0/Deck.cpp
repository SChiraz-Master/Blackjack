//Blackjack V2.0
//--------------
//Created by SChiraz on 01/12/2018

//Blackjack V3.0
//--------------
//Modified by SChiraz on 15/12/2018

#include "Deck.h"

int myrandom(int i) { return rand() % i; } //Randomize Seed

Deck::Deck(SDL_Renderer *GRenderer)
{
	this->Renderer = GRenderer;

	srand(time(nullptr)); // set seed according to TOD

	int CardValue;
	string CardFace;

	for (int cpt = 0; cpt < 4; cpt++)
	{
		for (int cpt2 = 0; cpt2 < 13; cpt2++)
		{
			if (cpt2 >= 9)
			{
				CardValue = 10;

				if (cpt2 == 10)
				{
					CardFace = "J";
				}
				else if (cpt2 == 11)
				{
					CardFace = "Q";
				}
				else if (cpt2 == 12)
				{
					CardFace = "K";
				}
			}
			else
			{
				CardValue = cpt2 + 1;
				CardFace = to_string(cpt2+1);
			}
			Card ACard(CardValue, CardFace);
			ACard.CreateTexture("Imgs/DeckV2.png", 0, 0, 75, 105, Renderer);
			ACard.setCurrentFrame(cpt, cpt2);
			TheDeck.push_back(ACard);
		}
	}
	random_shuffle(TheDeck.begin(), TheDeck.end(), myrandom);
}
//--
Deck::~Deck()
{
}
//==
Card Deck::GetTopDeck()
{
	return TheDeck[0];
}
//--
vector <Card> Deck::GetDeck()
{
	return TheDeck;
}
//--
void Deck::DeckUpdate(int Handsize)
{
	for (int cpt = 0; cpt < Handsize; cpt++)
	{
		TheDeck.erase(TheDeck.begin());
	}
}