/*
 * ServerConnexionHandler.cpp
 *
 *  Created on: 28 janv. 2015
 *      Author: rguyard
 */

#include <boost/asio.hpp>
#include "ServerConnexionHandler.h"
#include <iostream>

#include <boost/bind.hpp>
#include <net/common/NetworkEvent.h>
#include <net/common/NetworkEventManager.h>

using boost::asio::socket_base;

ServerConnexionHandler::ServerConnexionHandler(boost::asio::ip::tcp::socket* socket, NetworkManager* manager) :
		socket(socket), manager(manager), id(manager->getNewId()), messagesToSend(new SynchronizedBuffer<boost::shared_ptr<NetworkMessageOut> >())
{
	readHeader();
	handler();
	manager->reportNewBuffer(id, messagesToSend);
}

ServerConnexionHandler::~ServerConnexionHandler()
{
}

void ServerConnexionHandler::handler()
{
	start();
}
void ServerConnexionHandler::run()
{
	bool running = true;
	try
	{
		while (running)
		{
			boost::shared_ptr<NetworkMessageOut> message = messagesToSend->get();
			if (message->isEndConnectionMessage())
			{
				running = false;
			}
			else
			{
				if (!message->isRaw())
				{
					unsigned int value = message->getData()->size();
					std::string msgSize;
					msgSize.push_back((value >> 24) & 0xFF);
					msgSize.push_back((value >> 16) & 0xFF);
					msgSize.push_back((value >> 8) & 0xFF);
					msgSize.push_back((value) & 0xFF);

					socket->send(boost::asio::buffer(msgSize));
				}
				socket->send(boost::asio::buffer(*message->getData()));
			}
		}
	} catch (boost::system::system_error& e)
	{
		std::cerr << "error with the TCP connection : " << e.what() << std::endl;
	}
	manager->removeId(id);
	NetworkEvent event(NetworkEvent::DISCONECTION);
	event.id = id;
	NetworkEventManager::get()->onEvent(event);
	try
	{
		socket->shutdown(socket_base::shutdown_both);
	} catch (boost::system::system_error& e)
	{

	}
	try
	{
		socket->close();
	} catch (boost::system::system_error& e)
	{

	}
	manager->removeBuffer(id);
	std::cout << "id " << id << " has been disconnected" << std::endl;
}

void ServerConnexionHandler::readHeader()
{
	boost::asio::async_read(*socket, boost::asio::buffer(network_buffer_header), boost::asio::transfer_exactly(4),
			boost::bind(&ServerConnexionHandler::handle_readHeader, this, boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
}
void ServerConnexionHandler::read(unsigned int size)
{
	boost::asio::async_read(*socket, boost::asio::buffer(network_buffer), boost::asio::transfer_exactly(size),
			boost::bind(&ServerConnexionHandler::handle_read, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}
void ServerConnexionHandler::handle_readHeader(const boost::system::error_code& error, size_t number_bytes_read)
{
	if (!error)
	{
		unsigned int size = 0;
		size |= (network_buffer_header[0] << 24);
		size |= (network_buffer_header[1] << 16);
		size |= (network_buffer_header[2] << 8);
		size |= (network_buffer_header[3]);

		std::cout << "Server : get a message : " << size << " bytes" << std::endl;
		if (size > MAX_SIZE_PACKET)
		{
			std::cout << "error : message too large" << std::endl;
			boost::shared_ptr<boost::array<char, MAX_SIZE_PACKET> > data(new boost::array<char, MAX_SIZE_PACKET>());
			boost::shared_ptr<NetworkMessage> message(new NetworkMessage(id, 0, data));

			manager->newIncommingMessage(message);
			endConnection();
			//	readHeader();
		}
		else
		{
			read(size);
		}
	}
	else
	{
		std::cerr << "Error read Header : " << error.message() << std::endl;
		endConnection();
	}
}
void ServerConnexionHandler::handle_read(const boost::system::error_code& error, size_t number_bytes_read)
{
	if (!error)
	{
		boost::shared_ptr<boost::array<char, MAX_SIZE_PACKET> > data(new boost::array<char, MAX_SIZE_PACKET>());
		*data = network_buffer;
		boost::shared_ptr<NetworkMessage> message(new NetworkMessage(id, number_bytes_read, data));

		manager->newIncommingMessage(message);

		readHeader();
	}
	else
	{
		std::cerr << "Error read : " << error.message() << std::endl;
		endConnection();
	}
}
void ServerConnexionHandler::endConnection()
{
	boost::shared_ptr<NetworkMessageOut> message(new NetworkMessageOut(true));
	messagesToSend->add(message);
}

