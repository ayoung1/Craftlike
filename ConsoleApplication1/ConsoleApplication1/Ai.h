#pragma once

#include <list>
#include "Game.h"
#include "Creature.h"

class Ai {
public:
	static std::list<Ai*> getAiList() { return ai; }
	virtual void update(Map * map, Figure * figure) = 0;
	virtual bool unique() { return true; }
private:
	static std::list<Ai*> ai;
};

class Spreading : public Ai {
public:
	Spreading(int max, double chance, CreatureBuilder::Creature*(*f)());
	virtual void update(Map * map, Figure * figure);
	virtual bool unique() { return false; }

private:
	CreatureBuilder::Creature*(*spawnFunction)();
	int maxSpread = 1;
	int spread = 0;
	int cloneNumber = 0;
	double chance = 0.5;
};

class Wander : public Ai {
public:
	virtual void update(Map * map, Figure * figure);

private:
};