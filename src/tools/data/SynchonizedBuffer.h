/*
 * SynchonizedBuffer.h
 *
 *  Created on: 15 déc. 2014
 *      Author: rguyard
 */

#ifndef SYNCHONIZEDBUFFER_H_
#define SYNCHONIZEDBUFFER_H_

#include <iostream>

#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <queue>

#include "data/IBuffer.h"

template<typename T>
class SynchronizedBuffer: public IBuffer
{
public:
	SynchronizedBuffer(int maxSize = 1024) :
			maxSize(maxSize)
	{
		sem_init(&mutex, 0, 1);
		sem_init(&negativeSizeBlocker, 0, 0);
		sem_init(&maxSizeBlocker, 0, maxSize);
	}
	virtual ~SynchronizedBuffer()
	{
	}

	virtual void add(T value)
	{
		sem_wait(&maxSizeBlocker);
		sem_wait(&mutex);
		queue.push(value);
		sem_post(&mutex);
		sem_post(&negativeSizeBlocker);
	}

	virtual T get()
	{
		sem_wait(&negativeSizeBlocker);
		sem_wait(&mutex);
		T res = queue.front();
		queue.pop();
		sem_post(&mutex);
		sem_post(&maxSizeBlocker);
		return res;
	}

	virtual size_t getSize()
	{
		return queue.size();
	}
	virtual size_t getMaxSize()
	{
		return maxSize;
	}

private:

	sem_t mutex;
	sem_t negativeSizeBlocker;
	sem_t maxSizeBlocker;
	std::queue<T> queue;

	unsigned int maxSize;

};

#endif /* SYNCHONIZEDBUFFER_H_ */
