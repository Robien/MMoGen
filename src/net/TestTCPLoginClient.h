/*
 * TestTCPLoginClient.h
 *
 *  Created on: 13 juil. 2015
 *      Author: rguyard
 */

#ifndef TESTTCPLOGINCLIENT_H_
#define TESTTCPLOGINCLIENT_H_

#include <boost/asio.hpp>
#include <net/common/NetworkEvent.h>
#include <net/common/NetworkEventReceiver.h>
#include <net/common/NetworkMessage.h>

#include "net/common/NetworkManager.h"

#include "thread/Thread.h"

class TestTCPLoginClient : public NetworkEventReceiver, public Thread
{
public:
	TestTCPLoginClient();
	virtual ~TestTCPLoginClient();

public:
	void onEvent(NetworkEvent event);
	void onMessageReceived(boost::shared_ptr<NetworkMessage> message);
	void run();

private:
	void startMM();
	void sendReady();

private:
	NetworkManager manager;
	int status;
};

#endif /* TESTTCPLOGINCLIENT_H_ */
