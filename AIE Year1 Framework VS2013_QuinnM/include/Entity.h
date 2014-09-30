#include "Point.h"

#ifndef _Entity_h_
#define _Entity_h_

class Entity{
	
public:
	Entity(float in_x, float in_y, float in_width, float in_height);
	void BuildSprite(char* in_filePath);
	~Entity();

	virtual void Move(float in_deltaTime) = 0;
	virtual void Draw() = 0;

protected:
	Point position;
	float width;
	float height;
	unsigned int spriteId;

};

#endif