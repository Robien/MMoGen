/*
 * NetworkEventManager.h
 *
 *  Created on: 30 janv. 2015
 *      Author: rguyard
 */

#ifndef NETWORKEVENTMANAGER_H_
#define NETWORKEVENTMANAGER_H_

#include <net/common/NetworkEventReceiver.h>
#include <net/common/NetworkMessage.h>
#include <shared_ptr.h>
#include <vector>

#include "Singleton.h"

class NetworkEventManager: public Singleton<NetworkEventManager>
{
public:
	virtual ~NetworkEventManager();

public:
	void addEventReceiver(NetworkEventReceiver* receiver);

public:
	void onEvent(NetworkEvent event);
	void onMessage(boost::shared_ptr<NetworkMessage> message);

private:
	std::vector<NetworkEventReceiver*> receivers;
};

#endif /* NETWORKEVENTMANAGER_H_ */
