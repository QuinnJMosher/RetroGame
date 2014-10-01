#include "Entity.h"
#include "Point.h"
#include "AIE.h"

Entity::Entity(float in_x, float in_y, float in_width, float in_height, const char* in_texturePath) {
	this->position = Point(in_x, in_y);
	this->width = in_width;
	this->height = in_height;
	this->BuildSprite(in_texturePath);
}

void Entity::BuildSprite(const char* in_filePath) {
	this->spriteID = CreateSprite(in_filePath, position.x, position.y, true);
}

Entity::~Entity() {
	position.~Point();
}