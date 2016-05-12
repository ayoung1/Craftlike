#include "Game.h"
#include "Map.h"
#include "Player.h"
#include "StartScreen.h"
#include <chrono>
#include <thread>
#include <ctime>

Game * Game::game = 0;

Game * Game::instanceOf() {
	if (!game)
		game = new Game;
	return game;
}

Game::Game(){
	screenstack.push(new StartScreen());
}

void Game::run() {
	srand(time(0));
	gameLoop();
}

void Game::printEvent(std::string string){
	eventList.push(string);
}

std::stack<IScreen*>* Game::getScreenStack() {
	return &screenstack;
}

Figure * Game::getPlayer()
{
	if (!player)
		player = new Player;
	return player;
}

Map * Game::getNewMap()
{
	map = new Map(100, 100);
	return map;
}

Map * Game::getLastCreatedMap()
{
	return map;
}

void Game::dropScreen() {
	screenstack.pop();
}

void Game::stackScreen(IScreen* screen) {
	if(screen)
		screenstack.push(screen);
}

Game::~Game(){}

void Game::gameLoop() {
	char keypress; 
	initscr();

	if (has_colors() == FALSE)
	{
		endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}

	start_color();

	while (!screenstack.empty()) {		
		screenstack.top()->print();
		printEvents();
		eventCounter = 1;
		keypress = getch();
		screenstack.top()->update(keypress);
		refresh();
		++turns;
	}

	endwin();
}

void Game::printEvents(){
	int x, y;
	getmaxyx(stdscr, x, y);

	while (!eventList.empty()) {
		if (x - eventCounter < 0) {
			while (!eventList.empty())
				eventList.pop();
			return;
		}
		
		mvprintw(x - eventCounter, 0, eventList.top().c_str());
		eventList.pop();
		++eventCounter;
	}	
}

int Game::getRandom(int max)
{
	return rand() % max;
}
