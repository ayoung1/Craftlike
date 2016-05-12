#include "Ai.h"
#include "Map.h"
#include "Game.h"

void Wander::update(Map * map, Figure * figure) {
	if (Game::instanceOf()->getRandom(2) == 0)
		return;

	switch (Game::instanceOf()->getRandom(4)) {
	case 0:
		figure->setObjectLocation(figure->getXLocation() + 1, figure->getYLocation());

		break;
	case 1:
		figure->setObjectLocation(figure->getXLocation(), figure->getYLocation() + 1);

		break;
	case 2:
		figure->setObjectLocation(figure->getXLocation() - 1, figure->getYLocation());

		break;
	case 3:
		figure->setObjectLocation(figure->getXLocation(), figure->getYLocation() - 1);

		break;
	}

}

Spreading::Spreading(int max, double chance, CreatureBuilder::Creature*(*f)()) {
	maxSpread = max;
	this->chance = chance;
	this->spawnFunction = f;
}

void Spreading::update(Map * map, Figure * figure){
	if (spread < cloneNumber)
		spread = cloneNumber; 
	if (spread >= maxSpread)
		return;

	double rand = Game::instanceOf()->getRandom(100) + 1;
	rand = rand / 100;

	if (rand < chance) {
		int x = (Game::instanceOf()->getRandom(5) - 5) + figure->getXLocation();
		int y = (Game::instanceOf()->getRandom(5) - 5) + figure->getYLocation();

		if (Game::instanceOf()->getLastCreatedMap()->isPathable(x, y)) {
			++spread;
			
			CreatureBuilder::Creature* spawn = dynamic_cast<CreatureBuilder::Creature*>((spawnFunction)());
			Spreading * ai = dynamic_cast<Spreading*>(spawn->getCreatureAi());
			ai->cloneNumber = cloneNumber + 1;

			spawn->setObjectLocation(x, y);
		}
	}
}
