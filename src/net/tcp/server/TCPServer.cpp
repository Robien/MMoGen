/*
 * TCPServer.cpp
 *
 *  Created on: 9 juil. 2015
 *      Author: rguyard
 */

#include "net/tcp/server/TCPServer.h"
#include "net/common/NetworkEventManager.h"

TCPServer::TCPServer(unsigned int port) : port(port)
{
	NetworkEventManager::get()->addEventReceiver(this);
	server = NULL;
}

TCPServer::~TCPServer()
{
}

void TCPServer::listen()
{
		boost::asio::io_service io;
		server = new ServerListener(io, port, &manager);

		server->listen();

		io.run();
}

ServerListener* TCPServer::getServerEndpoint()
{
	return server;
}

NetworkManager& TCPServer::getManager()
{
	return manager;
}
