#pragma once
#include <string>
#include "Figure.h"

class Item : public MapObject {
public:
	enum class ItemType {
		WEAPON,
		POTION,
		FOOD,
		MISC
	};

	Item(std::string name, ItemType type);

	virtual void onUse(Figure * figure) = 0;
private:
	std::string name;

};