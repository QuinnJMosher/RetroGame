#include <cstring>
#include <cstdlib>

#ifndef _TimeTracker_h_
#define _TimeTracker_h_

class TimeTracker {
public:
	TimeTracker();
	TimeTracker(unsigned int in_startMin, unsigned int in_startSec, float in_startMili);
	~TimeTracker();

	void update(float in_deltaTime);

	char* toString();
	int getTotalSecs();
	int getOnlySecs();
	int getMin();

	void setTime(unsigned int in_newMin, unsigned int in_newSec);
	void setTime(unsigned int in_newMin, unsigned int in_newSec, float in_newMili);
	void reset();

private:
	float miliseconds;
	unsigned int seconds;
	unsigned int minutes;

};

#endif