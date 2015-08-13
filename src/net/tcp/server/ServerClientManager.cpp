/*
 * ClientManager.cpp
 *
 *  Created on: 29 janv. 2015
 *      Author: rguyard
 */

#include "ServerClientManager.h"

#include "ServerConnexionHandler.h"

ServerClientManager::ServerClientManager(NetworkManager* manager) :
		manager(manager)
{
}

ServerClientManager::~ServerClientManager()
{
}

void ServerClientManager::newClient(boost::asio::ip::tcp::socket* socket, bool raw)
{
	new ServerConnexionHandler(socket, manager, raw);
}

