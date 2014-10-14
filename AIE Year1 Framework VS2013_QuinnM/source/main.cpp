#include "AIE.h"
#include <iostream>
#include <vector>
#include <fstream>
#include "Game.h"
#include "GlobalInfo.h"
#include "Score.h"

using namespace std;

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
	Initialise(GlobalInfo::SCREEN_MAX_X, GlobalInfo::SCREEN_MAX_Y, false, "Retro Game");
    
    SetBackgroundColour(SColour(0, 0, 0, 255));

	ReadyHighScores();

    //Game Loop
    do
	{
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

	hsFile.open("highScores.txt", ios_base::in);
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
	}
	else {
		hsFile.open("highScores.txt", ios_base::out);
		if (hsFile.is_open()) {
			for (int i = 0; i < 3; i++) {
				highScores[i].Set(0, 0, 0);
				hsFile << 0 << " ";
				hsFile << 0 << " ";
				hsFile << 0 << "\n";
			}
		}
		else {
			cout << "Highscore creation error";
		}
	}

	hsFile.sync();
	hsFile.close();
	hsFile.clear();
}

void MainMenu() {
	//show menu
	DrawString("press \"Enter\" to start game", GlobalInfo::SCREEN_MAX_X * 0.02f, GlobalInfo::SCREEN_MAX_Y * 0.16f);
	DrawString("press \"h\" to view high scores", GlobalInfo::SCREEN_MAX_X * 0.02f, GlobalInfo::SCREEN_MAX_Y * 0.11f);
	DrawString("press \"e\" to end", GlobalInfo::SCREEN_MAX_X * 0.02f, GlobalInfo::SCREEN_MAX_Y * 0.06f);

	//input
	if (IsKeyDown(257)) {
		CurrentFunction = StartGame;
	}
	if (IsKeyDown('H')) {
		CurrentFunction = HighScores;
	}
	if (IsKeyDown('E')) {
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
	DrawString("Score:", GlobalInfo::SCREEN_MAX_X * 0.25f, GlobalInfo::SCREEN_MAX_Y * 0.90f);
	DrawString("Time:", GlobalInfo::SCREEN_MAX_X * 0.60f, GlobalInfo::SCREEN_MAX_Y * 0.90f);

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
		DrawString("New High Score!", GlobalInfo::SCREEN_MAX_X * 0.30f, GlobalInfo::SCREEN_MAX_Y * 0.80f);
	}

	//draw advance info
	DrawString("press \"m\" to return to menu", GlobalInfo::SCREEN_MAX_X * 0.02f, GlobalInfo::SCREEN_MAX_Y * 0.11f);
	DrawString("press \"e\" to end", GlobalInfo::SCREEN_MAX_X * 0.02f, GlobalInfo::SCREEN_MAX_Y * 0.06f);

	if (IsKeyDown('M')) {
		CurrentFunction = MainMenu;
	}
	if (IsKeyDown('E')) {
		CurrentFunction = End;
	}
}

void HighScores() {
	char scSt[6] = "";

	//display head
	DrawString("Score:", GlobalInfo::SCREEN_MAX_X * 0.25f, GlobalInfo::SCREEN_MAX_Y * 0.90f);
	DrawString("Time:", GlobalInfo::SCREEN_MAX_X * 0.60f, GlobalInfo::SCREEN_MAX_Y * 0.90f);

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
	DrawString("press \"m\" to return to menu", GlobalInfo::SCREEN_MAX_X * 0.02f, GlobalInfo::SCREEN_MAX_Y * 0.11f);
	DrawString("press \"e\" to end", GlobalInfo::SCREEN_MAX_X * 0.02f, GlobalInfo::SCREEN_MAX_Y * 0.06f);

	if (IsKeyDown('M')) {
		CurrentFunction = MainMenu;
	}
	if (IsKeyDown('E')) {
		CurrentFunction = End;
	}

}

void End() {
	hsFile.open("highScores.txt", ios_base::out);
	if (hsFile.is_open()) {
		for (int i = 0; i < 3; i++) {
			hsFile << highScores[i].points << " ";
			hsFile << highScores[i].min << " ";
			hsFile << highScores[i].sec << "\n";
		}
	}
	else {
		cout << "Highscore write error";
	}

	hsFile.sync();
	hsFile.close();
	hsFile.clear();

	continuePlay = false;
}