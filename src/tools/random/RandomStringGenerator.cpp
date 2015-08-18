/*
 * RandomStringGenerator.cpp
 *
 *  Created on: 18 août 2015
 *      Author: rguyard
 */

#include <random/RandomStringGenerator.h>

RandomStringGenerator::RandomStringGenerator()
{
}

RandomStringGenerator::~RandomStringGenerator()
{
}

std::string RandomStringGenerator::getString(unsigned int len)
{
	std::string chars("abcdefghijklmnopqrstuvwxyz"
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
			"1234567890");
	std::string res = "";
	boost::random::uniform_int_distribution<> index_dist(0, chars.size() - 1);

	for (unsigned int i = 0; i < len; ++i)
	{
		res += chars[index_dist(rng)];
	}
	return res;
}

