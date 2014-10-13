#include "GlobalInfo.h"
#include "Entity.h"
#include <vector>

const int GlobalInfo::SCREEN_MAX_X = 600;
const int GlobalInfo::SCREEN_MAX_Y = 700;

unsigned int GlobalInfo::globalPlayerHealth = 0;
unsigned int GlobalInfo::playerPoints = 0;
unsigned int GlobalInfo::playerLives = 3;

char* GlobalInfo::pointsToString() {
	char out[14] = "Points: ";

	if (playerPoints < 1000) {
		strcat(out, "0");
		if (playerPoints < 100) {
			strcat(out, "0");
			if (playerPoints < 10) {
				strcat(out, "0");
			}
		}
	}

	char pointsChar[6] = "";
	if (playerPoints > 9999) {
		strcpy(pointsChar, "9999+");
	} else {
		itoa(playerPoints, pointsChar, 10);
	}

	strcat(out, pointsChar);
	
	return out;
}

char* GlobalInfo::healthToString() {
	char out[9] = "HP: ";

		if (globalPlayerHealth < 100) {
			strcat(out, "0");
			if (globalPlayerHealth < 10) {
				strcat(out, "0");
			}
		}

	char healthChar[5] = "";
	if (globalPlayerHealth > 999) {
		strcpy(healthChar, "999+");
	} else {
		itoa(globalPlayerHealth, healthChar, 10);
	}

	strcat(out, healthChar);

	return out;
}

char* GlobalInfo::livesToString() {
	char out[6] = "L: ";

	char livesChar[3] = "";
	if (playerLives > 9) {
		strcpy(livesChar, "9+");
	}
	else {
		itoa(playerLives, livesChar, 10);
	}

	strcat(out, livesChar);

	return out;
}