////////////////////////////////////////////////////////////
// File:          GameObjects.h
// Author:        Miron Bury
// Date Created:  01/12/2019
// Brief:         Holds all game objects
////////////////////////////////////////////////////////////

#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H
#include "Constants.h"
#include "Vector.h"

struct Player
{
	//function
	void Reset()
	{
		acceleration.x = 0;
		acceleration.y = 0;
		velocity.x = 0;
		velocity.y = 0;
		position.x = 0;
		position.y = 0;
		hasLanded = false;
		hasCrashed = false;
		fuel = 100;
	}

	//constant
	static const int WIDTH = 2;
	static const int HEIGHT = 3;
	const char* PLAYER =
		R"(__)"
		R"({})"
		R"(/\)";

	const int COLOUR[WIDTH * HEIGHT]
	{
		0xf,0xf,
		0xf,0xf,
		0xe,0xe,
	};

	//variables
	bool hasLanded = false;
	bool hasCrashed = false;
	float fuel = 100;
	Vector position{ 0.0f, 0.0f };
	Vector velocity{ 0.0f, 0.0f };
	Vector acceleration{ 0.0f, 0.0f };
};

struct Explosion
{
	static const int WIDTH = 3;
	static const int HEIGHT = 3;
	const char *EXPLOSION = 
		R"(\|/)"
		R"(- -)"
		R"(/|\)";

	const char *EXPLOSION2 = 
		R"(   )"
		R"( * )"
		R"(   )";
};

struct Background
{
	//constant
	const char *BACKGROUND =
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                              ^                     )"
		R"(                                                                             / \   __               )"
		R"(                                                                            /    \/X4\              )"
		R"(                                                                           /          |             )"
		R"(                                                                          /            \            )"
		R"(                                                                         /              |           )"
		R"(                                                                        /                |          )"
		R"(                                                                       /                 |          )"
		R"(                                                                  ____/                   \         )"
		R"(                                                                 / X1                      |        )"
		R"(                                                                /                          |        )"
		R"(                                                               /                           |        )"
		R"(                                          ___                 |                             \       )"
		R"(                                         | X2\               /                               |      )"
		R"(                                        /     \__           |                                |     /)"
		R"(                                       |         \         /                                 |____/ )"
		R"(                              /\      /           \       |                                    X1   )"
		R"(                             /  \    |             \  ___/                                          )"
		R"(                    ____    /    \__/               \/ X2                                           )"
		R"(                   / X1 \ /       X4                /                                               )"
		R"(                  /      \                                                                          )"
		R"(                 /                                                                                  )"
		R"(                /                                                                                   )"
		R"(       ___     /                                                                                    )"
		R"(      /X2 \   /                                                                                     )"
		R"(     /     \ /                                                                                      )"
		R"(    |       V                                                                                       )"
		R"(    |                                                                                               )"
		R"(   /                                                                                                )"
		R"(__/                                                                                                 )"
		R"(X4                                                                                                  )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )";
};

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

#endif // !GAME_OBJECTS
