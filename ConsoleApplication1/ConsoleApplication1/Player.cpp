#include "Player.h"
#include "Map.h"
#include "Game.h"

Player::Player() : Figure::Figure("Player", 100, 10, "@", COLOR_WHITE){
	
}

void Player::addResources(std::string resource, int amount){
	if (resources.find(resource) == resources.end()) {
		resources[resource] = amount;
	}
	else {
		resources[resource] += amount;
	}
}

int Player::getResourceAmount(std::string resource)
{
	if (resources.find(resource) != resources.end())
		return resources[resource];
	return 0;
}

int Player::getSkillLevel(std::string skill)
{
	if (skills.find(skill) != skills.end())
		return skills[skill][LEVEL];
	return 0;
}

int Player::getSkillExp(std::string skill)
{
	if (skills.find(skill) != skills.end())
		return skills[skill][EXP];
	return 0;
}

void Player::addSkillExp(std::string skill, int amount)
{
	int level;
	if (skills.find(skill) == skills.end()) {
		int * temp = new int[2]{ 0,0 };
		skills[skill] = temp;
		skills[skill][EXP] = amount;
	}
	else
		skills[skill][EXP] += amount;

	calculateLevel(skill);
}

void Player::update(Map* map, char keypress){
	switch (keypress) {
	case 'w':
		setObjectLocation(getXLocation() - 1, getYLocation());
		break;
	case 's':
		setObjectLocation(getXLocation() + 1, getYLocation());
		break;
	case 'a':
		setObjectLocation(getXLocation(), getYLocation() - 1);
		break;
	case 'd':
		setObjectLocation(getXLocation(), getYLocation() + 1);
		break;

	default:
		;
	}
}

int Player::calculateLevel(std::string skill)
{
	int leftover;
	int expPerLevel = 100;
	int cur = skills[skill][LEVEL];
	int next = cur + 1;
	int required = (cur*expPerLevel) + (next*expPerLevel);

	while (skills[skill][EXP] > required) {
		Game::instanceOf()->printEvent("Your " + skill + " skill has grown to level " + std::to_string(++skills[skill][LEVEL]));

		leftover = skills[skill][EXP] - required;
		skills[skill][EXP] = leftover;
	}

	return skills[skill][LEVEL];
}

Player::~Player(){

}
