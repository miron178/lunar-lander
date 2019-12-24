////////////////////////////////////////////////////////////
// File:          Game.h
// Author:        Miron Bury
// Date Created:  01/12/2019
// Brief:         Declaration of Game class.
////////////////////////////////////////////////////////////

#ifndef __GAME_H__
#define __GAME_H__

#include "GameObjects.h"

#include <windows.h>

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

	bool m_exit = false;
	//game enums
	enum GAME_STATE
	{
		SPLASH,
		MENU,
		PLAY,
		SCOREBOARD,
	};

	//CONSOLE PARAMETERS
	//window size coordinates
	SMALL_RECT windowSize = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

	//SCREEN BUFFER DIMENTIONS
	COORD bufferSize = { SCREEN_WIDTH, SCREEN_HEIGHT };

	//SETTING UP VARIABLES
	COORD characterBufferSize = { SCREEN_WIDTH, SCREEN_HEIGHT };
	COORD characterPoition = { 0, 0 };
	SMALL_RECT ConsoleWriteArea = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

	//CHAR FOR FRAM
	CHAR_INFO consoleBuffer[SCREEN_WIDTH * SCREEN_HEIGHT];

	//Initialize handles
	HANDLE wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
	HANDLE rHnd = GetStdHandle(STD_INPUT_HANDLE);

	//game variables
	GAME_STATE currentGameState = GAME_STATE::SPLASH;
	Splash splash;
	Background background;
	Player player;
	Explosion explosion;
};
#endif //!__GAME_H__