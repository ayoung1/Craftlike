#include <string>

#include "Ai.h"
#include "Map.h"
#include "Game.h"
#include "Player.h"
#include "MapScreen.h"
#include "ResourceNodeBuilder.h"

MapScreen::MapScreen() {
	map = Game::instanceOf()->getNewMap();
	Figure * temp = Game::instanceOf()->getPlayer();

	this->generateResources();
	this->generateCreatures();

	temp = Game::instanceOf()->getPlayer();

	centerX = temp->getXLocation();
	centerY = temp->getYLocation();
}

void MapScreen::generateResources() {
	ResourceNodeBuilder builder;
	
	builder.setName("coal")->setExp(3)->setFailRate(.45)->setResourceAmount(100)->setResourceGrowthAmount(0.01)->setIcon("C")->setColor(COLOR_CYAN)->setGatherAmountFunction([]() {
		Player * player = dynamic_cast<Player*>(Game::instanceOf()->getPlayer());
		int level = player->getSkillLevel(ResourceNode::SKILL);
		
		if (level <= 2)
			return 0;
		return level - 2;
	})->buildNAdd(10);

	builder.setName("wood")->setExp(1)->setFailRate(.15)->setResourceAmount(100)->setResourceGrowthAmount(0.01)->setIcon("W")->setColor(COLOR_CYAN)->setGatherAmountFunction([]() {
		Player * player = dynamic_cast<Player*>(Game::instanceOf()->getPlayer());
		int level = player->getSkillLevel(ResourceNode::SKILL);
		
		return level+1;
	})->buildNAdd(10);
	
	builder.setName("stone")->setExp(1)->setFailRate(.25)->setResourceAmount(100)->setResourceGrowthAmount(0.01)->setIcon("S")->setColor(COLOR_CYAN)->setGatherAmountFunction([]() {
		Player * player = dynamic_cast<Player*>(Game::instanceOf()->getPlayer());
		int level = player->getSkillLevel(ResourceNode::SKILL);

		return level+1;
	})->buildNAdd(10);
}

void MapScreen::generateCreatures(){
	for (int i = 0; i < 100; ++i)
		CreatureBuilder::buildFungus();

	for (int i = 0; i < 25; ++i)
		CreatureBuilder::buildBat();
}

void MapScreen::update(char keypress) {
	IScreen::update(keypress);
	
	for(MapObject* obj : *map->getMapObjects())
		obj->update(map, keypress);

	map->updateMap();
	centerX = Game::instanceOf()->getPlayer()->getXLocation();
	centerY = Game::instanceOf()->getPlayer()->getYLocation();
}

void MapScreen::print() {
	printMap();
}

int MapScreen::getTile(int xloc, int yloc) {
	int height = map->getHeight();
	int width = map->getWidth();

	return 0;
}

void MapScreen::printMap() {
	int x = -1, y = -1, dx, mapx, mapy;
	Tile* tile;
	Tile*** tiles = map->getMap();
	getmaxyx(stdscr, x, y);
	dx = x;
	dx -= int(x * detailZone);

	for (int i = 0; i < dx; ++i) {
		for (int j = 0; j < y; ++j) {

			mapx = (centerX - (dx / 2)) + i;
			mapy = (centerY - (y / 2)) + j;

			if (mapx < 0 || mapy < 0 || mapx >= map->getHeight() || mapy >= map->getWidth()) {
				mvprintw(i, j, " ");
				continue;
			}else
				tile = tiles[mapx][mapy];

			if (tile) {
				if (map->objectAtLocation(mapx, mapy)->empty())
					tile->print(i, j);
				else
					map->objectAtLocation(mapx, mapy)->front()->print(i, j);
			}
		}
	}

	for (int i = dx; i < x; ++i) {
		for (int j = 0; j < y; ++j) {
			mvprintw(i, j, " ");
		}
	}
}

MapScreen::~MapScreen(){
	delete map;
}
