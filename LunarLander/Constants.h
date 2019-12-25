////////////////////////////////////////////////////////////
// File:          Constants.h 
// Author:        Miron Bury
// Date Created:  01/12/2019
// Brief:         Declaration of game constants.
////////////////////////////////////////////////////////////

#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include <windows.h>

// holds all constants

//DEFINS
#define SCREEN_WIDTH 100 //lowered to fix border
#define SCREEN_HEIGHT 40
#define FRAME_RATE 60

//consts
const int KEY_ESC = VK_ESCAPE;
const int KEY_ENTER = VK_RETURN;
const int KEY_W = 'W';
const int KEY_A = 'A';
const int KEY_S = 'S';
const int KEY_D = 'D';
const int KEY_1 = '1'; //note num+key (1Key) causes error
const int KEY_2 = '2';
const int KEY_3 = '3';
const int KEY_4 = '4';

//player Parameters
//Acceleration
const float ACCELERATION_RATE = 0.5f;
const float DECELERATION_RATE = 0.2f;
const float FUEL_CONSUMPTION = 0.5f;
const float MAX_VELOCITY = 4.5f;
const float MAX_LANDING_VELOCITY = 0.5f;

const int PLAYER_MIN_X = 0;
const int PLAYER_MIN_Y = 3;

#endif // !__CONSTANTS_H__
