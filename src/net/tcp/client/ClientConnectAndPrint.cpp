/*
 * ClientConnectAndPrint.cpp
 *
 *  Created on: 28 janv. 2015
 *      Author: rguyard
 */

#include <boost/asio.hpp>
#include "ClientConnectAndPrint.h"
#include <boost/bind.hpp>

ClientConnectAndPrint::ClientConnectAndPrint(boost::asio::io_service& ios_service, std::string ip, unsigned int port, NetworkManager* manager) :
		ios_service(ios_service), endpoint(boost::asio::ip::address::from_string(ip), port), socket(ios_service), messagesToSend(
				new SynchronizedBuffer<boost::shared_ptr<NetworkMessageOut> >()), manager(manager)
{
	start();
	manager->reportNewBuffer(0, messagesToSend);
}

ClientConnectAndPrint::~ClientConnectAndPrint()
{
}

void ClientConnectAndPrint::readHeader()
{
	boost::asio::async_read(socket, boost::asio::buffer(network_buffer), boost::asio::transfer_exactly(4),
			boost::bind(&ClientConnectAndPrint::handle_readHeader, this, boost::asio::placeholders::error,
					boost::asio::placeholders::bytes_transferred));
}
void ClientConnectAndPrint::read(unsigned int size)
{
	boost::asio::async_read(socket, boost::asio::buffer(network_buffer), boost::asio::transfer_exactly(size),
			boost::bind(&ClientConnectAndPrint::handle_read, this, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}
void ClientConnectAndPrint::handle_readHeader(const boost::system::error_code& error, size_t number_bytes_read)
{
	if (!error)
	{
		unsigned int size = 0;
		size |= (network_buffer[0] << 24);
		size |= (network_buffer[1] << 16);
		size |= (network_buffer[2] << 8);
		size |= (network_buffer[3]);

		std::cout << "get a message : " << size << " bytes" << std::endl;
		read(size);
	}
	else
	{
		std::cout << error.message();
	}
}
void ClientConnectAndPrint::handle_read(const boost::system::error_code& error, size_t number_bytes_read)
{
	if (!error)
	{
//		std::cout << "[CLIENT] receive a message : " << std::endl;
//		std::cout.write(&network_buffer[0], number_bytes_read);
//		std::cout << std::endl;

		boost::shared_ptr<boost::array<char, MAX_SIZE_PACKET> > data(new boost::array<char, MAX_SIZE_PACKET>());
		*data = network_buffer;
		boost::shared_ptr<NetworkMessage> message(new NetworkMessage(0, number_bytes_read, data));

		manager->newIncommingMessage(message);

		readHeader();
	}
	else
	{
		std::cout << error.message();
	}
}
void ClientConnectAndPrint::connect()
{
	socket.async_connect(endpoint, boost::bind(&ClientConnectAndPrint::handle_connect, this, boost::asio::placeholders::error));
}

void ClientConnectAndPrint::handle_connect(const boost::system::error_code& error)
{
	if (!error)
	{
		readHeader();
	}
}
void ClientConnectAndPrint::run()
{

	for (;;)
	{
		boost::shared_ptr<NetworkMessageOut> message = messagesToSend->get();

		unsigned int value = message->getData()->size();
		std::string msgSize;
		msgSize.push_back((value >> 24) & 0xFF);
		msgSize.push_back((value >> 16) & 0xFF);
		msgSize.push_back((value >> 8) & 0xFF);
		msgSize.push_back((value) & 0xFF);

		socket.send(boost::asio::buffer(msgSize));
//	socket.send(boost::asio::buffer(*message->getData()));
		socket.send(boost::asio::buffer(*message->getData()));
	}

}
