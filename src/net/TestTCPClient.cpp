/*
 * TestTCPClient.cpp
 *
 *  Created on: 6 juil. 2015
 *      Author: rguyard
 */

#include <net/common/NetworkEventManager.h>
#include <net/TestTCPClient.h>

#include "tcp/client/ClientConnectAndPrint.h"

TestTCPClient::TestTCPClient()
{
	NetworkEventManager::get()->addEventReceiver(this);
}

TestTCPClient::~TestTCPClient()
{
}

void TestTCPClient::run()
{
	boost::asio::io_service io;
	ClientConnectAndPrint client(io, "127.0.0.1", 12345, &manager);

	client.connect();

	io.run();
}

void TestTCPClient::onMessageReceived(boost::shared_ptr<NetworkMessage> message)
{
	std::cout << "YOO client : " << message->getSenderId() << std::endl;
//	std::cout.write(&(*message->getData())[0], message->getDataSize());
//
//	manager.sendMessage(NetworkMessageOut::factory(message->getSenderId(), message->getData()->c_array()));
//	std::cout << std::endl;
}

void TestTCPClient::onEvent(NetworkEvent event)
{
	switch (event.typeEvent)
	{
	case NetworkEvent::CONNECTION:
		std::cout << "CONNECTION id :" << event.id << std::endl;
		break;
	case NetworkEvent::DISCONECTION:
		std::cout << "DISCONECTION id :" << event.id << std::endl;
		break;
	default:
		std::cout << "Unhandled id :" << event.id << std::endl;
		break;
	}
}

NetworkManager* TestTCPClient::getManager()
{
	return &manager;
}
