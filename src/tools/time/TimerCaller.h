/*
 * TimerCaller.h
 *
 *  Created on: 7 août 2015
 *      Author: rguyard
 */

#ifndef TIMERCALLER_H_
#define TIMERCALLER_H_

#include "thread/Thread.h"

class TimerCallerCB
{
public:
	TimerCallerCB()
	{
	}
	virtual ~TimerCallerCB()
	{
	}
public:
	virtual void timedCall() = 0;
};

class TimerCaller: public Thread
{
public:
	TimerCaller();
	virtual ~TimerCaller();

public:
	void callMeIn(TimerCallerCB* me, int timeMs);

public:
	void run();

private:
	TimerCallerCB* toCall;
	int timer;

};

#endif /* TIMERCALLER_H_ */
