#include "Enemy.h"
#include "GlobalInfo.h"
#include "Player.h"
#include "Bullet.h"
#include "AIE.h"

//Enemy constants
const char* Enemy::ENEMY_TEXTURE_PATH = "./images/invaders/invaders_1_00.png";
const float Enemy::ENEMY_WIDTH = 40;
const float Enemy::ENEMY_HEIGHT = 40;
const char Enemy::ENEMY_TYPE_TAG = 'E';

Enemy::Enemy(float in_x, float in_y) : Entity(in_x, in_y, ENEMY_WIDTH, ENEMY_HEIGHT, ENEMY_TEXTURE_PATH, ENEMY_TYPE_TAG) {
	this->xVelocity = 0;
	this->yVelocity = 0;
	this->xSpeed = 0;
	this->ySpeed = -100;

	this->hitPoints = 25;
	this->pointValue = 10;
}

Enemy::Enemy(float in_x, float in_y, float in_width, float in_height, const char* in_txPath, float in_xSpeed, float in_ySpeed, int in_hp, int in_ptValue) : Entity(in_x, in_y, in_width, in_height,  in_txPath, ENEMY_TYPE_TAG) {
	this->xVelocity = 0;
	this->yVelocity = 0;
	this->xSpeed = in_xSpeed;
	this->ySpeed = in_ySpeed;

	this->hitPoints = in_hp;
	this->pointValue = in_ptValue;
}

Enemy::~Enemy() { }

bool Enemy::Update(float in_deltaTime) {//override
	Move(in_deltaTime);
	return false;
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
	if (in_dammage > hitPoints) {
		hitPoints = 0;
	} else {
		hitPoints -= in_dammage;
	}
	if (hitPoints <= 0) {
		return false;
	}
	return true;
}

void Enemy::Collide(Entity &other) {//override
	//we already know we hit somthing if this is called
	Player *playerPtr = NULL;
	Bullet *bulletPtr = NULL;
	switch (other.type) {

	case 'P'://player
		//ignore it (prevents taking double damage) 
		break;

	case 'E'://Enemy
		//ignore it
		break;

	case 'B'://bullet

		if (this->OwnerId != other.OwnerId) {
			bulletPtr = dynamic_cast<Bullet*>(&other);

			if (bulletPtr != NULL) {
				if (!(*bulletPtr).CheckHasHit()) {
					this->TakeDamage((*bulletPtr).damageValue);
					(*bulletPtr).Hit();
				}

			}
		}

		break;
	default:
		break;
	}

}