#include <windows.h>

#include <string>
#include <iostream>

static constexpr unsigned int FONT_WIDTH = 8;
static constexpr unsigned int FONT_HEIGHT = 8;

static constexpr unsigned int WINDOW_WIDTH = 100;
static constexpr unsigned int WINDOW_HEIGHT = 50;

int Error(const std::string &msg, int value = 1)
{
	std::cerr << msg << std::endl;
	return value;
}

int main()
{
	HANDLE hConsoleOut;

	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hConsoleOut == INVALID_HANDLE_VALUE)
		return Error("failed to open console output");

	//std::cout << "_/|\\_";

	// Set font size
	CONSOLE_FONT_INFOEX cfi;
	cfi.cbSize = sizeof(cfi);
	cfi.nFont = 0;
	cfi.dwFontSize.X = FONT_WIDTH;
	cfi.dwFontSize.Y = FONT_HEIGHT;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_NORMAL;
	wcscpy_s(cfi.FaceName, L"Consolas");
	if (!SetCurrentConsoleFontEx(hConsoleOut, FALSE, &cfi))
		return Error("Fail to set font");

	SMALL_RECT windowRect = {0, 0, WINDOW_WIDTH - 1, WINDOW_HEIGHT - 1};
	if (SetConsoleWindowInfo(hConsoleOut, TRUE, &windowRect) == FALSE)
		return Error("failed to set window size");

	// Clear screennn 
	CHAR_INFO screen[WINDOW_HEIGHT * WINDOW_WIDTH];
	for (int y = 0; y < WINDOW_HEIGHT; y++)
	{
		for (int x = 0; x < WINDOW_WIDTH; x++)
		{
			int offset = x + y * WINDOW_WIDTH;
			screen[offset].Char.UnicodeChar = ' ';
			screen[offset].Attributes = 
				FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY | //foreground flags
				0; //background flags
		}
	}

	// test coodinatessss
	int offset;
	offset = 0 + 0 * WINDOW_WIDTH;
	screen[offset].Char.UnicodeChar = 'A';
	offset = WINDOW_WIDTH-1 + 0 * WINDOW_WIDTH;
	screen[offset].Char.UnicodeChar = 'B';
	offset = 0 + (WINDOW_HEIGHT-1) * WINDOW_WIDTH;
	screen[offset].Char.UnicodeChar = 'C'; 
	offset = (WINDOW_WIDTH-1) + (WINDOW_HEIGHT-1) * WINDOW_WIDTH;
	screen[offset].Char.UnicodeChar = 'D';

	// Display screen in the console
	WriteConsoleOutput(hConsoleOut, screen, { WINDOW_WIDTH, WINDOW_HEIGHT }, {0, 0}, &windowRect);

	// Wait forever
	for (;;) {}

	return 0;
}
