#include "game.h"


Game::Game() {
	entities = std::vector<Entity*>();
	timeKeeper = TimeTracker();
	srand(time(NULL));
	//construct curentScript
}

Game::~Game() {
	entities.~vector();
	timeKeeper.~TimeTracker();
}

void Game::Update(float in_deltaTime) {
	//update time
	timeKeeper.update(in_deltaTime);
	//loop through vector
	for (unsigned int i = 0; i < entities.size(); i++) {

		(*entities[i]).Update(in_deltaTime);//call update (check if a bullet needs to be created)

		for (unsigned int j = 0; j < entities.size(); j++) {//loop through the rest of the array

			if ((*entities[i]).hasColidedWith((*entities[j]))) {//check weather a colision has hapened

				(*entities[i]).Collide((*entities[j]));//colide

			}

		}

		if (!(*entities[i]).IsAlive()) {//check if it is still alive

			if ((*entities[i]).type == 'P')//remove lives if needed
			{
				if (GlobalInfo::playerLives > 0) {
					entities.emplace_back(new Player());//and make a new player if there are lives to be spent
					GlobalInfo::playerLives--;
				} else {
					gamePlaying = false;
				}
			}

			entities.erase(entities.begin() + i);//remove if "dead"
			i--;//decrement to prevent skipping an entity

		}

	}

	//add enemies (currently random)
	if (rand() < ((timeKeeper.getMin() + 1) * 100)) {//decide to spawn an enemy or not
		int addType = rand() % 100;//decide what the enemie's type will be
		if (addType < 20 && timeKeeper.getOnlySecs() > 20) {// small + fase enemies

			int numSmallEnimies = rand() % 6;//decide how many to be spawned
			for (int k = 0; k < numSmallEnimies; k++) {
				//((rand() % 100) / 100) * GlobalInfo::SCREEN_MAX_X
				entities.emplace_back(new FastEnemy(((rand() % 100) / 100.f) * GlobalInfo::SCREEN_MAX_X, GlobalInfo::SCREEN_MAX_Y));
			}

		} else if (addType < 25 && timeKeeper.getOnlySecs() > 30) {//large + slow enemy

			entities.emplace_back(new BigEnemy(((rand() % 100) / 100.f) * GlobalInfo::SCREEN_MAX_X, GlobalInfo::SCREEN_MAX_Y));

		} else {//standard enemy

			entities.emplace_back(new Enemy(((rand() % 100) / 100.f) * GlobalInfo::SCREEN_MAX_X, GlobalInfo::SCREEN_MAX_Y));

		}
	}

	if (GlobalInfo::nexLifePoints >= 2000) {//check to see if a life should be given
		GlobalInfo::nexLifePoints -= 2000;
		GlobalInfo::playerLives++;
	}
}

void Game::Draw() {
	//draw background
	//\no background

	//loop through vector
	for (unsigned int i = 0; i < entities.size(); i++) {
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
	char drawL[6] = "";
	strcpy(drawL, GlobalInfo::livesToString());
	DrawString(drawL, GlobalInfo::SCREEN_MAX_X * 0.6f, GlobalInfo::SCREEN_MAX_Y * 0.06f);

	//time display
	char drawT[9] = "";
	strcpy(drawT, timeKeeper.toString());
	DrawString(drawT, GlobalInfo::SCREEN_MAX_X * 0.76f, GlobalInfo::SCREEN_MAX_Y * 0.06f);
}

int Game::Initalize() {//called before loadcontent
	GlobalInfo::playerPoints = 0;
	GlobalInfo::playerLives = 2;
	timeKeeper.reset();

	entities.emplace_back(new Player());
	return 0;
}


Score Game::Start() {
	Initalize();

	do {
		//quick exit
		if (IsKeyDown(256)) {
			gamePlaying = false;
		}

		Update(GetDeltaTime());
		Draw();

		ClearScreen();
	} while (gamePlaying && !FrameworkUpdate());

	Score score;//create a score to be read at endgame and compared to the current highscores
	score.Set(GlobalInfo::playerPoints, timeKeeper.getMin(), timeKeeper.getOnlySecs());

	return score;
}