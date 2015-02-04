/*
 * NetworkMessage.cpp
 *
 *  Created on: 29 janv. 2015
 *      Author: rguyard
 */

#include "NetworkMessage.h"

NetworkMessage::NetworkMessage(unsigned int senderId, unsigned int dataSize, boost::shared_ptr<boost::array<char, MAX_SIZE_PACKET> > data) :
		senderId(senderId), dataSize(dataSize), data(data)
{
}

NetworkMessage::~NetworkMessage()
{
}

unsigned int NetworkMessage::getSenderId()
{
	return senderId;
}

unsigned int NetworkMessage::getDataSize()
{
	return dataSize;
}
boost::shared_ptr<boost::array<char, MAX_SIZE_PACKET> > NetworkMessage::getData()
{
	return data;
}
