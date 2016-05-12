#pragma once
#include "Tile.h"

class Wall : public Tile {
public:
	Wall();

	virtual void onEntry();
	virtual void onAttemptEntry();
	virtual bool isPathable();
};