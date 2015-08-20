/*
 * ClientManager.cpp
 *
 *  Created on: 29 janv. 2015
 *      Author: rguyard
 */

#include "ServerClientManager.h"

ServerClientManager::ServerClientManager(NetworkManager* manager) :
		manager(manager)
{
}

ServerClientManager::~ServerClientManager()
{
}

void ServerClientManager::newClient(boost::asio::ip::tcp::socket* socket, bool raw)
{
	boost::shared_ptr<ServerConnexionHandler> connectionHandler(new ServerConnexionHandler(socket, manager, raw, this));
	connectionHandlers.insert(std::pair<boost::asio::ip::tcp::socket*, boost::shared_ptr<ServerConnexionHandler> >(socket, connectionHandler));
}

void ServerClientManager::stopConnection(boost::asio::ip::tcp::socket* socket)
{
	std::map<boost::asio::ip::tcp::socket*, boost::shared_ptr<ServerConnexionHandler> >::const_iterator find = connectionHandlers.find(socket);
	if (find != connectionHandlers.end())
	{
		connectionHandlers.erase(socket);
	}
	else
	{
		std::cerr << "ServerConnectionHandler not found in map" << std::endl;
	}

}
