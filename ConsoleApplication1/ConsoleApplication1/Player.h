#pragma once

#include <map>
#include <string>
#include "Figure.h"

class Player : public Figure {
public:
	Player();

	void addResources(std::string resource, int amount);
	int getResourceAmount(std::string resource);
	int getSkillLevel(std::string skill);
	int getSkillExp(std::string skill);
	void addSkillExp(std::string skill, int amount);
	virtual void update(Map* map, char keypress);

	~Player();
private:
	static const int EXP = 0;
	static const int LEVEL = 1;

	std::map<std::string, int> resources;
	std::map<std::string, int*> skills;

	int calculateLevel(std::string skill);
};