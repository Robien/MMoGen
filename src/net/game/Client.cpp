/*
 * Client.cpp
 *
 *  Created on: 9 juil. 2015
 *      Author: rguyard
 */

#include <net/game/Client.h>
#include <iostream>

namespace loginServer
{

	Client::Client(unsigned int id) :
			id(id), clientStatus(Client::DISCONNECTED), friendId(0)
	{
	}

	Client::~Client()
	{
	}

	unsigned int Client::getId()
	{
		return id;
	}

	Client::status Client::getStatus()
	{
		return clientStatus;
	}

	void Client::setIsConnected(bool isConnected)
	{
		if (isConnected)
		{
			clientStatus = Client::CONNECTED;
		}
		else
		{
			clientStatus = Client::DISCONNECTED;
		}
	}
	void Client::setIsAlone()
	{
		clientStatus = Client::ALONE;
		this->setFriend(0);
	}
	void Client::setStartMM()
	{
		clientStatus = Client::IN_MM;
	}
	void Client::setWaitingForReady()
	{
		clientStatus = Client::WAITING_FOR_READY;
	}
	void Client::setIsReady()
	{
		clientStatus = Client::READY;
	}
	void Client::setInGame()
	{
		clientStatus = Client::INGAME;
	}
	void Client::setFriend(unsigned int id)
	{
		friendId = id;
	}
	void Client::printStatus()
	{
		switch (clientStatus)
		{
		case loginServer::Client::CONNECTED:
			std::cout << "status : CONNECTED" << std::endl;
			break;
		case loginServer::Client::IN_MM:
			std::cout << "status : IN_MM" << std::endl;
			break;
		case loginServer::Client::WAITING_FOR_READY:
			std::cout << "status : WAITING_FOR_READY" << std::endl;
			break;
		case loginServer::Client::READY:
			std::cout << "status : READY" << std::endl;
			break;
		case loginServer::Client::INGAME:
			std::cout << "status : INGAME" << std::endl;
			break;
		case loginServer::Client::DISCONNECTED:
			std::cout << "status : DISCONNECTED" << std::endl;
			break;
		default:
			break;
		}
	}

	unsigned int Client::getFriend()
	{
		return friendId;
	}

} /* namespace loginServer */
