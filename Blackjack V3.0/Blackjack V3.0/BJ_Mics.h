//Created by SChiraz on 02/12/2018

#pragma once
#include "Deck.h"

class BJ_Mics
{
	bool Blackjack;

public:
	BJ_Mics();
	~BJ_Mics();

	void ResetBlackJack(); //**
	void HasBlackJack(); //**
	bool GetBlackJack(); //**

	int CalcPoints(vector <Card>); //**
	bool Bust(vector <Card>); //**
	vector <Card> AceUpdate(vector <Card>); //**
};