#include "Player.h"
#include "Enemy.h"

const char* Player::PLAYER_TEXTURE_PATH = "./images/invaders/invaders_4_00.png";
const float Player::PLAYER_WIDTH = 40.f;
const float Player::PLAYER_HEIGHT = 40.f;
const float Player::PLAYER_START_X = GlobalInfo::SCREEN_MAX_X / 2.f;
const float Player::PLAYER_START_Y = GlobalInfo::SCREEN_MAX_Y * 0.1f;
const char Player::PLAYER_TYPE_TAG = 'P';

Player::Player() : Entity(PLAYER_START_X, PLAYER_START_Y, PLAYER_WIDTH, PLAYER_HEIGHT, PLAYER_TEXTURE_PATH, PLAYER_TYPE_TAG) {
	this->inputKeyUp = 'W';
	this->inputKeyDown = 'S';
	this->inputKeyLeft = 'A';
	this->inputKeyRight = 'D';
	this->inputKeyFire = ' ';

	this->xVelocity = 0.f;
	this->yVelocity = 0.f;

	this->xSpeed = 400.f;
	this->ySpeed = 200.f;

	this->maxHitPoints = 100;
	this->hitPoints = 100;

	this->bullletDammage = 4;
	this->bullletSpeedX = 0;
	this->bullletSpeedY = 900;

	this->immunityTime = 1.25f;
	this->firePauseTime = 1.25f;

	bullets = std::vector<Bullet*>();
}

Player::~Player() { 
	bullets.~vector();
}

bool Player::Update(float in_deltaTime)  {//override

	Move(in_deltaTime);

	//check if dammage needs to be taken (or restored)
	if (immunityTime > 0) {//immunity time will prevent the player from being killed almost instantly from a single player
		immunityTime -= in_deltaTime;
	}

	if (firePauseTime > 0) {//prevent player from fireing a constant stream of bullets
		firePauseTime -= in_deltaTime;
	} else {
		if (IsKeyDown(inputKeyFire)) {
			//Fire();//add a bullet to the entity list in front of player (create an emitter point?)
			firePauseTime = FIRE_INTERVAL;
			Fire();
			//return true;
		}
	}

	for (int i = 0; i < bullets.size(); i++) {
		if ((*bullets[i]).IsAlive()) {
			(*bullets[i]).Update(in_deltaTime);
		} else {
			bullets.erase(bullets.begin() + i);
		}
	}

	GlobalInfo::globalPlayerHealth = this->hitPoints;

	return false;
}

void Player::Move(float in_deltaTime) {

	//apply constant movement
	position.x += xVelocity * in_deltaTime;
	position.y += yVelocity * in_deltaTime;

	//apply player's inputed movement
	if (IsKeyDown(inputKeyUp)) {
		position.y += ySpeed * in_deltaTime;
	}
	if (IsKeyDown(inputKeyDown)) {
		position.y -= ySpeed * in_deltaTime;
	}
	if (IsKeyDown(inputKeyRight)) {
		position.x += xSpeed * in_deltaTime;
	}
	if (IsKeyDown(inputKeyLeft)) {
		position.x -= xSpeed * in_deltaTime;
	}

	//check boundries
	if (position.x < 0 + (width / 2)) {
		position.x = width / 2;
	}
	else if (position.x > GlobalInfo::SCREEN_MAX_X - (width / 2)) {
		position.x = GlobalInfo::SCREEN_MAX_X - (width / 2);
	}

	if (position.y < 0 + (height / 2)) {
		position.y = height / 2;
	}
	else if (position.y > GlobalInfo::SCREEN_MAX_Y - (height / 2)) {
		position.y = GlobalInfo::SCREEN_MAX_Y - (height / 2);
	}

	//end movement
	MoveSprite(spriteID, position.x, position.y);
}

void Player::Fire() {
	bullets.emplace_back(new Bullet(position.x, position.y,0,600,bullletDammage, OwnerId));
}

void Player::Collide(Entity &other) {//override
	//we already know we hit somthing if this is called
	if (immunityTime <= 0) {
		Enemy *enemyPtr = NULL;
		Bullet *bulletPtr = NULL;
		switch (other.type) {

		case 'P'://player
			//ignore it
			break;

		case 'E'://Enemy

			this->TakeDamage(20);

			enemyPtr = dynamic_cast<Enemy*>(&other);
			if (enemyPtr != NULL) {
				(*enemyPtr).TakeDamage(20);
			}

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
}

void Player::Draw() {//Override
	for (int i = 0; i < bullets.size(); i++) {
		(*bullets[i]).Draw();
	}

	DrawSprite(spriteID);
}

bool Player::IsAlive() {//Override
	if (hitPoints > 0) {
		return true;
	}
	return false;
}

bool Player::TakeDamage(unsigned int in_dammage) {
	immunityTime += IMUNITY_INTERVAL;
	if (in_dammage > hitPoints) {
		hitPoints = 0;
	} else {
		hitPoints -= in_dammage;
	}
	return IsAlive();
}

void Player::RestoreHealth(unsigned int in_healing) {
	if (in_healing + hitPoints > maxHitPoints) {
		hitPoints = maxHitPoints;
	} else {
		hitPoints += in_healing;
	}
}

int Player::GetHitPoints() {
	return hitPoints;
}

void Player::ChangeVelocity(float in_xVelocity, float in_yVelocity) {
	xVelocity = in_xVelocity;
	yVelocity = in_yVelocity;
}

void Player::ChangeSpeed(float in_xSpeed, float in_ySpeed) {
	xSpeed = in_xSpeed;
	ySpeed = in_ySpeed;
}

Player& Player::operator=(Player other) {
	inputKeyUp = other.inputKeyUp;
	inputKeyDown = other.inputKeyDown;
	inputKeyLeft = other.inputKeyLeft;
	inputKeyRight = other.inputKeyRight;
	inputKeyFire = other.inputKeyFire;

	xVelocity = other.xVelocity;
	yVelocity = other.xVelocity;

	xSpeed = xSpeed;
	ySpeed = ySpeed;

	maxHitPoints = other.maxHitPoints;
	hitPoints = other.hitPoints;

	bullletDammage = other.bullletDammage;

	immunityTime = other.immunityTime;
	firePauseTime = other.firePauseTime;

	position = other.position;
	width = other.width;
	height = other.height;
	spriteID = other.spriteID;
	return other;
}

bool Player::hasColidedWith(Entity &other) {
	for (int i = 0; i < bullets.size(); i++) {
		if ((*bullets[i]).hasColidedWith(other)) {//check weather any bullet has colided
			(*bullets[i]).Collide(other);//colide
		}
	}

	return this->Entity::hasColidedWith(other);
}