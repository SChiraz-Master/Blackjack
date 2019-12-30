//Blackjack V2.0
//--------------
//Created by SChiraz on 01/12/2018

//Blackjack V3.0
//--------------
//Modified by SChiraz on 15/12/2018

#pragma once
#include <cstdlib>
#include <SDL.h>
#include <sdl_image.h>
#include <string>
using namespace std;

class Card
{
	int Value; //Card Value
	string Face;

public:
	Card(int, string);
	~Card();

	int GetValue();
	string GetFace();

	void SetValue(int);

	void CreateTexture(const char* filename, int xpos, int ypos, int width, int height, SDL_Renderer *GRenderer);
	void setCurrentFrame(Uint16, Uint16);
	void Draw();
	void SetXY(int, int);
	void SetVisible(bool);

private:
	void Load(const char* filename);

	SDL_Texture *imageF;
	SDL_Texture *imageB;
	SDL_Rect rect;
	int xpos, ypos;
	bool IsVisible;

	SDL_Renderer *CardRenderer;
};