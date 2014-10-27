#include "Entity.h"
#include "Player.h"
#include "Bullet.h"

#ifndef _Enemy_h_
#define _Enemy_h_

class Enemy : public Entity{
public:
	Enemy(float in_x, float in_y);
	~Enemy();

	bool Update(float in_deltaTime);
	void Draw();

	void Move(float in_deltaTime);
	void Collide(Entity &other);

	bool IsAlive();
	bool TakeDamage(unsigned int in_dammage); //returns false if dead

protected:
	Enemy(float in_x, float in_y, float in_width, float in_height, const char* in_txPath, float in_xSpeed, float in_ySpeed, int in_hp, int in_ptValue);

private:

	//actual speed
	float xSpeed;
	float ySpeed;

	//stats
	unsigned int hitPoints;
	unsigned int pointValue;

	//Enemy constants
	static const char* ENEMY_TEXTURE_PATH;
	static const float ENEMY_WIDTH;
	static const float ENEMY_HEIGHT;
	static const char ENEMY_TYPE_TAG;

	static const float ENEMY_DEFAULT_X_SPEED;
	static const float ENEMY_DEFAULT_Y_SPEED;
	static const int ENEMY_DEFAULT_POINT_VALUE;
	static const int ENEMY_DEFAULT_HIT_POINTS;
};

#endif