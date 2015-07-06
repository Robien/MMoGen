/*
 * TestTCPClient.h
 *
 *  Created on: 6 juil. 2015
 *      Author: rguyard
 */

#ifndef TESTTCPCLIENT_H_
#define TESTTCPCLIENT_H_

#include <boost/asio.hpp>
#include <net/common/NetworkEvent.h>
#include <net/common/NetworkEventReceiver.h>
#include <net/common/NetworkMessage.h>

#include "net/common/NetworkManager.h"

#include "thread/Thread.h"

class TestTCPClient : public NetworkEventReceiver, public Thread
{
public:
	TestTCPClient();
	virtual ~TestTCPClient();

public:
	void onEvent(NetworkEvent event);
	void onMessageReceived(boost::shared_ptr<NetworkMessage> message);
	void run();

	NetworkManager* getManager();


private:
	NetworkManager manager;

};

#endif /* TESTTCPCLIENT_H_ */
