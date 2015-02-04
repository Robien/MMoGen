/*
 * NetworkEvent.cpp
 *
 *  Created on: 30 janv. 2015
 *      Author: rguyard
 */

#include <net/common/NetworkEvent.h>

NetworkEvent::NetworkEvent(NetworkEvent::type type) :
		typeEvent(type), id(0)
{
}

NetworkEvent::~NetworkEvent()
{
}

