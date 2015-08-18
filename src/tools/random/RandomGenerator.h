/*
 * RandomGenerator.h
 *
 *  Created on: 18 août 2015
 *      Author: rguyard
 */

#ifndef RANDOMGENERATOR_H_
#define RANDOMGENERATOR_H_

#include "boost/random.hpp"
#include "boost/generator_iterator.hpp"

class RandomGenerator
{
public:
	RandomGenerator();
	virtual ~RandomGenerator();

public:
	int getInt(int start, int end);
	bool getBool();

private:
	 boost::mt19937 rng;
};

#endif /* RANDOMGENERATOR_H_ */
