//Blackjack V3.0
//--------------
//Created by SChiraz on 16/12/2018

#include "Button.h"

Button::Button(const char* filename, int xpos, int ypos, int width, int height, SDL_Renderer *renderer)
{
	this->renderer = renderer;

	rect.x = 0;
	rect.y = 0;
	rect.w = width;
	rect.h = height;

	this->xpos = xpos;
	this->ypos = ypos;

	this->visible = true;

	load(filename);
}

Button::~Button()
{
	SDL_DestroyTexture(image);
}

void Button::load(const char* filename)
{
	image = IMG_LoadTexture(renderer, filename);

	if (!image)
	{
		printf(IMG_GetError());
		exit(1);
	}
}

void Button::draw()
{
	if (this->visible)
	{
		SDL_Rect dest = { xpos, ypos, rect.w, rect.h };

		SDL_RenderCopy(renderer, image, &rect, &dest);
	}
}

bool Button::CheckClick(int x, int y)
{
	if (this->visible)
	{
		if ((x >= xpos) && (x <= xpos + rect.w))
		{
			if ((y >= ypos) && (y <= (ypos + rect.h)))
			{
				return true;
			}
		}
	}
	return false;
}

SDL_Texture *Button::getImage()
{
	return this->image;
}

int Button::getWidth()
{
	return this->rect.w;
}

int Button::getHeight()
{
	return this->rect.h;
}

int Button::getXPos()
{
	return this->xpos;
}

int Button::getYPos()
{
	return this->ypos;
}

bool Button::isVisible()
{
	return this->visible;
}

void Button::setWidth(int width)
{
	this->rect.w = width;
}

void Button::setHeight(int height)
{
	this->rect.h = height;
}

void Button::setXPos(int x)
{
	this->xpos = x;
}

void Button::setYPos(int y)
{
	this->ypos = y;
}

void Button::setVisible(bool visible)
{
	this->visible = visible;
}