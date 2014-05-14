/*
 * =====================================================================================
 *
 *       Filename:  configStruct.hpp
 *
 *    Description:  this file maintains all structures required to handle JSON configuration fiel of TCP stub
 *
 *        Version:  1.0
 *        Created:  Monday 03 March 2014 03:57:09  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy (), 
 *   Organization:  Cognizant Technological solutions
 *
 * =====================================================================================
 */

#ifndef CONFIGSTRUCT_HPP_
#define CONFIGSTRUCT_HPP_
#include "iostream"
//structure for json.cofig file
typedef struct _configTcpStub configTcpStub;
struct _configTcpStub {
	bool traceLog;
    bool errorLog;
    bool log;
	std::string dummyServerIp;
	int dummyServerPort;
	std::string sniffingIp;
	int sniffingPort;
};
extern configTcpStub configTcpFile;

#endif

