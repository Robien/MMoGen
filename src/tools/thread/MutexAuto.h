/*
 * MutexAuto.h
 *
 *  Created on: 9 janv. 2015
 *      Author: rguyard
 */

#ifndef MUTEXAUTO_H_
#define MUTEXAUTO_H_

#include <semaphore.h>

class MutexAuto
{

public:
	MutexAuto()
	{
		sem_init(&mutex, 0, 1);
	}
	virtual ~MutexAuto()
	{
//		sem_post(&mutex);
	}

	void lock()
	{
		sem_wait(&mutex);
	}
	void unlock()
	{
		sem_post(&mutex);
	}

	operator sem_t()
	{
		return mutex;
	}
	operator sem_t*()
	{
		return &mutex;
	}

private:
	sem_t mutex;
};

#endif /* MUTEXAUTO_H_ */
