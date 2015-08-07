/*
 * NetworkMessageOut.cpp
 *
 *  Created on: 30 janv. 2015
 *      Author: rguyard
 */

#include <net/common/NetworkMessageOut.h>

NetworkMessageOut::NetworkMessageOut(unsigned int receiverId, boost::shared_ptr<std::string> data) :
		receiver(receiverId), data(data), raw(false)
{
}

NetworkMessageOut::~NetworkMessageOut()
{
}

boost::shared_ptr<std::string> NetworkMessageOut::getData()
{
	return data;
}
boost::shared_ptr<std::vector<char> > NetworkMessageOut::getVectorData()
{
	boost::shared_ptr<std::vector<char> > res(new std::vector<char>(data->begin(), data->end()));
	return res;
}
unsigned int NetworkMessageOut::getReceiverId()
{
	return receiver;
}
boost::shared_ptr<NetworkMessageOut> NetworkMessageOut::factory(unsigned int receiverId, std::string data)
{
	boost::shared_ptr<std::string> dataS(new std::string(data));
	boost::shared_ptr<NetworkMessageOut> m(new NetworkMessageOut(receiverId, dataS));
	return m;
}
boost::shared_ptr<NetworkMessageOut> NetworkMessageOut::factory(boost::shared_ptr<NetworkMessage> messageIn)
{
	boost::shared_ptr<std::string> dataS(new std::string(messageIn->getData()->begin(), messageIn->getData()->begin() + messageIn->getDataSize()));
	boost::shared_ptr<NetworkMessageOut> m(new NetworkMessageOut(messageIn->getSenderId(), dataS));
	return m;
}
boost::shared_ptr<NetworkMessageOut> NetworkMessageOut::factory(boost::shared_ptr<NetworkMessage> messageIn, unsigned int receiverId)
{
	boost::shared_ptr<std::string> dataS(new std::string(messageIn->getData()->begin(), messageIn->getData()->begin() + messageIn->getDataSize()));
	boost::shared_ptr<NetworkMessageOut> m(new NetworkMessageOut(receiverId, dataS));
	return m;
}
void NetworkMessageOut::setRaw()
{
	raw = true;
}
bool NetworkMessageOut::isRaw()
{
	return raw;
}

