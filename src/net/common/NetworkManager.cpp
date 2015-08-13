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
#include <net/web/WebServer.h>

NetworkManager::NetworkManager(WebServer* webserver) :
		webserver(webserver), nbConnected(0), maxId(1)
{
	if (webserver)
	{
		webserver->start();
		std::cout << "Web server started on port " << webserver->getPort() << std::endl;
	}
}

std::string intToStr(int a)
{
	std::stringstream ss;
	ss << a;
	return (ss.str());
}

NetworkManager::~NetworkManager()
{
}

void NetworkManager::newIncommingMessage(boost::shared_ptr<NetworkMessage> message)
{
	//TODO : useful only with ASCII message
	message->getData()->at(message->getDataSize()) = '\0';
	getNetworkEventManager()->onMessage(message);
}

int NetworkManager::getNewId()
{
	mutexId.lock();
	nbConnected++;
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
	nbConnected--;
	removeIdNSV2(id);
	mutexId.unlock();
}

void NetworkManager::removeIdNSV2(unsigned int id)
{
	if (nbConnected == 0)
	{
		anusedId.clear();
		maxId = 1;
	}
	if (id + 1 == maxId)
	{
		maxId--;
	}
	else
	{
		anusedId.push_back(id);
	}
}
void NetworkManager::removeIdNS(unsigned int id)
{
	if (id + 1 == maxId)
	{
		maxId--;
		for (unsigned int i = anusedId.size() - 1; i > 0 && anusedId.size() != 0; --i)
		{
			std::cout << "i=" << i << " anusedId.size()=" << anusedId.size() << std::endl;
			if (anusedId[i] == maxId - 1)
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
	getNetworkEventManager()->onEvent(event);
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

NetworkEventManager* NetworkManager::getNetworkEventManager()
{
	return &networkEventManager;
}

std::string NetworkManager::getJSONData()
{

	mutexId.lock();
	int nbConnectedSave = nbConnected;
	mutexId.unlock();
	boost::shared_ptr<JSONObject> json(new JSONObject());

	(*json.get())[L"nb_connected"] = new JSONValue((double) nbConnectedSave);

	JSONValue value(*json.get());

	std::wstring JSONwstring = value.Stringify(false);

	std::string str(JSONwstring.begin(), JSONwstring.end());
	return str;
}
