/*
 * TCPServer.cpp
 *
 *  Created on: 9 juil. 2015
 *      Author: rguyard
 */

#include <net/web/WebServer.h>
#include "net/tcp/server/TCPServer.h"
#include "net/common/NetworkEventManager.h"

TCPServer::TCPServer(unsigned int port, bool withWebServer) :
	manager(withWebServer ? new WebServer(&manager) : NULL), port(port)
{
	manager.getNetworkEventManager()->addEventReceiver(this);
	server = NULL;
}

TCPServer::~TCPServer()
{
}

void TCPServer::listen()
{
	for (;;)
	{
		try
		{
			boost::asio::io_service io;
			for (;;)
			{
				try
				{
					server = new ServerListener(io, port, &manager);

					server->listen();

					io.run();
				}
				catch (boost::system::system_error& e)
				{
					std::cerr << "io.run error : " << e.what() << std::endl;
				}
				io.reset();
				exit(0); //TEMP kill the server to be sure to not being blocked in a infinite loop
			}
		}
		catch (std::exception& e)
		{
			std::cerr << "Error listen : " << e.what() << std::endl;
		}
	}
}

ServerListener* TCPServer::getServerEndpoint()
{
	return server;
}

NetworkManager& TCPServer::getManager()
{
	return manager;
}
