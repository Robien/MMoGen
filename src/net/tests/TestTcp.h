/*
 * TestTcp.h
 *
 *  Created on: 28 janv. 2015
 *      Author: rguyard
 */

#ifndef TESTTCP_H_
#define TESTTCP_H_

#include <boost/asio.hpp>
#include <net/common/NetworkEventReceiver.h>
#include "tcp/server/ServerListener.h"
#include "tcp/client/ClientConnectAndPrint.h"

class TestTcp : public NetworkEventReceiver
{
public:
	TestTcp();
	virtual ~TestTcp();

public:
	void run();
public:
	void onEvent(NetworkEvent event);
	void onMessageReceived(boost::shared_ptr<NetworkMessage> message);

private:
	NetworkManager manager;
};

#endif /* TESTTCP_H_ */
