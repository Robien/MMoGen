#ifndef UTIL_THREAD_H
#define UTIL_THREAD_H

#include <boost/thread.hpp>
#include <sched.h>

#define USE_PTHREAD true

class Thread
{
public:
	Thread();
	virtual ~Thread();
	/**
	 * Call this method to start running the thread.
	 */
	bool start();
	/**
	 * Call this method to wait for the thread represented by this object to terminate.
	 * You are responsible for actually making the thread shutdown somehow.
	 */
	bool join();
	/**
	 * Yield the cpu to any other runnable threads.
	 */
	void yield();
	//try to cancel a thread
	bool cancel();
	/**
	 * Set the thread priority.
	 * @param priority The priority value to set. You should check the range of priority values
	 *        that your system supports.
	 * @return True on success, false otherwise.
	 */
	bool setPriority(int priority);
	/**
	 * Set the thread priority to real time.
	 * @return True on success, false otherwise.
	 */
	bool setRealTimePriority();
	/**
	 * Set the name of the thread.
	 * @param name The name of this thread.
	 * @return True on success, false otherwise.
	 */
	bool setName(const char* name);
protected:
	static void* callback(void* arg);
	virtual void run() = 0;
private:
	boost::thread thread;
	bool mRunning;
};

#endif // UTIL_THREAD_H
