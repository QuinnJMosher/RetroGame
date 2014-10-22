#include "AIE.h"
#include <vector>
#include <time.h>
#include "Entity.h"
#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "BigEnemy.h"
#include "FastEnemy.h"
#include "TimeTracker.h"
#include "GlobalInfo.h"
#include "Score.h"

#ifndef _Game_h_
#define _Game_h_

class Game{
public: 
	Game();
	~Game();

	Score Start();

	std::vector<Entity*> entities;

private:
	void Update(float in_deltaTime);
	void Draw();
	int Initalize();
	
	TimeTracker timeKeeper;
	bool gamePlaying;
};

#endif