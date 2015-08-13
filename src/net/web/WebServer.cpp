/*
 * TestTCPServer.cpp
 *
 *  Created on: 6 juil. 2015
 *      Author: rguyard
 */

#include <net/common/NetworkEventManager.h>
#include <net/tcp/server/ServerListener.h>
#include <net/UnityPolicyServer.h>
#include <net/web/WebServer.h>

WebServer::WebServer(NetworkManager* gameManager, unsigned int port) :
		port(port), gameManager(gameManager)
{
	manager.getNetworkEventManager()->addEventReceiver(this);
}

WebServer::~WebServer()
{
}

void WebServer::run()
{
	boost::asio::io_service io;
	ServerListener server(io, port, &manager, true);

	server.listen();

	io.run();
}

void WebServer::onMessageReceived(boost::shared_ptr<NetworkMessage> message)
{
	std::cout.write(&(*message->getData())[0], message->getDataSize());

	std::cout << std::endl;

	std::string m = "HTTP/1.1 200 OK\r\nCache-Control: no-cache, private\r\nContent-Length: 107\r\nDate: Mon, 24 Nov 2014 10:21:21 GMT\r\n\r\n";
	if (gameManager != NULL)
	{
		m += gameManager->getJSONData();
	}
	else
	{
		m += "NO DATA";
	}
	boost::shared_ptr<NetworkMessageOut> messageOut = NetworkMessageOut::factory(message->getSenderId(), m);
	boost::shared_ptr<NetworkMessageOut> messageEnd(new NetworkMessageOut(true, message->getSenderId()));
	messageOut->setRaw();
	manager.sendMessage(messageOut);
	manager.sendMessage(messageEnd);

}

void WebServer::onEvent(NetworkEvent& event)
{

	boost::shared_ptr<NetworkMessageOut> messageOut;

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
unsigned int WebServer::getPort()
{
	return port;
}

