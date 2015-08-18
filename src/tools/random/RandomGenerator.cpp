/*
 * RandomGenerator.cpp
 *
 *  Created on: 18 août 2015
 *      Author: rguyard
 */

#include <random/RandomGenerator.h>

RandomGenerator::RandomGenerator() :
		rng(time(0))
{
}

RandomGenerator::~RandomGenerator()
{
}

int RandomGenerator::getInt(int start, int end)
{
	boost::uniform_int<> distribution(start, end);
	boost::variate_generator<boost::mt19937, boost::uniform_int<> > dice(rng, distribution);
	return dice();
}

bool RandomGenerator::getBool()
{
	return (getInt(0, 1));
}
