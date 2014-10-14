#include "AIE.h"
#include <iostream>
#include <vector>
#include <fstream>
#include "Game.h"
#include "GlobalInfo.h"
#include "Score.h"

using namespace std;

//prototypes
void closeAll();

enum GameState {
	MAIN_MENU,
	GAMEPLAY,
	SCORE_DISPLAY,
	HIGH_SCORES,
	END
};

int main( int argc, char* argv[] )
{	
	Initialise(GlobalInfo::SCREEN_MAX_X, GlobalInfo::SCREEN_MAX_Y, false, "Retro Game");
    
    SetBackgroundColour(SColour(0, 0, 0, 255));
	bool continuePlay = true;
	GameState currentState = MAIN_MENU;
	Game *game;

	Score lastScore;
	char scSt[6] = "";

	vector<Score> highScores = vector<Score>();
	for (int i = 0; i < 3; i++) {
		highScores.emplace_back(Score());
	}

	fstream hsFile;

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
	} else {
		hsFile.open("highScores.txt", ios_base::out);
		if (hsFile.is_open()) {
			for (int i = 0; i < 3; i++) {
				highScores[i].Set(0, 0, 0);
				hsFile << 0 << " ";
				hsFile << 0 << " ";
				hsFile << 0 << "\n";
			}
		} else {
			cout << "Highscore creation error";
		}
	}

    //Game Loop
    do
	{
		switch (currentState) {
		case MAIN_MENU: 
			//show menu
			DrawString("press \"Enter\" to start game", GlobalInfo::SCREEN_MAX_X * 0.02f, GlobalInfo::SCREEN_MAX_Y * 0.16f);
			DrawString("press \"h\" to view high scores", GlobalInfo::SCREEN_MAX_X * 0.02f, GlobalInfo::SCREEN_MAX_Y * 0.11f);
			DrawString("press \"e\" to end", GlobalInfo::SCREEN_MAX_X * 0.02f, GlobalInfo::SCREEN_MAX_Y * 0.06f);

			//input
			if (IsKeyDown(257)) {
				currentState = GAMEPLAY;
			}
			if (IsKeyDown('H')) {
				currentState = HIGH_SCORES;
			}
			if (IsKeyDown('E')) {
				currentState = END;
			}


			break;

		case GAMEPLAY:
			game = new Game();
			lastScore = (*game).Start(); //-> game contains it's own loop so anything beyond this is after the game loop has ended.
			//game has exited
			(*game).~Game();
			currentState = SCORE_DISPLAY;
			break;

		case SCORE_DISPLAY:
			//draw heading
			DrawString("Score:", GlobalInfo::SCREEN_MAX_X * 0.25f, GlobalInfo::SCREEN_MAX_Y * 0.90f);
			DrawString("Time:", GlobalInfo::SCREEN_MAX_X * 0.60f, GlobalInfo::SCREEN_MAX_Y * 0.90f);

			//draw score/time
			
			strcpy(scSt, lastScore.ToStringPoints());
			DrawString(scSt, GlobalInfo::SCREEN_MAX_X * 0.30f, GlobalInfo::SCREEN_MAX_Y * 0.85f);

			strcpy(scSt, lastScore.ToStringTime());
			DrawString(scSt, GlobalInfo::SCREEN_MAX_X * 0.65f, GlobalInfo::SCREEN_MAX_Y * 0.85f);

			//draw "New Highscore" if score is a highscore 

			//draw advance info
			DrawString("press \"m\" to return to menu", GlobalInfo::SCREEN_MAX_X * 0.02f, GlobalInfo::SCREEN_MAX_Y * 0.11f);
			DrawString("press \"e\" to end", GlobalInfo::SCREEN_MAX_X * 0.02f, GlobalInfo::SCREEN_MAX_Y * 0.06f);

			if (IsKeyDown('M')) {
				currentState = MAIN_MENU;
			}
			if (IsKeyDown('E')) {
				currentState = END;
			}

			break;

		case HIGH_SCORES:
			//display head
			DrawString("Score:", GlobalInfo::SCREEN_MAX_X * 0.25f, GlobalInfo::SCREEN_MAX_Y * 0.90f);
			DrawString("Time:", GlobalInfo::SCREEN_MAX_X * 0.60f, GlobalInfo::SCREEN_MAX_Y * 0.90f);

			//display scores

			///score1
			//strcpy(scSt, highScores[1].ToStringPoints());
			DrawString("0000", GlobalInfo::SCREEN_MAX_X * 0.30f, GlobalInfo::SCREEN_MAX_Y * 0.85f);
			//strcpy(scSt, highScores[1].ToStringTime());
			DrawString("0:00", GlobalInfo::SCREEN_MAX_X * 0.65f, GlobalInfo::SCREEN_MAX_Y * 0.85f);

			///score2
			//strcpy(scSt, highScores[2].ToStringPoints());
			DrawString("0000", GlobalInfo::SCREEN_MAX_X * 0.30f, GlobalInfo::SCREEN_MAX_Y * 0.80f);
			//strcpy(scSt, highScores[2].ToStringTime());
			DrawString("0:00", GlobalInfo::SCREEN_MAX_X * 0.65f, GlobalInfo::SCREEN_MAX_Y * 0.80f);

			///score3
			//strcpy(scSt, highScores[3].ToStringPoints());
			DrawString("0000", GlobalInfo::SCREEN_MAX_X * 0.30f, GlobalInfo::SCREEN_MAX_Y * 0.75f);
			//strcpy(scSt, highScores[3].ToStringTime());
			DrawString("0:00", GlobalInfo::SCREEN_MAX_X * 0.65f, GlobalInfo::SCREEN_MAX_Y * 0.75f);

			//draw advance info
			DrawString("press \"m\" to return to menu", GlobalInfo::SCREEN_MAX_X * 0.02f, GlobalInfo::SCREEN_MAX_Y * 0.11f);
			DrawString("press \"e\" to end", GlobalInfo::SCREEN_MAX_X * 0.02f, GlobalInfo::SCREEN_MAX_Y * 0.06f);

			if (IsKeyDown('M')) {
				currentState = MAIN_MENU;
			}
			if (IsKeyDown('E')) {
				currentState = END;
			}

			break;

		case END:
			continuePlay = false;
			break;

		default:
			throw "reached default case";
			continuePlay = false;
			break;

		}

		ClearScreen();

    } while(!FrameworkUpdate() && continuePlay);

	closeAll();
    Shutdown();

    return 0;
}

void closeAll() {
	//destroy evrything
	//EVRYTHING!!!
}
