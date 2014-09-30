#include "game.h"
#include "AIE.h"

Game::Game() {
	this->playerPoints = 0;
	this->playerLives = 1;
	//construct entities
	//construct curentScript
}

Game::~Game() {
	//destroy entities
	//destroy curentScript
}

void Game::Update(float in_deltaTime) {
	//loop through vector
	//call colide?
	//scores & stuff?
}

void Game::Draw() {
	// debug visuals
	DrawString("I'm here", 100, 100);
	//loop through vector
	//draw background
}

int Game::Initalize() {
	//create player in vector, ect
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