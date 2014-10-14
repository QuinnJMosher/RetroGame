#ifndef _Score_h_
#define _Score_h_

struct  Score {
	int points;
	int min;
	int sec;

	char* ToStringPoints();
	char* ToStringTime();

	void Set(int in_points, int in_min, int in_sec);
	int CompareTo(Score other);
};

#endif