////////////////////////////////////////////////////////////
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
#include <thread>

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
	Time previousFrameStart = HiResClock::now();
	Time currentFrameTime = HiResClock::now();

	//main game loop
	while (!gameInstance.Exit())
	{
		//calculate time since last frame
		Time currentFrameStart = HiResClock::now();
		TimeDiff diff = currentFrameStart - previousFrameStart;
		previousFrameStart = currentFrameStart;
		float deltaTime = diff.count();

		//update and draw game
		gameInstance.Update(deltaTime);
		gameInstance.Draw();

		//go to sleep if we finished early
		Time currentFrameEnd = HiResClock::now();
		TimeDiff currentFrameDuration = currentFrameEnd - currentFrameStart;
		float frameDuration = 1.0f / FRAME_RATE;
		float remainingTime = frameDuration - currentFrameDuration.count();
		if (remainingTime > 0)
		{
			std::chrono::milliseconds timespan((int)(remainingTime * 1000));
			std::this_thread::sleep_for(timespan);
		}
	}
	return 0;
}
