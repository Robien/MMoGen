/*
 * NetworkEventReceiver.h
 *
 *  Created on: 30 janv. 2015
 *      Author: rguyard
 */

#ifndef NETWORKEVENTRECEIVER_H_
#define NETWORKEVENTRECEIVER_H_

#include <net/common/NetworkEvent.h>
#include <net/common/NetworkMessage.h>
#include <shared_ptr.h>

class NetworkEventReceiver
{
public:
	NetworkEventReceiver();
	virtual ~NetworkEventReceiver();

public:
	virtual void onEvent(NetworkEvent& event) = 0;
	virtual void onMessageReceived(boost::shared_ptr<NetworkMessage> message) = 0;
};

#endif /* NETWORKEVENTRECEIVER_H_ */
