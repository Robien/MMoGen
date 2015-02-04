/*
 * ClientManager.h
 *
 *  Created on: 29 janv. 2015
 *      Author: rguyard
 */

#ifndef CLIENTMANAGER_H_
#define CLIENTMANAGER_H_

#include <boost/asio.hpp>
#include "net/common/NetworkManager.h"

class ServerClientManager
{
public:
	ServerClientManager(NetworkManager* manager);
	virtual ~ServerClientManager();

public:
	void newClient(boost::asio::ip::tcp::socket* socket);


private:
	NetworkManager* manager;
};

#endif /* CLIENTMANAGER_H_ */
