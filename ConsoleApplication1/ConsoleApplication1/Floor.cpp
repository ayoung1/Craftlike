#include "Floor.h"

Floor::Floor() : Tile(" ", -1) {}

void Floor::print(int x, int y){
	mvprintw(x, y, " ");
}

void Floor::onEntry(){

}

void Floor::onAttemptEntry(){

}

bool Floor::isPathable()
{
	return true;
}
