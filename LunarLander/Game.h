#ifndef GAME_H
#define GAME_H
#include <windows.h>
#include "GameObjects.h"

class Game
{
public:
	//functions
	Game();
	void Initialise();
	void Update(float deltaTime);
	void Draw();
	bool Exit() const { return m_exit; }

private:
	bool m_exit = false;
	//game enums
	enum GAME_STATE
	{
		SPLASH,
		MENU,
		PLAY,
		SCOREBOARD,
		OPTIONS
	};

	//CONSOLE PARAMETERS
	//window size coordinates
	SMALL_RECT windowSize = { 0, 0, SCREEN_WIDTH - 1, SCREEN_HEIGHT - 1 };

	//SCREEN BUFFER DIMENTIONS
	COORD bufferSize = { SCREEN_HEIGHT, SCREEN_WIDTH };

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
	GAME_STATE currentGameState = SPLASH;
	Splash splash;
	Background background;
	Player player;
	Explosion explosion;
};
#endif //GAME_H