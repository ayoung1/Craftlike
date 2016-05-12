#include "MapObject.h"
#include "Map.h"
#include "Game.h"

MapObject::MapObject(const char* _icon, int _color) {
	icon = _icon;
	init_pair(_color, _color, COLOR_BLACK);
	color = _color;
	Game::instanceOf()->getLastCreatedMap()->addMapObject(this);
}

void MapObject::print(int x, int y) {
	attron(COLOR_PAIR(color));
	mvprintw(x, y, icon);
	attroff(COLOR_PAIR(color));
}

void MapObject::setObjectLocation(int x, int y) {
	int oldx = locx, oldy = locy;
	
	if (Game::instanceOf()->getLastCreatedMap()->isPathable(x, y)) {		
		locx = x;
		locy = y;
	}
	
	for(MapObject * obj : *Game::instanceOf()->getLastCreatedMap()->objectAtLocation(x, y))
		obj->onCollision(this);

	Game::instanceOf()->getLastCreatedMap()->updateObjectLocation(this, oldx, oldy);
}