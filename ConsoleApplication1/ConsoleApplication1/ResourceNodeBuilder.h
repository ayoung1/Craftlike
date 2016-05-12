#pragma once
#include <string>
#include "ResourceNode.h"

class ResourceNodeBuilder {
public:

	ResourceNodeBuilder * setName(std::string name);
	ResourceNodeBuilder * setResourceAmount(int amount);
	ResourceNodeBuilder * setResourceGrowthAmount(double rate);
	ResourceNodeBuilder * setFailRate(double failRate);
	ResourceNodeBuilder * setIcon(const char * icon);
	ResourceNodeBuilder * setColor(int color);
	ResourceNodeBuilder * setExp(int exp);
	ResourceNodeBuilder * setGatherAmountFunction(int(*function)());
	ResourceNode * build();
	void buildNAdd(int n);

private:
	std::string resourceName;
	int color; 
	int(*gatherAmount)();
	int resourceAmount;
	int expReward;
	double regrowthRate;
	double failRate;
	const char * icon;
};