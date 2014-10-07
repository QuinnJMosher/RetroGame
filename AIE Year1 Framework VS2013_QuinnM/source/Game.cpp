#include "game.h"
#include "GlobalInfo.h"
#include "AIE.h"
#include <vector>
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"

Game::Game() {
	entities = std::vector<Entity*>();
	//construct curentScript
}

Game::~Game() {
	entities.~vector();
	//destroy curentScript
}

void Game::Update(float in_deltaTime) {
	//loop through vector
	for (int i = 0; i < entities.size(); i++) {

		(*entities[i]).Update(in_deltaTime);//call update

		for (int j = i + 1; j < entities.size(); j++) {

			if ((*entities[i]).hasColidedWith((*entities[j]))) {

				(*entities[i]).Collide((*entities[j]));

			}

		}

		if (!(*entities[i]).IsAlive()) {//check if it is still alive

			entities.erase(entities.begin() + i);//remove if "dead"
			i--;//decrement to prevent skipping an entity

		}
	}
	//scores & stuff?
}

void Game::Draw() {
	//draw background
	//loop through vector
	for (int i = 0; i < entities.size(); i++) {
		(*entities[i]).Draw();
	}
}

int Game::Initalize() {//called before loadcontent
	//create player in vector, ect
	GlobalInfo::playerPoints = 0;
	GlobalInfo::playerLives = 3;

	entities.emplace_back(new Player());
	entities.emplace_back(new Enemy(GlobalInfo::SCREEN_MAX_X * 0.33, GlobalInfo::SCREEN_MAX_Y));
	entities.emplace_back(new Enemy(GlobalInfo::SCREEN_MAX_X * 0.66, GlobalInfo::SCREEN_MAX_Y - 50));
	entities.emplace_back(new Enemy(GlobalInfo::SCREEN_MAX_X * 1, GlobalInfo::SCREEN_MAX_Y - 100));
	return 0;
}

int Game::LoadContent() {//called before start
	//open enemyscript, create sprites
	return 0;
}

void Game::Start() {
	Initalize();
	LoadContent();

	do {
		//debug inputs
		if (IsKeyDown('M')) {
			gamePlaying = false;
		}

		Update(GetDeltaTime());
		Draw();

		ClearScreen();
	} while (gamePlaying && !FrameworkUpdate());
}