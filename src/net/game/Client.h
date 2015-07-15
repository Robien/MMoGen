/*
 * Client.h
 *
 *  Created on: 9 juil. 2015
 *      Author: rguyard
 */

#ifndef CLIENT_H_
#define CLIENT_H_

namespace loginServer
{

	class Client
	{
	public:
		enum status
		{
			CONNECTED, IN_MM, WAITING_FOR_READY, READY, INGAME, DISCONNECTED
		};

	public:
		Client(unsigned int id);
		virtual ~Client();

	public:
		unsigned int getId();

	public:
		status getStatus();
		void printStatus();

		void setIsConnected(bool isConnected);
		void setStartMM();
		void setWaitingForReady();
		void setIsReady();
		void setInGame();
		void setFriend(unsigned int id);
		unsigned int getFriend();

	private:
		unsigned int id;
		status clientStatus;
		unsigned int friendId;
	};

} /* namespace loginServer */

#endif /* CLIENT_H_ */
