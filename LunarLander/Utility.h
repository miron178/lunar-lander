////////////////////////////////////////////////////////////
// File:          Utility.h
// Author:        Miron Bury
// Date Created:  01/12/2019
// Brief:         Various utility functions.
////////////////////////////////////////////////////////////

#ifndef UTILITY_H
#define UTILITY_H

#include<Windows.h>
#include<string>
#include "Constants.h"
#include "Vector.h"

static int Clamp(int intToClamp, int lowerLimit, int upperLimit)
{
	{
		if (intToClamp < lowerLimit)
			return lowerLimit;
		else if (intToClamp > upperLimit)
			return upperLimit;
		else
			return intToClamp;
	}
}

static float ClampF(float floatToClamp, float lowerLimit, float upperLimit)
{
	return floatToClamp <= lowerLimit ? lowerLimit : floatToClamp >= upperLimit ? upperLimit : floatToClamp;
}

static void WriteImageToBuffer(CHAR_INFO* consoleBuffer, const int charsToPrint[], const int coloursToPrint[], int imageHeight, int imageWidth, int imageXPos, int imageYPos)
{
	for (int y = 0; y < imageHeight; y++)
	{
		for (int x = 0; x < imageWidth; x++)
		{
			consoleBuffer[(imageXPos + x) + SCREEN_WIDTH * (imageYPos + y)].Char.AsciiChar = charsToPrint[x + imageWidth * y];
			if (coloursToPrint)
			{
				consoleBuffer[(imageXPos + x) + SCREEN_WIDTH * (imageYPos + y)].Attributes = coloursToPrint[x + imageWidth * y];
			}
			else
			{
				consoleBuffer[(imageXPos + x) + SCREEN_WIDTH * (imageYPos + y)].Attributes = 7;
			}
		}
	}
}

static void WriteImageToBuffer2(CHAR_INFO* consoleBuffer, const char charsToPrint[], const int coloursToPrint[], int imageHeight, int imageWidth, int imageXPos, int imageYPos)
{
	for (int y = 0; y < imageHeight; y++)
	{
		for (int x = 0; x < imageWidth; x++)
		{
			consoleBuffer[(imageXPos + x) + SCREEN_WIDTH * (imageYPos + y)].Char.AsciiChar = charsToPrint[x + imageWidth * y];
			if (coloursToPrint)
			{
				consoleBuffer[(imageXPos + x) + SCREEN_WIDTH * (imageYPos + y)].Attributes = coloursToPrint[x + imageWidth * y];
			}
			else
			{
				consoleBuffer[(imageXPos + x) + SCREEN_WIDTH * (imageYPos + y)].Attributes = 7;
			}
		}
	}
}

static void ClearScreen(CHAR_INFO* consoleBuffer)
{
	for (int i = 0; i < (SCREEN_WIDTH * SCREEN_HEIGHT); i++)
	{
		consoleBuffer[i].Char.AsciiChar = 0;
		consoleBuffer[i].Attributes = 0;
	}
}

static void WriteTextToBuffer(CHAR_INFO* consoleBuffer, std::string stringToPrint, int textXPos, int textYPos)
{
	for (unsigned int x = 0; x < stringToPrint.length(); x++)
	{
		consoleBuffer[(textXPos + x) + SCREEN_WIDTH * textYPos].Char.AsciiChar = stringToPrint[x];
		consoleBuffer[(textXPos + x) + SCREEN_WIDTH * textYPos].Attributes = 0xF;
	}
}

#endif // !UTILITY
