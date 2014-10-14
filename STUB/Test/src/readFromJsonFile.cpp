/*
 * =====================================================================================
 *
 *       Filename:  readFromJsonFile.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Sunday 12 October 2014 11:16:58  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  SUMAN ROY (), email.suman.roy@gmail.com
 *   Organization:  SELF
 *
 * =====================================================================================
 */
#include "../include/readFromJsonFile.hpp"

test::TestStub::TestStub ( void ){

	Json::Value     root;
	Json::Reader    reader;
	std::string     fileName;
	Json::Value     nodeValue;
	std::ifstream   fileHandler;
	
	fileName = "../CONFIG/test.json";

	try{
		fileHandler.open( fileName.c_str() );
		std::cout<<"FileName:"<<fileName<<std::endl;
		if ( ! fileHandler.is_open() ){
			std::cerr<<"File Name ["<<__FILE__<<"] Function ["<<__FUNCTION__
				<<" ] Line [ "<<__LINE__<<" ] DateTime ["<<__DATE__<<"_"<<__TIME__<<"] Cant open file\n ";
			exit ( 0 );
		}
		if ( !reader.parse ( fileHandler , root ) ){

			std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
				<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
				<<__TIME__<<"]failed to parse JSON file\n";
		}
		nodeValue = root [ "Path" ];
		if ( not nodeValue.isNull() ){
			testParameters.path = nodeValue.asString();

		} else errorFlag = false ;
		nodeValue = root ["DatabaseName"];
		if ( not nodeValue.isNull() ){
			testParameters.databaseName = 
				nodeValue.asString();
		}else errorFlag = false;
		nodeValue = root [ "ScenarioName" ];
		if ( not nodeValue.isNull() ){
			testParameters.scenarioName =
				nodeValue.asString() ;
		}else errorFlag = false ;
		nodeValue = root [ "Catagory" ];
		if ( not nodeValue.isNull() ){
			testParameters.catagory = 
				nodeValue.asString();
		} else errorFlag = false;
		nodeValue = root [ "Protocol" ];
		if ( not nodeValue.isNull() ){
			testParameters.protocol =
				nodeValue.asString();
		}else errorFlag = false;
		nodeValue = root [ "Server" ];
		if ( not nodeValue.isNull() ){
			testParameters.filterIp =
				nodeValue.asString();
		} else errorFlag = false;
		nodeValue = root ["PortNo"];
		if ( not nodeValue.isNull() ){
			testParameters.portNo =
				nodeValue.asString() ;
		} else errorFlag = false ;
		nodeValue = root ["LoadProject"];
		if ( not nodeValue.isNull() ){
			testParameters.loadProject =
				nodeValue.asString();
		} else errorFlag = false;
		nodeValue = root [ "StubServerIp"];
		if( not nodeValue.isNull() ){
			testParameters.stubServerIp =
				nodeValue.asString();
		}else errorFlag = false;
		nodeValue = root [ "StubServerPort" ];
		if ( not nodeValue.isNull() ){
			testParameters.stubPort =
				nodeValue.asString();
		}else errorFlag = false ;
		nodeValue = root [ "GenFromTcpDump" ];
		if ( not nodeValue.isNull() ){
			testParameters.readFromTcpDump =
				nodeValue.asString();
		}else errorFlag = false ;
		nodeValue = root [ "TcpDumpPath" ];
		if ( not nodeValue.isNull() ){
			testParameters.tcpDumpFile =
				nodeValue.asString();
		}else errorFlag = false ;
		nodeValue = root [ "RecordInterface" ];
		if ( not nodeValue.isNull() ){
			testParameters.interface =
				nodeValue.asString();
		}else errorFlag = false ;
	}
	catch ( std::exception &e){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__
			<<"_"<<__TIME__<<"]Exception :"<<e.what()<<std::endl;
		errorFlag = false ;

	}
	fileHandler.close();
}


