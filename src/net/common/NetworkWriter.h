/*
 * NetworkWriter.h
 *
 *  Created on: 21 août 2015
 *      Author: rguyard
 */

#ifndef NETWORKWRITER_H_
#define NETWORKWRITER_H_

#include <boost/thread.hpp>
#include <net/common/NetworkMessageOut.h>

class NetworkWriter
{
public:
	NetworkWriter();
	virtual ~NetworkWriter();
public:
	virtual void writeToNet(boost::shared_ptr<NetworkMessageOut> message) = 0;
};

#endif /* NETWORKWRITER_H_ */
