/*
 * DataLen.h
 *
 *  Created on: 29 déc. 2014
 *      Author: rguyard
 */

#ifndef DATALEN_H_
#define DATALEN_H_

class DataLen
{
public:
	DataLen();
	virtual ~DataLen();

public:
	void* data;
	unsigned int len;
};

#endif /* DATALEN_H_ */
