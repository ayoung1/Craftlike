#include "Tile.h"

Tile::Tile(const char* _icon, int _color)
{
	icon = _icon;
	init_pair(_color, _color, COLOR_BLACK);
	color = _color;
}

void Tile::print(int x, int y)
{
	attron(COLOR_PAIR(color));
	mvprintw(x, y, icon);
	attroff(COLOR_PAIR(color));
}
