#include "BigEnemy.h"

const char* BigEnemy::BIG_ENEMY_TEXTURE_PATH = "./images/invaders/invaders_1_01.png";
const float BigEnemy::BIG_ENEMY_WIDTH = 100;
const float BigEnemy::BIG_ENEMY_HEIGHT = 100;
const float BigEnemy::BIG_ENEMY_X_SPEED = 0;
const float BigEnemy::BIG_ENEMY_Y_SPEED = -60;
const int BigEnemy::BIG_ENEMY_HIT_POINTS = 140;
const int BigEnemy::BIG_ENEMY_POINT_VALUE = 30;

BigEnemy::BigEnemy(float in_x, float in_y) : Enemy(in_x, in_y, BIG_ENEMY_WIDTH, BIG_ENEMY_HEIGHT, BIG_ENEMY_TEXTURE_PATH, BIG_ENEMY_X_SPEED, BIG_ENEMY_Y_SPEED, BIG_ENEMY_HIT_POINTS, BIG_ENEMY_POINT_VALUE) {

}

BigEnemy::~BigEnemy() { }