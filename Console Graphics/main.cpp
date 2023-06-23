#include "Graphics.h"

void render(HDC dc) {
	drawRect(dc, 10, 10, 35, 35, RGB(0, 255, 0));
	drawRect(dc, 100, 100, 100, 100, RGB(255, 0, 0));
	drawRect(dc, 150, 250, 50, 50, RGB(0, 0, 255));
	//drawSpiral(dc, 100, 100, 10, RGB(255, 0, 0));
	//drawCircle(dc, 400, 400, 100, RGB(255, 0, 0));
	//drawFilledCircle(dc, 400, 400, 100, RGB(255, 0, 0));
}

int main() //ctrl K + ctrl D = format
{
	system("cls");

	Graphics g = Graphics();
	g.render = render;
	g.start();

	return 0;
}