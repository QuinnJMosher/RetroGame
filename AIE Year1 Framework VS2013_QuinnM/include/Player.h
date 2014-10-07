#include "Entity.h"

#ifndef _Player_h_
#define _Player_h_

class Player : public Entity{
public:
	Player();
	~Player();

	void Update(float in_deltaTime);
	void Draw();

	Player& operator=(Player other);

	void Collide(Entity &other);
	void Move(float in_deltaTime);
	void Fire();

	bool IsAlive();
	bool TakeDammage(unsigned int in_dammage); //returns false if dead
	void RestoreHealth(unsigned int in_healing);
	int GetHitPoints();
	void ChangeVelocity(float in_xVelocity, float in_yVelocity);
	void ChangeSpeed(float in_xSpeed, float in_ySpeed);

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
	unsigned int bullletDammage;

	//interval vars
	float immunityTime;
	float firePauseTime;
	//interval constants
	const float IMUNITY_INTERVAL = 1.f;
	const float FIRE_INTERVAL = 0.25f;

	//player constants
	static const char* PLAYER_TEXTURE_PATH;
	static const float PLAYER_WIDTH;
	static const float PLAYER_HEIGHT;
	static const float PLAYER_START_X;
	static const float PLAYER_START_Y;
};

#endif