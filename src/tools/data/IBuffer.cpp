/*
 * IBuffer.cpp
 *
 *  Created on: 21 janv. 2015
 *      Author: rguyard
 */

#include "IBuffer.h"

IBuffer::IBuffer()
{
}

IBuffer::~IBuffer()
{
}

float IBuffer::getLoadLevel()
{
	return (float) getSize() / (float) getMaxSize();
}
int IBuffer::getPercentLoadLevel()
{
	return getLoadLevel()*100;
}
