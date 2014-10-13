#ifndef _TimeContainer_h_
#define _TimeContainer_h_

class TimeContainer {
public:
	TimeContainer();
	TimeContainer(unsigned int in_startMin, unsigned int in_startSec, float in_startMili);
	~TimeContainer();

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