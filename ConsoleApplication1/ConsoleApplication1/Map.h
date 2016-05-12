#pragma once
#ifndef MAP_H
#define MAP_H

class MapObject;

#include <list>
#include <iostream>
#include "Wall.h"
#include "Floor.h"

class Map {
public:
	Map(int _height, int _width);
	std::list<MapObject*>* objectAtLocation(int x, int y);
	std::list<MapObject*>* getMapObjects();
	bool isPathable(int x, int y);
	bool isInBounds(int x, int y);
	void removeObject(MapObject* obj);
	void addMapObject(MapObject* obj);
	void updateObjectLocation(MapObject* obj, int oldx, int oldy);
	void updateMap();
	int getHeight();
	int getWidth();
	Tile*** getMap();
	~Map();
private:
	const int smoothIterations = 3;
	int height, width, numberOfObjects = 0;

	std::list<MapObject*> mapObjects;
	std::list<MapObject*> loadedChunk;
	std::list<MapObject*> toRemove;
	std::list<MapObject*>*** objectMatrix;
	Tile*** tiles;

	void randomize();
	void smooth(int loops);
	void loadChunk();

};

#endif //MAP_H