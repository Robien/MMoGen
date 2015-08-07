/*
 * TCPServer.h
 *
 *  Created on: 9 juil. 2015
 *      Author: rguyard
 */

#ifndef TCPSERVER_H_
#define TCPSERVER_H_

#include <boost/asio.hpp>
#include "net/common/NetworkEventReceiver.h"
#include "net/common/NetworkManager.h"

#include "ServerListener.h"

class TCPServer : public NetworkEventReceiver
{
public:
	TCPServer(unsigned int port);
	virtual ~TCPServer();

	public:
		virtual void onEvent(NetworkEvent event) = 0;
		virtual void onMessageReceived(boost::shared_ptr<NetworkMessage> message) = 0;

	public:
		void listen();

	protected:
		ServerListener* getServerEndpoint();
		NetworkManager& getManager();

	private:
		NetworkManager manager;
		ServerListener* server;

	private:
		unsigned int port;
};

#endif /* TCPSERVER_H_ */
