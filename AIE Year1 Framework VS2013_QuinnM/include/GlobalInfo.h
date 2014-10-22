#include <vector>
#include "Entity.h"

#ifndef _GlobalInfo_h_
#define _GlobalInfo_h_

class GlobalInfo {
public:
	static const float SCREEN_MAX_X; 
	static const float SCREEN_MAX_Y;

	static unsigned int globalPlayerHealth;
	static unsigned int playerPoints;
	static unsigned int playerLives;
	static unsigned int nexLifePoints;

	static char* pointsToString();
	static char* healthToString();
	static char* livesToString();
};

#endif