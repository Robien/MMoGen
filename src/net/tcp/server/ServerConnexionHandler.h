/*
 * ServerConnexionHandler.h
 *
 *  Created on: 28 janv. 2015
 *      Author: rguyard
 */

#ifndef SERVERCONNEXIONHANDLER_H_
#define SERVERCONNEXIONHANDLER_H_

#include <boost/asio.hpp>
#include <data/SynchonizedBuffer.h>

#include "thread/Thread.h"
#include "net/common/networkConf.h"
#include <vector>

#include "net/common/NetworkManager.h"

class ServerConnexionHandler: public Thread
{
public:
	ServerConnexionHandler(boost::asio::ip::tcp::socket* socket, NetworkManager* manager);
	virtual ~ServerConnexionHandler();

	void readHeader();
	void read(unsigned int size);
	void handle_readHeader(const boost::system::error_code& error, size_t number_bytes_read);
	void handle_read(const boost::system::error_code& error, size_t number_bytes_read);

public:
	void handler();
public:
	void run();

private:
	void endConnection();

private:
	boost::asio::ip::tcp::socket* socket;
	NetworkManager* manager;
	unsigned int id;
	boost::shared_ptr<SynchronizedBuffer<boost::shared_ptr<NetworkMessageOut> > > messagesToSend;
	boost::array<char, MAX_SIZE_PACKET> network_buffer;
	boost::array<char, 4> network_buffer_header;
};

#endif /* SERVERCONNEXIONHANDLER_H_ */
