#ifndef GAME_OBJECTS_H
#define GAME_OBJECTS_H

#include"Constants.h"

struct Player
{
	//function
	void Reset()
	{
		xPos = 0;
		yPos = 0;
		isAccelerating = false;
		landerAcceleration = 0.0f;
		hasLanded = false;
		hasCrashed = false;
	}
	//constant
	static const int WIDTH = 2;
	static const int HEIGHT = 3;
	const char PLAYER[WIDTH * HEIGHT + 1] =
	{
		R"(__)"
		R"({})"
		R"(/\)"
	};

	const int COLOUR[WIDTH * HEIGHT] =
	{
		0xf,0xf,
		0xf,0xf,
		0xe,0xe,
	};

	//variables
	int xPos = 0;
	int yPos = 0;
	bool isAccelerating = false;
	float landerAcceleration = 0.0f;
	bool hasLanded = false;
	bool hasCrashed = false;
	float fuel = 100;
};

struct Explosion
{
	static const int WIDTH = 3;
	static const int HEIGHT = 3;
	const int EXPLOSION[WIDTH * HEIGHT]
	{
		'\\', '|', '/',
		'-', ' ', '-',
		'/', '|', '\\',
	};
	const int EXPLOSION2[WIDTH * HEIGHT]
	{
		' ', ' ', ' ',
		' ', ' ', ' ',
		' ', ' ', ' ',
	};
};

struct Background
{
	//constant
	const char BACKGROUND[SCREEN_WIDTH * SCREEN_HEIGHT + 1]
	{
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
		R"(                                                                                                    )"
	};
};

struct Splash
{
	//constant
	static const int HEIGHT= 11;
	static const int WIDTH= 30;
	const char SCREEN[WIDTH* HEIGHT+ 1] // +1 for null
	{

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
		R"(                    \________ )"
	};

	//Variable
	float duration = 0.0f;
};

#endif // !GAME_OBJECTS
