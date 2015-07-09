/*
 * TCPServer.h
 *
 *  Created on: 9 juil. 2015
 *      Author: rguyard
 */

#ifndef TCPSERVER_H_
#define TCPSERVER_H_

#include "net/common/NetworkEventReceiver.h"
#include "net/common/NetworkManager.h"

class TCPServer : public NetworkEventReceiver
{
public:
	TCPServer();
	virtual ~TCPServer();

	public:
		virtual void onEvent(NetworkEvent event) = 0;
		virtual void onMessageReceived(boost::shared_ptr<NetworkMessage> message) = 0;

	public:
		void listen();

	private:
		NetworkManager manager;
};

#endif /* TCPSERVER_H_ */
