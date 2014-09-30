#include <vector>

#ifndef _Game_h_
#define _Game_h_

class Game{
public: 
	Game();
	~Game();

	void Start();

private:
	void Update(float in_deltaTime);
	void Draw();
	int Initalize();
	int LoadContent();

	//std::vector<Entity> entities;
	//EnemyScript curentScript;
	unsigned int playerPoints;
	unsigned int playerLives;
	bool gamePlaying;
};

#endif