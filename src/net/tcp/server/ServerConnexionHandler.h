/*
 * ServerConnexionHandler.h
 *
 *  Created on: 28 janv. 2015
 *      Author: rguyard
 */

#ifndef SERVERCONNEXIONHANDLER_H_
#define SERVERCONNEXIONHANDLER_H_

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <common/NetworkWriter.h>
#include <data/SynchonizedBuffer.h>

#include "thread/Thread.h"
#include "net/common/networkConf.h"
#include <vector>

#include "net/common/NetworkManager.h"
#include <queue>

class ServerClientManager;

class ServerConnexionHandler: public NetworkWriter, public boost::enable_shared_from_this<ServerConnexionHandler>
{
public:
	ServerConnexionHandler(boost::asio::ip::tcp::socket* socket, NetworkManager* manager, bool raw, ServerClientManager* connectionManager);
	virtual ~ServerConnexionHandler();

public:
	void readHeader();
	void read(unsigned int size);
	void readAll();
	void handle_readHeader(const boost::system::error_code& error, size_t number_bytes_read);
	void handle_read(const boost::system::error_code& error, size_t number_bytes_read);

public:
	void write(boost::shared_ptr<NetworkMessageOut> message);
	void writeToNet(boost::shared_ptr<NetworkMessageOut> message);

private:
	void writeOne();

public:
	void handler();
	void handlerWrite(const boost::system::error_code& error, std::size_t bytes_transferred);

private:
	void endConnection();

private:
	boost::asio::ip::tcp::socket* socket;
	NetworkManager* manager;
	unsigned int id;
	boost::shared_ptr<SynchronizedBuffer<boost::shared_ptr<NetworkMessageOut> > > messagesToSend;
	std::queue<boost::shared_ptr<std::string> > messagesToSendV2;
	boost::shared_ptr<std::string> currDataSend;
	bool sendPending;
	boost::array<char, MAX_SIZE_PACKET> network_buffer;
	boost::array<char, 4> network_buffer_header;
	bool raw;
	ServerClientManager* connectionManager;
	bool stopping;
};

#endif /* SERVERCONNEXIONHANDLER_H_ */
