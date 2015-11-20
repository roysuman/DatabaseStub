/*
 * =====================================================================================
 *
 *       Filename:  configStruct.hpp
 *
 *    Description:  this file maSTUB_INTains all structures required to handle JSON configuration fiel of TCP stub
 *
 *        Version:  1.0
 *        Created:  Monday 03 March 2014 03:57:09  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy (), 
 *   Organization:  SELF
 *
 * =====================================================================================
 */

#ifndef CONFIGSTRUCT_HPP_
#define CONFIGSTRUCT_HPP_
#include "iostream"
#include "../../SUPPORT/globalDatatypes.hpp"
//structure for json.cofig file
//structure that will read configuration data from file ( json )
typedef struct _configTcpStub configTcpStub;
struct _configTcpStub {
	bool traceLog;
    bool errorLog;
    bool log;
	std::string dummyServerIp;
	STUB_INT dummyServerPort;
	std::string sniffingIp;
	STUB_INT sniffingPort;
};
extern configTcpStub configTcpFile; // a global veriable for stoing config.

#endif

