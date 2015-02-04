/*
 * ServerListener.h
 *
 *  Created on: 28 janv. 2015
 *      Author: rguyard
 */

#ifndef SERVERLISTENER_H_
#define SERVERLISTENER_H_

#include "ServerListener.h"

#include <boost/asio.hpp>

#include "net/common/NetworkManager.h"

#include "ServerClientManager.h"

class ServerListener
{
public:
	ServerListener(boost::asio::io_service& io_service, unsigned int port, NetworkManager* manager);
	virtual ~ServerListener();

public:
	void listen();

public:
	void handler(const boost::system::error_code& error);
private:
	boost::asio::ip::tcp::acceptor acceptor;
	boost::asio::io_service& io_service;
	boost::asio::ip::tcp::socket* socket;
	NetworkManager* manager;
	ServerClientManager serverClientManager;

};

#endif /* SERVERLISTENER_H_ */
