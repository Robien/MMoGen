/*
 * TestTcp.cpp
 *
 *  Created on: 28 janv. 2015
 *      Author: rguyard
 */

#include "TestTcp.h"

#include <boost/asio.hpp>
#include <net/common/NetworkEventManager.h>
#include <net/common/NetworkMessage.h>
#include <net/common/NetworkMessageOut.h>
#include <vector>

TestTcp::TestTcp()
{
	NetworkEventManager::get()->addEventReceiver(this);
}

TestTcp::~TestTcp()
{
}

void TestTcp::run()
{

	boost::asio::io_service io;
	ServerListener server(io, 12345, &manager);
	ClientConnectAndPrint client(io, "127.0.0.1", 12345, &manager);
//	ClientConnectAndPrint client2(io, "127.0.0.1", 12345, &manager);

	server.listen();
	client.connect();
//	client2.connect();

	io.run();
}

void TestTcp::onEvent(NetworkEvent event)
{
	switch (event.typeEvent)
	{
	case NetworkEvent::CONNECTION:
		std::cout << "CONNECTION id :" << event.id << std::endl;
		if (event.id == 0)
		{
			manager.sendMessage(NetworkMessageOut::factory(event.id, "salut !"));
		}
		else
		{
			manager.sendMessage(NetworkMessageOut::factory(event.id, "Hey !"));
		}
		break;
	case NetworkEvent::DISCONECTION:
		std::cout << "DISCONECTION id :" << event.id << std::endl;
		break;
	default:
		std::cout << "Unhandled id :" << event.id << std::endl;
		break;
	}
}
