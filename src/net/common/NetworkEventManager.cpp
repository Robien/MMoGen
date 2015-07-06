/*
 * NetworkEventManager.cpp
 *
 *  Created on: 30 janv. 2015
 *      Author: rguyard
 */

#include <net/common/NetworkEventManager.h>

NetworkEventManager::~NetworkEventManager()
{
}

void NetworkEventManager::addEventReceiver(NetworkEventReceiver* receiver)
{
	receivers.push_back(receiver);
}

void NetworkEventManager::onEvent(NetworkEvent event)
{
	for (std::vector<NetworkEventReceiver*>::const_iterator itt = receivers.begin(); itt != receivers.end(); itt++)
	{
		(*itt)->onEvent(event);
	}
}

void NetworkEventManager::onMessage(boost::shared_ptr<NetworkMessage> message)
{
	for (std::vector<NetworkEventReceiver*>::const_iterator itt = receivers.begin(); itt != receivers.end(); itt++)
	{
		(*itt)->onMessageReceived(message);
	}
}
