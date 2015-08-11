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
#include <time/Timer.h>
#include <time/TimerCaller.h>

#include "net/common/NetworkManager.h"

#include "thread/Thread.h"

class TestTCPLoginClient : public NetworkEventReceiver, public Thread, public TimerCallerCB
{
public:
	TestTCPLoginClient(std::string host, unsigned int port);
	virtual ~TestTCPLoginClient();

public:
	void onEvent(NetworkEvent& event);
	void onMessageReceived(boost::shared_ptr<NetworkMessage> message);
	void run();

private:
	void startMM();
	void sendReady();
	void sendPingMessage();
	void sendPongMessage(unsigned int id);
	void timedCall();
	void computeInGameMessage(boost::shared_ptr<NetworkMessage> message);

private:
	NetworkManager manager;
	int status;

private:
	unsigned int pingId;
	Timer timerPing;
	TimerCaller timerCaller;

private:
	std::string host;
	unsigned int port;
};

#endif /* TESTTCPLOGINCLIENT_H_ */
