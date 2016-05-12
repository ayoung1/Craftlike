#pragma once
#define _SECURE_SCL 0
#include "Game.h"

int main(int argc, char *argv) {
	Game::instanceOf()->run();
	return 0;
}