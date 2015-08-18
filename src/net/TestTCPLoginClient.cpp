/*
 * TestTCPLoginClient.cpp
 *
 *  Created on: 13 juil. 2015
 *      Author: rguyard
 */

#include <net/common/NetworkEventManager.h>
#include <net/TestTCPLoginClient.h>
#include <proto/src/Game.pb.h>
#include <random/RandomStringGenerator.h>
#include <unistd.h>

#include "tcp/client/ClientConnectAndPrint.h"
#include "proto/src/Connection.pb.h"

TestTCPLoginClient::TestTCPLoginClient(std::string host, unsigned int port) : host(host), port(port)
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	manager.getNetworkEventManager()->addEventReceiver(this);
	status = 0;
	pingId = 0;
}

TestTCPLoginClient::~TestTCPLoginClient()
{
}

void TestTCPLoginClient::run()
{
	boost::asio::ip::tcp::resolver resolver(io);
	boost::asio::ip::tcp::resolver::query query(host, "");
	boost::asio::ip::tcp::resolver::iterator i = resolver.resolve(query);
	boost::asio::ip::tcp::endpoint end = *i;

	ClientConnectAndPrint client(io, end.address().to_string(), port, &manager);

	client.connect();

	io.run();
}

void TestTCPLoginClient::onMessageReceived(boost::shared_ptr<NetworkMessage> message)
{
//	std::cout.write(&(*message->getData())[0], message->getDataSize());
//
//	manager.sendMessage(NetworkMessageOut::factory(message->getSenderId(), message->getData()->c_array()));
//	std::cout << std::endl;
//	std::cout << "status : " << status << std::endl;

	if (status == 0)
	{
	}
	else if (status == 1)
	{
		sendReady();
	}
	else if (status == 2)
	{
		std::cout << "INGAME !!!" << std::endl;

		
	Connection::StartGame sg;

	sg.ParseFromArray(message->getData()->c_array(), message->getDataSize());

	if (sg.ismain())
	{
		std::cout << "IS MAIN !" << std::endl;
	}
	else
	{
		std::cout << "IS NOT MAIN !" << std::endl;
	}

		timerCaller.callMeIn(this, 1000);
	}
	else if (status > 2)
	{
		computeInGameMessage(message);
	}
	status++;

}

void TestTCPLoginClient::onEvent(NetworkEvent& event)
{
	switch (event.typeEvent)
	{
	case NetworkEvent::CONNECTION:
		std::cout << "CONNECTION id :" << event.id << std::endl;
		startMM();
		break;
	case NetworkEvent::DISCONECTION:
		std::cout << "DISCONECTION id :" << event.id << std::endl;
		break;
	default:
		std::cout << "Unhandled id :" << event.id << std::endl;
		break;
	}
}

void TestTCPLoginClient::startMM()
{
	Connection::ConnectionMessageClient cmc;

	cmc.set_type(Connection::ConnectionMessageClient_ConnectionMessageTypeClient_START_MATCH_MAKING);

	Connection::StartMatchMaking* smm = cmc.mutable_startmatchmaking();

	smm->set_elo(0);
	smm->set_versionmajor(0);
	smm->set_versionminor(0);
	smm->set_myname(RandomStringGenerator().getString(64));

	manager.sendMessage(NetworkMessageOut::factory(0, cmc.SerializeAsString()));
}
void TestTCPLoginClient::sendReady()
{
	Connection::ConnectionMessageClient cmc;

	cmc.set_type(Connection::ConnectionMessageClient_ConnectionMessageTypeClient_READY);

	manager.sendMessage(NetworkMessageOut::factory(0, cmc.SerializeAsString()));
}

void TestTCPLoginClient::sendPingMessage()
{
	Game::MessageType message;
	Game::Ping* ping = message.mutable_ping();

	ping->set_id(pingId);

	message.set_type(Game::MessageType_EMessageType_PING);

	timerPing.start();
	manager.sendMessage(NetworkMessageOut::factory(0, message.SerializeAsString()));

	pingId++;

}
void TestTCPLoginClient::sendPongMessage(unsigned int id)
{
	Game::MessageType message;
	Game::Pong* pong = message.mutable_pong();

	pong->set_id(id);

	message.set_type(Game::MessageType_EMessageType_PONG);

	manager.sendMessage(NetworkMessageOut::factory(0, message.SerializeAsString()));
}

void TestTCPLoginClient::timedCall()
{
	sendPingMessage();
}

void TestTCPLoginClient::computeInGameMessage(boost::shared_ptr<NetworkMessage> message)
{
	Game::MessageType messageType;

	messageType.ParseFromArray(message->getData()->c_array(), message->getDataSize());

	if (messageType.type() == Game::MessageType::PING)
	{
		sendPongMessage(messageType.pong().id());
	}
	else if (messageType.type() == Game::MessageType::PONG)
	{
		std::cout << "ping : " << timerPing.getValueinMilliSecond() << "ms" << std::endl;
		timerCaller.callMeIn(this, 1000);
	}
	else if (messageType.type() == Game::MessageType::REMOTE_DISCONNECTION)
	{
		std::cout << "the other player has been disconnected !" << std::endl;
		io.stop();
	}
	else
	{
		std::cout << "what ?" << std::endl;
	}
}

