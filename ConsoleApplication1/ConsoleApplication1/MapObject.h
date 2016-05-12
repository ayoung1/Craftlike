#pragma once

class Map;

#include "curses.h"

class MapObject {
public:
	MapObject() {};
	MapObject(const char* _icon, int _color);
	virtual bool isPathable() = 0;
	virtual void update(Map* map, char keypress) = 0;
	virtual void onCollision(MapObject * mapObject) = 0;
	virtual void print(int x, int y);
	void setObjectLocation(int x, int y);
	int getXLocation() { return locx; }
	int getYLocation() { return locy; }

private:
	const char* icon;
	int color;
	int locx = -1;
	int locy = -1;
};