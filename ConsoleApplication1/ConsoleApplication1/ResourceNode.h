#pragma once

class Map;
class Player;

#include <string>
#include "MapObject.h"

class ResourceNode : public MapObject {
public:
	static const std::string SKILL;

	ResourceNode(std::string resourceName, int resourceAmount, int expReward, double regrowthRate, const char * icon, double failRate, int color, int (*function)());
	int getRemainingResources();
	void mineResource(Player * player, int amount);
	std::string getResourceName();
	void emptyMessage();

	virtual bool isPathable() { return false; }
	virtual void onCollision(MapObject * mapObject); 
	virtual void update(Map * map, char keypress);
private:
	double const regrowthRate;
	std::string name;
	int const maxAmount;
	int resourceAmount;
	int expReward;
	int(*getGatheredAmount)();
	double regrowth;
	double failRate;
};