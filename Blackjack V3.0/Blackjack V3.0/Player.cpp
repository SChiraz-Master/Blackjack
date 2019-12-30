//Blackjack V2.0
//--------------
//Created by SChiraz on 01/12/2018
//Modified by SChiraz on 02/12/2018

//Blackjack V3.0
//--------------
//Modified by SChiraz on 15/12/2018
//Modified by SChiraz on 16/12/2018
//Modified by SChiraz on 17/12/2018
//Modified by SChiraz on 18/12/2018

#include "Player.h"

Player::Player()
{
	Credits = 100;
	Bet1 = 1;
	Bet2 = 0;
	Insurance = 0;
	State = "N/A";
	State2 = "N/A";
}
//--
Player::~Player()
{
}
//==
void Player::PlayerHit(vector <Card> TheDeck)
{
	PHand.push_back(TheDeck[0]);
	PHand = AceUpdate(PHand);
	PrintPHand();
}
//--
void Player::PlayerDouble(vector <Card> TheDeck)
{
	Credits -= Bet1;
	Bet1 = Bet1 * 2;
	PHand.push_back(TheDeck[0]);
	PHand = AceUpdate(PHand);
}
//--
void Player::PlayerSplit(vector <Card> TheDeck)
{
	//-- Split hand
	SHand.push_back(PHand[1]);
	PHand.erase(PHand.end() - 1);

	//-- Deal 1 to each
	PHand.push_back(TheDeck[0]);
	TheDeck.erase(TheDeck.begin());

	SHand.push_back(TheDeck[0]);
	TheDeck.erase(TheDeck.begin());

	PHand = AceUpdate(PHand);
	SHand = AceUpdate(SHand);

	PrintPHand();
}
void Player::PlayerHitSHand(vector <Card> TheDeck)
{
	SHand.push_back(TheDeck[0]);
	SHand = AceUpdate(SHand);
	PrintPHand();
}
//==
void Player::PrintPHand()
{
	for (int cpt = 0; cpt < PHand.size(); cpt++)
	{
		int SPoint;

		if (SHand.size() != NULL)
		{ 
			SPoint = (975 - PHand.size() * 75) / 8;
		}
		else
		{
			SPoint = (975 - PHand.size() * 75) / 2;
		}

		PHand[cpt].SetXY(SPoint + 75 * cpt, 330);
		PHand[cpt].Draw();
	}

	if (SHand.size() != NULL)
	{
		for (int cpt = 0; cpt < SHand.size(); cpt++)
		{
			int SPoint = (975 - SHand.size() * 75) / 2;

			SHand[cpt].SetXY(SPoint+ 100 + 75 * cpt, 330);
			SHand[cpt].Draw();
		}
	}
}
//==
vector <Card> Player::GetPHand()
{
	return PHand;
}
//--
vector <Card> Player::GetSHand()
{
	return SHand;
}
//--
int Player::GetCredits()
{
	return Credits;
}
//
int Player::GetBet1()
{
	return Bet1;
}
//--
int Player::Getbet2()
{
	return Bet2;
}
//--
int Player::GetInsurance()
{
	return Insurance;
}
//--
const char* Player::GetState()
{
	return State;
}
const char* Player::GetState2()
{
	return State2;
}
//==
void Player::SetState(const char* Condition)
{
	State = Condition;
}
void Player::SetState2(const char* Condition)
{
	State2 = Condition;
}
//--
void Player::SetBet(int PlayerBet)
{
	Bet1 += PlayerBet;
}
//--
void Player::SetBet2()
{
	Bet2 = Bet1;
	Credits -= Bet2;
}
//--
void Player::SetInsurance(int PlayerInsurance)
{
	Insurance += PlayerInsurance;
	Bet1 -= PlayerInsurance;
}
//--
void Player::UpdateCredits(int Amount)
{
	Credits += Amount;
}
//==
void Player::PlayerDraw(Card ACard)
{
	PHand.push_back(ACard);
	PHand = AceUpdate(PHand);
}
//==
void Player::HandReset()
{
	PHand.clear();
	SHand.clear();
}
//--