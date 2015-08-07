/*
 * Timer.h
 *
 *  Created on: 7 août 2015
 *      Author: rguyard
 */

#ifndef TIMER_H_
#define TIMER_H_

#include <sys/time.h>

class Timer
{
public:
	Timer();
	virtual ~Timer();

public:
	void start();
	float getValueinSecond();
	int getValueinMilliSecond();

private:
	time_t timer;
};

#endif /* TIMER_H_ */
