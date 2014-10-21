#include "Score.h"

char* Score::ToStringPoints() {
	if (points > 9999) {
		return "9999+";
	}
	else {
		char temp[5] = "";

		if (points < 1000) {
			strcat_s(temp, "0");

			if (points < 100) {
				strcat_s(temp, "0");

				if (points < 10) {
					strcat_s(temp, "0");
				}
			}
		}

		char pointChar[5] = "";
		_itoa_s(points, pointChar, 10);

		strcat_s(temp, pointChar);

		return temp;
	}

}

char* Score::ToStringTime() {
	if (min < 10) {
		char out[5] = "";

		char minChar[2] = "";
		_itoa_s(min, minChar, 10);
		strcat_s(out, minChar);

		strcat_s(out, ":");

		char secChar[3] = "";
		if (sec < 10) {
			strcat_s(out, "0");
		}
		_itoa_s(sec, secChar, 10);
		strcat_s(out, secChar);

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

		} else {
			return other.min - this->min;
		}

	} else {
		return this->points - other.points;
	}
}