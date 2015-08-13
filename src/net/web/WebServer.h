/*
 * TestTCPServer.h
 *
 *  Created on: 6 juil. 2015
 *      Author: rguyard
 */

#ifndef WebServer_H_
#define WebServer_H_

#include <iostream>

#include <boost/asio.hpp>
#include <net/common/NetworkEvent.h>
#include <net/common/NetworkEventReceiver.h>
#include <net/common/NetworkMessage.h>

#include "net/common/NetworkManager.h"

#include "thread/Thread.h"

class WebServer : public NetworkEventReceiver, public Thread
{
public:
	WebServer(NetworkManager* gameManager, unsigned int port);
	virtual ~WebServer();

public:
	unsigned int getPort();

public:
	void onEvent(NetworkEvent& event);
	void onMessageReceived(boost::shared_ptr<NetworkMessage> message);
	void run();

private:
	unsigned int port;
	NetworkManager manager;
	NetworkManager* gameManager;

};

#endif /* WebServer_H_ */
