#pragma once
#include <windows.h>

void drawRect(HDC hdc, int x, int y, int width, int height, COLORREF color);
void drawCircle(HDC hdc, int x, int y, int radius, COLORREF color);
void drawSpiral(HDC dc, int x, int y, int spread, COLORREF color);
void drawline(HDC dc, int x1, int y1, int x2, int y2, COLORREF color);
void drawFilledCircle(HDC hdc, int x, int y, int radius, COLORREF color);

class Graphics {
public:
	void start();
	void stop();
	void (*render)(HDC);
private:
	bool isRunning;
};