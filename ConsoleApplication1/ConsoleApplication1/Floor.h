#pragma once
#include "Tile.h"

class Floor : public Tile {
public:
	Floor();

	virtual void print(int x, int y);
	virtual void onEntry();
	virtual void onAttemptEntry();
	virtual bool isPathable();
};