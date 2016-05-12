#include "EndScreen.h"

void EndScreen::update(char keypress) {
	
}

void EndScreen::print() {
	mvprintw(0, 0, "Game Over");
	mvprintw(1, 0, "Press any key to exit...");
}

EndScreen::~EndScreen()
{

}
