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

#include "Game.h"
#include <SDL_ttf.h>
#include <iostream>

Game::Game()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) != 0)
	{
		cerr << "\nUnable to initialize SDL: " << SDL_GetError() << endl;
		exit(1);
	}
	atexit(SDL_Quit);

	GameWindow = SDL_CreateWindow("Blackjack", 100, 100, 975, 514, SDL_WINDOW_SHOWN);
	if (!GameWindow)
	{
		cerr << "SDL_CreateWindow Error: " << SDL_GetError() << endl;
		exit(1);
	}

	GameRenderer = SDL_CreateRenderer(GameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!GameRenderer)
	{
		cerr << "SDL_CreateRenderer Error: " << SDL_GetError() << endl;
		exit(1);
	}

	IncrementBtn = new Button("Imgs/Increment.png", 557.5f, 480, 32, 32, GameRenderer);

	DecrementBtn = new Button("Imgs/Decrement.png", 387.5f, 480, 32, 32, GameRenderer);

	StandBtn = new Button("Imgs/button_stand.png", 111.75f / 2, 257, 96, 40, GameRenderer);
	StandBtn->setVisible(false);

	HitBtn = new Button("Imgs/button_hit.png", 257.75f, 257, 68, 40, GameRenderer);
	HitBtn->setVisible(false);

	DoubleBtn = new Button("Imgs/button_double.png", 646.75f, 257, 111, 40, GameRenderer);
	DoubleBtn->setVisible(false);

	SurrenderBtn = new Button("Imgs/button_surrender.png", 792.75f, 257, 141, 40, GameRenderer);
	SurrenderBtn->setVisible(false);

	SplitBtn = new Button("Imgs/button_split.png", 0, 474, 84, 40, GameRenderer);
	SplitBtn->setVisible(false);

	YesBtn = new Button("Imgs/button_yes.png", 975 / 4, 514 / 2, 73, 40, GameRenderer);
	YesBtn->setVisible(false);

	NoBtn = new Button("Imgs/button_no.png", 663.25f, 514 / 2, 68, 40, GameRenderer);
	NoBtn->setVisible(false);

	if (Mix_OpenAudio(AUDIO_RATE, AUDIO_FORMAT, AUDIO_CHANNELS, AUDIO_BUFFERS) < 0)
	{
		cerr << "MixAudio Error: " << Mix_GetError() << endl;
	}
	atexit(Mix_CloseAudio);

	GameMusic = Mix_LoadMUS("Sound/Milk_Bar.ogg");
	if (!GameMusic) { cerr << "Mix_LoadMUS Error: " << Mix_GetError() << endl; }

	Sound = Mix_LoadWAV("Sound/Click.wav");
	if (!Sound) { cerr << "Mix_LoadWAV Error: " << Mix_GetError() << endl; }
}
Game::~Game()
{
	SDL_DestroyTexture(GameBG);
	GameBG = nullptr;

	SDL_DestroyRenderer(GameRenderer);
	GameRenderer = nullptr;

	SDL_DestroyWindow(GameWindow);
	GameWindow = nullptr;

	delete IncrementBtn;
	IncrementBtn = nullptr;

	delete DecrementBtn;
	DecrementBtn = nullptr;

	delete StandBtn;
	StandBtn = nullptr;

	delete HitBtn;
	HitBtn = nullptr;

	delete DoubleBtn;
	DoubleBtn = nullptr;

	delete SurrenderBtn;
	SurrenderBtn = nullptr;

	delete SplitBtn;
	SplitBtn = nullptr;

	delete YesBtn;
	YesBtn = nullptr;

	delete NoBtn;
	NoBtn = nullptr;

	Mix_HaltMusic();
	Mix_FreeMusic(GameMusic);
	Mix_FreeChunk(Sound);
}
//==
void Game::YNBtns()
{
	YesBtn->setVisible(true);
	NoBtn->setVisible(true);

	StandBtn->setVisible(false);
	HitBtn->setVisible(false);
	DoubleBtn->setVisible(false);
	SurrenderBtn->setVisible(false);
	SplitBtn->setVisible(false);
}
void Game::ResetBtns()
{
	YesBtn->setVisible(false);
	NoBtn->setVisible(false);
	IncrementBtn->setVisible(false);
	DecrementBtn->setVisible(false);

	StandBtn->setVisible(true);
	HitBtn->setVisible(true);
	DoubleBtn->setVisible(true);
	SurrenderBtn->setVisible(true);
	SplitBtn->setVisible(false);
}
void Game::DrawBtns()
{
	StandBtn->draw();
	HitBtn->draw();
	DoubleBtn->draw();
	SurrenderBtn->draw();
	SplitBtn->draw();
	YesBtn->draw();
	NoBtn->draw();
	IncrementBtn->draw();
	DecrementBtn->draw();
}
//==
void Game::GameMenu()
{
	Mix_PlayMusic(GameMusic, -1);

	GameBG = IMG_LoadTexture(GameRenderer, "Imgs/MenuBG.png");
	if (!GameBG) { cerr << "SDL_LoadTexture Error: " << (IMG_GetError()); exit(1); }

	bool OnMenu = true;
	bool Start = false;

	TTF_Init();

	TTF_Font* Myfont = TTF_OpenFont("Fonts/AlexBrush-Regular.ttf", 100);
	if (!Myfont) { printf("Unable to open font"); exit(1); }

	SDL_Color White = { 255, 255, 255 };
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Myfont, "Blackjack", White);
	SDL_Texture* Title = SDL_CreateTextureFromSurface(GameRenderer, surfaceMessage);

	int texW = 100;
	int texH = 100;

	SDL_QueryTexture(Title, NULL, NULL, &texW, &texH);
	SDL_Rect MsgLocation = { (975 / 2) - 150, 0, texW, texH };
	//--
	Button *StartBtn = nullptr;
	StartBtn = new Button("Imgs/button_start.png", (975 - 100) / 2, 200, 100, 40, GameRenderer);

	Button *InstructionsBtn = nullptr;
	InstructionsBtn = new Button("Imgs/button_instructions.png", (975 - 161) / 2, 300, 161, 40, GameRenderer);

	Button *QuitBtn = nullptr;
	QuitBtn = new Button("Imgs/button_quit.png", (975 - 86) / 2, 400, 86, 40, GameRenderer);

	//--
	while (OnMenu)
	{
		if (SDL_GetTicks() - updatedTime >= deltaT)
		{
			while (SDL_PollEvent(&GameEvents))
			{
				switch (GameEvents.type)
				{
				case SDL_QUIT:
					OnMenu = false;
					break;

				case SDL_MOUSEBUTTONDOWN:
					Uint32 SDL_GetMouseState(int* x, int* y);
					
					if (StartBtn->CheckClick(GameEvents.button.x, GameEvents.button.y))
					{
						Mix_PlayChannel(-1, Sound, 0);
						OnMenu = false;
						Start = true;
						break;
					}
					else if (InstructionsBtn->CheckClick(GameEvents.button.x, GameEvents.button.y))
					{
						Mix_PlayChannel(-1, Sound, 0);
						GameInstructions();
						break;
					}
					else if (QuitBtn->CheckClick(GameEvents.button.x, GameEvents.button.y))
					{
						Mix_PlayChannel(-1, Sound, 0);
						OnMenu = false;
						break;
					}

					break;
				}
			}
			updatedTime = SDL_GetTicks();
		}
		SDL_RenderCopy(GameRenderer, GameBG, nullptr, nullptr);
		SDL_RenderCopy(GameRenderer, Title, NULL, &MsgLocation);

		StartBtn->draw();
		InstructionsBtn->draw();
		QuitBtn->draw();

		SDL_RenderPresent(GameRenderer);
	}

	delete StartBtn;
	StartBtn = nullptr;

	delete InstructionsBtn;
	InstructionsBtn = nullptr;

	delete QuitBtn;
	QuitBtn = nullptr;

	//--
	TTF_CloseFont(Myfont);
	SDL_DestroyTexture(Title);
	SDL_FreeSurface(surfaceMessage);

	TTF_Quit();
	//--

	if(Start){ GameStart(); }
}
//--
void Game::GameInstructions()
{
	const char* Instrucitons;

	Instrucitons = "The object of blackjack is to get as close to 21 as possible, without going over!\n\n Here is how you play:\n1- Blackjack may be played with one to eight decks of 52-card decks. \n\n2- Aces may be counted as 1 or 11 points, 2 to 9 according to pip value, and tens and face cards count as ten points. \n\n3- The value of a hand is the sum of the point values of the individual cards. Except, a 'blackjack' is the highest hand, consisting of an ace and any 10-pointcard, and it outranks all other 21-point hands. \n\n4- After the players have Bet1, the dealer will give two cards to each player and two cards to himself. One of the dealer cards is dealt face up. The facedowncard is called the 'hole card'. \n\n5- If the dealer has an ace showing, he will offer a side Bet1 called 'Insurance'. This side wager pays 2 to 1 if the dealer's hole card is any 10-point card. Insurance wagers are optional and may not exceed half the original wager. \n\n6- If the dealer has a ten or an ace showing (after offering insurance with an ace showing), then he will peek at his facedown card to see if he has a blackjack. If he does, then he will turn it over immediately. \n\n7- If the dealer does have a blackjack, then all wagers (except insurance) will lose, unless the player also has a blackjack, which will result in a push. The dealer will resolve insurance wagers at this time. \n\n8- Play begins with the player to the dealer's left. The following are the choices available to the player: \n\n	a) STAND: Player stands pat with his cards.\n\n	b) HIT: Player draws another card (and more if he wishes). If this card causes the player's total points to exceed 21 (known as 'breaking' or\n	'busting') then he loses.\n\n	c) DOUBLE: Player doubles his Bet1 and gets one, and only one, more card.\n\n	d) SPLIT: If the player has a pair, or any two 10-point cards, then he may double his Bet1 and separate his cards into two individual hands. The dealer will automatically give each card a second card.\n	Then, the player may hit, stand, or double normally. However, when splitting aces, each ace gets only one card. If the player gets a ten and ace after splitting, then it counts as 21 points, not a\n	blackjack. You can only split once.\n\n	e) SURRENDER: The player forfeits half his wager, keeping the other half, and does not play out his hand. This option is only available on the initial two cards.\n\n9- After each player has had his turn, the dealer will turn over his hole card. If the dealer has 16 or less, then he will draw another card. A special situation is when the dealer has an ace and any number of cards totaling six points (known as a 'soft 17'). The dealer can also hit a on a soft 17.\n\n10- If the dealer goes over 21 points, then any player who didn't already bust will win.\n\n11- If the dealer does not bust, then the higher point total Bet1ween the player and dealer will win.\n\n12- Winning wagers pay even money, except a winning player blackjack pays 3 to 2.";

	MessageBox(NULL, Instrucitons, "Instructions", MB_OK | MB_ICONQUESTION);
}
//--
void Game::GameStart()
{
	GameBG = IMG_LoadTexture(GameRenderer, "Imgs/GameBG.png");
	if (!GameBG) {cerr << "IMG_LoadTexture Error: " << IMG_GetError() << endl; return;}

	Player ThePlayer;
	Dealer TheDealer;

	//== Text
	TTF_Init();

	TTF_Font* Myfont = TTF_OpenFont("Fonts/Oswald-Regular.ttf", 24);
	if (!Myfont) { printf("Unable to open font"); exit(1); }
	SDL_Color White = { 255, 255, 255 };
	int texW = 150;
	int texH = 100;


	SDL_Surface* PlayerState = TTF_RenderText_Solid(Myfont, "Hand 1 Status", White);
	SDL_Texture* CurrentState = SDL_CreateTextureFromSurface(GameRenderer, PlayerState);

	SDL_QueryTexture(CurrentState, NULL, NULL, &texW, &texH);
	SDL_Rect StateLoc = { 90, 105, texW, texH };
	//--
	SDL_Surface* PlayerState2 = TTF_RenderText_Solid(Myfont, "Hand 2 Status", White);
	SDL_Texture* CurrentState2 = SDL_CreateTextureFromSurface(GameRenderer, PlayerState2);

	SDL_QueryTexture(CurrentState2, NULL, NULL, &texW, &texH);
	SDL_Rect State2Loc = { 90, 135, texW, texH };
	//--
	SDL_Surface* MsgText = TTF_RenderText_Solid(Myfont, "Is this your wager ?", White);
	SDL_Texture* CurrentMsg = SDL_CreateTextureFromSurface(GameRenderer, MsgText);

	SDL_QueryTexture(CurrentMsg, NULL, NULL, &texW, &texH);
	SDL_Rect MsgLocation = { 407.5f, 260, texW, texH };
	//--
	SDL_Surface* Bet1Amount = TTF_RenderText_Solid(Myfont, "Current bet: 1", White);
	SDL_Texture* CurrentBet1 = SDL_CreateTextureFromSurface(GameRenderer, Bet1Amount);

	SDL_QueryTexture(CurrentBet1, NULL, NULL, &texW, &texH);
	SDL_Rect BetLocation = { 427.5f, 480, texW, texH };
	//--
	SDL_Surface* Bet2Amount = TTF_RenderText_Solid(Myfont, "Second bet: XX", White);
	SDL_Texture* CurrentBet2 = SDL_CreateTextureFromSurface(GameRenderer, Bet2Amount);

	SDL_QueryTexture(CurrentBet2, NULL, NULL, &texW, &texH);
	SDL_Rect Bet2Location = { 5, 165, texW, texH };
	//--
	SDL_Surface* Credits = TTF_RenderText_Solid(Myfont, "Current credits: 100", White);
	SDL_Texture* CurrentCredits = SDL_CreateTextureFromSurface(GameRenderer, Credits);

	SDL_QueryTexture(CurrentCredits, NULL, NULL, &texW, &texH);
	SDL_Rect CredLoc = { 5, 70, texW, texH };
	//--
	SDL_Surface* TxtIns = TTF_RenderText_Solid(Myfont, "Current Insurance: 0", White);
	SDL_Texture* CurrentIns = SDL_CreateTextureFromSurface(GameRenderer, TxtIns);

	SDL_QueryTexture(CurrentIns, NULL, NULL, &texW, &texH);
	SDL_Rect InsLoc = { 5, 195, texW, texH };
	//--
	SDL_Surface* PTotal = TTF_RenderText_Solid(Myfont, "Total: XX", White);
	SDL_Texture* CurPtotal = SDL_CreateTextureFromSurface(GameRenderer, PTotal);

	SDL_QueryTexture(CurPtotal, NULL, NULL, &texW, &texH);
	SDL_Rect TotalLoc = { 5, 105, texW, texH };
	//--
	SDL_Surface* PTotal2 = TTF_RenderText_Solid(Myfont, "Total: XX", White);
	SDL_Texture* CurPtotal2 = SDL_CreateTextureFromSurface(GameRenderer, PTotal2);

	SDL_QueryTexture(CurPtotal2, NULL, NULL, &texW, &texH);
	SDL_Rect Total2Loc = { 5, 135, texW, texH };
	//--
	SDL_Surface* DTotal = TTF_RenderText_Solid(Myfont, "Dealer's Total: XX", White);
	SDL_Texture* CurDtotal = SDL_CreateTextureFromSurface(GameRenderer, DTotal);

	SDL_QueryTexture(CurDtotal, NULL, NULL, &texW, &texH);
	SDL_Rect TotalDLoc = { 810, 110, texW, texH };
	//--

	//==

	YesBtn->setVisible(true);

	bool PlayAgain = true;

	SDL_RenderCopy(GameRenderer, GameBG, nullptr, nullptr);
	while (PlayAgain == true)
	{
		NoBtn->setVisible(false);
		IncrementBtn->setVisible(true);
		DecrementBtn->setVisible(true);

		bool PlaceBet = true;
		while (PlaceBet)
		{
			if (SDL_GetTicks() - updatedTime >= deltaT)
			{
				while (SDL_PollEvent(&GameEvents))
				{
					switch (GameEvents.type)
					{
					case SDL_QUIT:
						PlaceBet = false;
						break;

					case SDL_MOUSEBUTTONDOWN:

						if (IncrementBtn->CheckClick(GameEvents.button.x, GameEvents.button.y))
						{
							Mix_PlayChannel(-1, Sound, 0);
							if (ThePlayer.GetBet1() < ThePlayer.GetCredits())
							{
								SDL_RenderCopy(GameRenderer, GameBG, nullptr, nullptr);

								ThePlayer.SetBet(1);

								string Bet = "Current bet: " + to_string(ThePlayer.GetBet1());
								Bet1Amount = TTF_RenderText_Solid(Myfont, Bet.c_str(), White);
								CurrentBet1 = SDL_CreateTextureFromSurface(GameRenderer, Bet1Amount);
							}

							break;
						}
						else if (DecrementBtn->CheckClick(GameEvents.button.x, GameEvents.button.y))
						{
							Mix_PlayChannel(-1, Sound, 0);
							if (ThePlayer.GetBet1() > 1)
							{
								SDL_RenderCopy(GameRenderer, GameBG, nullptr, nullptr);

								ThePlayer.SetBet(-1);

								string Bet = "Current bet: " + to_string(ThePlayer.GetBet1());
								Bet1Amount = TTF_RenderText_Solid(Myfont, Bet.c_str(), White);
								CurrentBet1 = SDL_CreateTextureFromSurface(GameRenderer, Bet1Amount);
							}

							break;
						}
						else if (YesBtn->CheckClick(GameEvents.button.x, GameEvents.button.y))
						{
							Mix_PlayChannel(-1, Sound, 0);
							PlaceBet = false;
							IncrementBtn->setVisible(false);
							DecrementBtn->setVisible(false);
							break;
						}

						break;
					}
				}
				updatedTime = SDL_GetTicks();
			}
			SDL_RenderCopy(GameRenderer, CurrentMsg, NULL, &MsgLocation);

			SDL_RenderCopy(GameRenderer, CurrentCredits, NULL, &CredLoc);
			SDL_RenderCopy(GameRenderer, CurrentBet1, NULL, &BetLocation);

			DrawBtns();
			CurrentGameState(ThePlayer, TheDealer, GameRenderer);

			SDL_RenderPresent(GameRenderer);
		}

		//--
		ThePlayer.UpdateCredits(-(ThePlayer.GetBet1()));

		string PCredits = "Current credits: " + to_string(ThePlayer.GetCredits());
		Credits = TTF_RenderText_Solid(Myfont, PCredits.c_str(), White);
		CurrentCredits = SDL_CreateTextureFromSurface(GameRenderer, Credits);

		Deck TheDeck(GameRenderer);


		for (int cpt = 0; cpt < 2; cpt++)
		{
			ThePlayer.PlayerDraw((TheDeck.GetTopDeck()));
			TheDeck.DeckUpdate(1);
		}
		for (int cpt = 0; cpt < 2; cpt++)
		{
			TheDealer.DealerDraw((TheDeck.GetTopDeck()));
			TheDeck.DeckUpdate(1);
		}


		string Total = "Total: " + to_string(ThePlayer.CalcPoints(ThePlayer.GetPHand()));
		PTotal = TTF_RenderText_Solid(Myfont, Total.c_str(), White);
		CurPtotal = SDL_CreateTextureFromSurface(GameRenderer, PTotal);
		
		if (TheDealer.GetDHand()[0].GetValue() == 11)
		{
			if (ThePlayer.GetBet1() > 1)
			{
				MessageBox(NULL, "Dealer has an Ace,\n Enter your Insurance amount.", "Game Info.", MB_OK | MB_ICONQUESTION);

				MsgText = TTF_RenderText_Solid(Myfont, "Is this the desired amount ?", White);
				CurrentMsg = SDL_CreateTextureFromSurface(GameRenderer, MsgText);

				IncrementBtn->setVisible(true);
				DecrementBtn->setVisible(true);

				SDL_RenderCopy(GameRenderer, GameBG, nullptr, nullptr);
				CurrentGameState(ThePlayer, TheDealer, GameRenderer);

				bool PlacedInc = true;
				while (PlacedInc)
				{
					if (SDL_GetTicks() - updatedTime >= deltaT)
					{
						while (SDL_PollEvent(&GameEvents))
						{
							switch (GameEvents.type)
							{
							case SDL_QUIT:
								PlacedInc = false;
								break;

							case SDL_MOUSEBUTTONDOWN:

								if (IncrementBtn->CheckClick(GameEvents.button.x, GameEvents.button.y))
								{
									SDL_RenderCopy(GameRenderer, GameBG, nullptr, nullptr);
									CurrentGameState(ThePlayer, TheDealer, GameRenderer);

									if (ThePlayer.GetInsurance() < ThePlayer.GetBet1())
									{
										ThePlayer.SetInsurance(1);

										string Ins = "Current Insurance: " + to_string(ThePlayer.GetInsurance());
										TxtIns = TTF_RenderText_Solid(Myfont, Ins.c_str(), White);
										CurrentIns = SDL_CreateTextureFromSurface(GameRenderer, TxtIns);

										string Bet = "Current bet: " + to_string(ThePlayer.GetBet1());
										Bet1Amount = TTF_RenderText_Solid(Myfont, Bet.c_str(), White);
										CurrentBet1 = SDL_CreateTextureFromSurface(GameRenderer, Bet1Amount);
									}

									break;
								}
								else if (DecrementBtn->CheckClick(GameEvents.button.x, GameEvents.button.y))
								{
									SDL_RenderCopy(GameRenderer, GameBG, nullptr, nullptr);
									CurrentGameState(ThePlayer, TheDealer, GameRenderer);

									if (ThePlayer.GetInsurance() >= 1)
									{
										ThePlayer.SetInsurance(-1);

										string Ins = "Current Insurance: " + to_string(ThePlayer.GetInsurance());
										TxtIns = TTF_RenderText_Solid(Myfont, Ins.c_str(), White);
										CurrentIns = SDL_CreateTextureFromSurface(GameRenderer, TxtIns);

										string Bet = "Current bet: " + to_string(ThePlayer.GetBet1());
										Bet1Amount = TTF_RenderText_Solid(Myfont, Bet.c_str(), White);
										CurrentBet1 = SDL_CreateTextureFromSurface(GameRenderer, Bet1Amount);
									}

									break;
								}
								else if (YesBtn->CheckClick(GameEvents.button.x, GameEvents.button.y))
								{
									SDL_RenderCopy(GameRenderer, GameBG, nullptr, nullptr);
									CurrentGameState(ThePlayer, TheDealer, GameRenderer);

									PlacedInc = false;
									IncrementBtn->setVisible(false);
									DecrementBtn->setVisible(false);
									break;
								}

								break;
							}
						}
						updatedTime = SDL_GetTicks();
					}
					SDL_RenderCopy(GameRenderer, CurrentMsg, NULL, &MsgLocation);

					SDL_RenderCopy(GameRenderer, CurrentCredits, NULL, &CredLoc);
					SDL_RenderCopy(GameRenderer, CurrentBet1, NULL, &BetLocation);
					SDL_RenderCopy(GameRenderer, CurrentIns, NULL, &InsLoc);

					DrawBtns();
					SDL_RenderPresent(GameRenderer);
				}
			}		
		}

		bool RoundStart = true;

		if (TheDealer.CalcPoints((TheDealer.GetDHand())) == 21) { TheDealer.HasBlackJack(); }
		//*********************************
		if ((TheDealer.GetDHand()[0].GetValue() == 11) && (TheDealer.GetDHand()[1].GetValue() == 10)){ RoundStart = false;}
		//*********************************
		if (ThePlayer.CalcPoints((ThePlayer.GetPHand())) == 21){ThePlayer.HasBlackJack();RoundStart = false;}
		//*********************************

		SDL_RenderCopy(GameRenderer, GameBG, nullptr, nullptr);
		TheDealer.SetStadby(false);
		ResetBtns();
		if ((ThePlayer.GetPHand()[0].GetFace() == ThePlayer.GetPHand()[1].GetFace()) && (ThePlayer.GetCredits() >= ThePlayer.GetBet1() * 2))
		{
			if ((ThePlayer.GetBet1()) <= ThePlayer.GetCredits())
			{
				SplitBtn->setVisible(true);
			}
		}

		MsgText = TTF_RenderText_Solid(Myfont, "What would you like to do ?", White);
		CurrentMsg = SDL_CreateTextureFromSurface(GameRenderer, MsgText);

		bool Surrender = false;

		while (RoundStart)
		{
			if (SDL_GetTicks() - updatedTime >= deltaT)
			{
				while (SDL_PollEvent(&GameEvents))
				{
					switch (GameEvents.type)
					{
					case SDL_QUIT:
						RoundStart = false;
						break;

					case SDL_MOUSEBUTTONDOWN:

						if (StandBtn->CheckClick(GameEvents.button.x, GameEvents.button.y))
						{
							Mix_PlayChannel(-1, Sound, 0);
							TheDealer.DealerHit(TheDeck.GetDeck(), ThePlayer);
							TheDeck.DeckUpdate(TheDealer.GetDHand().size() - 2);
							RoundStart = false;
							break;
						}
						else if (HitBtn->CheckClick(GameEvents.button.x, GameEvents.button.y))
						{
							Mix_PlayChannel(-1, Sound, 0);
							YNBtns();

							bool EndTurn = false;
							ThePlayer.PlayerHit(TheDeck.GetDeck());
							TheDeck.DeckUpdate(ThePlayer.GetPHand().size() - 2);

							SDL_RenderCopy(GameRenderer, GameBG, nullptr, nullptr);
							string Total = "Total: " + to_string(ThePlayer.CalcPoints(ThePlayer.GetPHand()));
							PTotal = TTF_RenderText_Solid(Myfont, Total.c_str(), White);
							CurPtotal = SDL_CreateTextureFromSurface(GameRenderer, PTotal);

							MsgText = TTF_RenderText_Solid(Myfont, "Do you like to hit again ?", White);
							CurrentMsg = SDL_CreateTextureFromSurface(GameRenderer, MsgText);

							while (!EndTurn)
							{
								if ((ThePlayer.Bust(ThePlayer.GetPHand()) == false) && (ThePlayer.CalcPoints(ThePlayer.GetPHand()) < 21))
								{
									if (SDL_GetTicks() - updatedTime >= deltaT)
									{
										while (SDL_PollEvent(&GameEvents))
										{
											switch (GameEvents.type)
											{
											case SDL_QUIT:

												break;
											case SDL_MOUSEBUTTONDOWN:

												if (YesBtn->CheckClick(GameEvents.button.x, GameEvents.button.y))
												{
													Mix_PlayChannel(-1, Sound, 0);
													ThePlayer.PlayerHit(TheDeck.GetDeck());
													TheDeck.DeckUpdate(1);

													SDL_RenderCopy(GameRenderer, GameBG, nullptr, nullptr);
													string Total = "Total: " + to_string(ThePlayer.CalcPoints(ThePlayer.GetPHand()));
													PTotal = TTF_RenderText_Solid(Myfont, Total.c_str(), White);
													CurPtotal = SDL_CreateTextureFromSurface(GameRenderer, PTotal);

													break;
												}
												else if (NoBtn->CheckClick(GameEvents.button.x, GameEvents.button.y))
												{
													Mix_PlayChannel(-1, Sound, 0);
													EndTurn = true;
													break;
												}
												break;
											}
										}
										updatedTime = SDL_GetTicks();
									}
								}
								else
								{
									EndTurn = true;
								}
								SDL_RenderCopy(GameRenderer, CurrentMsg, NULL, &MsgLocation);
								SDL_RenderCopy(GameRenderer, CurPtotal, NULL, &TotalLoc);

								SDL_RenderCopy(GameRenderer, CurrentCredits, NULL, &CredLoc);
								SDL_RenderCopy(GameRenderer, CurrentBet1, NULL, &BetLocation);

								DrawBtns();
								CurrentGameState(ThePlayer, TheDealer, GameRenderer);
							}

							TheDealer.DealerHit(TheDeck.GetDeck(), ThePlayer);
							TheDeck.DeckUpdate(TheDealer.GetDHand().size() - 2);
							RoundStart = false;

							break;
						}
						else if (DoubleBtn->CheckClick(GameEvents.button.x, GameEvents.button.y))
						{
							Mix_PlayChannel(-1, Sound, 0);
							SDL_RenderCopy(GameRenderer, GameBG, nullptr, nullptr);

							if ((ThePlayer.GetBet1()) <= ThePlayer.GetCredits())
							{
								SDL_RenderCopy(GameRenderer, GameBG, nullptr, nullptr);

								ThePlayer.PlayerDouble(TheDeck.GetDeck());
								TheDeck.DeckUpdate(ThePlayer.GetPHand().size() - 2);

								TheDealer.DealerHit(TheDeck.GetDeck(), ThePlayer);
								TheDeck.DeckUpdate(TheDealer.GetDHand().size() - 2);
								RoundStart = false;

								string PCredits = "Current credits: " + to_string(ThePlayer.GetCredits());
								Credits = TTF_RenderText_Solid(Myfont, PCredits.c_str(), White);
								CurrentCredits = SDL_CreateTextureFromSurface(GameRenderer, Credits);

								string Bet = "Current bet: " + to_string(ThePlayer.GetBet1());
								Bet1Amount = TTF_RenderText_Solid(Myfont, Bet.c_str(), White);
								CurrentBet1 = SDL_CreateTextureFromSurface(GameRenderer, Bet1Amount);
							}
							else
							{
								MessageBox(NULL, "Insufficient funds to preform a Double Down !", "Alert", MB_OK | MB_ICONQUESTION);
							}

							string Total = "Total: " + to_string(ThePlayer.CalcPoints(ThePlayer.GetPHand()));
							PTotal = TTF_RenderText_Solid(Myfont, Total.c_str(), White);
							CurPtotal = SDL_CreateTextureFromSurface(GameRenderer, PTotal);

							break;
						}
						else if (SurrenderBtn->CheckClick(GameEvents.button.x, GameEvents.button.y))
						{
							Mix_PlayChannel(-1, Sound, 0);
							Surrender = true;

							ThePlayer.UpdateCredits(ThePlayer.GetBet1() / 2);
							RoundStart = false;

							break;
						}
						else if (SplitBtn->CheckClick(GameEvents.button.x, GameEvents.button.y))
						{
							Mix_PlayChannel(-1, Sound, 0);
							SDL_RenderCopy(GameRenderer, GameBG, nullptr, nullptr);
							YNBtns();

							bool EndTurn1 = false;
							bool EndTurn2 = false;

							ThePlayer.SetBet2();
							ThePlayer.PlayerSplit(TheDeck.GetDeck());
							TheDeck.DeckUpdate(2);

							string Total = "Total (H1): " + to_string(ThePlayer.CalcPoints(ThePlayer.GetPHand()));
							PTotal = TTF_RenderText_Solid(Myfont, Total.c_str(), White);
							CurPtotal = SDL_CreateTextureFromSurface(GameRenderer, PTotal);

							Total = "Total (H2): " + to_string(ThePlayer.CalcPoints(ThePlayer.GetSHand()));
							PTotal2 = TTF_RenderText_Solid(Myfont, Total.c_str(), White);
							CurPtotal2 = SDL_CreateTextureFromSurface(GameRenderer, PTotal2);

							string Bet2 = "Second bet: " + to_string(ThePlayer.Getbet2());
							Bet2Amount = TTF_RenderText_Solid(Myfont, Bet2.c_str(), White);
							CurrentBet2 = SDL_CreateTextureFromSurface(GameRenderer, Bet2Amount);

							SDL_RenderCopy(GameRenderer, GameBG, nullptr, nullptr);
							MsgText = TTF_RenderText_Solid(Myfont, "Hit again ? (first hand)", White);
							CurrentMsg = SDL_CreateTextureFromSurface(GameRenderer, MsgText);

							PCredits = "Current credits: " + to_string(ThePlayer.GetCredits());
							Credits = TTF_RenderText_Solid(Myfont, PCredits.c_str(), White);
							CurrentCredits = SDL_CreateTextureFromSurface(GameRenderer, Credits);

							while (!EndTurn1)
							{
								if ((ThePlayer.Bust(ThePlayer.GetPHand()) == false) && (ThePlayer.CalcPoints(ThePlayer.GetPHand()) < 21))
								{
									if (SDL_GetTicks() - updatedTime >= deltaT)
									{
										while (SDL_PollEvent(&GameEvents))
										{
											switch (GameEvents.type)
											{
											case SDL_QUIT:

												break;
											case SDL_MOUSEBUTTONDOWN:

												if (YesBtn->CheckClick(GameEvents.button.x, GameEvents.button.y))
												{
													Mix_PlayChannel(-1, Sound, 0);
													SDL_RenderCopy(GameRenderer, GameBG, nullptr, nullptr);

													ThePlayer.PlayerHit(TheDeck.GetDeck());
													TheDeck.DeckUpdate(1);

													string Total = "Total (H1): " + to_string(ThePlayer.CalcPoints(ThePlayer.GetPHand()));
													PTotal = TTF_RenderText_Solid(Myfont, Total.c_str(), White);
													CurPtotal = SDL_CreateTextureFromSurface(GameRenderer, PTotal);

													break;
												}
												else if (NoBtn->CheckClick(GameEvents.button.x, GameEvents.button.y))
												{
													Mix_PlayChannel(-1, Sound, 0);
													EndTurn1 = true;
												}

											}
										}
										updatedTime = SDL_GetTicks();
									}
								}
								else
								{
									EndTurn1 = true;
								}
								SDL_RenderCopy(GameRenderer, CurrentMsg, NULL, &MsgLocation);
								
								SDL_RenderCopy(GameRenderer, CurPtotal, NULL, &TotalLoc);
								SDL_RenderCopy(GameRenderer, CurPtotal2, NULL, &Total2Loc);

								SDL_RenderCopy(GameRenderer, CurrentCredits, NULL, &CredLoc);
								SDL_RenderCopy(GameRenderer, CurrentBet1, NULL, &BetLocation);
								SDL_RenderCopy(GameRenderer, CurrentBet2, NULL, &Bet2Location);

								if (ThePlayer.GetInsurance() > 0) { SDL_RenderCopy(GameRenderer, CurrentIns, NULL, &InsLoc); }

								DrawBtns();
								CurrentGameState(ThePlayer, TheDealer, GameRenderer);
							}

							SDL_RenderCopy(GameRenderer, GameBG, nullptr, nullptr);
							MsgText = TTF_RenderText_Solid(Myfont, "Hit again ? (second hand)", White);
							CurrentMsg = SDL_CreateTextureFromSurface(GameRenderer, MsgText);

							while (!EndTurn2)
							{
								if ((ThePlayer.Bust(ThePlayer.GetSHand()) == false) && (ThePlayer.CalcPoints(ThePlayer.GetSHand()) < 21))
								{
									if (SDL_GetTicks() - updatedTime >= deltaT)
									{
										while (SDL_PollEvent(&GameEvents))
										{
											switch (GameEvents.type)
											{
											case SDL_QUIT:

												break;
											case SDL_MOUSEBUTTONDOWN:

												if (YesBtn->CheckClick(GameEvents.button.x, GameEvents.button.y))
												{
													Mix_PlayChannel(-1, Sound, 0);
													SDL_RenderCopy(GameRenderer, GameBG, nullptr, nullptr);

													ThePlayer.PlayerHitSHand(TheDeck.GetDeck());
													TheDeck.DeckUpdate(1);

													string Total = "Total (H2): " + to_string(ThePlayer.CalcPoints(ThePlayer.GetSHand()));
													PTotal2 = TTF_RenderText_Solid(Myfont, Total.c_str(), White);
													CurPtotal2 = SDL_CreateTextureFromSurface(GameRenderer, PTotal2);

													break;
												}
												else if (NoBtn->CheckClick(GameEvents.button.x, GameEvents.button.y))
												{
													Mix_PlayChannel(-1, Sound, 0);
													EndTurn2 = true;
												}

											}
										}
										updatedTime = SDL_GetTicks();
									}
								}
								else
								{
									EndTurn2 = true;
								}
								SDL_RenderCopy(GameRenderer, CurrentMsg, NULL, &MsgLocation);\

								SDL_RenderCopy(GameRenderer, CurPtotal, NULL, &TotalLoc);
								SDL_RenderCopy(GameRenderer, CurPtotal2, NULL, &Total2Loc);

								SDL_RenderCopy(GameRenderer, CurrentCredits, NULL, &CredLoc);
								SDL_RenderCopy(GameRenderer, CurrentBet1, NULL, &BetLocation);
								SDL_RenderCopy(GameRenderer, CurrentBet2, NULL, &Bet2Location);

								if (ThePlayer.GetInsurance() > 0) { SDL_RenderCopy(GameRenderer, CurrentIns, NULL, &InsLoc); }

								DrawBtns();
								CurrentGameState(ThePlayer, TheDealer, GameRenderer);
							}

							TheDealer.DealerHit(TheDeck.GetDeck(), ThePlayer);
							TheDeck.DeckUpdate(TheDealer.GetDHand().size() - 2);
							RoundStart = false;
							break;
						}

						break;
					}
				}
				updatedTime = SDL_GetTicks();
			}
			SDL_RenderCopy(GameRenderer, CurrentMsg, NULL, &MsgLocation);
			SDL_RenderCopy(GameRenderer, CurPtotal, NULL, &TotalLoc);

			SDL_RenderCopy(GameRenderer, CurrentCredits, NULL, &CredLoc);
			SDL_RenderCopy(GameRenderer, CurrentBet1, NULL, &BetLocation);

			if (ThePlayer.GetSHand().size() != NULL)
			{
				SDL_RenderCopy(GameRenderer, CurrentBet2, NULL, &Bet2Location);
				SDL_RenderCopy(GameRenderer, CurPtotal2, NULL, &Total2Loc);
			}

			if (ThePlayer.GetInsurance() > 0) { SDL_RenderCopy(GameRenderer, CurrentIns, NULL, &InsLoc); }

			DrawBtns();
			CurrentGameState(ThePlayer, TheDealer, GameRenderer);
		}
		//--

		if (!Surrender)
		{
			TheDealer.SetRotation(true);
			ThePlayer = GamesResults(TheDealer, ThePlayer);

			Total = "Deater's Total: " + to_string(TheDealer.CalcPoints(TheDealer.GetDHand()));
			DTotal = TTF_RenderText_Solid(Myfont, Total.c_str(), White);
			CurDtotal = SDL_CreateTextureFromSurface(GameRenderer, DTotal);
		}
		else
		{
			ThePlayer.SetState("You Surrendered");
		}

		SDL_RenderCopy(GameRenderer, GameBG, nullptr, nullptr);
		YNBtns();

		MsgText = TTF_RenderText_Solid(Myfont, "Do you want to play again ?", White);
		CurrentMsg = SDL_CreateTextureFromSurface(GameRenderer, MsgText);

		PlayerState = TTF_RenderText_Solid(Myfont, ThePlayer.GetState(), White);
		CurrentState = SDL_CreateTextureFromSurface(GameRenderer, PlayerState);

		PlayerState2 = TTF_RenderText_Solid(Myfont, ThePlayer.GetState2(), White);
		CurrentState2 = SDL_CreateTextureFromSurface(GameRenderer, PlayerState2);

		bool EndGame = true;
		while (EndGame)
		{
			if (SDL_GetTicks() - updatedTime >= deltaT)
			{
				while (SDL_PollEvent(&GameEvents))
				{
					switch (GameEvents.type)
					{
					case SDL_QUIT:
						EndGame = false;
						break;

					case SDL_MOUSEBUTTONDOWN:
						if (YesBtn->CheckClick(GameEvents.button.x, GameEvents.button.y))
						{
							Mix_PlayChannel(-1, Sound, 0);
							EndGame = false;

							ThePlayer.HandReset();
							ThePlayer.ResetBlackJack();
							ThePlayer.UpdateCredits(ThePlayer.GetInsurance());
							ThePlayer.UpdateCredits(1);
							ThePlayer.SetBet(-(ThePlayer.GetBet1())+1);
							ThePlayer.SetBet2();
							ThePlayer.SetInsurance(-(ThePlayer.GetInsurance()));

							IncrementBtn->setVisible(true);
							DecrementBtn->setVisible(true);
							break;
						}
						else if(NoBtn->CheckClick(GameEvents.button.x, GameEvents.button.y))
						{
							Mix_PlayChannel(-1, Sound, 0);
							EndGame = false;
							PlayAgain = false;
							break;
						}

						break;
					}
				}
				updatedTime = SDL_GetTicks();
			}
			SDL_RenderCopy(GameRenderer, CurrentMsg, NULL, &MsgLocation);
			SDL_RenderCopy(GameRenderer, CurrentCredits, NULL, &CredLoc);

			SDL_RenderCopy(GameRenderer, CurPtotal, NULL, &TotalLoc);
			SDL_RenderCopy(GameRenderer, CurrentBet1, NULL, &BetLocation);

			SDL_RenderCopy(GameRenderer, CurrentState, NULL, &StateLoc);

			if(ThePlayer.GetSHand().size() != NULL)
			{ 
				SDL_RenderCopy(GameRenderer, CurrentState2, NULL, &State2Loc);
				SDL_RenderCopy(GameRenderer, CurPtotal2, NULL, &Total2Loc);
				SDL_RenderCopy(GameRenderer, CurrentBet2, NULL, &Bet2Location);
			}

			if (ThePlayer.GetInsurance() > 0) { SDL_RenderCopy(GameRenderer, CurrentIns, NULL, &InsLoc); }

			SDL_RenderCopy(GameRenderer, CurDtotal, NULL, &TotalDLoc);

			DrawBtns();
			CurrentGameState(ThePlayer, TheDealer, GameRenderer);
		}

		TheDealer.HandReset();
		TheDealer.SetRotation(false);
		TheDealer.SetStadby(true);
		TheDealer.ResetBlackJack();
		SDL_RenderCopy(GameRenderer, GameBG, nullptr, nullptr);

		MsgText = TTF_RenderText_Solid(Myfont, "Is this your wager ?", White);
		CurrentMsg = SDL_CreateTextureFromSurface(GameRenderer, MsgText);

		Bet1Amount = TTF_RenderText_Solid(Myfont, "Current bet: 1", White);
		CurrentBet1 = SDL_CreateTextureFromSurface(GameRenderer, Bet1Amount);

		PCredits = "Current credits: " + to_string(ThePlayer.GetCredits());
		Credits = TTF_RenderText_Solid(Myfont, PCredits.c_str(), White);
		CurrentCredits = SDL_CreateTextureFromSurface(GameRenderer, Credits);

		DTotal = TTF_RenderText_Solid(Myfont, "Dealer's Total: XX", White);
		CurDtotal = SDL_CreateTextureFromSurface(GameRenderer, DTotal);

		if (ThePlayer.GetCredits() == 0)
		{ 
			PlayAgain = false;
			MessageBox(NULL, "You are out of credits !\nReturning to the Main Menu...", "Alert", MB_OK | MB_ICONQUESTION);
		}
	}

	//--
	TTF_CloseFont(Myfont);

	SDL_FreeSurface(PlayerState);
	SDL_DestroyTexture(CurrentState);

	SDL_FreeSurface(PlayerState2);
	SDL_DestroyTexture(CurrentState2);

	SDL_FreeSurface(MsgText);
	SDL_DestroyTexture(CurrentMsg);

	SDL_FreeSurface(Credits);
	SDL_DestroyTexture(CurrentCredits);

	SDL_FreeSurface(Bet1Amount);
	SDL_DestroyTexture(CurrentBet1);

	SDL_FreeSurface(Bet2Amount);
	SDL_DestroyTexture(CurrentBet2);

	SDL_FreeSurface(TxtIns);
	SDL_DestroyTexture(CurrentIns);

	SDL_FreeSurface(PTotal);
	SDL_DestroyTexture(CurPtotal);

	SDL_FreeSurface(PTotal2);
	SDL_DestroyTexture(CurPtotal2);

	SDL_FreeSurface(DTotal);
	SDL_DestroyTexture(CurDtotal);

	TTF_Quit();

	GameMenu();
}
//--
void Game::CurrentGameState(Player ThePlayer, Dealer TheDealer, SDL_Renderer *MyRenderer)
{
	//-- Player's hand --
	ThePlayer.PrintPHand();
	//--------------------
	//-- Dealer's hand --
	TheDealer.PrintDHand();
	//--------------------
	SDL_RenderPresent(MyRenderer);
}
//==
Player Game::GamesResults(Dealer TheDealer, Player ThePlayer)
{
	if ((TheDealer.GetBlackJack() == true) || (ThePlayer.GetBlackJack() == true))
	{
		if ((TheDealer.GetBlackJack() == true) && (ThePlayer.GetBlackJack() == true))
		{
			ThePlayer.SetState("It's a draw!");
			ThePlayer.UpdateCredits(ThePlayer.GetBet1());
		}
		else if ((TheDealer.GetBlackJack() == true) && (ThePlayer.GetBlackJack() == false))
		{
			ThePlayer.SetState("Dealer Wins!");
		}
		else if ((TheDealer.GetBlackJack() == false) && (ThePlayer.GetBlackJack() == true))
		{
			ThePlayer.SetState("You Win!");
			ThePlayer.UpdateCredits(ThePlayer.GetBet1() * 0.5);
			ThePlayer.UpdateCredits(ThePlayer.GetBet1() * 2);
		}
	}
	else
	{
		if ((TheDealer.CalcPoints(TheDealer.GetDHand()) == ThePlayer.CalcPoints(ThePlayer.GetPHand())) || ((TheDealer.Bust(TheDealer.GetDHand()) == true) && (ThePlayer.Bust(ThePlayer.GetPHand()) == true)))
		{
			ThePlayer.SetState("It's a draw!");
			ThePlayer.UpdateCredits(ThePlayer.GetBet1());
		}
		else if (((TheDealer.CalcPoints(TheDealer.GetDHand()) > ThePlayer.CalcPoints(ThePlayer.GetPHand())) && (TheDealer.Bust(TheDealer.GetDHand()) == false)) || (ThePlayer.Bust(ThePlayer.GetPHand()) == true))
		{
			ThePlayer.SetState("Dealer Wins!");
		}
		else if (((TheDealer.CalcPoints(TheDealer.GetDHand()) < ThePlayer.CalcPoints(ThePlayer.GetPHand())) && (ThePlayer.Bust(ThePlayer.GetPHand()) == false)) || (TheDealer.Bust(TheDealer.GetDHand()) == true))
		{
			ThePlayer.SetState("You Win!");
			ThePlayer.UpdateCredits(ThePlayer.GetBet1() * 2);
		}
	}
	//--
	if (ThePlayer.GetSHand().size() != NULL)
	{
		if ((TheDealer.CalcPoints(TheDealer.GetDHand()) == ThePlayer.CalcPoints(ThePlayer.GetSHand())) || ((TheDealer.Bust(TheDealer.GetDHand()) == true) && (ThePlayer.Bust(ThePlayer.GetSHand()) == true)))
		{
			ThePlayer.SetState2("It's a draw!");
			ThePlayer.UpdateCredits(ThePlayer.Getbet2());
		}
		else if (((TheDealer.CalcPoints(TheDealer.GetDHand()) > ThePlayer.CalcPoints(ThePlayer.GetSHand())) && (TheDealer.Bust(TheDealer.GetDHand()) == false)) || (ThePlayer.Bust(ThePlayer.GetSHand()) == true))
		{
			ThePlayer.SetState2("Dealer Wins!");
		}
		else if (((TheDealer.CalcPoints(TheDealer.GetDHand()) < ThePlayer.CalcPoints(ThePlayer.GetSHand())) && (ThePlayer.Bust(ThePlayer.GetSHand()) == false)) || (TheDealer.Bust(TheDealer.GetDHand()) == true))
		{
			ThePlayer.SetState2("You Win!");
			ThePlayer.UpdateCredits(ThePlayer.Getbet2() * 2);
		}
	}

	return ThePlayer;
}