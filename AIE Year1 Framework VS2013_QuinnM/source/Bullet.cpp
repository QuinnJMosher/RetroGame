#include "Bullet.h"
#include "GlobalInfo.h"
#include "Enemy.h"
#include "Player.h"
#include "AIE.h"

const char* Bullet::BULLET_TEXTURE_PATH = "./images/invaders/invaders_7_01.png";
const float Bullet::BULLET_WIDTH = 20;
const float Bullet:: BULLET_HEIGHT = 20;
const char Bullet::BULLET_TYPE_TAG = 'B';

Bullet::Bullet(float in_x, float in_y, float in_velocityX, float in_velocityY, int in_damage, int in_owner) : Entity(in_x, in_y, BULLET_WIDTH, BULLET_HEIGHT, BULLET_TEXTURE_PATH, BULLET_TYPE_TAG, in_owner) {
	this->xVelocity = in_velocityX;
	this->yVelocity = in_velocityY;
	this->damageValue = in_damage;
	this->hasHit = false;
}

Bullet::Bullet(float in_x, float in_y, int in_owner) : Entity(in_x, in_y, BULLET_WIDTH, BULLET_HEIGHT, BULLET_TEXTURE_PATH, BULLET_TYPE_TAG, in_owner) {
	this->xVelocity = 0;
	this->yVelocity = 200;
	this->damageValue = 5;
	this->hasHit = false;
}

Bullet::Bullet(float in_x, float in_y) : Entity(in_x, in_y, BULLET_WIDTH, BULLET_HEIGHT, BULLET_TEXTURE_PATH, BULLET_TYPE_TAG) {
	this->xVelocity = 0;
	this->yVelocity = 200;
	this->damageValue = 5;
	this->hasHit = false;
}

Bullet::~Bullet() { }

bool Bullet::IsAlive() {
	if (!hasHit) {//hasent hit something
		if (((position.x > 0 && position.x < GlobalInfo::SCREEN_MAX_X)// and is on screen
			&& (position.y > 0 && position.y < GlobalInfo::SCREEN_MAX_Y))) {
			return true;
		}
	}
	return false;
}

void Bullet::Collide(Entity &other) {
		Enemy *enemyPtr = NULL;
		Player *playerPtr = NULL;
		switch (other.type) {

		case 'P'://player

			if (!this->CheckHasHit()) {
				this->Hit();

				playerPtr = dynamic_cast<Player*>(&other);
				if (playerPtr != NULL) {
					(*playerPtr).TakeDamage(damageValue);
				}
			}

			break;

		case 'E'://Enemy

			if (!this->CheckHasHit()) {
				this->Hit();

				enemyPtr = dynamic_cast<Enemy*>(&other);
				if (enemyPtr != NULL) {
					(*enemyPtr).TakeDamage(damageValue);
				}
			}

			break;
		case 'B'://bullet
			//ignore it
			break;
		default:
			break;
		}
}

bool Bullet::CheckHasHit() {
	return hasHit;
}

void Bullet::Hit() {
	hasHit = true;
}

bool Bullet::Update(float in_deltaTime) {
	position.x += (xVelocity * in_deltaTime);
	position.y += (yVelocity * in_deltaTime);

	MoveSprite(spriteID, position.x, position.y);
	return false;
}

void Bullet::Draw() {
	DrawSprite(spriteID);
}