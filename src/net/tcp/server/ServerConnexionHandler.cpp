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
#include <unistd.h>
#include "ServerClientManager.h"

ServerConnexionHandler::ServerConnexionHandler(boost::asio::ip::tcp::socket* socket, NetworkManager* manager, bool raw,
		ServerClientManager* connectionManager) :
		socket(socket), manager(manager), id(manager->getNewId()), messagesToSend(new SynchronizedBuffer<boost::shared_ptr<NetworkMessageOut> >()), raw(
				raw), connectionManager(connectionManager)
{
	readHeader();
	handler();
	manager->reportNewWriter(id, this);
	sendPending = false;
	stopping = false;
}

ServerConnexionHandler::~ServerConnexionHandler()
{
	std::cout << "~ServerConnexionHandler()" << std::endl;
	try
	{
		socket->shutdown(boost::asio::ip::tcp::socket::shutdown_both);
	} catch (boost::system::system_error& e)
	{
		std::cerr << "error socket shutdown : " << e.what() << " error code " << e.code().value() << std::endl;
	}
	try
	{
		socket->close();
	} catch (boost::system::system_error& e)
	{
		std::cerr << "error socket close : " << e.what() << " error code " << e.code().value() << std::endl;
	}
	std::cout << "~ServerConnexionHandler() finish" << std::endl;
}

void ServerConnexionHandler::handler()
{
///	start();
}
void ServerConnexionHandler::writeToNet(boost::shared_ptr<NetworkMessageOut> message)
{
	if (message->isEndConnectionMessage())
	{
		std::cout << "DEPRECATED isEndConnectionMessage" << std::endl;
		endConnection();
		return;
	}

	if (!message->isRaw())
	{
		unsigned int value = message->getData()->size();
		boost::shared_ptr<std::string> msgSize(new std::string());
		msgSize->push_back((value >> 24) & 0xFF);
		msgSize->push_back((value >> 16) & 0xFF);
		msgSize->push_back((value >> 8) & 0xFF);
		msgSize->push_back((value) & 0xFF);
		messagesToSendV2.push(msgSize);
	}
	messagesToSendV2.push(message->getData());
	writeOne();

}

void ServerConnexionHandler::writeOne()
{
	if (sendPending || stopping || !socket || !socket->is_open())
	{
		return;
	}
	if (messagesToSendV2.size() == 0)
	{
		sendPending = false;
		return;
	}
	sendPending = true;
	currDataSend = messagesToSendV2.front();
	messagesToSendV2.pop();
	socket->async_send(boost::asio::buffer(currDataSend->c_str(), currDataSend->size()),
			boost::bind(&ServerConnexionHandler::handlerWrite, this, boost::asio::placeholders::error(),
					boost::asio::placeholders::bytes_transferred()));

}

void ServerConnexionHandler::handlerWrite(const boost::system::error_code& error, std::size_t bytes_transferred)
{
	if (!error)
	{
		sendPending = false;
		writeOne();
	}
	else
	{
		std::cerr << "Error write : " << error.message() << std::endl;
		endConnection();
	}
}

void ServerConnexionHandler::readHeader()
{
	if (raw)
	{
		readAll();
	}
	else
	{
		boost::asio::async_read(*socket, boost::asio::buffer(network_buffer_header), boost::asio::transfer_exactly(4),
				boost::bind(&ServerConnexionHandler::handle_readHeader, this, boost::asio::placeholders::error,
						boost::asio::placeholders::bytes_transferred));
	}
}

void ServerConnexionHandler::readAll()
{
	boost::asio::async_read(*socket, boost::asio::buffer(network_buffer), boost::asio::transfer_at_least(1),
			boost::bind(&ServerConnexionHandler::handle_read, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
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

//		std::cout << "Server : get a message : " << size << " bytes" << std::endl;
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
	if (stopping)
	{
		return;
	}
	stopping = true;
	sendPending = true;
	if (socket && socket->is_open())
	{
		manager->removeWriter(id);
		manager->removeId(id);
		NetworkEvent event(NetworkEvent::DISCONECTION);
		event.id = id;
		manager->getNetworkEventManager()->onEvent(event);
//		manager->removeBuffer(id);
		std::cout << "id " << id << " has been disconnected" << std::endl;
//		connectionManager->stopConnection(socket);

		try
		{
			socket->shutdown(boost::asio::ip::tcp::socket::shutdown_both);
		} catch (boost::system::system_error& e)
		{
			std::cerr << "error socket shutdown : " << e.what() << " error code " << e.code().value() << std::endl;
		}
		try
		{
			socket->close();
		} catch (boost::system::system_error& e)
		{
			std::cerr << "error socket close : " << e.what() << " error code " << e.code().value() << std::endl;
		}

	}
}

