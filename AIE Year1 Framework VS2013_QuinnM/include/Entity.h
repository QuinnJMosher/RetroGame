#include "Point.h"
#include "Point.h"
#include "AIE.h"

#ifndef _Entity_h_
#define _Entity_h_

class Entity{
	
public:
	Entity(float in_x, float in_y, float in_width, float in_height, const char* in_filePath, char in_type);
	Entity(float in_x, float in_y, float in_width, float in_height, const char* in_filePath, char in_type, int in_owner);

	void BuildSprite(const char* in_filePath);
	virtual bool hasColidedWith(Entity &other);
	virtual ~Entity();

	virtual bool Update(float in_deltaTime) = 0;
	virtual void Draw() = 0;
	virtual bool IsAlive() = 0;
	virtual void Collide(Entity &other) = 0;

	char type;
	int OwnerId;

	//bullet creation stuff
	unsigned int bullletDammage;
	float bullletSpeedX;
	float bullletSpeedY;

	Point position;

protected:
	unsigned int spriteID;

	float width;
	float height;
	
private:
	static int nextOwnerId;

};

#endif