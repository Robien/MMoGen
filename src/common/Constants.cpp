/*
 * Contstants.cpp
 *
 *  Created on: 18 août 2015
 *      Author: rguyard
 */

#include <common/Constants.h>

Constants::~Constants()
{
}

void Constants::add(std::string name, std::string value)
{
	constStr.insert(std::pair<std::string, std::string>(name, value));
}
void Constants::add(std::string name, int value)
{
	constInt.insert(std::pair<std::string, int>(name, value));
}
void Constants::add(std::string name, bool value)
{
	constBool.insert(std::pair<std::string, bool>(name, value));
}

std::string Constants::getString(std::string name) throw (std::out_of_range)
{
	return (constStr.at(name));
}
int Constants::getInt(std::string name) throw (std::out_of_range)
{
	return (constInt[name]);
}
bool Constants::getBool(std::string name) throw (std::out_of_range)
{
	return (constBool[name]);
}
std::string Constants::getString(std::string name, std::string defaultValue)
{
	try
	{
		return getString(name);
	} catch (std::out_of_range& e)
	{
		return defaultValue;
	}
}
int Constants::getInt(std::string name, int defaultValue)
{
	try
	{
		return getInt(name);
	} catch (std::out_of_range& e)
	{
		return defaultValue;
	}

}
bool Constants::getBool(std::string name, bool defaultValue)
{
	try
	{
		return getBool(name);
	} catch (std::out_of_range& e)
	{
		return defaultValue;
	}

}
