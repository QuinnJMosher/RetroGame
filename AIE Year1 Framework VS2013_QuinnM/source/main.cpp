#include "AIE.h"
#include <iostream>

//constant vars
static int SCREEN_MAX_X = 900, SCREEN_MAX_Y = 600;

struct Player {
	unsigned int spriteID;

	unsigned int score;
	unsigned int hitPoints;

	float posX;
	float posY;

	float velX;
	float velY;

};

struct Point {
	float x, y;
};

struct Rectangle {
	Point a, b;
	SColour color;

	float getWidth() {
		return abs(a.x - b.x);
	}

	float getHeight() {
		return abs(a.y - b.y);
	}

	void draw() {
		int tempSprite = CreateSprite("./images/crate_sideup.png", getHeight(), getWidth(), true, color);
		MoveSprite(tempSprite, b.x - a.x, b.y - a.y);
		DrawSprite(tempSprite);
		DestroySprite(tempSprite);
	}

};

int main( int argc, char* argv[] )
{	
	Initialise(SCREEN_MAX_X, SCREEN_MAX_Y, false, "My Awesome Game");
    
    SetBackgroundColour(SColour(0, 0, 0, 255));

	Rectangle rect;
	rect.a.x = 5;
	rect.a.y = 10;
	rect.b.x = 200;
	rect.b.y = 200;
	rect.color = SColour(255, 0, 0, 255);

    //Game Loop
    do
	{
		rect.draw();
        ClearScreen();

    } while(!FrameworkUpdate());

    Shutdown();

    return 0;
}
