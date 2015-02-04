/*
 * NetworkMessageOut.h
 *
 *  Created on: 30 janv. 2015
 *      Author: rguyard
 */

#ifndef NETWORKMESSAGEOUT_H_
#define NETWORKMESSAGEOUT_H_

#include <boost/asio.hpp>
#include <iostream>
#include <vector>

class NetworkMessageOut
{
public:
	NetworkMessageOut(unsigned int receiverId, boost::shared_ptr<std::string> data);
	virtual ~NetworkMessageOut();

	boost::shared_ptr<std::string> getData();
	boost::shared_ptr<std::vector<char> > getVectorData();
	unsigned int getReceiverId();

public:
	static boost::shared_ptr<NetworkMessageOut> factory(unsigned int receiverId, std::string data);

private:
	unsigned int receiver;
	boost::shared_ptr<std::string> data;
};

#endif /* NETWORKMESSAGEOUT_H_ */
