#include "Wall.h"

Wall::Wall() : Tile::Tile("#", COLOR_GREEN){

}

void Wall::onEntry()
{

}

void Wall::onAttemptEntry()
{

}

bool Wall::isPathable()
{
	return false;
}
