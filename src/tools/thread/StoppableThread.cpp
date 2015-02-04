/*
 * StoppableThread.cpp
 *
 *  Created on: 9 janv. 2015
 *      Author: rguyard
 */

#include "StoppableThread.h"

StoppableThread::StoppableThread()
{
	isRunning = false;
}

StoppableThread::~StoppableThread()
{
	stop();
}

void StoppableThread::start()
{
	threadMutex.lock();
	isRunning = true;
	OnInit();
	Thread::start();
}
void StoppableThread::askForStop()
{
	isRunning = false;
}
void StoppableThread::stop()
{
	isRunning = false;
	threadMutex.lock();
	threadMutex.unlock();
}

void StoppableThread::run()
{
	do
	{
		nonBlockingRun();
	} while (isRunning);
	threadMutex.unlock();
}
