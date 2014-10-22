#include "Entity.h"
#include "Bullet.h"
#include "GlobalInfo.h"
#include "AIE.h"
#include <typeinfo> 
#include <vector>

#ifndef _Player_h_
#define _Player_h_

class Player : public Entity{
public:
	Player();
	~Player();

	//standard method calls
	bool Update(float in_deltaTime);
	void Draw();

	void Collide(Entity &other);//preform actions to things that have been colided with (called ON conlide)
	void Move(float in_deltaTime);//preform the movement portion of update
	void Fire();//create a bullet

	bool IsAlive();//check if object should still be updating
	bool TakeDamage(unsigned int in_dammage); //reduce hitPoints (returns false if dead)
	void RestoreHealth(unsigned int in_healing);//increase hitPoints
	int GetHitPoints();//gettre for hitPoints
	void ChangeVelocity(float in_xVelocity, float in_yVelocity);//change the forced movement values
	void ChangeSpeed(float in_xSpeed, float in_ySpeed);//change the speed of player-inputed movement

	bool hasColidedWith(Entity &other);//overide

private:
	//input key vars
	char inputKeyUp;
	char inputKeyDown;
	char inputKeyLeft;
	char inputKeyRight;
	char inputKeyFire;

	//forced movement vars
	float xVelocity;
	float yVelocity;
	//actual speed
	float xSpeed;
	float ySpeed;

	//stats
	unsigned int maxHitPoints;
	unsigned int hitPoints;

	//interval vars
	float immunityTime;
	float firePauseTime;
	//interval constants
	const float IMUNITY_INTERVAL = 1.f;
	const float FIRE_INTERVAL = 0.1f;

	//bullet container
	std::vector<Bullet*> bullets;

	//player constants
	static const char* PLAYER_TEXTURE_PATH;
	static const float PLAYER_WIDTH;
	static const float PLAYER_HEIGHT;
	static const float PLAYER_START_X;
	static const float PLAYER_START_Y;
	static const char PLAYER_TYPE_TAG;
};

#endif