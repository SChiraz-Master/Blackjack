//Blackjack V3.0
//--------------
//Created by SChiraz on 16/12/2018

#pragma once
#include <iostream>
#include <cstdlib>
#include <string>
#include <sdl.h>
#include <sdl_image.h>
#include <sdl_ttf.h>
#include <sdl_mixer.h>

using namespace std;

class Button
{
public:
	Button(const char* filename, int xpos, int ypos, int width, int height, SDL_Renderer *renderer);
	~Button();
	void draw();

	SDL_Texture *getImage();
	int getWidth();
	int getHeight();
	int getXPos();
	int getYPos();
	bool isVisible();

	void setWidth(int width);
	void setHeight(int height);
	void setXPos(int x);
	void setYPos(int y);
	void setVisible(bool visible);

	bool CheckClick(int, int);

private:
	void load(const char* filename);

	SDL_Texture *image;
	SDL_Rect rect;
	int xpos, ypos;
	bool visible;

	SDL_Renderer *renderer;

};

