/*
 * RandomStringGenerator.h
 *
 *  Created on: 18 août 2015
 *      Author: rguyard
 */

#ifndef RANDOMSTRINGGENERATOR_H_
#define RANDOMSTRINGGENERATOR_H_

#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>

class RandomStringGenerator
{
public:
	RandomStringGenerator();
	virtual ~RandomStringGenerator();

public:
	std::string getString(unsigned int len);

private:
	 boost::random::random_device rng;
};

#endif /* RANDOMSTRINGGENERATOR_H_ */
