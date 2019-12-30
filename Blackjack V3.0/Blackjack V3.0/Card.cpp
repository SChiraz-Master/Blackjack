//Blackjack V2.0
//--------------
//Created by SChiraz on 01/12/2018

//Blackjack V3.0
//--------------
//Modified by SChiraz on 15/12/2018
//Modified by SChiraz on 16/12/2018

#include "Card.h"

Card::Card(int CV, string CF)
{
	Value = CV;
	Face = CF;
}
Card::~Card()
{
}
void Card::CreateTexture(const char* filename, int xpos, int ypos, int width, int height, SDL_Renderer *GRender)
{
	this->CardRenderer = GRender;

	rect.x = 0;
	rect.y = 0;
	rect.w = width;
	rect.h = height;

	this->xpos = xpos;
	this->ypos = ypos;

	this->IsVisible = true;

	Load(filename);
}
void Card::setCurrentFrame(Uint16 Row, Uint16 Col)
{
	if ((!rect.w) || (!rect.h))
		return;

	/** Calculate current frame of spritesheet */
	rect.x = Col * rect.w;
	rect.y = Row * rect.h;
}
void Card::Draw()
{
	if (this->IsVisible)
	{
		SDL_Rect dest = { xpos, ypos, rect.w, rect.h };

		SDL_RenderCopy(CardRenderer, imageF, &rect, &dest);
	}
	else
	{
		SDL_Rect dest = { xpos, ypos, rect.w, rect.h };

		SDL_RenderCopy(CardRenderer, imageB, nullptr, &dest);
	}

	SDL_RenderPresent(CardRenderer);
}
void Card::Load(const char* filename)
{
	imageF = IMG_LoadTexture(CardRenderer, filename);
	if (!imageF)
	{
		printf(IMG_GetError());
		exit(1);
	}
	//-
	imageB = IMG_LoadTexture(CardRenderer, "Imgs/CardBack.png");
	if (!imageB)
	{
		printf(IMG_GetError());
		exit(1);
	}
}

void Card::SetXY(int x, int y)
{
	xpos = x;
	ypos = y;
}

void Card::SetVisible(bool Visibility)
{
	IsVisible = Visibility;
}
//==
int Card::GetValue()
{
	return Value;
}
string Card::GetFace()
{
	return Face;
}
//==
void Card::SetValue(int NewValue)
{
	Value = NewValue;
}