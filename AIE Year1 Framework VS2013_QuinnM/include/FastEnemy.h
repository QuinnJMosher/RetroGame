#include "Enemy.h"

#ifndef _FastEnemy_h_
#define _FastEnemy_h_

class FastEnemy : public Enemy {
public:
	FastEnemy(float in_x, float in_y);
	~FastEnemy();

private:
	static const char* FAST_ENEMY_TEXTURE_PATH;
	static const float FAST_ENEMY_WIDTH;
	static const float FAST_ENEMY_HEIGHT;
	static const float FAST_ENEMY_X_SPEED;
	static const float FAST_ENEMY_Y_SPEED;
	static const int FAST_ENEMY_HIT_POINTS;
	static const int FAST_ENEMY_POINT_VALUE;
};

#endif