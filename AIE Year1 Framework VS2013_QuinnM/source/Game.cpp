#include "game.h"
#include "GlobalInfo.h"
#include "AIE.h"
#include <vector>
#include <time.h>
#include "Entity.h"
#include "Player.h"
#include "Enemy.h"
#include "BigEnemy.h"
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

			switch ((*entities[i]).type)//add points/remove lives
			{
			case 'P'://consider changing to an if statement
				if (GlobalInfo::playerLives > 0) {
					entities.emplace_back(new Player());
					GlobalInfo::playerLives--;
				} else {
					gamePlaying = false;
				}
				break;
			case 'E':
				//points applied in Isalive Meathod
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

		if (i > 0) {
			if (addBullet) {//add a bullet if needed
				entities.emplace_back(new Bullet((*entities[i]).position.x, (*entities[i]).position.y, (*entities[i]).bullletSpeedX, (*entities[i]).bullletSpeedY, (*entities[i]).bullletDammage, (*entities[i]).OwnerId));
			}
		}
	}

	//add enemies (currently random)
	if (rand() < 100) {
		int addType = rand() % 100;
		if (addType < 10) {
			entities.emplace_back(new BigEnemy(rand() % GlobalInfo::SCREEN_MAX_X, GlobalInfo::SCREEN_MAX_Y));
		} else {
			entities.emplace_back(new Enemy(rand() % GlobalInfo::SCREEN_MAX_X, GlobalInfo::SCREEN_MAX_Y));
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

	//draw displays
	//point display
	char drawP[14] = "";
	strcpy(drawP, GlobalInfo::pointsToString());
	DrawString(drawP, GlobalInfo::SCREEN_MAX_X * 0.01f, GlobalInfo::SCREEN_MAX_Y * 0.06f);

	//health display
	char drawH[9] = "";
	strcpy(drawH, GlobalInfo::healthToString());
	DrawString(drawH, GlobalInfo::SCREEN_MAX_X * 0.35f, GlobalInfo::SCREEN_MAX_Y * 0.06f);

	//life display
	char drawL[6] = "L: ";
	strcpy(drawL, GlobalInfo::livesToString());
	DrawString(drawL, GlobalInfo::SCREEN_MAX_X * 0.6f, GlobalInfo::SCREEN_MAX_Y * 0.06f);
}

int Game::Initalize() {//called before loadcontent
	//create player in vector, ect
	GlobalInfo::playerPoints = 0;
	GlobalInfo::playerLives = 2;

	entities.emplace_back(new Player());
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