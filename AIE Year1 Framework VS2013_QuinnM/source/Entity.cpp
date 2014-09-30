#include "Entity.h"
#include "Point.h"
#include "AIE.h"

Entity::Entity(float in_x, float in_y, float in_width, float in_height) {
	this->position = Point(in_x, in_y);
	this->width = in_width;
	this->height = in_height;
}

void Entity::BuildSprite(char* in_filePath) {
	this->spriteId = CreateSprite(in_filePath, position.x, position.y, true);
}

Entity::~Entity() {
	position.~Point();
}