#include "AIE.h"
#include <iostream>
#include "Game.h"

//prototypes
void closeAll();

//constant vars
static int SCREEN_MAX_X = 900, SCREEN_MAX_Y = 600;

enum GameState {
	MAIN_MENU,
	GAMEPLAY,
	END
};

int main( int argc, char* argv[] )
{	
	Initialise(SCREEN_MAX_X, SCREEN_MAX_Y, false, "Retro Game");
    
    SetBackgroundColour(SColour(0, 0, 0, 255));

	bool continuePlay = true;
	GameState currentState = MAIN_MENU;
	Game game;

    //Game Loop
    do
	{
		switch (currentState) {
		case MAIN_MENU: 
			//show menu
			DrawString("press \"s\" to start", 20, 100);
			DrawString("press \"e\" to end", 20, 50);

			//input
			if (IsKeyDown('S')) {
				currentState = GAMEPLAY;
			}
			if (IsKeyDown('E')) {
				currentState = END;
			}

			ClearScreen();
			break;

		case GAMEPLAY:
			game = Game();
			game.Start(); //-> game will contain it's own loop so anything beyond this is after the game loop has ended.
			//game has exited
			game.~Game();
			currentState = MAIN_MENU;
			break;

		case END:
			continuePlay = false;
			break;

		default:
			continuePlay = false;
			break;

		}

    } while(!FrameworkUpdate() && continuePlay);

	closeAll();
    Shutdown();

    return 0;
}

void closeAll() {
	//destroy evrything
}
