/*
 * StoppableThread.h
 *
 *  Created on: 9 janv. 2015
 *      Author: rguyard
 */

#ifndef STOPPABLETHREAD_H_
#define STOPPABLETHREAD_H_

#include "Thread.h"
#include "MutexAuto.h"

class StoppableThread: public Thread
{
public:
	StoppableThread();
	virtual ~StoppableThread();

public:
	virtual void nonBlockingRun() = 0;
	virtual void OnInit()
	{

	}

public:
	void start();
	void askForStop();
	void stop();

public:
	void run();

private:
	MutexAuto threadMutex;
	bool isRunning;
};

#endif /* STOPPABLETHREAD_H_ */
