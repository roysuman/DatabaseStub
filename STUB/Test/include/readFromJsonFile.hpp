/*
 * =====================================================================================
 *
 *       Filename:  readFromJsonFile.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Sunday 12 October 2014 11:04:35  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  SUMAN ROY (), email.suman.roy@gmail.com
 *   Organization:  SELF
 *
 * =====================================================================================
 */
#include <iostream>
#include <fstream>
#include "jsoncpp/json.h"
#include "jsoncpp/writer.h"
#include "../../SUPPORT/globalDatatypes.hpp"
namespace test{
	typedef struct _inputJsonStruct inputJsonStruct;

	struct _inputJsonStruct{
		std::string path;
		std::string databaseName;
		std::string scenarioName;
		std::string catagory;
		std::string protocol;
		std::string filterIp;
		std::string    portNo;
		std::string    loadProject;
		std::string stubServerIp;
		std::string    stubPort;
		std::string    readFromTcpDump;
		std::string tcpDumpFile;
		std::string interface;
		


		
	};

	class TestStub{
		
		public:
			bool errorFlag;

			inputJsonStruct   testParameters; 
			TestStub( void );
			~TestStub(){};

			
	};
	
}


