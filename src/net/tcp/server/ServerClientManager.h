/*
 * ClientManager.h
 *
 *  Created on: 29 janv. 2015
 *      Author: rguyard
 */

#ifndef CLIENTMANAGER_H_
#define CLIENTMANAGER_H_

#include <map>

#include <boost/asio.hpp>

#include "net/common/NetworkManager.h"
#include "ServerConnexionHandler.h"

class ServerClientManager
{
public:
	ServerClientManager(NetworkManager* manager);
	virtual ~ServerClientManager();

public:
	void newClient(boost::asio::ip::tcp::socket* socket, bool raw);

public:
	void stopConnection(boost::asio::ip::tcp::socket* socket);

private:
	NetworkManager* manager;
	std::map<boost::asio::ip::tcp::socket*, boost::shared_ptr<ServerConnexionHandler> > connectionHandlers;
};

#endif /* CLIENTMANAGER_H_ */
