﻿////////////////////////////////////////////////////////////
// File:          LunarLander.cpp
// Author:        Miron Bury
// Date Created:  01/12/2019
// Brief:         Implementation of main function.
////////////////////////////////////////////////////////////

#include "GameObjects.h"
#include "Game.h"

#include <windows.h>
#include <chrono>
#include <iostream>

//Typedefs
typedef std::chrono::steady_clock::time_point Time;
typedef std::chrono::high_resolution_clock HiResClock;
typedef std::chrono::duration<float> TimeDiff;

//main entry point
int main()
{
	Game gameInstance;
	//initialise
	if (!gameInstance.Initialise())
	{
		std::cerr << "Failed to initialise game. " << std::endl;
		return 1;
	}
	Time previousFrameTime = HiResClock::now();
	Time currentFrameTime = HiResClock::now();
	float deltaTime = 0.0f;


	//main game loop
	while (!gameInstance.Exit())
	{
		//calculate time since last frame
		Time currentFrameTime = HiResClock::now();
		TimeDiff diff = currentFrameTime - previousFrameTime;
		deltaTime = diff.count();

		if (deltaTime >= (1.0f / FRAME_RATE))
		{
			gameInstance.Update(deltaTime);

			previousFrameTime = currentFrameTime;
		}
		gameInstance.Draw();
	}
	return 0;
}
