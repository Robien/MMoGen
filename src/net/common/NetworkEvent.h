/*
 * NetworkEvent.h
 *
 *  Created on: 30 janv. 2015
 *      Author: rguyard
 */

#ifndef NETWORKEVENT_H_
#define NETWORKEVENT_H_

class NetworkEvent
{
public:
	enum type
	{
		CONNECTION, DISCONECTION
	};
public:
	NetworkEvent(NetworkEvent::type type);
	virtual ~NetworkEvent();

public:
	NetworkEvent::type typeEvent;
	unsigned int id;
};

#endif /* NETWORKEVENT_H_ */
