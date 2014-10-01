#include "Point.h"

#ifndef _Entity_h_
#define _Entity_h_

class Entity{
	
public:
	Entity(float in_x, float in_y, float in_width, float in_height, const char* in_filePath);
	void BuildSprite(const char* in_filePath);
	virtual ~Entity();

	virtual void Update(float in_deltaTime) = 0;
	virtual void Draw() = 0;

protected:
	Point position;
	float width;
	float height;
	unsigned int spriteID;

};

#endif