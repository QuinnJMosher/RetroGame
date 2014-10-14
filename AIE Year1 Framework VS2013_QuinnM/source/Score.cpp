#include "Score.h"

char* Score::ToStringPoints() {
	if (points > 9999) {
		return "9999+";
	}
	else {
		char temp[5] = "";

		if (points < 1000) {
			strcat(temp, "0");

			if (points < 100) {
				strcat(temp, "0");

				if (points < 10) {
					strcat(temp, "0");
				}
			}
		}

		char pointChar[5] = "";
		itoa(points, pointChar, 10);

		strcat(temp, pointChar);

		return temp;
	}

}

char* Score::ToStringTime() {
	if (min < 10) {
		char out[5] = "";

		char minChar[2] = "";
		itoa(min, minChar, 10);
		strcat(out, minChar);

		strcat(out, ":");

		char secChar[3] = "";
		if (sec < 10) {
			strcat(out, "0");
		}
		itoa(sec, secChar, 10);
		strcat(out, secChar);

		return out;
	}
	else {
		return "9:59+";
	}
}

void Score::Set(int in_points, int in_min, int in_sec) {
	this->points = in_points;
	this->min = in_min;
	this->sec = in_sec;
}

int Score::CompareTo(Score other) {
	if (this->points == other.points) {

		if (this->min == other.min) {

			return other.sec - this->sec;

		}
		else {
			return other.min - this->min;
		}

	}
	else {
		return this->points - other.points;
	}
}