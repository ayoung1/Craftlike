#pragma once
#ifndef GAME_H
#define GAME_H

class Map;
class Figure;
class IScreen;

#include <stack>
#include <string>
#include <cstdlib>

class Game {
public:
	static Game * instanceOf();

	std::stack<IScreen*>* getScreenStack();

	Figure * getPlayer();
	Map * getNewMap();
	Map * getLastCreatedMap();
	int getTurns() { return turns; }
	void dropScreen();
	void stackScreen(IScreen* screen);
	void run();
	void printEvent(std::string string);
	int getRandom(int max);

	~Game();
private:
	static Game * game;
	
	Map * map = 0;
	int turns = -1;
	int eventCounter = 1;
	Figure * player = 0;
	std::stack<IScreen*> screenstack;
	std::stack<std::string> eventList;

	Game();
	void gameLoop();
	void printEvents();
};

#endif //GAME_H