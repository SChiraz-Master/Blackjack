//Created by SChiraz on 01/12/2018
//Modified by SChiraz on 02/12/2018

#pragma once
#include "Deck.h"
#include "Player.h"
#include "BJ_Mics.h"

class Dealer : public BJ_Mics
{
	vector <Card> DHand;
	bool EndRotation;
	bool Standby;

public:
	Dealer();
	~Dealer();

	void DealerHit(vector <Card>, Player);
	void PrintDHand();
	void DealerDraw(Card);

	//-----------------------------

	void SetStadby(bool);
	bool GetStandby();
	void SetRotation(bool);

	vector <Card> GetDHand();
	void HandReset();
};