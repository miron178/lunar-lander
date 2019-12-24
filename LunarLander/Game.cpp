////////////////////////////////////////////////////////////
// File:          Game.cpp 
// Author:        Miron Bury
// Date Created:  01/12/2019
// Brief:         Implementation of Game class.
////////////////////////////////////////////////////////////

#include "Game.h"

#include "Utility.h"
#include "Constants.h"

//
Game::Game()
{
	memset(&m_consoleBuffer, 0, sizeof(m_consoleBuffer));
}

//sets window and consoleBuffer 
bool Game::Initialise()
{
	SetConsoleTitle(L"Title of my Console Window");
	if (!SetConsoleWindowInfo(m_wHnd, TRUE, &m_windowSize))
	{
		return false;
	}
	if (!SetConsoleScreenBufferSize(m_wHnd, m_bufferSize))
	{
		return false;
	}
	return true;
}

//state machine usd to change game state
void Game::Update(float deltaTime)
{
	switch (m_currentGameState)
	{
	case GAME_STATE_SPLASH:
	{
		UpdateSplash(deltaTime);
		break;
	}
	case GAME_STATE_MENU:
	{
		UpdateMenu(deltaTime);
		break;
	}
	case GAME_STATE_PLAY:
	{
		UpdatePlay(deltaTime);
		break;
	}
	case GAME_STATE_SCOREBOARD:
	{
		UpdateScoreboard(deltaTime);
		break;
	}
	}
}

//updats splash - dosen't clear frame on purpose
void Game::UpdateSplash(float deltaTime)
{
	m_splash.duration += deltaTime;
	if (m_splash.duration < 3.0f)
	{
		//draw splash
		static const int SPEED = 10;
		WriteImageToBuffer(m_consoleBuffer, m_splash.SCREEN, nullptr,
			m_splash.HEIGHT, m_splash.WIDTH,
			(SCREEN_WIDTH - m_splash.WIDTH) / 2 - (int)(m_splash.duration * SPEED),
			(SCREEN_HEIGHT - m_splash.HEIGHT) / 2);
	}
	else
	{
		m_splash.duration = 0.0f;
		m_currentGameState = GAME_STATE_MENU;
	}
}

