#pragma once
#include <string>
#include "MapObject.h"

class Figure : public MapObject {

public:
	Figure() {}
	Figure(std::string name, int life, int damage, const char* icon, int color);
	bool isAlive();
	std::string getName();
	virtual bool isPathable();
	virtual void onCollision(MapObject * mapObject);
private:
	std::string name;
	int life = 0;
	int damage = 0;

	void takeDamage(Figure * figure);
	int getDamage();
};