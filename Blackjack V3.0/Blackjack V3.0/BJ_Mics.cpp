//Created by SChiraz on 02/12/2018

#include "BJ_Mics.h"

BJ_Mics::BJ_Mics()
{
	Blackjack = false;
}

BJ_Mics::~BJ_Mics()
{
}
//==
void BJ_Mics::ResetBlackJack()
{
	Blackjack = false;
}
//--
void BJ_Mics::HasBlackJack()
{
	Blackjack = true;
}
//--
bool BJ_Mics::GetBlackJack()
{
	return Blackjack;
}
//--
int BJ_Mics::CalcPoints(vector <Card> TheHand)
{
	int Total = 0;
	if (TheHand.size() != NULL)
	{
		for (int cpt = 0; cpt < TheHand.size(); cpt++)
		{
			Total += TheHand[cpt].GetValue();
		}
		return Total;
	}
	else
	{
		return Total;
	}
}
//--
bool BJ_Mics::Bust(vector <Card> PlayerHand)
{
	if (CalcPoints(PlayerHand) > 21)
	{
		return true;
	}
	else
	{
		return false;
	}
}
//--
vector <Card> BJ_Mics::AceUpdate(vector <Card> TheHand)
{
	int Total = 0;
	int FirstAce = -1;

	for (int cpt = 0; cpt < TheHand.size(); cpt++)
	{
		if (((TheHand[cpt].GetValue() == 1) || (TheHand[cpt].GetValue() == 11)) && (FirstAce == -1))
		{
			FirstAce = cpt;
		}
		else
		{
			Total += TheHand[cpt].GetValue();
		}
	}
	//**
	if (Total <= 10)
	{
		if (FirstAce != -1)
		{
			TheHand[FirstAce].SetValue(11);
		}
		return TheHand;
	}
	else
	{
		if (FirstAce != -1)
		{
			TheHand[FirstAce].SetValue(1);
		}
		return TheHand;
	}
}