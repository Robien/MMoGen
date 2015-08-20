/*
 * Singleton.h
 *
 *  Created on: 8 janv. 2015
 *      Author: rguyard
 */

#ifndef SINGLETON_H_
#define SINGLETON_H_

#include <semaphore.h>
#include <thread/MutexAuto.h>

template<typename T>
class Singleton
{
protected:
	Singleton()
	{

	}
	virtual void onInit()
	{
	}
public:
	virtual ~Singleton()
	{
		if (instance != 0x0)
		{
			delete instance;
		}
	}

public:
	static T* get()
	{
		if (instance == 0x0)
		{
			mutex.lock();
			if (instance == 0x0)
			{
				instance = new T();
				static_cast<Singleton*>(instance)->onInit();
			}
			mutex.unlock();
		}
		return instance;
	}

private:
	static T* instance;
	static MutexAuto mutex;
};
template<typename T>
T* Singleton<T>::instance = 0x0;
template<typename T>
MutexAuto Singleton<T>::mutex;

#endif /* SINGLETON_H_ */
