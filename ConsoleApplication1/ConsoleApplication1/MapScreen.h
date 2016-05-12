#pragma once
#ifndef MAPSCREEN_H
#define MAPSCREEN_H
#include <cmath>

#include "Map.h"
#include "IScreen.h"
#include "Creature.h"

class MapScreen : public IScreen {
public:
	MapScreen();

	void generateResources();
	void generateCreatures();

	~MapScreen();
	virtual void update(char keypress);
	virtual void print();
private:
	Map * map;
	const double detailZone = .10;
	int centerX;
	int centerY;

	int getTile(int xloc, int yloc);
	void printMap();
};

#endif //MAPSCREEN_H