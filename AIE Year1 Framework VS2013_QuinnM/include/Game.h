#include <vector>
#include "Entity.h"
#include "Player.h"
#include "TimeTracker.h"

#ifndef _Game_h_
#define _Game_h_

class Game{
public: 
	Game();
	~Game();

	void Start();

	std::vector<Entity*> entities;

private:
	void Update(float in_deltaTime);
	void Draw();
	int Initalize();
	int LoadContent();
	

	//EnemyScript curentScript;
	TimeTracker timeKeeper;
	bool gamePlaying;
};

#endif