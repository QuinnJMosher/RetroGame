#include "TimeContainer.h"
#include <cstring>
#include <cstdlib>

TimeContainer::TimeContainer() {
	this->miliseconds = 0.0f;
	this->seconds = 0;
	this->minutes = 0;
}

TimeContainer::TimeContainer(unsigned int in_startMin, unsigned int in_startSec, float in_startMili) {
	this->miliseconds = in_startMili;
	while (miliseconds > 0) {
		miliseconds /= 10;
	}
	this->seconds = in_startSec;
	this->minutes = in_startMin;
}

TimeContainer::~TimeContainer() { }

void TimeContainer::update(float in_deltaTime) {
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

char* TimeContainer::toString() {

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

int TimeContainer::getTotalSecs() {
	return ((minutes * 60) + seconds);
}

int TimeContainer::getOnlySecs() {
	return seconds;
}

int TimeContainer::getMin() {
	return minutes;
}

void TimeContainer::setTime(unsigned int in_newMin, unsigned int in_newSec) {
	this->seconds = in_newSec;
	this->minutes = in_newMin;
}

void TimeContainer::setTime(unsigned int in_newMin, unsigned int in_newSec, float in_newMili) {
	this->miliseconds = in_newMili;
	while (miliseconds > 0) {
		miliseconds /= 10;
	}
	this->seconds = in_newSec;
	this->minutes = in_newMin;
}

void TimeContainer::reset() {
	this->miliseconds = 0.0f;
	this->seconds = 0;
	this->minutes = 0;
}