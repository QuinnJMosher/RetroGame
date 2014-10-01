#include "Player.h"
#include "AIE.h"

Player::Player() : Entity(PLAYER_START_X,PLAYER_START_Y, PLAYER_WIDTH, PLAYER_HEIGHT, TEXTURE_PATH) {
	this->inputKeyUp = 'W';
	this->inputKeyDown = 'S';
	this->inputKeyLeft = 'A';
	this->inputKeyRight = 'D';
	this->inputKeyFire = ' ';

	this->xVelocity = 0.f;
	this->yVelocity = 0.f;

	this->xSpeed = 100.f;
	this->ySpeed = 100.f;

	this->maxHitPoints = 100;
	this->hitPoints = 100;

	this->bullletDammage = 10;

	this->immunityTime = 0.f;
	this->firePauseTime = 0.f;
}

Player::~Player() { }

void Player::Update(float in_deltaTime)  {//override

	Move(in_deltaTime);

	//check if dammage needs to be taken (or restored)
	if (immunityTime > 0) {//immunity time will prevent the player from being killed almost instantly from a single player
		immunityTime -= in_deltaTime;
	}
	else {
		Collide();
	}

	if (firePauseTime > 0) {//prevent player from fireing a constant stream of bullets
		firePauseTime -= in_deltaTime;
	} else {
		if (IsKeyDown(inputKeyFire)) {
			//add a bullet to the entity list in front of player (create an emitter point?)
			firePauseTime = FIRE_INTERVAL;
		}
	}
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
	else if (position.x > 900/*screen max width*/ - (width / 2)) {
		position.x = 900/*screen max width*/ - (width / 2);
	}

	if (position.y < 0 + (height / 2)) {
		position.y = height / 2;
	}
	else if (position.y > 600/*screen max height*/ - (height / 2)) {
		position.y = 600/*screen max height*/ - (height / 2);
	}

	//end movement
	MoveSprite(spriteID, position.x, position.y);
}

void Player::Collide() {
	//collide stuff here (implement in Entity? <-nope!)
	if (/*colided with a stuff*/ false) {
		this->TakeDammage(/*make a const somewhere containing colide dammage*/20);
		//dammage only happens per frame but immunity is by time
		//^if framerate is low then dammage could be taken evry other frame
	}
}

void Player::Draw() {//Override
	DrawSprite(spriteID);
}

bool Player::IsAlive() {
	if (hitPoints > 0) {
		return true;
	}
	return false;
}

bool Player::TakeDammage(unsigned int in_dammage) {
	maxHitPoints -= in_dammage;
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