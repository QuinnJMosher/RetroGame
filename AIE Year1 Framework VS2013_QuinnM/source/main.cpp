#include "AIE.h"
#include <iostream>
#include <vector>
#include <fstream>
#include "Game.h"
#include "GlobalInfo.h"
#include "Score.h"

using namespace std;

//highscores file
const char* highScoresfileName = "highScores.txt";

//text vars
//title 
const char* gameTitle = "Space Shooter";
//genral menu text
const char* menuTextGenral0 = "press \"Enter\" to start game";
const char* menuTextGenral1 = "press \"h\" to view high scores";
const char* menuTextGenral2 = "press \"e\" to end";
const char* menuTextGenral3 = "press \"m\" to return to menu";
//score menu text
const char* menuTextScores0 = "Score:";
const char* menuTextScores1 = "Time:";
const char* menuTextScores2 = "New High Score!";
//splash text
const char* splashText0 = "Loading...";
//file error messages
const char* fErrortext0 = "Highscore creation error";
const char* fErrortext1 = "Highscore write error";

//input keys
const short startGameButton = 257;//enter key
const char exitGameButton = 'E';
const char goToHighscoresButton = 'H';
const char goToMainMenuButton = 'M';

//prototypes
void ReadyHighScores();
void MainMenu();
void StartGame();
void ScoreDisplay();
void HighScores();
void End();

bool hasScoreChecked = false;
bool newHighScore = false;

bool continuePlay = true;

Game *game;
Score lastScore;

vector<Score> highScores = vector<Score>();
fstream hsFile;

void(*CurrentFunction)() = MainMenu;

int main( int argc, char* argv[] )
{	
	Initialise(GlobalInfo::SCREEN_MAX_X, GlobalInfo::SCREEN_MAX_Y, false, gameTitle);
    
    SetBackgroundColour(SColour(0, 0, 0, 255));

	//splashscreen
	float splashtime = 1;
	do {
		ClearScreen();
		DrawString(gameTitle, GlobalInfo::SCREEN_MAX_X * 0.35f, GlobalInfo::SCREEN_MAX_Y * 0.66f);
		DrawString(splashText0, GlobalInfo::SCREEN_MAX_X * 0.4f, GlobalInfo::SCREEN_MAX_Y * 0.62f);
		splashtime -= GetDeltaTime();
	} while (!FrameworkUpdate() && splashtime > 0);

	ReadyHighScores();

    //Game Loop
    do {
		CurrentFunction();
		ClearScreen();

    } while(!FrameworkUpdate() && continuePlay);

    Shutdown();

    return 0;
}

void ReadyHighScores() {
	for (int i = 0; i < 3; i++) {
		highScores.emplace_back(Score());
	}

	hsFile.open(highScoresfileName, ios_base::in);
	if (hsFile.is_open()) {
		for (int i = 0; i < 3; i++) {
			int tempScore = 0;
			hsFile >> tempScore;

			int tempMin = 0;
			hsFile >> tempMin;

			int tempSec = 0;
			hsFile >> tempSec;

			highScores[i].Set(tempScore, tempMin, tempSec);
		}
	} else {
		hsFile.open(highScoresfileName, ios_base::out);
		if (hsFile.is_open()) {
			for (int i = 0; i < 3; i++) {
				highScores[i].Set(0, 0, 0);
				hsFile << 0 << " ";
				hsFile << 0 << " ";
				hsFile << 0 << "\n";
			}
		} else {
			cerr << fErrortext0;
		}
	}

	hsFile.sync();
	hsFile.close();
	hsFile.clear();
}

void MainMenu() {
	DrawString(gameTitle, GlobalInfo::SCREEN_MAX_X * 0.35f, GlobalInfo::SCREEN_MAX_Y * 0.66f);

	//show menu
	DrawString(menuTextGenral0, GlobalInfo::SCREEN_MAX_X * 0.02f, GlobalInfo::SCREEN_MAX_Y * 0.16f);
	DrawString(menuTextGenral1, GlobalInfo::SCREEN_MAX_X * 0.02f, GlobalInfo::SCREEN_MAX_Y * 0.11f);
	DrawString(menuTextGenral2, GlobalInfo::SCREEN_MAX_X * 0.02f, GlobalInfo::SCREEN_MAX_Y * 0.06f);

	//input
	if (IsKeyDown(startGameButton)) {
		CurrentFunction = StartGame;
	}
	if (IsKeyDown(goToHighscoresButton)) {
		CurrentFunction = HighScores;
	}
	if (IsKeyDown(exitGameButton)) {
		CurrentFunction = End;
	}

}

void StartGame() {
	hasScoreChecked = false;
	newHighScore = false;
	game = new Game();
	lastScore = (*game).Start(); //-> game contains it's own loop so anything beyond this is after the game loop has ended.
	//game has exited
	(*game).~Game();
	CurrentFunction = ScoreDisplay;
}

