#include "Enemy.h"
#include "GlobalInfo.h"
#include "AIE.h"

//Enemy constants
const char* Enemy::ENEMY_TEXTURE_PATH = "./images/invaders/invaders_1_00.png";
const float Enemy::ENEMY_WIDTH = 40;
const float Enemy::ENEMY_HEIGHT = 40;

Enemy::Enemy(float in_x, float in_y) : Entity(in_x, in_y, ENEMY_WIDTH, ENEMY_HEIGHT, ENEMY_TEXTURE_PATH, 'E') {
	this->xVelocity = 0;
	this->yVelocity = 0;
	this->xSpeed = 0;
	this->ySpeed = -100;

	this->hitPoints = 40;
	this->pointValue = 10;
}

Enemy::~Enemy() { }

void Enemy::Update(float in_deltaTime) {//override
	Move(in_deltaTime);
}

void Enemy::Draw() {//override
	DrawSprite(spriteID);
}

void Enemy::Move(float in_deltaTime){
	position.x += xVelocity + (xSpeed * in_deltaTime);
	position.y += yVelocity + (ySpeed * in_deltaTime);

	MoveSprite(spriteID, position.x, position.y);
}

bool Enemy::IsAlive() {//override
	if (hitPoints <= 0) {
		GlobalInfo::playerPoints += pointValue;
		return false;
	} else if (position.y < 0 - width) {
		return false;
	}
	return true;
}

bool Enemy::TakeDamage(unsigned int in_dammage) {
	hitPoints -= in_dammage;
	if (hitPoints <= 0) {
		return false;
	}
	return true;
}
