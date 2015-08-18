/*
 * FormattedDate.h
 *
 *  Created on: 18 août 2015
 *      Author: rguyard
 */

#ifndef FORMATTEDDATE_H_
#define FORMATTEDDATE_H_

#include <iostream>

class FormattedDate
{
public:
	FormattedDate();
	virtual ~FormattedDate();

public:
	std::string currentDateTime();

private:
	char buf[80];
};

#endif /* FORMATTEDDATE_H_ */
