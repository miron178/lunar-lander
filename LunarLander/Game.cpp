////////////////////////////////////////////////////////////
// File:          Game.cpp 
// Author:        Miron Bury
// Date Created:  01/12/2019
// Brief:         Implementation of Game class.
////////////////////////////////////////////////////////////

#include "Game.h"

#include "Utility.h"
#include "Constants.h"

Game::Game()
{
	memset(&consoleBuffer, 0, sizeof(consoleBuffer));
}

bool Game::Initialise()
{
	SetConsoleTitle(L"Title of my Console Window");
	if (!SetConsoleWindowInfo(wHnd, TRUE, &windowSize))
	{
		return false;
	}
	if (!SetConsoleScreenBufferSize(wHnd, bufferSize))
	{
		return false;
	}
	return true;
}

void Game::Update(float deltaTime)
{
	switch (currentGameState)
	{
	case SPLASH:
	{
		UpdateSplash(deltaTime);
		break;
	}
	case MENU:
	{
		UpdateMenu(deltaTime);
		break;
	}
	case PLAY:
	{
		UpdatePlay(deltaTime);
		break;
	}
	case SCOREBOARD:
	{
		UpdateScoreboard(deltaTime);
		break;
	}
	}
}

void Game::UpdateSplash(float deltaTime)
{
	splash.duration += deltaTime;
	if (splash.duration < 3.0f)
	{
		//draw splash
		static const int SPEED = 10;
		WriteImageToBuffer(consoleBuffer, splash.SCREEN, nullptr,
			splash.HEIGHT, splash.WIDTH,
			(SCREEN_WIDTH - splash.WIDTH) / 2 - (int)(splash.duration * SPEED),
			(SCREEN_HEIGHT - splash.HEIGHT) / 2);
	}
	else
	{
		splash.duration = 0.0f;
		currentGameState = MENU;
	}
}
void Game::UpdateMenu(float deltaTime)
{
	ClearScreen(consoleBuffer);

	WriteTextToBuffer(consoleBuffer, "1. PLAY", (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2));
	WriteTextToBuffer(consoleBuffer, "2. SCOREBOARD", (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) + 1);
	WriteTextToBuffer(consoleBuffer, "3. EXIT", (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) + 2);

	//switch game state
	if (GetAsyncKeyState(KEY_1))
	{
		currentGameState = PLAY;
	}
	if (GetAsyncKeyState(KEY_2))
	{
		currentGameState = SCOREBOARD;
	}

	//stop game
	if (GetAsyncKeyState(KEY_3))
	{
		m_exit = true;
	}
	if (GetAsyncKeyState(KEY_ESC))
	{
		m_exit = true;
	}
}
void Game::UpdatePlay(float deltaTime)
{
	if (GetAsyncKeyState(KEY_ESC))
	{
		m_exit = true;
	}

	if (GetAsyncKeyState(KEY_ENTER) && (player.hasCrashed || player.hasLanded))
	{
		player.Reset();
		currentGameState = MENU;
	}
	if (!player.hasLanded && !player.hasCrashed)
	{
		HandlePlayerControls();
		UpdatePlayer(deltaTime);
	}

	//clearscreen
	ClearScreen(consoleBuffer);

	//draw background
	WriteImageToBuffer(consoleBuffer, background.BACKGROUND, nullptr, SCREEN_HEIGHT, SCREEN_WIDTH, 0, 0);

	//crash draw
	if (player.hasCrashed)
	{
		DrawExplosion(deltaTime);
		WriteTextToBuffer(consoleBuffer, "CRASHED!", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		WriteTextToBuffer(consoleBuffer, "Press enter to retun to menu", SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 1);
	}
	else if (player.hasLanded)
	{
		WriteTextToBuffer(consoleBuffer, "Craft has landed", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		WriteTextToBuffer(consoleBuffer, "Press enter to retun to menu", SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 1);
	}
	else
	{
		//draw player
		WriteImageToBuffer(consoleBuffer, player.PLAYER, player.COLOUR, player.HEIGHT, player.WIDTH, (int)player.position.x, (int)player.position.y);
	}
	DrawUI();
}

void Game::HandlePlayerControls()
{
	// vertical control
	if (GetAsyncKeyState(KEY_W) && player.fuel > 0.0f)
	{
		player.acceleration.y = -ACCELERATION_RATE;
		player.fuel -= FUEL_CONSUMPTION;
	}
	else
	{
		player.acceleration.y = DECELERATION_RATE;
	}
	//if (GetAsyncKeyState(KEY_S))
	//{
	//}

	// horizontal
	if (GetAsyncKeyState(KEY_A))
	{
		player.acceleration.x = -ACCELERATION_RATE;
	}
	else if (GetAsyncKeyState(KEY_D))
	{
		player.acceleration.x = ACCELERATION_RATE;
	}
	else
	{
		player.acceleration.x = 0.0f;
	}
}
void Game::UpdatePlayer(float deltaTime)
{
	player.velocity.x += player.acceleration.x * deltaTime;
	player.velocity.y += player.acceleration.y * deltaTime;
	player.velocity.x = ClampF(player.velocity.x, -MAX_VELOCITY, MAX_VELOCITY);
	player.velocity.y = ClampF(player.velocity.y, -MAX_VELOCITY, MAX_VELOCITY);

	player.position.x += player.velocity.x * deltaTime;
	player.position.y += player.velocity.y * deltaTime;
	player.position.x = ClampF(player.position.x, 0, SCREEN_WIDTH - player.WIDTH);
	player.position.y = ClampF(player.position.y, 0, SCREEN_HEIGHT - player.HEIGHT);

	//chars on landing gear
	char bottomLeftChar = background.BACKGROUND[(int)player.position.x + SCREEN_WIDTH *
		((int)player.position.y + (player.HEIGHT - 1))];
	char BottomRightChar = background.BACKGROUND
		[((int)player.position.x + (player.WIDTH - 1) + SCREEN_WIDTH * ((int)player.position.y + (player.HEIGHT - 1)))];

	//land or crash
	if (bottomLeftChar == '_' && BottomRightChar == '_')
	{
		player.hasLanded = true;
	}
	else if (bottomLeftChar != ' ' || BottomRightChar != ' ')
	{
		player.hasCrashed = true;
	}
}

void Game::DrawExplosion(float deltaTime)
{
	static const float ANIMATION_DELAY = 0.5f;

	int frame = 0;
	static float explosionTimer = 0.0f;
	explosionTimer += deltaTime;

	// move to next frame
	if (explosionTimer >= ANIMATION_DELAY)
	{
		explosionTimer -= ANIMATION_DELAY;
		frame = (frame + 1) % explosion.FRAMES;
	}

	WriteImageToBuffer(consoleBuffer, explosion.EXPLOSION[frame], nullptr,
		explosion.HEIGHT, explosion.WIDTH, (int)player.position.x, (int)player.position.y);
}

void Game::DrawUI()
{
	WriteTextToBuffer(consoleBuffer, "SCORE", 1, 0);
	WriteTextToBuffer(consoleBuffer, "TIME", 1, 1);
	WriteTextToBuffer(consoleBuffer, "FULE " + std::to_string(player.fuel), 1, 2);
	WriteTextToBuffer(consoleBuffer, "POSITION     " + std::to_string(player.position.x) + ", " + std::to_string(player.position.y), 20, 0);
	WriteTextToBuffer(consoleBuffer, "VELOCITY     " + std::to_string(player.velocity.x) + ", " + std::to_string(player.velocity.y), 20, 1);
	WriteTextToBuffer(consoleBuffer, "ACCELERATION " + std::to_string(player.acceleration.x) + ", " + std::to_string(player.acceleration.y), 20, 2);
}

void Game::UpdateScoreboard(float deltaTime)
{
	
}

void Game::Draw()
{
	WriteConsoleOutputA(wHnd, consoleBuffer, characterBufferSize, characterPoition, &ConsoleWriteArea);
}
