#include "FastEnemy.h"

const char* FastEnemy::FAST_ENEMY_TEXTURE_PATH = "./images/invaders/invaders_6_00.png";
const float FastEnemy::FAST_ENEMY_WIDTH = 20;
const float FastEnemy::FAST_ENEMY_HEIGHT = 20;
const float FastEnemy::FAST_ENEMY_X_SPEED = 0;
const float FastEnemy::FAST_ENEMY_Y_SPEED = -350;
const int FastEnemy::FAST_ENEMY_HIT_POINTS = 4;
const int FastEnemy::FAST_ENEMY_POINT_VALUE = 5;

FastEnemy::FastEnemy(float in_x, float in_y) : Enemy(in_x, in_y, FAST_ENEMY_WIDTH, FAST_ENEMY_HEIGHT, FAST_ENEMY_TEXTURE_PATH, FAST_ENEMY_X_SPEED, FAST_ENEMY_Y_SPEED, FAST_ENEMY_HIT_POINTS, FAST_ENEMY_POINT_VALUE) {

}

FastEnemy::~FastEnemy() { }