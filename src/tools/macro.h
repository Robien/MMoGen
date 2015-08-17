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

#endif /* MACRO_H_ */