void ScoreDisplay() {
	char scSt[6] = "";

	//draw heading
	DrawString(menuTextScores0, GlobalInfo::SCREEN_MAX_X * 0.25f, GlobalInfo::SCREEN_MAX_Y * 0.90f);
	DrawString(menuTextScores1, GlobalInfo::SCREEN_MAX_X * 0.60f, GlobalInfo::SCREEN_MAX_Y * 0.90f);

	//draw score/time

	strcpy(scSt, lastScore.ToStringPoints());
	DrawString(scSt, GlobalInfo::SCREEN_MAX_X * 0.30f, GlobalInfo::SCREEN_MAX_Y * 0.85f);

	strcpy(scSt, lastScore.ToStringTime());
	DrawString(scSt, GlobalInfo::SCREEN_MAX_X * 0.65f, GlobalInfo::SCREEN_MAX_Y * 0.85f);

	//draw "New Highscore" if score is a highscore
	if (!hasScoreChecked) {
		for (int i = 0; i < 3; i++) {
			if (lastScore.CompareTo(highScores[i]) >= 0) {
				newHighScore = true;
				highScores.insert(highScores.begin() + i, lastScore);
				highScores.erase(highScores.begin() + 3);
				break;
			}
		}
		hasScoreChecked = true;
	}

	if (newHighScore) {
		DrawString(menuTextScores2, GlobalInfo::SCREEN_MAX_X * 0.30f, GlobalInfo::SCREEN_MAX_Y * 0.80f);
	}

	//draw advance info
	DrawString(menuTextGenral3, GlobalInfo::SCREEN_MAX_X * 0.02f, GlobalInfo::SCREEN_MAX_Y * 0.11f);
	DrawString(menuTextGenral2, GlobalInfo::SCREEN_MAX_X * 0.02f, GlobalInfo::SCREEN_MAX_Y * 0.06f);

	if (IsKeyDown(goToMainMenuButton)) {
		CurrentFunction = MainMenu;
	}
	if (IsKeyDown(exitGameButton)) {
		CurrentFunction = End;
	}
}

void HighScores() {
	char scSt[6] = "";

	//display head
	DrawString(menuTextScores0, GlobalInfo::SCREEN_MAX_X * 0.25f, GlobalInfo::SCREEN_MAX_Y * 0.90f);
	DrawString(menuTextScores1, GlobalInfo::SCREEN_MAX_X * 0.60f, GlobalInfo::SCREEN_MAX_Y * 0.90f);

	//display scores

	///score1
	strcpy(scSt, highScores[0].ToStringPoints());
	DrawString(scSt, GlobalInfo::SCREEN_MAX_X * 0.30f, GlobalInfo::SCREEN_MAX_Y * 0.85f);
	strcpy(scSt, highScores[0].ToStringTime());
	DrawString(scSt, GlobalInfo::SCREEN_MAX_X * 0.65f, GlobalInfo::SCREEN_MAX_Y * 0.85f);

	///score2
	strcpy(scSt, highScores[1].ToStringPoints());
	DrawString(scSt, GlobalInfo::SCREEN_MAX_X * 0.30f, GlobalInfo::SCREEN_MAX_Y * 0.80f);
	strcpy(scSt, highScores[1].ToStringTime());
	DrawString(scSt, GlobalInfo::SCREEN_MAX_X * 0.65f, GlobalInfo::SCREEN_MAX_Y * 0.80f);

	///score3
	strcpy(scSt, highScores[2].ToStringPoints());
	DrawString(scSt, GlobalInfo::SCREEN_MAX_X * 0.30f, GlobalInfo::SCREEN_MAX_Y * 0.75f);
	strcpy(scSt, highScores[2].ToStringTime());
	DrawString(scSt, GlobalInfo::SCREEN_MAX_X * 0.65f, GlobalInfo::SCREEN_MAX_Y * 0.75f);

	//draw advance info
	DrawString(menuTextGenral3, GlobalInfo::SCREEN_MAX_X * 0.02f, GlobalInfo::SCREEN_MAX_Y * 0.11f);
	DrawString(menuTextGenral2, GlobalInfo::SCREEN_MAX_X * 0.02f, GlobalInfo::SCREEN_MAX_Y * 0.06f);

	if (IsKeyDown(goToMainMenuButton)) {
		CurrentFunction = MainMenu;
	}
	if (IsKeyDown(exitGameButton)) {
		CurrentFunction = End;
	}

}

void End() {
	hsFile.open(highScoresfileName, ios_base::out);
	if (hsFile.is_open()) {
		for (int i = 0; i < 3; i++) {
			hsFile << highScores[i].points << " ";
			hsFile << highScores[i].min << " ";
			hsFile << highScores[i].sec << "\n";
		}
	}
	else {
		cerr << fErrortext1;
	}

	hsFile.sync();
	hsFile.close();
	hsFile.clear();

	continuePlay = false;
}