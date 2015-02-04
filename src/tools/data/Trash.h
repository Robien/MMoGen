/*
 * Trash.h
 *
 *  Created on: 5 janv. 2015
 *      Author: rguyard
 */

#ifndef TRASH_H_
#define TRASH_H_

#include <unistd.h>

#include "thread/Thread.h"
#include "SynchonizedBuffer.h"

#include <iostream>

template<typename T>
class Trash: public Thread, public SynchronizedBuffer<T>
{
public:
	Trash()
	{
		Thread::start();
	}
	virtual ~Trash()
	{
	}

public:
	void run()
	{
		setName("trash");
		for (;;)
		{
			if (SynchronizedBuffer<T>::getSize() > 300)
			{
				SynchronizedBuffer<T>::get();
			}
			else
			{
				usleep(100000);
			}
		}
	}
};

#endif /* TRASH_H_ */
