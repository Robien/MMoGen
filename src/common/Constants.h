/*
 * Contstants.h
 *
 *  Created on: 18 août 2015
 *      Author: rguyard
 */

#ifndef CONTSTANTS_H_
#define CONTSTANTS_H_

#include <Singleton.h>
#include <iostream>
#include <map>
#include <stdexcept>

class Constants: public Singleton<Constants>
{
public:
	virtual ~Constants();

public:
	void add(std::string name, std::string value);
	void add(std::string name, int value);
	void add(std::string name, bool value);

public:
	std::string getString(std::string name) throw(std::out_of_range);
	int getInt(std::string name) throw(std::out_of_range);
	bool getBool(std::string name) throw(std::out_of_range);

	std::string getString(std::string name, std::string defaultValue);
	int getInt(std::string name, int defaultValue);
	bool getBool(std::string name, bool defaultValue);

private:
	std::map<std::string, std::string> constStr;
	std::map<std::string, int> constInt;
	std::map<std::string, bool> constBool;
};

#endif /* CONTSTANTS_H_ */
