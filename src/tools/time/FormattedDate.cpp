/*
 * FormattedDate.cpp
 *
 *  Created on: 18 août 2015
 *      Author: rguyard
 */

#include <time/FormattedDate.h>
#include <string>
#include <stdio.h>
#include <time.h>

FormattedDate::FormattedDate()
{
}

FormattedDate::~FormattedDate()
{
}

// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
std::string FormattedDate::currentDateTime()
{
	time_t now = time(0);
	struct tm tstruct;
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d : %X", &tstruct);

	return buf;
}
