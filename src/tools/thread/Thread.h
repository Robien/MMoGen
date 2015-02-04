// Copyright 2014 Google Inc. All Rights Reserved.

#ifndef ANDROID_AUTO_PROJECTION_PROTOCOL_CORE_UTIL_THREAD_H
#define ANDROID_AUTO_PROJECTION_PROTOCOL_CORE_UTIL_THREAD_H

#include <pthread.h>
#include <sched.h>

/**
 * A class that wraps a thread. Extend this class to create threads. The default
 * implementation uses pthreads, you must customize this to work on your platform.
 */
class Thread {
public:
    Thread() : mThread(0), mRunning(false) { }
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
     * Return an identifier for this thread.
     */
    unsigned long id();
    /**
     * Yield the cpu to any other runnable threads.
     */
    void yield();
    //try to cancel a thread
    void cancel();
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
    /**
     * @internal
     * The actual method sent to pthreads to run. This calls the overloaded run
     * method internally. The this pointer is sent across while calling pthread_create
     * so we can differentiate objects.
     * @param arg The address of the thread object that needs to be run.
     */
    static void* callback(void* arg);
    /**
     * Override this method with your actual thread function. The idea is that since
     * you have to extend this class, you can add any necessary methods to set up the
     * state that your threads need.
     */
    virtual void run() = 0;
private:
    pthread_t mThread;
    bool mRunning;
};

#endif // ANDROID_AUTO_PROJECTION_PROTOCOL_CORE_UTIL_THREAD_H
