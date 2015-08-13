/*
 * ServerListener.cpp
 *
 *  Created on: 28 janv. 2015
 *      Author: rguyard
 */

#include "ServerListener.h"

#include <iostream>
#include <boost/bind.hpp>

#include "ServerConnexionHandler.h"

ServerListener::ServerListener(boost::asio::io_service& io_service, unsigned int port, NetworkManager* manager, bool raw) :
		acceptor(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)), io_service(io_service), socket(NULL), manager(
				manager), serverClientManager(manager), raw(raw)
{
}

ServerListener::~ServerListener()
{
}

void ServerListener::handler(const boost::system::error_code& error)
{

	if (!error)
	{
		serverClientManager.newClient(socket, raw);
		listen();
	}
	else
	{
		std::cerr << "Error server accept : " << error.message() << std::endl;
	}
}

void ServerListener::listen()
{
	socket = new boost::asio::ip::tcp::socket(io_service);
	acceptor.async_accept(*socket, boost::bind(&ServerListener::handler, this, boost::asio::placeholders::error));
}
