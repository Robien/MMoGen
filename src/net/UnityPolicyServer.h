/*
 * TestTCPServer.h
 *
 *  Created on: 6 juil. 2015
 *      Author: rguyard
 */

#ifndef UNITYPOLICYSERVER_H_
#define UNITYPOLICYSERVER_H_

#include <boost/asio.hpp>
#include <net/common/NetworkEvent.h>
#include <net/common/NetworkEventReceiver.h>
#include <net/common/NetworkMessage.h>

#include "net/common/NetworkManager.h"

class UnityPolicyServer : public NetworkEventReceiver
{
public:
	UnityPolicyServer();
	virtual ~UnityPolicyServer();

public:
	void onEvent(NetworkEvent& event);
	void onMessageReceived(boost::shared_ptr<NetworkMessage> message);
	void run();

private:
	NetworkManager manager;

};

#endif /* UNITYPOLICYSERVER_H_ */
