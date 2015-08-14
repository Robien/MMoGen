/*
 * NetworkManager.h
 *
 *  Created on: 29 janv. 2015
 *      Author: rguyard
 */

#ifndef NETWORKMANAGER_H_
#define NETWORKMANAGER_H_

#include <boost/asio.hpp>
#include <data/SynchonizedBuffer.h>
#include <net/common/NetworkEventManager.h>
#include <net/common/NetworkMessageOut.h>
#include <thread/MutexAuto.h>
#include <time/Timer.h>
#include <vector>

#include "NetworkMessage.h"
#include <map>

#include "SimpleJSON/src/JSON.h"

class WebServer;

class NetworkManager
{
public:
	NetworkManager(WebServer* webserver = NULL);
	virtual ~NetworkManager();

public:
	void newIncommingMessage(boost::shared_ptr<NetworkMessage> message);

public:
	void reportNewBuffer(unsigned int id, boost::shared_ptr<SynchronizedBuffer<boost::shared_ptr<NetworkMessageOut> > > buff);
	void removeBuffer(unsigned int id);
	void sendMessage(boost::shared_ptr<NetworkMessageOut> message);

public:
	NetworkEventManager* getNetworkEventManager();

public:
	int getNewId();
	void removeId(unsigned int id);

public:
	std::string getJSONData();
	unsigned int** getNbGamePtr();
	unsigned int** getNbPlayerInGamePtr();
	unsigned int** getTotalNbGamePtr();
	float** getAverageWaitingTimePtr();
	float** getTotalSecondPlayedPtr();

private:
	void removeIdNS(unsigned int id);
	void removeIdNSV2(unsigned int id);

private:
	Timer uptime;
	unsigned int* nbGame;
	unsigned int* nbPlayerInGame;
	unsigned int* totalNbGame;
	float* averageWaitingTime;
	float* totalSecondPlayed;

private:
	WebServer* webserver;
private:
	unsigned int nbConnected;
	//IDs
	MutexAuto mutexId;
	unsigned int maxId;
	std::vector<unsigned int> anusedId;

	std::map<unsigned int, boost::shared_ptr<SynchronizedBuffer<boost::shared_ptr<NetworkMessageOut> > > > idMap;

private:
	NetworkEventManager networkEventManager;

};

#endif /* NETWORKMANAGER_H_ */
