#include "game.h"
#include "AIE.h"
#include <vector>
#include "Entity.h"
#include "Player.h"

Game::Game() {
	this->playerPoints = 0;
	this->playerLives = 1;
	//entities = std::vector<Entity>();
	//construct curentScript
	player = Player();
}

Game::~Game() {
	//entities.~vector();
	player.~Player();
	//destroy curentScript
}

void Game::Update(float in_deltaTime) {
	//loop through vector
	/*for (int i = 0; i < entities.size(); i++) {
		entities[i].Update(in_deltaTime);
	}*/
	player.Update(in_deltaTime);
	//scores & stuff?
}

void Game::Draw() {
	//draw background
	// debug visuals
	DrawString("I'm here", 100, 100);
	//loop through vector
	/*for (int i = 0; i < entities.size(); i++) {
		entities[i].Draw();
	}*/
	player.Draw();
}

int Game::Initalize() {
	//create player in vector, ect
	//entities.emplace_back(Player());
	return 0;
}

int Game::LoadContent() {
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