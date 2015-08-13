/*
 * TestTCPServer.cpp
 *
 *  Created on: 6 juil. 2015
 *      Author: rguyard
 */

#include <net/common/NetworkEventManager.h>
#include <net/TestTCPServer.h>

#include "tcp/server/ServerListener.h"

TestTCPServer::TestTCPServer()
{
	manager.getNetworkEventManager()->addEventReceiver(this);
}

TestTCPServer::~TestTCPServer()
{
}

void TestTCPServer::run()
{
	boost::asio::io_service io;
	ServerListener server(io, 12345, &manager);

	server.listen();

	io.run();
}

void TestTCPServer::onMessageReceived(boost::shared_ptr<NetworkMessage> message)
{
	std::cout.write(&(*message->getData())[0], message->getDataSize());

	manager.sendMessage(NetworkMessageOut::factory(message->getSenderId(), message->getData()->c_array()));
	std::cout << std::endl;
}

void TestTCPServer::onEvent(NetworkEvent event)
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
