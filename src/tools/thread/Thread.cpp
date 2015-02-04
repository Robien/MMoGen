// Copyright 2014 Google Inc. All Rights Reserved.

#include "Thread.h"
#include <iostream>

void* Thread::callback(void* arg)
{
	Thread* thread = (Thread*) arg;
	thread->run();
	return NULL;
}

Thread::~Thread()
{
	if (mRunning)
	{
//		AAPLOGW("Thread %lx went out of scope while running!", (unsigned long ) mThread);
	}
}

bool Thread::start()
{
	int ret = pthread_create(&mThread, NULL, callback, this);
	mRunning = (ret == 0);
	return mRunning;
}

bool Thread::join()
{
	if (!mRunning)
	{
		return false;
	}
	int ret = pthread_join(mThread, NULL);
	if (ret == 0)
	{
		mRunning = false;
		return true;
	}
	return false;
}

unsigned long Thread::id()
{
	return (unsigned long) mThread;
}

void Thread::yield()
{
	sched_yield();
}

bool Thread::setPriority(int priority)
{
	struct sched_param params;
	params.sched_priority = priority;
	int ret = pthread_setschedparam(mThread, SCHED_FIFO, &params);
	return ret == 0;
}
bool Thread::setRealTimePriority()
{
	struct sched_param params;
	params.sched_priority = sched_get_priority_max(SCHED_FIFO);
	int ret = pthread_setschedparam(mThread, SCHED_FIFO, &params);
	return ret == 0;
}
bool Thread::setName(const char* name)
{
	if (pthread_setname_np(mThread, name) == 0)
	{
		return true;
	}
	else
	{
		std::cout << "#################### SetName Error : " << name << std::endl;
		return false;
	}
}

void Thread::cancel()
{
	pthread_cancel(mThread);
}
