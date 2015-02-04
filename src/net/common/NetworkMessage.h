/*
 * NetworkMessage.h
 *
 *  Created on: 29 janv. 2015
 *      Author: rguyard
 */

#ifndef NETWORKMESSAGE_H_
#define NETWORKMESSAGE_H_

#include <boost/asio.hpp>

#include "networkConf.h"

class NetworkMessage
{
public:
	NetworkMessage(unsigned int senderId, unsigned int dataSize, boost::shared_ptr<boost::array<char, MAX_SIZE_PACKET> > data);
	virtual ~NetworkMessage();

public:
	unsigned int getSenderId();
	unsigned int getDataSize();
	boost::shared_ptr<boost::array<char, MAX_SIZE_PACKET> > getData();

private:
	unsigned int senderId;
	unsigned int dataSize;
	boost::shared_ptr<boost::array<char, MAX_SIZE_PACKET> > data;

};

#endif /* NETWORKMESSAGE_H_ */
