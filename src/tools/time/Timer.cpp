/*
 * Timer.cpp
 *
 *  Created on: 7 août 2015
 *      Author: rguyard
 */

#include <time/Timer.h>
#include <iostream>

Timer::Timer() :
		timer(0)
{

}

Timer::~Timer()
{
}

void Timer::start()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	timer = tv.tv_sec * 1000000 + tv.tv_usec;
}

float Timer::getValueinSecond()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	time_t currTime = tv.tv_sec * 1000000 + tv.tv_usec;
	return ((float) (currTime - timer) / 1000000);
}
int Timer::getValueinMilliSecond()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	time_t currTime = tv.tv_sec * 1000000 + tv.tv_usec;
	return (int) (((float) (currTime - timer) / 1000));
}

