/*
 * LoginServer.h
 *
 *  Created on: 9 juil. 2015
 *      Author: rguyard
 */

#ifndef LOGINSERVER_H_
#define LOGINSERVER_H_

#include <boost/asio.hpp>
#include <net/game/Client.h>
#include "net/common/NetworkEventReceiver.h"
#include "net/common/NetworkManager.h"

#include "net/tcp/server/TCPServer.h"

class LoginServer: public TCPServer
{
public:
	LoginServer(unsigned int port);
	virtual ~LoginServer();

public:
	void onEvent(NetworkEvent event);
	void onMessageReceived(boost::shared_ptr<NetworkMessage> message);

private:
	void computeMMMessage(boost::shared_ptr<NetworkMessage> message,
			std::map<unsigned int, boost::shared_ptr<loginServer::Client> >::const_iterator client);
	void computeREADYMessage(boost::shared_ptr<NetworkMessage> message,
			std::map<unsigned int, boost::shared_ptr<loginServer::Client> >::const_iterator client);
	void sendMFMessage(unsigned int id);
	void sendStartGame(unsigned int id, bool isMain);

private:

	void startGame(std::map<unsigned int, boost::shared_ptr<loginServer::Client> >::const_iterator player1,
			std::map<unsigned int, boost::shared_ptr<loginServer::Client> >::const_iterator player2);

private:
	boost::shared_ptr<loginServer::Client> waiting;
	std::map<unsigned int, boost::shared_ptr<loginServer::Client> > clients;
};

#endif /* LOGINSERVER_H_ */
