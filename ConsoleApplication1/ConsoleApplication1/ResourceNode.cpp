#include "ResourceNode.h"
#include "Player.h"
#include "Game.h"

const std::string ResourceNode::SKILL = "gathering";

ResourceNode::ResourceNode(std::string resourceName, int resourceAmount, int expReward, double regrowthRate, const char * icon, double failRate, int color, int(*function)()) : MapObject(icon, color), regrowthRate(regrowthRate), maxAmount(resourceAmount) {
	this->failRate = failRate;
	this->resourceAmount = maxAmount;
	this->expReward = expReward;
	getGatheredAmount = function;
	name = resourceName;
	regrowth = 0.0;
}

int ResourceNode::getRemainingResources()
{
	return resourceAmount;
}

void ResourceNode::mineResource(Player * player, int amount)
{
	double chance = ((double)((Game::instanceOf()->getRandom(100) + 1)) / 100);
	if (chance < failRate || amount < 1){
		Game::instanceOf()->printEvent("You've failed to gather any resources");
		return;
	}

	int finalamount = amount;

	if (resourceAmount > amount) {
		resourceAmount -= amount;
	}else {
		finalamount = resourceAmount;
		resourceAmount = 0;
		Game::instanceOf()->printEvent("This node has run out of resources");
	}

	player->addSkillExp(SKILL, expReward);
	player->addResources(name, finalamount);
	Game::instanceOf()->printEvent("You gather " + std::to_string(finalamount) + " " + name + "!");
	Game::instanceOf()->printEvent("You have " + std::to_string(player->getResourceAmount(name)) + " " + name);
}

std::string ResourceNode::getResourceName()
{
	return name;
}

void ResourceNode::emptyMessage(){
	Game::instanceOf()->printEvent("This " + getResourceName() + " is out of resources");
}

void ResourceNode::onCollision(MapObject * mapObject){
	if (Player * player = dynamic_cast<Player*>(mapObject)) {
		if (getRemainingResources() > 0) {
			mineResource(player, getGatheredAmount());
		}
		else {
			emptyMessage();
		}
	}
}

void ResourceNode::update(Map * map, char keypress) {
	if (resourceAmount == maxAmount)
		return;

	regrowth += regrowthRate;
	if (regrowth >= 1.0) {
		regrowth = 0.0;
		resourceAmount++;
	}
}