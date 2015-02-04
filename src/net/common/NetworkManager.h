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
#include <net/common/NetworkMessageOut.h>
#include <thread/MutexAuto.h>
#include <vector>

#include "NetworkMessage.h"
#include <map>

class NetworkManager
{
public:
	NetworkManager(bool isServer = true);
	virtual ~NetworkManager();

public:
	void newIncommingMessage(boost::shared_ptr<NetworkMessage> message);

public:
	void reportNewBuffer(unsigned int id, boost::shared_ptr<SynchronizedBuffer<boost::shared_ptr<NetworkMessageOut> > > buff);
	void sendMessage(boost::shared_ptr<NetworkMessageOut> message);

public:
	int getNewId();
	void removeId(unsigned int id);

private:
	void removeIdNS(unsigned int id);

private:
	bool isServer;
	//IDs
	MutexAuto mutexId;
	unsigned int maxId;
	std::vector<unsigned int> anusedId;

	std::map<unsigned int, boost::shared_ptr<SynchronizedBuffer<boost::shared_ptr<NetworkMessageOut> > > > idMap;

};

#endif /* NETWORKMANAGER_H_ */
