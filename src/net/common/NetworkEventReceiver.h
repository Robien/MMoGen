/*
 * NetworkEventReceiver.h
 *
 *  Created on: 30 janv. 2015
 *      Author: rguyard
 */

#ifndef NETWORKEVENTRECEIVER_H_
#define NETWORKEVENTRECEIVER_H_

#include <net/common/NetworkEvent.h>

class NetworkEventReceiver
{
public:
	NetworkEventReceiver();
	virtual ~NetworkEventReceiver();

public:
	virtual void onEvent(NetworkEvent event) = 0;
};

#endif /* NETWORKEVENTRECEIVER_H_ */
