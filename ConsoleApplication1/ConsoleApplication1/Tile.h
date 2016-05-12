#pragma once
#include "curses.h"

class Tile {
private:
	const char* icon;
	int color;
public:
	Tile() {};
	Tile(const char* _icon, int _color);
	virtual void print(int x, int y);
	virtual void onEntry() = 0;
	virtual void onAttemptEntry() = 0;
	virtual bool isPathable() = 0;
};