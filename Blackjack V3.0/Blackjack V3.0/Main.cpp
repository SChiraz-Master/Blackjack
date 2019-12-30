//Blackjack V1.0
//--------------
//Created by SChiraz on 11/11/2018
//Modified by SChiraz on 14/11/2018
//--------------

//Blackjack V2.0
//--------------
//Modified by SChiraz on 01/12/2018

//Blackjack V3.0
//--------------
//Modified by SChiraz on 15/12/2018

#include "Game.h"

using namespace std;

int main(int argc, char **argv)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "SDL_Init Error: " << SDL_GetError() << endl;
		return 1;
	}

	Game MyGame;
	MyGame.GameMenu();

	SDL_Quit();
	return 0;
}