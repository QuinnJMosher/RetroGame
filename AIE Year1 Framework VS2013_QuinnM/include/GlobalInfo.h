#include <vector>
#include "Entity.h"
#include "Game.h"
#ifndef _GlobalInfo_h_
#define _GlobalInfo_h_

static class GlobalInfo {
public:
	static const int SCREEN_MAX_X; 
	static const int SCREEN_MAX_Y;
	static unsigned int playerPoints;
	static unsigned int playerLives;
};

#endif