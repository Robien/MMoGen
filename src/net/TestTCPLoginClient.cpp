/*
 * TestTCPLoginClient.cpp
 *
 *  Created on: 13 juil. 2015
 *      Author: rguyard
 */

#include <net/common/NetworkEventManager.h>
#include <net/TestTCPLoginClient.h>

#include "tcp/client/ClientConnectAndPrint.h"
#include "proto/src/Connection.pb.h"

TestTCPLoginClient::TestTCPLoginClient()
{
	GOOGLE_PROTOBUF_VERIFY_VERSION;
	NetworkEventManager::get()->addEventReceiver(this);
	status = 0;
}

TestTCPLoginClient::~TestTCPLoginClient()
{
}

void TestTCPLoginClient::run()
{
	boost::asio::io_service io;
	ClientConnectAndPrint client(io, "127.0.0.1", 12345, &manager);

	client.connect();

	io.run();
}

void TestTCPLoginClient::onMessageReceived(boost::shared_ptr<NetworkMessage> message)
{
	std::cout << "YOO client : " << message->getSenderId() << std::endl;
//	std::cout.write(&(*message->getData())[0], message->getDataSize());
//
//	manager.sendMessage(NetworkMessageOut::factory(message->getSenderId(), message->getData()->c_array()));
//	std::cout << std::endl;
	std::cout << "status : " << status << std::endl;

	if (status == 0)
	{
	}
	else if (status == 1)
	{
		sendReady();
	}
	status++;

}

void TestTCPLoginClient::onEvent(NetworkEvent event)
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
	Connection::MM mm;

	mm.set_command(Connection::MM_MMCommandType_START);
	mm.set_elo(0);
	mm.set_versionmajor(0);
	mm.set_versionminor(0);

	manager.sendMessage(NetworkMessageOut::factory(0, mm.SerializeAsString()));
}
void TestTCPLoginClient::sendReady()
{
	Connection::Ready r;

	manager.sendMessage(NetworkMessageOut::factory(0, r.SerializeAsString()));
}
