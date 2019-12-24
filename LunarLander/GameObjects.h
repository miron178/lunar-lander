////////////////////////////////////////////////////////////
// File:          GameObjects.h
// Author:        Miron Bury
// Date Created:  01/12/2019
// Brief:         Holds all game objects
////////////////////////////////////////////////////////////

#ifndef __GAME_OBJECTS_H__
#define __GAME_OBJECTS_H__

#include "Constants.h"
#include "Vector.h"

#include <math.h>

//holds all data needed to make the player
struct Player
{
	void ResetMovement()
	{
		acceleration.x = 0;
		acceleration.y = 0;
		velocity.x = 0;
		velocity.y = 0;
	}

	//resets the position, fuel, and state (crashed  / landed)
	void Reset()
	{
		ResetMovement();
		position.x = 0;
		position.y = 0;
		hasLanded = false;
		hasCrashed = false;
		fuel = 100;
		score = 0;
	}

	bool CanLand()
	{
		return orientation == ORIENTATION_DOWN &&
			fabs(velocity.x) <= MAX_LANDING_VELOCITY && 
			fabs(velocity.y) <= MAX_LANDING_VELOCITY;
	}

	enum ORIENTATION
	{
		ORIENTATION_DOWN,
		ORIENTATION_RIGHT,
		ORIENTATION_LEFT
	};
	//constant
	static const int WIDTH = 3;
	static const int HEIGHT = 3;
	static const int FRAMES = 3;
	const char* PLAYER[FRAMES] =
	{
		//down
		R"(__ )"
		R"(|| )"
		R"(/\ )",

		//right
		R"( _ )"
		R"(>_|)"
		R"(   )",

		//left
		R"( _ )"
		R"(|_<)"
		R"(   )"
	};

	const int COLOUR[FRAMES][WIDTH * HEIGHT]
	{
		{   //down
			0xf,0xf,0xf,
			0xf,0xf,0xf,
			0xe,0xe,0xe
		},
		{	//right
			0xe,0xf,0xf,
			0xe,0xf,0xf,
			0xe,0xf,0xf
		},
		{	//left
			0xf,0xf,0xe,
			0xf,0xf,0xe,
			0xf,0xf,0xe
		},
	};

	//variables
	bool hasLanded = false;
	bool hasCrashed = false;
	float fuel = 100;
	int score = 0;
	Vector position{ 0.0f, 0.0f };
	Vector velocity{ 0.0f, 0.0f };
	Vector acceleration{ 0.0f, 0.0f };
	ORIENTATION orientation = ORIENTATION_DOWN;
};

// holds the models used for explosion
struct Explosion
{
	static const int WIDTH = 3;
	static const int HEIGHT = 3;
	static const int FRAMES = 2;
	const char *EXPLOSION[FRAMES] =
	{
		R"(   )"
		R"( * )"
		R"(   )",

		R"(\|/)"
		R"(- -)"
		R"(/|\)",
	};
};

//holds chars which make the background
struct Background
{
	//constant
	const char *BACKGROUND =
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                   .     '                                         *                                )"
		R"(    *                                   *                                     ^                     )"
		R"(                                                                             / \   __       *       )"
		R"(          '               *                          *                      /    \/X8\         .    )"
		R"(                                             *                             /          |             )"
		R"(                  *                                        *              /            \       *    )"
		R"(    .                                                                    /              |           )"
		R"(           .                 '         *                       .        /                |          )"
		R"(                                                           ,           /                 |   ,      )"
		R"(  *            *                                  ,               ____/                   \         )"
		R"(                                        .                        / X1                      |     *  )"
		R"(          *                 .                    .   '          /                          |        )"
		R"(                                                               /                           |   .    )"
		R"(      ,                .                  ___                 |                             \    '  )"
		R"(                                   *     | X2\  *            /                               |      )"
		R"(   '               '                    /     \__      .    |                                |  .  /)"
		R"(                                       |         \         /                                 |____/ )"
		R"(                       *      /\      /           \  ,    |                                    X2   )"
		R"(             *               /  \    |             \  ___/                                          )"
		R"(  .                 ____    /    \__/               \/ X2                                           )"
		R"(     .             / X1 \ /       X4                /                                               )"
		R"(                  /      \                                                                          )"
		R"(             '   /                                                                                  )"
		R"(    *           /                                                                                   )"
		R"(       ___     /                                                                                    )"
		R"(      /X2 \   /                                                                                     )"
		R"(     /     \ /                                                                                      )"
		R"(    |       V                                                                                       )"
		R"(    |                                                                                               )"
		R"(   /                                                                                                )"
		R"(__/                                                                                                 )"
		R"(X1                                                                                                  )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )";

	const char* HIT_MAP =
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                              ^                     )"
		R"(                                                                             / \   88               )"
		R"(                                                                            /    \/  \              )"
		R"(                                                                           /          |             )"
		R"(                                                                          /            \            )"
		R"(                                                                         /              |           )"
		R"(                                                                        /                |          )"
		R"(                                                                       /                 |          )"
		R"(                                                                  1111/                   \         )"
		R"(                                                                 /                         |        )"
		R"(                                                                /                          |        )"
		R"(                                                               /                           |        )"
		R"(                                          222                 |                             \       )"
		R"(                                         |   \               /                               |      )"
		R"(                                        /     \__           |                                |     /)"
		R"(                                       |         \         /                                 |2222/ )"
		R"(                              /\      /           \       |                                         )"
		R"(                             /  \    |             \  222/                                          )"
		R"(                    1111    /    \44/               \/                                              )"
		R"(                   /    \ /                         /                                               )"
		R"(                  /      \                                                                          )"
		R"(                 /                                                                                  )"
		R"(                /                                                                                   )"
		R"(       222     /                                                                                    )"
		R"(      /   \   /                                                                                     )"
		R"(     /     \ /                                                                                      )"
		R"(    |       V                                                                                       )"
		R"(    |                                                                                               )"
		R"(   /                                                                                                )"
		R"(11/                                                                                                 )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )";

};

//holds chars which make the splash screen 
struct Splash
{
	//constant
	static const int HEIGHT= 11;
	static const int WIDTH= 30;
	const char* SCREEN =
		R"(                      _______ )"
		R"(                     /        )"
		R"(                    /    /    )"
		R"(      ___________________     )"
		R"(    /                         )"
		R"(   /    ----          ###| / ~)"
		R"(-<<    (    )            |<~~~)"
		R"(   \    ----          ###| \ ~)"
		R"(    \ ____________________    )"
		R"(                   \     \    )"
		R"(                    \________ )";

	//Variable
	float duration = 0.0f;
};

#endif // !__GAME_OBJECTS__
