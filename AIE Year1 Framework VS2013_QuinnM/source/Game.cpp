#include "game.h"
#include "GlobalInfo.h"
#include "AIE.h"
#include <vector>
#include <time.h>
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

Game::Game() {
	entities = std::vector<Entity*>();
	srand(time(NULL));
	//construct curentScript
}

Game::~Game() {
	entities.~vector();
	//destroy curentScript
}

void Game::Update(float in_deltaTime) {
	//loop through vector
	for (int i = 0; i < entities.size(); i++) {

		bool addBullet = (*entities[i]).Update(in_deltaTime);//call update (check if a bullet needs to be created)

		for (int j = i + 1; j < entities.size(); j++) {//loop through the rest of the array

			if ((*entities[i]).hasColidedWith((*entities[j]))) {//check weather a colision has hapened

				(*entities[i]).Collide((*entities[j]));//colide

			}

		}

		if (!(*entities[i]).IsAlive()) {//check if it is still alive

			switch ((*entities[i]).type)//add points
			{
			case 'P':
				gamePlaying = false;
				break;
			case 'E':
				GlobalInfo::playerPoints += 10;
				break;
			case 'B':
				//no points
				break;
			default:
				break;
			}

			entities.erase(entities.begin() + i);//remove if "dead"
			i--;//decrement to prevent skipping an entity

		}

		if (addBullet) {//add a bullet if needed
			entities.emplace_back(new Bullet((*entities[i]).position.x, (*entities[i]).position.y, (*entities[i]).bullletSpeedX, (*entities[i]).bullletSpeedY, (*entities[i]).bullletDammage, (*entities[i]).OwnerId));
		}
	}
	//add enemies (currently random)
	if (rand() < 10) {
		entities.emplace_back(new Enemy(rand() % GlobalInfo::SCREEN_MAX_X, GlobalInfo::SCREEN_MAX_Y));
	}
	//scores & stuff?
}

void Game::Draw() {
	//draw background
	//loop through vector
	for (int i = 0; i < entities.size(); i++) {
		(*entities[i]).Draw();
	}

	//draw displays
	DrawString("display", GlobalInfo::SCREEN_MAX_X * 0.01f, GlobalInfo::SCREEN_MAX_Y * 0.06f);
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