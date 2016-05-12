#include "Map.h"
#include "Figure.h"
#include "Game.h"

int Map::getHeight() { return height; }
int Map::getWidth() { return width; }
Tile*** Map::getMap() { return tiles; }

Map::Map(int _height, int _width)
{
	if (_width < 1 || _height < 1)
		throw std::invalid_argument("Dimentions need to be larger than 0");

	height = _height;
	width = _width;
	tiles = new Tile**[height];
	objectMatrix = new std::list<MapObject*>**[height];

	for (int i = 0; i < height; ++i) {
		tiles[i] = new Tile*[width];
		objectMatrix[i] = new std::list<MapObject*>*[width];
	}

	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j)
			objectMatrix[i][j] = new std::list<MapObject*>;
	}

	randomize();
	smooth(smoothIterations);
}

std::list<MapObject*>* Map::objectAtLocation(int x, int y)
{
	if (!isInBounds(x, y))
		return new std::list<MapObject*>;

	return objectMatrix[x][y];
}

std::list<MapObject*>* Map::getMapObjects()
{
	if (Game::instanceOf()->getTurns() == 0 || Game::instanceOf()->getTurns() % 25 == 0)
		loadChunk();

	return &loadedChunk;
}

bool Map::isPathable(int x, int y)
{
	if (!isInBounds(x, y))
		return false;

	if (!tiles[x][y]->isPathable())
		return false;

	for (MapObject * obj : *this->objectAtLocation(x, y)) {
		if (!obj->isPathable())
			return false;
	}

	return true;
}

bool Map::isInBounds(int x, int y)
{
	if (x < 0 || y < 0 || x >= getHeight() || y >= getWidth())
		return false;
	return true;
}

void Map::removeObject(MapObject* obj) {
	toRemove.insert(toRemove.begin(), obj);
}

void Map::addMapObject(MapObject * obj)
{
	int locx, locy;
	do {
		locx = std::rand() % height;
		locy = std::rand() % width;
	} while (!isPathable(locx, locy));

	obj->setObjectLocation(locx, locy);
	mapObjects.insert(mapObjects.end(), obj);
	objectMatrix[locx][locy]->insert(objectMatrix[locx][locy]->end(), obj);
}

void Map::updateObjectLocation(MapObject * obj, int oldx, int oldy){
	if (!isInBounds(oldx, oldy))
		return;
	
	if (!objectMatrix[oldx][oldy]->empty()) {
		objectMatrix[oldx][oldy]->remove(obj);
	}

	objectMatrix[obj->getXLocation()][obj->getYLocation()]->insert(objectMatrix[obj->getXLocation()][obj->getYLocation()]->begin(), obj);
}

void Map::updateMap(){
	for (auto obj : toRemove) {
		objectMatrix[obj->getXLocation()][obj->getYLocation()]->remove(obj);
		mapObjects.remove(obj);
		loadedChunk.remove(obj);
	}
	toRemove.clear();
}

void Map::randomize(){
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			
			switch (Game::instanceOf()->getRandom(2)) {
			case 0:
				tiles[i][j] = new Wall();
				break;
			case 1:
				tiles[i][j] = new Floor();
				break;
			default:
				;
			}
		}
	}
}

void Map::smooth(int loops){
	Tile*** temparray = new Tile**[height];
	for (int i = 0; i < height; ++i)
		temparray[i] = new Tile*[width];

	for (int i = 0; i < loops; ++i) {
		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				temparray[i][j] = tiles[i][j];
			}
		}
		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				int floor = 0;
				int walls = 0;

				for (int ox = i - 1; ox < i + 2; ++ox) {
					for (int oy = j - 1; oy < j + 2; ++oy) {
						if (!isInBounds(ox, oy))
							continue;
						if (tiles[ox][oy]->isPathable())
							++floor;
						else
							++walls;
					}
				}

				if (floor + 1 > walls)
					tiles[i][j] = new Floor();
				else
					tiles[i][j] = new Wall();

			}
		}
	}

	for (int i = 0; i < height; ++i)
		delete[] temparray[i];
	delete[] temparray;
}

void Map::loadChunk(){
	Figure* temp = Game::instanceOf()->getPlayer();
	loadedChunk.clear();

	for (int i = temp->getXLocation() - 100; i < temp->getXLocation() + 100; ++i) {
		for (int j = temp->getYLocation() - 100; j < temp->getYLocation() + 100; ++j) {
			if (!isInBounds(i, j))
				continue;

			if (this->objectAtLocation(i, j)->empty())
				continue;

			for (MapObject* obj : *this->objectAtLocation(i, j)) {
				loadedChunk.insert(loadedChunk.begin(), obj);
			}
		}
	}
}

Map::~Map() {
	for (int i = 0; i < height; ++i) {
		delete[] tiles[i];
		delete[] objectMatrix[i];
	}
	delete[] objectMatrix;
	delete[] tiles;
}