/*
 * TestTCPServer.h
 *
 *  Created on: 6 juil. 2015
 *      Author: rguyard
 */

#ifndef TESTTCPSERVER_H_
#define TESTTCPSERVER_H_

#include <boost/asio.hpp>
#include <net/common/NetworkEvent.h>
#include <net/common/NetworkEventReceiver.h>
#include <net/common/NetworkMessage.h>

#include "net/common/NetworkManager.h"

class TestTCPServer : public NetworkEventReceiver
{
public:
	TestTCPServer();
	virtual ~TestTCPServer();

public:
	void onEvent(NetworkEvent event);
	void onMessageReceived(boost::shared_ptr<NetworkMessage> message);
	void run();

private:
	NetworkManager manager;

};

#endif /* TESTTCPSERVER_H_ */
