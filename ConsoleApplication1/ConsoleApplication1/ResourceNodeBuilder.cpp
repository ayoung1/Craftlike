#include "ResourceNodeBuilder.h"
#include "curses.h"

ResourceNodeBuilder * ResourceNodeBuilder::setName(std::string name)
{
	resourceName = name;
	return this;
}

ResourceNodeBuilder * ResourceNodeBuilder::setResourceAmount(int amount)
{
	resourceAmount = amount;
	return this;
}

ResourceNodeBuilder * ResourceNodeBuilder::setResourceGrowthAmount(double rate)
{
	regrowthRate = rate;
	return this;
}

ResourceNodeBuilder * ResourceNodeBuilder::setFailRate(double failRate)
{
	this->failRate = failRate;
	return this;
}

ResourceNodeBuilder * ResourceNodeBuilder::setIcon(const char * icon)
{
	this->icon = icon;
	return this;
}

ResourceNodeBuilder * ResourceNodeBuilder::setColor(int color)
{
	this->color = color;
	return this;
}

ResourceNodeBuilder * ResourceNodeBuilder::setExp(int exp)
{
	expReward = exp;
	return this;
}

ResourceNodeBuilder * ResourceNodeBuilder::setGatherAmountFunction(int(*function)())
{
	gatherAmount = function;
	return this;
}

ResourceNode * ResourceNodeBuilder::build()
{
	if (resourceName.empty())
		resourceName = "null";
	if (!resourceAmount)
		resourceAmount = 0;
	if (!expReward)
		expReward = 0;
	if (!regrowthRate)
		regrowthRate = 0.0;
	if (!failRate)
		failRate = 1.0;
	if (!icon)
		icon = "?";
	if (!color)
		color = COLOR_BLACK;
	if(!gatherAmount)
		gatherAmount = []() {
		return 0;
	};

	return new ResourceNode(resourceName, resourceAmount, expReward, regrowthRate, icon, failRate, color, gatherAmount);
}

void ResourceNodeBuilder::buildNAdd(int n){
	for (int i = 0; i < n; ++i)
		build();
}
