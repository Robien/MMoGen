/*
 * BufferToFd.h
 *
 *  Created on: 13 janv. 2015
 *      Author: rguyard
 */

#ifndef BUFFERTOFD_H_
#define BUFFERTOFD_H_

#include <stdlib.h>
#include "thread/Thread.h"

#include "macro.h"

#include "DataLen.h"
#include "SynchonizedBuffer.h"

//copy a element from a SynchonizedBuffer to pipe
//it's useful to re-sample data.
class BufferToFd: public Thread
{
public:
	BufferToFd(SynchronizedBuffer<DataLen>* buff) :
			buff(buff)
	{
		if (pipe(pipes) == -1)
		{
		}
		else
		{
			start();
		}
	}
	virtual ~BufferToFd()
	{
	}

public:
	int getFd()
	{
		return pipes[0];
	}

public:
	void run()
	{
		for (;;)
		{
			DataLen data = buff->get();

			int ret = write(pipes[1], data.data, data.len);
			free(data.data);
			if (ret == -1 || (unsigned int) ret != data.len)
			{
				break;
			}
		}
	}

private:
	SynchronizedBuffer<DataLen>* buff;
	int pipes[2];
};

#endif /* BUFFERTOFD_H_ */
