/*
 * Client.h
 *
 *  Created on: 9 juil. 2015
 *      Author: rguyard
 */

#ifndef CLIENT_H_
#define CLIENT_H_

#include <iostream>
#include <time/Timer.h>

namespace loginServer
{

	class Client
	{
	public:
		enum status
		{
			CONNECTED, IN_MM, WAITING_FOR_READY, READY, INGAME, ALONE, DISCONNECTED
		};

	public:
		Client(unsigned int id);
		virtual ~Client();

	public:
		unsigned int getId();
		void setName(std::string name);
		std::string& getName();

	public:
		status getStatus();
		void printStatus();

		void setIsConnected(bool isConnected);
		void setStartMM();
		void setWaitingForReady();
		void setIsReady();
		void setInGame();
		void setFriend(unsigned int id);
		void setIsAlone();
		unsigned int getFriend();

	public:
		Timer* getGameTimer();
		float getWaitingTime();

	private:
		std::string name;
		unsigned int id;
		status clientStatus;
		unsigned int friendId;
		Timer gameTimer;
		Timer waitingTimer;
		float waitingTime;
	};

} /* namespace loginServer */

#endif /* CLIENT_H_ */
