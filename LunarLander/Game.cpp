//class header
#include "Game.h"
#include "Utility.h"
#include "Constants.h"

Game::Game()
{
	//constructor
}

void Game::Initialise()
{
	SetConsoleTitle(L"Title of my Console Window");

	SetConsoleScreenBufferSize(wHnd, bufferSize);

	bool result = SetConsoleWindowInfo(wHnd, TRUE, &windowSize); //dosen't work on small screen
}

void Game::Update(float deltaTime)
{
	switch (currentGameState)
	{
	case SPLASH:
	{
		splash.duration += deltaTime;
		if (splash.duration < 3.0f)
		{
			//draw splash
			//WriteImageToBuffer(consoleBuffer, splashScreen, nullptr, 
			//	splashHeight, splashWidth, 
			//	(WIDTH - splashWidth) / 2 - splashDuration*10, (HEIGHT - splashHeight) / 2);
			WriteImageToBuffer2(consoleBuffer, splash.SCREEN, nullptr,
				splash.HEIGHT, splash.WIDTH,
				(SCREEN_WIDTH - splash.WIDTH) / 2 - splash.duration * 10, (SCREEN_HEIGHT - splash.HEIGHT) / 2);
		}
		else
		{
			splash.duration = 0.0f;
			currentGameState = MENU;
		}
		break;
	}
	case MENU:
	{
		ClearScreen(consoleBuffer);

		WriteTextToBuffer(consoleBuffer, "1. PLAY", (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2));
		WriteTextToBuffer(consoleBuffer, "2. OPTIONS", (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) + 1);
		WriteTextToBuffer(consoleBuffer, "3. SCOREBOARD", (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) + 2);
		WriteTextToBuffer(consoleBuffer, "4. EXIT", (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) + 3);

		//switch game state
		if (GetAsyncKeyState(KEY_1))
		{
			currentGameState = PLAY;
		}
		if (GetAsyncKeyState(KEY_2))
		{
			currentGameState = OPTIONS;
		}
		if (GetAsyncKeyState(KEY_3))
		{
			currentGameState = SCOREBOARD;
		}

		//stop game
		if (GetAsyncKeyState(KEY_4))
		{
			m_exit = true;
		}
		if (GetAsyncKeyState(KEY_ESC))
		{
			m_exit = true;
		}

		break;
	}
	case PLAY:
	{
		if (!player.hasLanded && !player.hasCrashed)
		{
			if (GetAsyncKeyState(KEY_ESC))
			{
				m_exit = true;
			}
			if (GetAsyncKeyState(KEY_W) && player.fuel > 0.0f)
			{
				player.isAccelerating = true;
				player.fuel -= FUEL_CONSUMPTION;
			}
			if (GetAsyncKeyState(KEY_A))
			{
				--player.xPos;
			}
			if (GetAsyncKeyState(KEY_S))
			{
				++player.yPos;
			}
			if (GetAsyncKeyState(KEY_D))
			{
				++player.xPos;
			}

			//should accelerate
			if (player.isAccelerating)
			{
				player.landerAcceleration += (ACCELERATION_RATE * deltaTime);
			}
			if (!player.isAccelerating)
			{
				player.landerAcceleration -= (DECELERATION_RATE * deltaTime);
			}

			//reset acceleration
			player.landerAcceleration = ClampF(player.landerAcceleration, 0.0, 1.5);

			if (player.landerAcceleration >= 1.0f)
			{
				player.yPos--;
			}
			else if (player.landerAcceleration < 0.5f)
			{
				player.yPos++;
			}
			player.isAccelerating = false;

			//clamp input
			player.xPos = Clamp(player.xPos, 0, SCREEN_WIDTH - player.WIDTH);
			player.yPos = Clamp(player.yPos, 0, SCREEN_HEIGHT - player.HEIGHT);

			//chars on landing gear
			char bottomLeftChar = background.BACKGROUND[player.xPos + SCREEN_WIDTH * (player.yPos + (player.HEIGHT - 1))];
			char BottomRightChar = background.BACKGROUND[(player.xPos + (player.WIDTH - 1) + SCREEN_WIDTH * (player.yPos + (player.HEIGHT - 1)))];

			//land or crash
			if (bottomLeftChar == '_' && BottomRightChar == '_')
			{
				player.hasLanded = true;
				currentGameState = GAME_OVER;
			}
			else if (bottomLeftChar != ' ' || BottomRightChar != ' ')
			{
				player.hasCrashed = true;
				currentGameState = GAME_OVER;
			}
		}

		//clearscreen
		ClearScreen(consoleBuffer);

		//draw background
		WriteImageToBuffer(consoleBuffer, background.BACKGROUND, nullptr, SCREEN_HEIGHT, SCREEN_WIDTH, 0, 0);

		//draw player
		WriteImageToBuffer2(consoleBuffer, player.PLAYER, player.COLOUR, player.HEIGHT, player.WIDTH, player.xPos, player.yPos);

		//draw UI
		WriteTextToBuffer(consoleBuffer, "SCORE", 1, 0);
		WriteTextToBuffer(consoleBuffer, "TIME", 1, 1);
		WriteTextToBuffer(consoleBuffer, "FULE " + std::to_string(player.fuel), 1, 2);

		break;
	}
	case SCOREBOARD:
	{
		break;
	}
	case OPTIONS:
	{
		break;
	}
	case GAME_OVER:
	{
		if (GetAsyncKeyState(KEY_ESC))
		{
			m_exit = true;
		}

		if (GetAsyncKeyState(KEY_ENTER))
		{
			player.Reset();
			currentGameState = MENU;
		}

		//Draw game over text
		if (player.hasLanded)
		{
			WriteTextToBuffer(consoleBuffer, "Craft has landed", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			WriteTextToBuffer(consoleBuffer, "Press enter to retun to menu", SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 1);
		}
		else if (player.hasCrashed)
		{
			WriteTextToBuffer(consoleBuffer, "CRASHED!", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			WriteTextToBuffer(consoleBuffer, "Press enter to retun to menu", SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 1);
		}
		break;
	}
	}
}

void Game::Draw()
{
	WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPoition, &ConsoleWriteArea);
}
