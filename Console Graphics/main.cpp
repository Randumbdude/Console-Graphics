#include "Graphics.h"

void render(HDC dc) {
	drawRect(10, 10, 35, 35, RGB(0, 255, 0));
	drawRect(100, 100, 100, 100, RGB(255, 0, 0));
	drawRect(150, 250, 50, 50, RGB(0, 0, 255));
	drawSwirl(300, 100, 10, RGB(255, 0, 255));
	drawCircle(400, 400, 100, RGB(255, 0, 0));
	//drawFilledCircle(400, 400, 100, RGB(255, 0, 0));
}

int main() //ctrl K + ctrl D = format
{
	system("cls");

	Graphics g = Graphics();
	g.render = render;
	g.start();

	return 0;
}