/*
 * ClientConnectAndPrint.h
 *
 *  Created on: 28 janv. 2015
 *      Author: rguyard
 */

#ifndef CLIENTCONNECTANDPRINT_H_
#define CLIENTCONNECTANDPRINT_H_

#include <boost/asio.hpp>
#include <data/SynchonizedBuffer.h>
#include <net/common/NetworkMessage.h>
#include <net/common/NetworkMessageOut.h>

#include "thread/Thread.h"

#include "net/common/NetworkManager.h"

class ClientConnectAndPrint: public Thread
{
public:
	ClientConnectAndPrint(boost::asio::io_service& ios_service, std::string ip, unsigned int port, NetworkManager* manager);
	virtual ~ClientConnectAndPrint();

	void readHeader();
	void read(unsigned int size);
	void connect();
	void handle_readHeader(const boost::system::error_code& error, size_t number_bytes_read);
	void handle_read(const boost::system::error_code& error, size_t number_bytes_read);
	void handle_connect(const boost::system::error_code& error);

public:
	void run();
private:
	boost::asio::io_service& ios_service;
	boost::asio::ip::tcp::endpoint endpoint;
	boost::asio::ip::tcp::socket socket;
	boost::array<char, MAX_SIZE_PACKET> network_buffer;
	boost::shared_ptr<SynchronizedBuffer<boost::shared_ptr<NetworkMessageOut> > > messagesToSend;
	NetworkManager* manager;
};

#endif /* CLIENTCONNECTANDPRINT_H_ */
