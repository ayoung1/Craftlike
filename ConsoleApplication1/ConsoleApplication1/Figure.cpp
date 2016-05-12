#include "Figure.h"
#include "Game.h"
#include "Map.h"

Figure::Figure(std::string name, int life, int damage, const char * icon, int color) : MapObject(icon, color) {
	this->name = name;
	this->life = life;
	this->damage = damage;
}

bool Figure::isAlive(){	
	return life > 0;
}

std::string Figure::getName()
{
	return name;
}

bool Figure::isPathable(){
	return false;
}

void Figure::onCollision(MapObject * mapObject){
	if (Figure * figure = dynamic_cast<Figure*>(mapObject)) {
		takeDamage(figure);
	}
}

void Figure::takeDamage(Figure* other){
	int damage = other->getDamage();
	life -= damage;
	Game::instanceOf()->printEvent(other->getName() + " dealt " + std::to_string(damage) + " to " + getName());
	if (!isAlive()) {
		Game::instanceOf()->printEvent(getName() + " was killed by " + other->getName());
		Game::instanceOf()->getLastCreatedMap()->removeObject(this);
	}
}

int Figure::getDamage(){
	return damage;
}

