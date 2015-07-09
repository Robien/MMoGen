/*
 * TCPServer.cpp
 *
 *  Created on: 9 juil. 2015
 *      Author: rguyard
 */

#include "net/tcp/server/TCPServer.h"
#include "net/common/NetworkEventManager.h"
#include "net/tcp/server/ServerListener.h"

TCPServer::TCPServer()
{
	NetworkEventManager::get()->addEventReceiver(this);
}

TCPServer::~TCPServer()
{
}

void TCPServer::listen()
{
		boost::asio::io_service io;
		ServerListener server(io, 12345, &manager);

		server.listen();

		io.run();
}
