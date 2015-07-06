/*
 * NetworkManager.cpp
 *
 *  Created on: 29 janv. 2015
 *      Author: rguyard
 */

#include <net/common/NetworkEvent.h>
#include <net/common/NetworkEventManager.h>
#include <net/common/NetworkMessageOut.h>
#include "NetworkManager.h"

NetworkManager::NetworkManager(bool isServer) :
		isServer(isServer), maxId(1)
{
}

NetworkManager::~NetworkManager()
{
}
void NetworkManager::newIncommingMessage(boost::shared_ptr<NetworkMessage> message)
{
//	std::cout << "YOO" << std::endl;
// 	std::cout.write(&(*message->getData())[0], message->getDataSize());
//	std::cout << std::endl;

	message->getData()->at(message->getDataSize())= '\0';

	NetworkEventManager::get()->onMessage(message);

}
int NetworkManager::getNewId()
{
	mutexId.lock();
	if (anusedId.size() > 0)
	{
		unsigned int res = anusedId[anusedId.size() - 1];
		anusedId.pop_back();
		mutexId.unlock();
		return res;
	}
	else
	{
		mutexId.unlock();
		return maxId++;
	}
}

void NetworkManager::removeId(unsigned int id)
{
	mutexId.lock();
	removeIdNS(id);
	mutexId.unlock();
}
void NetworkManager::removeIdNS(unsigned int id)
{
	if (id + 1 == maxId)
	{
		maxId--;
		for (unsigned int i = anusedId.size() - 1; i >= 0; ++i)
		{
			if (anusedId[i] == maxId)
			{
				anusedId[i] = anusedId[anusedId.size() - 1];
				anusedId.pop_back();
				maxId--;
				i = anusedId.size() - 1;
			}
		}
	}
	else
	{
		anusedId.push_back(id);
	}
}

void NetworkManager::reportNewBuffer(unsigned int id, boost::shared_ptr<SynchronizedBuffer<boost::shared_ptr<NetworkMessageOut> > > buff)
{
	idMap[id] = buff;
	NetworkEvent event(NetworkEvent::CONNECTION);
	event.id = id;
	NetworkEventManager::get()->onEvent(event);
}

void NetworkManager::sendMessage(boost::shared_ptr<NetworkMessageOut> message)
{
	if (message.get() == NULL)
	{
		std::cout << "ERROR NULL" << std::endl;
	}
	idMap[message->getReceiverId()]->add(message);
}
