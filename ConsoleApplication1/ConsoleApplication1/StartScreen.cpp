#include "StartScreen.h"
#include "Game.h"

void StartScreen::update(char keypress){
	IScreen::update(keypress);
	IScreen * screen = new MapScreen();
	clear();
	Game::instanceOf()->dropScreen();
	Game::instanceOf()->stackScreen(screen);
}

void StartScreen::print(){
	mvprintw(0, 0, "Start Screen");
}

StartScreen::~StartScreen(){

}
