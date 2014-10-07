#include "Point.h"

#ifndef _Entity_h_
#define _Entity_h_

class Entity{
	
public:
	Entity(float in_x, float in_y, float in_width, float in_height, const char* in_filePath, char in_type);
	Entity(float in_x, float in_y, float in_width, float in_height, const char* in_filePath, char in_type, int in_owner);

	void BuildSprite(const char* in_filePath);
	virtual ~Entity();

	virtual void Update(float in_deltaTime) = 0;
	virtual void Draw() = 0;
	virtual bool IsAlive() = 0;

	Point position;
	float width;
	float height;

	char type;
	int OwnerId;

protected:
	unsigned int spriteID;
	
private:
	static int nextOwnerId;

};

#endif