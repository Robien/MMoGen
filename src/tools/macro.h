/*
 * macro.h
 *
 *  Created on: 24 déc. 2014
 *      Author: rguyard
 */

#ifndef MACRO_H_
#define MACRO_H_

//convert to string
#define SSTR(x) dynamic_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()
//boolean to char*
#define btoa(x) ((x) ? "true":"false")

#if false

//to log you should use :
// for error AAPLOGE("formated message" ...)
// for warnings AAPLOGW("formated message" ...)
// for info AAPLOGI("formated message" ...)
// for debug AAPLOGD("formated message" ...)

//if you don't want to use ULOG and you want to log in std only you can set log=std in /etc/app.conf

#include "conf/ConstManager.h"
#include "ulog.h"

#define ULOGAAPE(...) ULOGE(__VA_ARGS__); ULOGE("\t ... at %s:%d", __FILE__ , __LINE__ )
#define ULOGAAPW(...) ULOGW(__VA_ARGS__); ULOGW("\t ... at %s:%d", __FILE__ , __LINE__ )
#define ULOGAAPI(...) ULOGI(__VA_ARGS__);
#define ULOGAAPD(...) ULOGD(__VA_ARGS__);

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define COUTALL(...) printf(__VA_ARGS__)

#define COUTLOGAAPE(...) std::cout << "[E] \t"; COUTALL(__VA_ARGS__);std::cout << std::endl; \
	std::cout << "\t ... at " <<  __FILE__ << ":" << __LINE__ << std::endl;
#define COUTLOGAAPW(...) std::cout << "[W] \t"; COUTALL(__VA_ARGS__);std::cout << std::endl; \
	std::cout << "\t ... at " <<  __FILE__ << ":" << __LINE__ << std::endl;
#define COUTLOGAAPI(...) std::cout << "[I] \t"; COUTALL(__VA_ARGS__);std::cout << std::endl;
#define COUTLOGAAPD(...) std::cout << "[D] \t"; COUTALL(__VA_ARGS__);std::cout << std::endl;

#define AAPLOGE(...) \
	do { \
		if (ConstManager::get()->shouldIUseUlog()) \
		{ \
			ULOGAAPE(__VA_ARGS__); \
		} \
		else \
		{ \
			COUTLOGAAPE(__VA_ARGS__); \
		} \
	}\
    while (false)
#define AAPLOGW(...) \
	do { \
		if (ConstManager::get()->shouldIUseUlog()) \
		{ \
			ULOGAAPW(__VA_ARGS__); \
		} \
		else \
		{ \
			COUTLOGAAPW(__VA_ARGS__); \
		} \
	}\
    while (false)
#define AAPLOGI(...) \
	do { \
		if (ConstManager::get()->shouldIUseUlog()) \
		{ \
			ULOGAAPI(__VA_ARGS__); \
		} \
		else \
		{ \
			COUTLOGAAPI(__VA_ARGS__); \
		} \
	}\
    while (false)
#define AAPLOGD(...) \
	do { \
		if (ConstManager::get()->shouldIUseUlog()) \
		{ \
			ULOGAAPD(__VA_ARGS__); \
		} \
		else \
		{ \
			COUTLOGAAPD(__VA_ARGS__); \
		} \
	}\
    while (false)
#define AAPLOG(...) \
	do { \
		if (ConstManager::get()->shouldIUseUlog()) \
		{ \
			ULOGAAPD(__VA_ARGS__); \
		} \
		else \
		{ \
			COUTLOGAAPD(__VA_ARGS__); \
		} \
	}\
    while (false)

#endif

#endif /* MACRO_H_ */
