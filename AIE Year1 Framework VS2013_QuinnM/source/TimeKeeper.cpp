#include "TimeKeeper.h"
#include <cstring>
#include <cstdlib>

TimeKeeper::TimeKeeper() {
	this->miliseconds = 0.0f;
	this->seconds = 0;
	this->minutes = 0;
}

TimeKeeper::TimeKeeper(unsigned int in_startMin, unsigned int in_startSec, float in_startMili) {
	this->miliseconds = in_startMili;
	while (miliseconds > 0) {
		miliseconds /= 10;
	}
	this->seconds = in_startSec;
	this->minutes = in_startMin;
}

TimeKeeper::~TimeKeeper() { }

void TimeKeeper::update(float in_deltaTime) {
	miliseconds += in_deltaTime;
	
	while (miliseconds > 0) {
		miliseconds--;
		seconds++;
	}

	while (seconds > 60) {
		seconds -= 60;
		minutes++;
	}
}

char* TimeKeeper::toString() {

	if (minutes < 10) {
		char out[8] = "T: ";

		char minChar[2] = "";
		itoa(minutes, minChar, 10);
		strcat(out, minChar);

		strcat(out, ":");

		char secChar[3] = "";
		itoa(seconds, secChar, 10);
		strcat(out, secChar);

		return out;
	} else {
		return "T: 9:99+";
	}
}

int TimeKeeper::getTotalSecs() {
	return ((minutes * 60) + seconds);
}

int TimeKeeper::getOnlySecs() {
	return seconds;
}

int TimeKeeper::getMin() {
	return minutes;
}

void TimeKeeper::setTime(unsigned int in_newMin, unsigned int in_newSec) {
	this->seconds = in_newSec;
	this->minutes = in_newMin;
}

void TimeKeeper::setTime(unsigned int in_newMin, unsigned int in_newSec, float in_newMili) {
	this->miliseconds = in_newMili;
	while (miliseconds > 0) {
		miliseconds /= 10;
	}
	this->seconds = in_newSec;
	this->minutes = in_newMin;
}

void TimeKeeper::reset() {
	this->miliseconds = 0.0f;
	this->seconds = 0;
	this->minutes = 0;
}