/*
 * LoginServer.cpp
 *
 *  Created on: 9 juil. 2015
 *      Author: rguyard
 */

#include <proto/src/Game.pb.h>
#include "net/game/LoginServer.h"

#include "proto/src/Connection.pb.h"

LoginServer::LoginServer(unsigned int port, unsigned int webPort) :
		TCPServer(port, true, webPort), nbGame(0), nbPlayerInGame(0), totalNbGame(0), averageWaitingTime(0), totalSecondPlayed(0)
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	waiting.reset();

	*(getManager().getNbGamePtr()) = &nbGame;
	*(getManager().getNbPlayerInGamePtr()) = &nbPlayerInGame;
	*(getManager().getTotalNbGamePtr()) = &totalNbGame;
	*(getManager().getAverageWaitingTimePtr()) = &averageWaitingTime;
	*(getManager().getTotalSecondPlayedPtr()) = &totalSecondPlayed;
}

LoginServer::~LoginServer()
{
	*(getManager().getNbGamePtr()) = NULL;
	*(getManager().getNbPlayerInGamePtr()) = NULL;
	*(getManager().getTotalNbGamePtr()) = NULL;
	*(getManager().getAverageWaitingTimePtr()) = NULL;
	*(getManager().getTotalSecondPlayedPtr()) = NULL;
}

void LoginServer::onEvent(NetworkEvent& event)
{
	if (event.typeEvent == NetworkEvent::CONNECTION)
	{
		std::cout << "[EVENT] connection id : " << event.id << std::endl;
		mutexInterClient.lock();
		std::map<unsigned int, boost::shared_ptr<loginServer::Client> >::iterator client = clients.find(event.id);

		if (client != clients.end())
		{
			std::cout << " ... [E] client with id " << event.id << " is already known" << std::endl;
			clients.erase(client);
		}
		mutexInterClient.unlock();
		boost::shared_ptr<loginServer::Client> clientPtr(new loginServer::Client(event.id));
		clientPtr->setIsConnected(true);
		mutexInterClient.lock();
		clients.insert(std::pair<unsigned int, boost::shared_ptr<loginServer::Client> >(event.id, clientPtr));
		mutexInterClient.unlock();
	}
	else
	{
		mutexInterClient.lock();
		std::cout << "[EVENT] disconnection id : " << event.id << std::endl;
		if (waiting.get() != NULL && waiting->getId() == event.id)
		{
			waiting.reset();
		}

		std::map<unsigned int, boost::shared_ptr<loginServer::Client> >::iterator client = clients.find(event.id);

		if (client == clients.end())
		{
			std::cerr << " ... [E] client with id " << event.id << " is not known" << std::endl;
		}
		else
		{
			if (client->second->getStatus() == loginServer::Client::INGAME || client->second->getStatus() == loginServer::Client::ALONE)
			{
				nbPlayerInGame--;
				if (client->second->getStatus() == loginServer::Client::INGAME)
				{
					totalSecondPlayed += client->second->getGameTimer()->getValueinSecond();
				}
			}
			if (client->second->getFriend() != 0)
			{
				nbGame--;
				std::map<unsigned int, boost::shared_ptr<loginServer::Client> >::iterator clientFriend = clients.find(client->second->getFriend());

				if (clientFriend != clients.end())
				{
					std::cout << "sending to client " << clientFriend->second->getId() << " a disconnection message ..." << std::endl;
					sendInGameRemoteDisconnection(clientFriend->second->getId());
					clientFriend->second->setIsAlone();
				}
				else
				{
					std::cout << "client with id " << event.id << " has no friend ! (2) " << std::endl;
				}
			}
			else
			{
				std::cout << "client with id " << event.id << " has no friend ! (1)" << std::endl;
			}
			clients.erase(client);
		}
		mutexInterClient.unlock();

		std::cout << "[EVENT] disconnection done id : " << event.id << std::endl;

	}
}
void LoginServer::onMessageReceived(boost::shared_ptr<NetworkMessage> message)
{
	std::cout << "received a message from id " << message->getSenderId() << std::endl;
	mutexInterClient.lock();
	std::map<unsigned int, boost::shared_ptr<loginServer::Client> >::const_iterator client = clients.find(message->getSenderId());
	mutexInterClient.unlock();

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
			//TODO : avoid copy
			getManager().sendMessage(NetworkMessageOut::factory(message, client->second->getFriend()));
			break;
		case loginServer::Client::DISCONNECTED:
			std::cout << "status : DISCONNECTED" << std::endl;
			break;
		case loginServer::Client::ALONE:
			std::cout << "status : ALONE : message ignored" << std::endl;
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
		client->second->setStartMM();
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
	mutexInterClient.lock();
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
	mutexInterClient.unlock();
}

void LoginServer::sendMFMessage(unsigned int id)
{
	Connection::MatchFound mf;

	std::string mfStr = mf.SerializeAsString();
	getManager().sendMessage(NetworkMessageOut::factory(id, mfStr));
}

void LoginServer::sendStartGame(unsigned int id, bool isMain)
{
	Connection::StartGame sg;

	sg.set_ismain(isMain);

	std::string sgStr = sg.SerializeAsString();
	getManager().sendMessage(NetworkMessageOut::factory(id, sgStr));
}

void LoginServer::startGame(std::map<unsigned int, boost::shared_ptr<loginServer::Client> >::const_iterator player1,
		std::map<unsigned int, boost::shared_ptr<loginServer::Client> >::const_iterator player2)
{
	averageWaitingTime = averageWaitingTime * (2 * totalNbGame) + player1->second->getWaitingTime() + player2->second->getWaitingTime();
	nbGame++;
	totalNbGame++;
	nbPlayerInGame += 2;
	averageWaitingTime /= (2 * totalNbGame);
	sendStartGame(player1->second->getId(), true);
	sendStartGame(player2->second->getId(), false);
	std::cout << "starting game with id : " << player1->second->getId() << " and id : " << player2->second->getId() << std::endl;
}

void LoginServer::sendInGameRemoteDisconnection(unsigned int id)
{
	Game::MessageType mt;

	mt.set_type(Game::MessageType_EMessageType_REMOTE_DISCONNECTION);

	getManager().sendMessage(NetworkMessageOut::factory(id, mt.SerializeAsString()));
}
