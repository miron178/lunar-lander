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
	case GAME_STATE::SPLASH:
	{
		UpdateSplash(deltaTime);
		break;
	}
	case GAME_STATE::MENU:
	{
		UpdateMenu(deltaTime);
		break;
	}
	case GAME_STATE::PLAY:
	{
		UpdatePlay(deltaTime);
		break;
	}
	case GAME_STATE::SCOREBOARD:
	{
		UpdateScoreboard(deltaTime);
		break;
	}
	}
}

//updats splash - dosen't clear frame on purpose
void Game::UpdateSplash(float deltaTime)
{
	if (GetAsyncKeyState(KEY_ESC))
	{
		m_currentGameState = GAME_STATE::MENU;
	}

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
		m_currentGameState = GAME_STATE::MENU;
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
		m_player.Reset(); //resets player pos, fuel, etc.
		m_startTime = std::chrono::high_resolution_clock::now();
		m_currentGameState = GAME_STATE::PLAY;
	}
	if (GetAsyncKeyState(KEY_2))
	{
		m_currentGameState = GAME_STATE::SCOREBOARD;
	}

	//stop game
	if (GetAsyncKeyState(KEY_3))
	{
		m_exit = true;
	}
}

//main game update
void Game::UpdatePlay(float deltaTime)
{
	if (GetAsyncKeyState(KEY_ESC))
	{
		m_currentGameState = GAME_STATE::MENU;
	}

	if (GetAsyncKeyState(KEY_ENTER) && (m_player.hasCrashed || m_player.hasLanded))
	{
		m_currentGameState = GAME_STATE::MENU; //sets state to menu
	}
	if (!m_player.hasLanded && !m_player.hasCrashed)
	{
		HandlePlayerControls(deltaTime); //player controls
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
	else
	{
		//draw player
		WriteImageToBuffer(m_consoleBuffer, 
			m_player.PLAYER[m_player.orientation], 
			m_player.COLOUR[m_player.orientation], 
			m_player.HEIGHT, m_player.WIDTH, 
			(int)m_player.position.x, (int)m_player.position.y);

		if (m_player.hasLanded)
		{
			WriteTextToBuffer(m_consoleBuffer, "Craft has landed", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			WriteTextToBuffer(m_consoleBuffer, "Press enter to retun to menu", SCREEN_WIDTH / 2, (SCREEN_HEIGHT / 2) + 1);
		}
	}
	DrawUI();
}

void Game::HandlePlayerControls(float deltaTime)
{
	// acceleration control
	if (GetAsyncKeyState(KEY_W) && m_player.fuel > 0.0f)
	{
		switch (m_player.orientation)
		{
		case Player::ORIENTATION_DOWN:
		{
			m_player.acceleration.x = 0.0f;
			m_player.acceleration.y = -ACCELERATION_RATE;
			break;
		}
		case Player::ORIENTATION_RIGHT:
		{
			m_player.acceleration.x = ACCELERATION_RATE;
			m_player.acceleration.y = DECELERATION_RATE;
			break;
		}
		case Player::ORIENTATION_LEFT:
		{
			m_player.acceleration.x = -ACCELERATION_RATE;
			m_player.acceleration.y = DECELERATION_RATE;
			break;
		}
		}
		m_player.fuel -= FUEL_CONSUMPTION * deltaTime;
	}
	else
	{
		m_player.acceleration.x = 0.0f;
		m_player.acceleration.y = DECELERATION_RATE;
	}

	// change orientation
	if (GetAsyncKeyState(KEY_A))
	{
		m_player.orientation = Player::ORIENTATION_LEFT;
	}
	else if (GetAsyncKeyState(KEY_S))
	{
		m_player.orientation = Player::ORIENTATION_DOWN;
	}
	else if (GetAsyncKeyState(KEY_D))
	{
		m_player.orientation = Player::ORIENTATION_RIGHT;
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
	m_player.position.x = ClampF(m_player.position.x, PLAYER_MIN_X, SCREEN_WIDTH - m_player.WIDTH);
	m_player.position.y = ClampF(m_player.position.y, PLAYER_MIN_Y, SCREEN_HEIGHT - m_player.HEIGHT);

	//chars on landing gear
	char bottomLeftChar = m_background.HIT_MAP[(int)m_player.position.x + 
		SCREEN_WIDTH * ((int)m_player.position.y + (m_player.HEIGHT - 1))];
	char bottomRightChar = m_background.HIT_MAP
		[((int)m_player.position.x + (m_player.WIDTH - 2) + //the 3rd column is empty 
			SCREEN_WIDTH * ((int)m_player.position.y + (m_player.HEIGHT - 1)))];

	//land or crash
	if ((bottomLeftChar == bottomRightChar) && 
		(bottomLeftChar >= '1') && 
		(bottomLeftChar <= '9') &&
		m_player.CanLand())
	{
		int multiplier = bottomLeftChar - '0';
		m_player.ResetMovement();
		m_player.hasLanded = true;
		m_player.score += (50 + (int)m_player.fuel) * multiplier;

		//update best score
		if (m_bestScore < m_player.score)
		{
			m_bestScore = m_player.score;
		}
	}
	else if (bottomLeftChar != ' ' || bottomRightChar != ' ')
	{
		m_player.hasCrashed = true;
	}
}

void Game::DrawExplosion(float deltaTime)
{
	static const float ANIMATION_DELAY = 0.5f;

	static int frame = 0;
	static float explosionTimer = 0.0f;
	explosionTimer += deltaTime;

	// move to next frame
	if (explosionTimer >= ANIMATION_DELAY)
	{
		explosionTimer = 0;
		frame = (frame + 1) % m_explosion.FRAMES;
	}

	WriteImageToBuffer(m_consoleBuffer, m_explosion.EXPLOSION[frame], nullptr,
		m_explosion.HEIGHT, m_explosion.WIDTH, (int)m_player.position.x, (int)m_player.position.y);
}

void Game::DrawUI()
{
	std::chrono::duration<float> diff = std::chrono::high_resolution_clock::now() - m_startTime;
	int duration = (int)diff.count();
	std::string warn = m_player.CanLand() ? "" : " TOO FAST!";
	WriteTextToBuffer(m_consoleBuffer, "SCORE  " + std::to_string(m_player.score), 1, 0);
	WriteTextToBuffer(m_consoleBuffer, "TIME   " + std::to_string(duration), 1, 1);
	WriteTextToBuffer(m_consoleBuffer, "FUEL   " + std::to_string(m_player.fuel), 1, 2);
	WriteTextToBuffer(m_consoleBuffer, "POSITION     " + std::to_string(m_player.position.x) + ", " + std::to_string(m_player.position.y), 20, 0);
	WriteTextToBuffer(m_consoleBuffer, "VELOCITY     " + std::to_string(m_player.velocity.x) + ", " + std::to_string(m_player.velocity.y) + warn, 20, 1);
	WriteTextToBuffer(m_consoleBuffer, "ACCELERATION " + std::to_string(m_player.acceleration.x) + ", " + std::to_string(m_player.acceleration.y), 20, 2);
}


//
void Game::UpdateScoreboard(float deltaTime)
{
	if (GetAsyncKeyState(KEY_ESC))
	{
		m_currentGameState = GAME_STATE::MENU;
	}
	ClearScreen(m_consoleBuffer);
	WriteTextToBuffer(m_consoleBuffer, "---- SCOREBOARD ----", SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 2);
	WriteTextToBuffer(m_consoleBuffer, "BEST SCORE " + std::to_string(m_bestScore), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 0);
	WriteTextToBuffer(m_consoleBuffer, "YOUR SCORE " + std::to_string(m_player.score), SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 + 1);
}

//display to console
void Game::Draw()
{
	WriteConsoleOutputA(m_wHnd, m_consoleBuffer, m_characterBufferSize, m_characterPoition, &m_consoleWriteArea);
}
