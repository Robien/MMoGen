/*
 * IBuffer.h
 *
 *  Created on: 21 janv. 2015
 *      Author: rguyard
 */

#ifndef IBUFFER_H_
#define IBUFFER_H_

#include <stdlib.h>

class IBuffer
{
public:
	IBuffer();
	virtual ~IBuffer();

public:
	float getLoadLevel();
	int getPercentLoadLevel();

public:
	virtual size_t getSize() = 0;
	virtual size_t getMaxSize() = 0;
};

#endif /* IBUFFER_H_ */
