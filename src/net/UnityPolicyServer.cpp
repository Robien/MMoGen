/*
 * TestTCPServer.cpp
 *
 *  Created on: 6 juil. 2015
 *      Author: rguyard
 */

#include <net/common/NetworkEventManager.h>
#include <net/UnityPolicyServer.h>

#include "tcp/server/ServerListener.h"

UnityPolicyServer::UnityPolicyServer()
{
	NetworkEventManager::get()->addEventReceiver(this);
}

UnityPolicyServer::~UnityPolicyServer()
{
}

void UnityPolicyServer::run()
{
	boost::asio::io_service io;
	ServerListener server(io, 843, &manager);

	server.listen();

	io.run();
}

void UnityPolicyServer::onMessageReceived(boost::shared_ptr<NetworkMessage> message)
{
	std::cout.write(&(*message->getData())[0], message->getDataSize());

	std::cout << std::endl;

	std::string m = "<?xml version=\"1.0\"?>\n";
	m += "<cross-domain-policy>\n";
	m += "<allow-access-from domain=\"*\" to-ports=\"4242-4242\"/>\n";
	m += "</cross-domain-policy>\n";
	boost::shared_ptr<NetworkMessageOut> messageOut = NetworkMessageOut::factory(message->getSenderId(), m);
	messageOut->setRaw();
	manager.sendMessage(messageOut);

}

void UnityPolicyServer::onEvent(NetworkEvent& event)
{

	std::string message = "<?xml version=\"1.0\"?>\n";
	message += "<cross-domain-policy>\n";
	message += "<allow-access-from domain=\"*\" to-ports=\"4242-4242\"/>\n";
	message += "</cross-domain-policy>\n";

	boost::shared_ptr<NetworkMessageOut> messageOut;

	switch (event.typeEvent)
	{
	case NetworkEvent::CONNECTION:
		std::cout << "CONNECTION id :" << event.id << std::endl;
		std::cout << "send message : " << std::endl << message << std::endl;
		messageOut = NetworkMessageOut::factory(event.id, message);
		messageOut->setRaw();
		manager.sendMessage(messageOut);
		break;
	case NetworkEvent::DISCONECTION:
		std::cout << "DISCONECTION id :" << event.id << std::endl;
		break;
	default:
		std::cout << "Unhandled id :" << event.id << std::endl;
		break;
	}
}
