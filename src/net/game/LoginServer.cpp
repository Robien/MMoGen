/*
 * LoginServer.cpp
 *
 *  Created on: 9 juil. 2015
 *      Author: rguyard
 */

#include "net/game/LoginServer.h"

#include "proto/src/Connection.pb.h"

LoginServer::LoginServer(unsigned int port) : TCPServer(port)
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;
}

LoginServer::~LoginServer()
{
}

void LoginServer::onEvent(NetworkEvent event)
{
	if (event.typeEvent == NetworkEvent::CONNECTION)
	{
		std::cout << "[EVENT] connection id : " << event.id << std::endl;

		std::map<unsigned int, boost::shared_ptr<loginServer::Client> >::iterator client = clients.find(event.id);

		if (client != clients.end())
		{
			std::cout << " ... [E] client with id " << event.id << " is already known" << std::endl;
			clients.erase(client);
		}
		boost::shared_ptr<loginServer::Client> clientPtr(new loginServer::Client(event.id));
		clientPtr->setIsConnected(true);
		clients.insert(std::pair<unsigned int, boost::shared_ptr<loginServer::Client> >(event.id, clientPtr));
	}
	else
	{
		//TODO unlink with potential friends
		std::cout << "[EVENT] disconnection id : " << event.id << std::endl;
		if (waiting->getId() == event.id)
		{
			waiting.reset();
		}

		std::map<unsigned int, boost::shared_ptr<loginServer::Client> >::iterator client = clients.find(event.id);

		if (client == clients.end())
		{
			std::cout << " ... [E] client with id " << event.id << " is not known" << std::endl;
		}
		else
		{
			clients.erase(client);
		}

	}
}
void LoginServer::onMessageReceived(boost::shared_ptr<NetworkMessage> message)
{
	std::cout << "received a message from id " << message->getSenderId() << std::endl;
	std::map<unsigned int, boost::shared_ptr<loginServer::Client> >::const_iterator client = clients.find(message->getSenderId());

	if (client == clients.end())
	{
		std::cout << " ... [E] client with id " << message->getSenderId() << " is not known : message ignored" << std::endl;
	}
	else
	{
		switch (client->second->getStatus())
		{
		case loginServer::Client::CONNECTED:
			client->second->printStatus();
			computeMMMessage(message, client);
			client->second->printStatus();
			break;
		case loginServer::Client::IN_MM:
			std::cout << "status : IN_MM" << std::endl;
			break;
		case loginServer::Client::WAITING_FOR_READY:
			client->second->printStatus();
			computeREADYMessage(message, client);
			client->second->printStatus();
			break;
		case loginServer::Client::READY:
			client->second->printStatus();
			break;
		case loginServer::Client::INGAME:
			std::cout << "status : INGAME" << std::endl;
			getManager().sendMessage(NetworkMessageOut::factory(message, client->second->getFriend()));
			break;
		case loginServer::Client::DISCONNECTED:
			std::cout << "status : DISCONNECTED" << std::endl;
			break;
		default:
			break;
		}
	}
}

void LoginServer::computeMMMessage(boost::shared_ptr<NetworkMessage> message,
		std::map<unsigned int, boost::shared_ptr<loginServer::Client> >::const_iterator client)
{
	Connection::MM mm;
	if (!mm.ParseFromArray(message->getData()->c_array(), message->getDataSize()))
	{
		std::cerr << "Failed to parse MM message." << std::endl;
	}

	Connection::ACKMM ack;

	ack.set_isok(true);

	std::string ackStr = ack.SerializeAsString();

	if (!waiting)
	{
		client->second->setStartMM();
		waiting = client->second;
		std::cout << "!waiting" << std::endl;
	}
	else
	{
		std::cout << "waiting" << std::endl;
		client->second->setFriend(waiting->getId());
		client->second->setWaitingForReady();
		waiting->setFriend(client->second->getId());
		waiting->setWaitingForReady();

		sendMFMessage(waiting->getId());
		sendMFMessage(message->getSenderId());

		waiting.reset();
	}

	getManager().sendMessage(NetworkMessageOut::factory(message->getSenderId(), ackStr));

}
void LoginServer::computeREADYMessage(boost::shared_ptr<NetworkMessage> message,
		std::map<unsigned int, boost::shared_ptr<loginServer::Client> >::const_iterator client)
{
	Connection::Ready ready;

	if (!ready.ParseFromArray(message->getData()->c_array(), message->getDataSize()))
	{
		std::cerr << "Failed to parse READY message." << std::endl;
	}
	client->second->setIsReady();

	std::map<unsigned int, boost::shared_ptr<loginServer::Client> >::const_iterator other = clients.find(client->second->getFriend());

	if (other == clients.end())
	{
		std::cout << "ERROR friend !" << std::endl;
	}

	if (other->second->getStatus() == loginServer::Client::READY)
	{
		other->second->setInGame();
		client->second->setInGame();
		startGame(other, client);
	}

}

void LoginServer::sendMFMessage(unsigned int id)
{
	Connection::MatchFound mf;

	std::string mfStr = mf.SerializeAsString();
	getManager().sendMessage(NetworkMessageOut::factory(id, mfStr));
}

void LoginServer::sendStartGame(unsigned int id)
{
	Connection::StartGame sg;

	std::string sgStr = sg.SerializeAsString();
	getManager().sendMessage(NetworkMessageOut::factory(id, sgStr));
}

void LoginServer::startGame(std::map<unsigned int, boost::shared_ptr<loginServer::Client> >::const_iterator player1,
		std::map<unsigned int, boost::shared_ptr<loginServer::Client> >::const_iterator player2)
{
	sendStartGame(player1->second->getId());
	sendStartGame(player2->second->getId());
	std::cout << "starting game with id : " << player1->second->getId() << " and id : " << player2->second->getId() << std::endl;
}
