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

#pragma once
#include "Dealer.h"
#include "Button.h"
#include "SDL_mixer.h"
#include <Windows.h>

class Game
{
	const int AUDIO_RATE = 44100;
	const Uint16 AUDIO_FORMAT = AUDIO_S16;
	const int AUDIO_CHANNELS = 2;
	const int AUDIO_BUFFERS = 2048;

	SDL_Window *GameWindow;
	SDL_Renderer *GameRenderer;
	SDL_Texture	*GameBG = nullptr;

	Mix_Music *GameMusic = nullptr;
	Mix_Chunk *Sound = nullptr;

	Uint32 deltaT = 75;
	Uint32 updatedTime = 0;

	SDL_Event GameEvents;

	Button *IncrementBtn = nullptr;
	Button *DecrementBtn = nullptr;
	Button *StandBtn = nullptr;
	Button *HitBtn = nullptr;
	Button *DoubleBtn = nullptr;
	Button *SurrenderBtn = nullptr;
	Button *SplitBtn = nullptr;
	Button *YesBtn = nullptr;
	Button *NoBtn = nullptr;

public:
	Game();
	~Game();

	void YNBtns();
	void ResetBtns();
	void DrawBtns();

	void GameMenu();
	void GameInstructions();
	void GameStart();
	void CurrentGameState(Player, Dealer, SDL_Renderer *CurrentGRender);
	Player GamesResults(Dealer, Player);

};