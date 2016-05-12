#pragma once
#ifndef ENDSCREEN_H
#define ENDSCREEN_H

#include "IScreen.h"

class EndScreen : public IScreen {
public:
	virtual void update(char keypress);
	virtual void print();

protected:
	~EndScreen();
};

#endif //ENDSCREEN_H