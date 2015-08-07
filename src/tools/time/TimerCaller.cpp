/*
 * TimerCaller.cpp
 *
 *  Created on: 7 août 2015
 *      Author: rguyard
 */

#include <time/TimerCaller.h>
#include <unistd.h>
#include <iostream>

TimerCaller::TimerCaller() :
		toCall(NULL), timer(0)
{
}

TimerCaller::~TimerCaller()
{
}

void TimerCaller::callMeIn(TimerCallerCB* me, int timeMs)
{
	toCall = me;
	timer = timeMs * 1000;
	start();
}

void TimerCaller::run()
{
	usleep(timer);
	toCall->timedCall();
}
