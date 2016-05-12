#include "Creature.h"
#include "Game.h"
#include "Ai.h"

CreatureBuilder* CreatureBuilder::builder = new CreatureBuilder;

CreatureBuilder::Creature::Creature(std::string name, int life, int damage, const char * icon, Ai* ai) : Figure(name, life, damage, icon, COLOR_WHITE){
	this->ai = ai;
}

Ai * CreatureBuilder::Creature::getCreatureAi()
{
	return ai;
}

void CreatureBuilder::Creature::update(Map * map, char keypress){
	ai->update(map, this);
}

CreatureBuilder * CreatureBuilder::setName(std::string name){
	this->name = name;
	return this;
}

CreatureBuilder * CreatureBuilder::setLife(int life){
	this->life = life;
	return this;
}

CreatureBuilder * CreatureBuilder::setDamage(int damage){
	this->damage = damage;
	return this;
}

CreatureBuilder * CreatureBuilder::setIcon(const char * icon){
	this->icon = icon;
	return this;
}

CreatureBuilder * CreatureBuilder::setAi(Ai * ai){
	if (ai->unique()) {
		for (Ai * obj : Ai::getAiList()) {
			if (typeid(*obj) == typeid(*ai)) {
				this->ai = obj;
				delete ai;
				break;
			}
		}
		if (!this->ai) {
			this->ai = ai;
			Ai::getAiList().insert(Ai::getAiList().begin(), ai);
		}
	}else
		this->ai = ai;

	return this;
}

CreatureBuilder::Creature * CreatureBuilder::build(){
	if (name.empty())
		name = " ";
	if (life < 1)
		life = 1;
	if (damage < 0)
		damage = 0;
	if (!icon)
		icon = " ";
	if (!ai)
		ai = new Wander();
	
	return new CreatureBuilder::Creature(name, life, damage, icon, ai);
}

CreatureBuilder::Creature * CreatureBuilder::buildFungus()
{
	return builder->setName("Fungus")->setLife(15)->setDamage(0)->setIcon("F")->setAi(new Spreading(2, .15, buildFungus))->build();
}

CreatureBuilder::Creature * CreatureBuilder::buildBat()
{
	return builder->setName("Bat")->setLife(10)->setDamage(5)->setIcon("B")->setAi(new Wander())->build();
}
