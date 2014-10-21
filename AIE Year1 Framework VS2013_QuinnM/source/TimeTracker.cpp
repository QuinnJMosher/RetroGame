#include "TimeTracker.h"

TimeTracker::TimeTracker() {
	this->miliseconds = 0.0f;
	this->seconds = 0;
	this->minutes = 0;
}

TimeTracker::TimeTracker(unsigned int in_startMin, unsigned int in_startSec, float in_startMili) {
	this->miliseconds = in_startMili;
	while (miliseconds > 0) {
		miliseconds /= 10;
	}
	this->seconds = in_startSec;
	this->minutes = in_startMin;
}

TimeTracker::~TimeTracker() { }

void TimeTracker::update(float in_deltaTime) {
	miliseconds += in_deltaTime;

	while (miliseconds > 0) {
		miliseconds--;
		seconds++;
	}

	while (seconds >= 60) {
		seconds -= 60;
		minutes++;
	}
}

char* TimeTracker::toString() {

	if (minutes < 10) {
		char out[8] = "T: ";

		char minChar[2] = "";
		_itoa(minutes, minChar, 10);
		strcat(out, minChar);

		strcat(out, ":");

		char secChar[3] = "";
		if (seconds < 10) {
			strcat(out, "0");
		}
		_itoa(seconds, secChar, 10);
		strcat(out, secChar);

		return out;
	} else {
		return "T: 9:59+";
	}
}

int TimeTracker::getTotalSecs() {
	return ((minutes * 60) + seconds);
}

int TimeTracker::getOnlySecs() {
	return seconds;
}

int TimeTracker::getMin() {
	return minutes;
}

void TimeTracker::setTime(unsigned int in_newMin, unsigned int in_newSec) {
	this->seconds = in_newSec;
	this->minutes = in_newMin;
}

void TimeTracker::setTime(unsigned int in_newMin, unsigned int in_newSec, float in_newMili) {
	this->miliseconds = in_newMili;
	while (miliseconds > 0) {
		miliseconds /= 10;
	}
	this->seconds = in_newSec;
	this->minutes = in_newMin;
}

void TimeTracker::reset() {
	this->miliseconds = 0.0f;
	this->seconds = 0;
	this->minutes = 0;
}