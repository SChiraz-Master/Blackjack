//Blackjack V2.0
//--------------
//Created by SChiraz on 01/12/2018
//Modified by SChiraz on 02/12/2018

//Blackjack V3.0
//--------------
//Modified by SChiraz on 15/12/2018
//Modified by SChiraz on 16/12/2018
//Modified by SChiraz on 17/12/2018

#include "Dealer.h"

Dealer::Dealer()
{
	EndRotation = false;
	Standby = true;
}
//--
Dealer::~Dealer()
{
}
//==
void Dealer::DealerHit(vector <Card> TheDeck, Player ThePlayer)
{
	bool EndTurn = false;

	if (CalcPoints(DHand) == 21)
	{
		this->HasBlackJack();
	}
	else if (ThePlayer.GetBlackJack() == false)
	{
		while (EndTurn == false)
		{
			if (((CalcPoints(DHand) <= ThePlayer.CalcPoints(ThePlayer.GetPHand())) && (ThePlayer.Bust(ThePlayer.GetPHand()) == false)) || ((CalcPoints(DHand) <= ThePlayer.CalcPoints(ThePlayer.GetSHand())) && (ThePlayer.Bust(ThePlayer.GetSHand()) == false)))
			{
				if (CalcPoints(DHand) < 17)
				{
					DHand.push_back(TheDeck[0]);
					TheDeck.erase(TheDeck.begin());

					DHand = AceUpdate(DHand);
				}
				else
				{
					EndTurn = true;
				}
			}
			else
			{
				EndTurn = true;
			}
		}
	}
}
//--
void Dealer::PrintDHand()
{
	for (int cpt = 0; cpt < DHand.size(); cpt++)
	{
		if (cpt == 1)
		{
			if ((EndRotation == false))
			{
				//--
				DHand[cpt].SetVisible(false);
				//--
			}
			else
			{
				DHand[cpt].SetVisible(true);
			}
		}
		//--
		int SPoint = (975 - DHand.size() * 75) / 2;
		DHand[cpt].SetXY(SPoint + 75 * cpt, 60);
		DHand[cpt].Draw();
		//--
	}
}
//--
void Dealer::DealerDraw(Card ACard)
{
	DHand.push_back(ACard);
	DHand = AceUpdate(DHand);
}
//==
void Dealer::SetStadby(bool Status)
{
	Standby = Status;;
}
//--
bool Dealer::GetStandby()
{
	return Standby;
}
//--
void Dealer::SetRotation(bool RotStat)
{
	EndRotation = RotStat;
}
//--
vector <Card> Dealer::GetDHand()
{
	return DHand;
}
//--
void Dealer::HandReset()
{
	DHand.clear();
}