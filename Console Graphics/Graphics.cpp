#include <cmath>
#include <iostream>
#include <chrono>
#include <ctime>
#include <thread>
#include "Graphics.h"

HWND console = GetConsoleWindow();
HDC dc;

void showConsoleCursor(bool showCursor)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showCursor;
	SetConsoleCursorInfo(out, &cursorInfo);
}
void disableQuickEdit() {
	HANDLE hInput;
	DWORD prev_mode;
	hInput = GetStdHandle(STD_INPUT_HANDLE);
	GetConsoleMode(hInput, &prev_mode);
	SetConsoleMode(hInput, prev_mode & ENABLE_EXTENDED_FLAGS);
}
void disableScrollBars() {
	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsole, &screenBufferInfo);
	COORD new_screen_buffer_size;
	new_screen_buffer_size.X = screenBufferInfo.srWindow.Right - screenBufferInfo.srWindow.Left + 1;
	new_screen_buffer_size.Y = screenBufferInfo.srWindow.Bottom - screenBufferInfo.srWindow.Top + 1;
	SetConsoleScreenBufferSize(hConsole, new_screen_buffer_size);
}

void Graphics::start()
{

	this->isRunning = true;
	do {
		showConsoleCursor(false);
		disableScrollBars();
		disableQuickEdit();
		dc = GetDC(console);
		if (!this->render) break;
		this->render(dc);
		ReleaseDC(console, dc);
	} while (this->isRunning);
}

void Graphics::stop()
{
	this->isRunning = false;
}

void drawRect(int x, int y, int width, int height, COLORREF color) {


	int pixelX = x;
	int pixelY = y;

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++)
		{
			SetPixel(dc, pixelX, pixelY, color);
			pixelX += 1;
		}
		pixelY += 1;
		pixelX = x;
	}
}

void drawSwirl(int x, int y, int spread, COLORREF color) {
	int pixel = x;

	//Draw pixels
	for (double i = 0; i < 3.14 * 4; i += 0.05)
	{
		SetPixel(dc, pixel, (int)(y + spread * cos(i)), color);
		pixel += 1;
	}
}

void drawCircle(int x, int y, int r, COLORREF color)
{
	int tmpX, tmpY, lastX, lastY;
	lastX = lastY = 0;

	for (float angle = 0.5; angle < r * r; angle += 0.5)//Bigger circle, Smaller angle step
	{
		tmpX = r * cos(angle * 3.14);
		tmpY = r * sin(angle * 3.14);
		if (tmpX == lastX && tmpY == lastY)
		{
			continue;
		}
		SetPixel(dc, x + tmpX, y + tmpY, color);
		SetPixel(dc, x - tmpX, y + tmpY, color);
		SetPixel(dc, x + tmpX, y - tmpY, color);
		SetPixel(dc, x - tmpX, y - tmpY, color);
	}
}

void drawFilledCircle(int x, int y, int r, COLORREF color)
{
	auto start = std::chrono::system_clock::now();
	// Some computation here

	int tmpX, tmpY, lastX, lastY;
	lastX = lastY = 0;

	int newR = r;

	for (int i = 0; i < r; i++) {
		for (float angle = 0.5; angle < r * r; angle += 0.5)//Bigger circle, Smaller angle step
		{
			tmpX = newR * cos(angle * 3.14);
			tmpY = newR * sin(angle * 3.14);
			if (tmpX == lastX && tmpY == lastY)
			{
				continue;
			}
			SetPixel(dc, x + tmpX, y + tmpY, color);
			SetPixel(dc, x - tmpX, y + tmpY, color);
			SetPixel(dc, x + tmpX, y - tmpY, color);
			SetPixel(dc, x - tmpX, y - tmpY, color);
		}
		newR--;
	}

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::time_t end_time = std::chrono::system_clock::to_time_t(end);
	std::cout << "Done! elapsed time: " << elapsed_seconds.count() << "s" << std::endl;
}

void drawline(int x0, int y0, int x1, int y1, COLORREF color)
{
	int dx, dy, p, x, y;

	dx = x1 - x0;
	dy = y1 - y0;

	x = x0;
	y = y0;

	p = 2 * dy - dx;

	while (x < x1)
	{
		if (p >= 0)
		{
			SetPixel(dc, x, y, color);
			y = y + 1;
			p = p + 2 * dy - 2 * dx;
		}
		else
		{
			SetPixel(dc, x, y, color);
			p = p + 2 * dy;
		}
		x = x + 1;
	}
}