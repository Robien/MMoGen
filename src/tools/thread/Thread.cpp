#include "Thread.h"
#include <iostream>

Thread::Thread() :
		mRunning(false)
{
}

Thread::~Thread()
{
}

bool Thread::start()
{
	thread = boost::thread(&Thread::run, this);
	mRunning = true;
	return mRunning;
}

bool Thread::join()
{
	if (!mRunning)
	{
		return false;
	}
	thread.join();
	mRunning = false;
	return true;
}

void Thread::yield()
{
	boost::thread::yield();
}

bool Thread::setPriority(int priority)
{
	bool ret = false;
#if USE_PTHREAD
	boost::thread_attributes attr;

	struct sched_param params;
	params.sched_priority = priority;
	ret = (pthread_setschedparam(thread.native_handle(), SCHED_FIFO, &params) == 0);
#endif
	return ret;
}
bool Thread::setRealTimePriority()
{
	bool ret = false;
#if USE_PTHREAD
	struct sched_param params;
	params.sched_priority = sched_get_priority_max(SCHED_FIFO);
	ret = (pthread_setschedparam(thread.native_handle(), SCHED_FIFO, &params) == 0);
#endif
	return ret;
}
bool Thread::setName(const char* name)
{
	bool ret = false;
#if USE_PTHREAD
	ret = (pthread_setname_np(thread.native_handle(), name) == 0);
#endif
	return ret;
}

bool Thread::cancel()
{
#if USE_PTHREAD
	pthread_cancel (thread.native_handle());
	return true;
#endif
	return false;
}
