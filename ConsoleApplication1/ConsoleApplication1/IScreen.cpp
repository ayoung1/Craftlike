#include "IScreen.h"
#include "Game.h"

void IScreen::update(char keypress){
	if (keypress == 27) {
		Game::instanceOf()->dropScreen();
	}
}