//Updates UI & switches game state
void Game::UpdateMenu(float deltaTime)
{
	ClearScreen(m_consoleBuffer);

	WriteTextToBuffer(m_consoleBuffer, "1. PLAY", (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2));
	WriteTextToBuffer(m_consoleBuffer, "2. SCOREBOARD", (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) + 1);
	WriteTextToBuffer(m_consoleBuffer, "3. EXIT", (SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) + 2);

	//switch game state
	if (GetAsyncKeyState(KEY_1))
	{
		m_currentGameState = GAME_STATE_PLAY;
	}
	if (GetAsyncKeyState(KEY_2))
	{
		m_currentGameState = GAME_STATE_SCOREBOARD;
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

//main game update
void Game::UpdatePlay(float deltaTime)
{
	if (GetAsyncKeyState(KEY_ESC)) //exit game
	{
		m_exit = true;
	}

	if (GetAsyncKeyState(KEY_ENTER) && (m_player.hasCrashed || m_player.hasLanded))
	{
		m_player.Reset(); //resets player pos, fuel, etc.
		m_currentGameState = GAME_STATE_MENU; //sets state to menu
	}
	if (!m_player.hasLanded && !m_player.hasCrashed)
	{
		HandlePlayerControls(); //player controls
		UpdatePlayer(deltaTime); //update player
	}

	//clearscreen
	ClearScreen(m_consoleBuffer);

	//draw background
	WriteImageToBuffer(m_consoleBuffer, m_background.BACKGROUND, nullptr, SCREEN_HEIGHT, SCREEN_WIDTH, 0, 0);

	//crash draw
	if (m_player.hasCrashed)
	{
		DrawExplosion(deltaTime);
		WriteTextToBuffer(m_consoleBuffer, "CRASHED!", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		WriteTextToBuffer(m_consoleBuffer, "Press enter to retun to menu", SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 1);
	}
	else if (m_player.hasLanded)
	{
		WriteTextToBuffer(m_consoleBuffer, "Craft has landed", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		WriteTextToBuffer(m_consoleBuffer, "Press enter to retun to menu", SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 1);
	}
	else
	{
		//draw player
		WriteImageToBuffer(m_consoleBuffer, m_player.PLAYER, m_player.COLOUR, m_player.HEIGHT, m_player.WIDTH, (int)m_player.position.x, (int)m_player.position.y);
	}
	DrawUI();
}

void Game::HandlePlayerControls()
{
	// vertical control
	if (GetAsyncKeyState(KEY_W) && m_player.fuel > 0.0f)
	{
		m_player.acceleration.y = -ACCELERATION_RATE;
		m_player.fuel -= FUEL_CONSUMPTION;
	}
	else
	{
		m_player.acceleration.y = DECELERATION_RATE;
	}
	//if (GetAsyncKeyState(KEY_S))
	//{
	//}

	// horizontal
	if (GetAsyncKeyState(KEY_A))
	{
		m_player.acceleration.x = -ACCELERATION_RATE;
	}
	else if (GetAsyncKeyState(KEY_D))
	{
		m_player.acceleration.x = ACCELERATION_RATE;
	}
	else
	{
		m_player.acceleration.x = 0.0f;
	}
}

void Game::UpdatePlayer(float deltaTime)
{
	m_player.velocity.x += m_player.acceleration.x * deltaTime;
	m_player.velocity.y += m_player.acceleration.y * deltaTime;
	m_player.velocity.x = ClampF(m_player.velocity.x, -MAX_VELOCITY, MAX_VELOCITY);
	m_player.velocity.y = ClampF(m_player.velocity.y, -MAX_VELOCITY, MAX_VELOCITY);

	m_player.position.x += m_player.velocity.x * deltaTime;
	m_player.position.y += m_player.velocity.y * deltaTime;
	m_player.position.x = ClampF(m_player.position.x, 0, SCREEN_WIDTH - m_player.WIDTH);
	m_player.position.y = ClampF(m_player.position.y, 0, SCREEN_HEIGHT - m_player.HEIGHT);

	//chars on landing gear
	char bottomLeftChar = m_background.BACKGROUND[(int)m_player.position.x + SCREEN_WIDTH *
		((int)m_player.position.y + (m_player.HEIGHT - 1))];
	char BottomRightChar = m_background.BACKGROUND
		[((int)m_player.position.x + (m_player.WIDTH - 1) + SCREEN_WIDTH * ((int)m_player.position.y + (m_player.HEIGHT - 1)))];

	//land or crash
	if (bottomLeftChar == '_' && BottomRightChar == '_')
	{
		m_player.hasLanded = true;
	}
	else if (bottomLeftChar != ' ' || BottomRightChar != ' ')
	{
		m_player.hasCrashed = true;
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
		frame = (frame + 1) % m_explosion.FRAMES;
	}

	WriteImageToBuffer(m_consoleBuffer, m_explosion.EXPLOSION[frame], nullptr,
		m_explosion.HEIGHT, m_explosion.WIDTH, (int)m_player.position.x, (int)m_player.position.y);
}

void Game::DrawUI()
{
	WriteTextToBuffer(m_consoleBuffer, "SCORE", 1, 0);
	WriteTextToBuffer(m_consoleBuffer, "TIME", 1, 1);
	WriteTextToBuffer(m_consoleBuffer, "FULE " + std::to_string(m_player.fuel), 1, 2);
	WriteTextToBuffer(m_consoleBuffer, "POSITION     " + std::to_string(m_player.position.x) + ", " + std::to_string(m_player.position.y), 20, 0);
	WriteTextToBuffer(m_consoleBuffer, "VELOCITY     " + std::to_string(m_player.velocity.x) + ", " + std::to_string(m_player.velocity.y), 20, 1);
	WriteTextToBuffer(m_consoleBuffer, "ACCELERATION " + std::to_string(m_player.acceleration.x) + ", " + std::to_string(m_player.acceleration.y), 20, 2);
}


//
void Game::UpdateScoreboard(float deltaTime)
{
	
}

//display to console
void Game::Draw()
{
	WriteConsoleOutputA(m_wHnd, m_consoleBuffer, m_characterBufferSize, m_characterPoition, &m_consoleWriteArea);
}
