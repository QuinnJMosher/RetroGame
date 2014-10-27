#include "Entity.h"
#include "GlobalInfo.h"
#include "AIE.h"

#ifndef _Bullet_h_
#define _Bullet_h_

class Bullet : public Entity {
public:
	Bullet(float in_x, float in_y, float in_velocityX, float in_velocityY, int in_damage, int in_owner);
	Bullet(float in_x, float in_y, int in_owner);
	Bullet(float in_x, float in_y);
	~Bullet();

	bool Update(float in_deltaTime);
	void Draw();

	bool IsAlive();
	void Collide(Entity &other);

	bool CheckHasHit();
	void Hit();

	int damageValue;

private:

	//movement vars
	float xVelocity;
	float yVelocity;

	bool hasHit;

	//Bullet constants
	static const char* BULLET_TEXTURE_PATH;
	static const float BULLET_WIDTH;
	static const float BULLET_HEIGHT;
	static const char BULLET_TYPE_TAG;

	//defaults
	static const float BULLET_DEFAULT_X_VELOCITY;
	static const float BULLET_DEFAULT_Y_VELOCITY;
	static const int BULLET_DEFAULT_DAMAGE;

};

#endif