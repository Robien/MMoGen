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
	//TODO : useful only with ASCII message
	message->getData()->at(message->getDataSize()) = '\0';
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
		for (unsigned int i = anusedId.size() - 1; i > 0 && anusedId.size() != 0; --i)
		{
			std::cout << "i=" << i << " anusedId.size()=" << anusedId.size() << std::endl;
			if (anusedId[i] == maxId)
			{
				anusedId[i] = anusedId[anusedId.size() - 1];
				anusedId.pop_back();
				maxId--;
				if (anusedId.size() != 0)
				{
					i = anusedId.size() - 1;
				}
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
	mutexId.lock();
	idMap[id] = buff;
	mutexId.unlock();
	NetworkEvent event(NetworkEvent::CONNECTION);
	event.id = id;
	NetworkEventManager::get()->onEvent(event);
}
void NetworkManager::removeBuffer(unsigned int id)
{
	mutexId.lock();
	idMap.erase(id);
	mutexId.unlock();
}
void NetworkManager::sendMessage(boost::shared_ptr<NetworkMessageOut> message)
{
	mutexId.lock();
	if (message.get() == NULL)
	{
		std::cerr << "ERROR NULL" << std::endl;
	}
	std::map<unsigned int, boost::shared_ptr<SynchronizedBuffer<boost::shared_ptr<NetworkMessageOut> > > >::const_iterator buf = idMap.find(
			message->getReceiverId());
	mutexId.unlock();
	if (buf != idMap.end())
	{
		buf->second->add(message);
	}
	else
	{
		std::cerr << "message can't be send : remote client disconnected" << std::endl;
	}
}
