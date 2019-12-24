////////////////////////////////////////////////////////////
// File:          Game.h
// Author:        Miron Bury
// Date Created:  01/12/2019
// Brief:         Declaration of Game class.
////////////////////////////////////////////////////////////

#ifndef __GAME_H__
#define __GAME_H__

#include "GameObjects.h"

#include <chrono>
#include <windows.h>

//declares all functions used in Game.cpp - along with: enums, paramaters and variables
class Game
{
public:
	//functions
	Game();
	bool Initialise();
	void Update(float deltaTime);
	void Draw();
	bool Exit() const { return m_exit; }

private:
	void UpdateSplash(float deltaTime);
	void UpdateMenu(float deltaTime);
	void UpdatePlay(float deltaTime);
	void UpdateScoreboard(float deltaTime);
	void HandlePlayerControls();
	void UpdatePlayer(float deltaTime);
	void DrawExplosion(float deltaTime);
	void DrawUI();

private:
	bool m_exit = false;
	//game enums
	enum GAME_STATE
	{
		GAME_STATE_SPLASH,
		GAME_STATE_MENU,
		GAME_STATE_PLAY,
		GAME_STATE_SCOREBOARD,
	};

	//CONSOLE PARAMETERS
	//window size coordinates
	SMALL_RECT m_windowSize = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

	//SCREEN BUFFER DIMENTIONS
	COORD m_bufferSize = { SCREEN_WIDTH, SCREEN_HEIGHT };

	//SETTING UP VARIABLES
	COORD m_characterBufferSize = { SCREEN_WIDTH, SCREEN_HEIGHT };
	COORD m_characterPoition = { 0, 0 };
	SMALL_RECT m_consoleWriteArea = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

	//CHAR FOR FRAM
	CHAR_INFO m_consoleBuffer[SCREEN_WIDTH * SCREEN_HEIGHT];

	//Initialize handles
	HANDLE m_wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE m_rHnd = GetStdHandle(STD_INPUT_HANDLE);

	//game variables
	GAME_STATE m_currentGameState = GAME_STATE::GAME_STATE_SPLASH;
	Splash m_splash;
	Background m_background;
	Player m_player;
	Explosion m_explosion;
	std::chrono::steady_clock::time_point m_startTime;
	int m_bestScore = 0;
};
#endif //!__GAME_H__