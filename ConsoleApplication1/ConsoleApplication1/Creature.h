#pragma once

class Ai;

#include <string>
#include "Figure.h"

class CreatureBuilder{
public:
	class Creature : public Figure {
	public:
		Creature(std::string name, int life, int damage, const char * icon, Ai* ai);

		Ai* getCreatureAi();
		virtual void update(Map * map, char keypress);
	private:
		Ai* ai;
	};

	CreatureBuilder * setName(std::string name);
	CreatureBuilder * setLife(int life);
	CreatureBuilder * setDamage(int damage);
	CreatureBuilder * setIcon(const char* icon);
	CreatureBuilder * setAi(Ai* ai);

	Creature * build();
	static Creature* buildFungus();
	static Creature* buildBat();

private:
	static CreatureBuilder* builder;

	std::string name = 0;
	Ai * ai = 0;
	int life, damage;
	const char* icon = 0;
};