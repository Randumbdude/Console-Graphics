#pragma once
#define _WIN32_WINNT 0x0500
#include <windows.h>

void drawRect(int x, int y, int width, int height, COLORREF color);
void drawCircle(int x, int y, int radius, COLORREF color);
void drawSwirl(int x, int y, int spread, COLORREF color);
void drawline(int x1, int y1, int x2, int y2, COLORREF color);
void drawFilledCircle(int x, int y, int radius, COLORREF color);

class Graphics {
public:
	void start();
	void stop();
	void (*render)(HDC);
private:
	bool isRunning;
};