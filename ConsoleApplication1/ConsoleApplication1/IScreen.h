#pragma once
#ifndef ISCREEN_H
#define ISCREEN_H

#include "curses.h"

class Game;

class IScreen {
public:
	virtual void update(char keypress);
	virtual void print() = 0;
	virtual ~IScreen() {}
};

#endif //ISCREEN_H