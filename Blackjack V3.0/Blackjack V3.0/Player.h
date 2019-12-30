//Created by SChiraz on 01/12/2018
//Modified by SChiraz on 02/12/2018

//Blackjack V3.0
//--------------
//Modified by SChiraz on 16/12/2018
//Modified by SChiraz on 17/12/2018
//Modified by SChiraz on 18/12/2018

#pragma once
#include "Deck.h"
#include "BJ_Mics.h"

class Player : public BJ_Mics
{
	vector <Card> PHand;
	vector <Card> SHand;
	int Credits;
	int Bet1;
	int Bet2;
	int Insurance;

	const char* State;
	const char* State2;

public:
	Player();
	~Player();

	void PlayerHit(vector <Card>);
	void PlayerDouble(vector <Card>);
	
	void PlayerSplit(vector <Card>);
	void PlayerHitSHand(vector <Card>);

	void PrintPHand();

	vector <Card> GetPHand();
	vector <Card> GetSHand();
	int GetCredits();
	int GetBet1();
	int Getbet2();
	int GetInsurance();

	const char* GetState();
	const char* GetState2();

	void SetBet(int);
	void SetBet2();
	void SetInsurance(int);
	void UpdateCredits(int);

	void SetState(const char*);
	void SetState2(const char*);

	void PlayerDraw(Card);

	//-----------------------------
	void HandReset();
};