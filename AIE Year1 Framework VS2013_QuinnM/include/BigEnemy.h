#include "Enemy.h"

#ifndef _BigEnemy_h_
#define _BigEnemy_h_

class BigEnemy : public Enemy {
public:
	BigEnemy(float in_x, float in_y);
	~BigEnemy();

private:
	static const char* BIG_ENEMY_TEXTURE_PATH;
	static const float BIG_ENEMY_WIDTH;
	static const float BIG_ENEMY_HEIGHT;
	static const float BIG_ENEMY_X_SPEED;
	static const float BIG_ENEMY_Y_SPEED;
	static const int BIG_ENEMY_HIT_POINTS;
	static const int BIG_ENEMY_POINT_VALUE;
};

#endif