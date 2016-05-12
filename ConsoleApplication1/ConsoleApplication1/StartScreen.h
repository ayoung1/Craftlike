#pragma once
#ifndef STARTSCREEN_H
#define STARTSCREEN_H
#include "MapScreen.h"

class StartScreen : public IScreen {

public:
	virtual void update(char keypress);
	virtual void print();
protected:
	~StartScreen();
};

#endif //STARTSCREEN_H