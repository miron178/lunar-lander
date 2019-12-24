#ifndef Constants_h
#define Constants_h
#include <Windows.h>

//DEFINS
#define SCREEN_WIDTH 100 //lowered to fix border
#define SCREEN_HEIGHT 40
#define FRAME_RATE 10

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

#endif // !Constants_h
