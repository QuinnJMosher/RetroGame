#include "Entity.h"
#include "Point.h"
#include "AIE.h"

int Entity::nextOwnerId = 0;

Entity::Entity(float in_x, float in_y, float in_width, float in_height, const char* in_texturePath, char in_type) {
	this->position = Point(in_x, in_y);
	this->width = in_width;
	this->height = in_height;
	this->BuildSprite(in_texturePath);
	this->OwnerId = nextOwnerId;
	this->type = in_type;

	nextOwnerId++;
}

Entity::Entity(float in_x, float in_y, float in_width, float in_height, const char* in_texturePath, char in_type, int in_owner) {
	this->position = Point(in_x, in_y);
	this->width = in_width;
	this->height = in_height;
	this->BuildSprite(in_texturePath);
	this->OwnerId = in_owner;
	this->type = in_type;
}

void Entity::BuildSprite(const char* in_filePath) {
	this->spriteID = CreateSprite(in_filePath, width, height, true);
}

Entity::~Entity() {
	position.~Point();
}

bool Entity::hasColidedWith(Entity &other) {

}