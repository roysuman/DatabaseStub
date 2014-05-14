/*
 * =====================================================================================
 *
 *       Filename:  init.cpp
 *
 *    Description:  all the init code that need to be execuated during the launch
 *
 *        Version:  1.0
 *        Created:  01/07/2014 08:03:12 AM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  SUMAN ROY (), suman.roy@cognizant.com
 *   Organization:  COGNIZANT TECHNOLOGICAL SOLUTIONS 
 *
 * =====================================================================================
 */

#include "init.hpp"



bool init(){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<'\n';
	//Register mysql protocol
        Mysql::initialize();
	//register ldap protocol
	Ldap::initialize();
        initDataStructure();

        return true;

}
std::ifstream LoadConfig::configFileHandler;
void LoadConfig::initConfig(){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<'\n';
	try{
		configFileHandler.open("../CONFIG/tcpstub.config", std::ios::in);
	}
	catch ( std::ifstream::failure &e){
		std::cerr<<__FUNCTION__<<"exception caught-- can't open file\n"; 
		exit ( 0);
		
	}
	Json::Value root;   // will contains the root value after parsing.
	Json::Reader reader;
        if ( !reader.parse( configFileHandler , root ) ){
		std::cerr  << "Failed to parse configuration\n";
		exit ( 1 );
		
	}
	//read the JSON value from .json file
	Json::Value nodeValue = root [ "traceLog" ];
	if ( not nodeValue.isNull() ){
		std::cout<<"traceLog= "
			<<nodeValue.asString()<<'\n';
		configTcpFile.traceLog =( bool )strcmp( nodeValue.asString().c_str(), "false" );
		
	}else{
		std::cerr<<"can't read traceLog\n";
		exit ( 1 );		
	}
	nodeValue = root [ "errorLog" ];
	if ( not nodeValue.isNull() ){
        std::cout<<"errorLog="
            <<nodeValue.asString()
            <<std::endl;
                configTcpFile.errorLog = ( bool ) strcmp ( nodeValue.asString().c_str() , "false" );
	}else{
		std::cerr<<"can't read errorLog\n";
		exit ( 1 );
	}
	nodeValue = root [ "log" ];
	if ( not nodeValue.isNull() ){
		std::cout<<"log="
			<<nodeValue.asString()<<'\n';
		configTcpFile.log = ( bool ) strcmp ( nodeValue.asString().c_str() , "false" );
	}else{
		std::cerr<<"can't read log\n";
		exit ( -1  );

	}
}

LoadConfig::LoadConfig(){}
LoadConfig::~LoadConfig(){
	try{
		configFileHandler.close();
	}
	catch ( std::exception &e ){
		std::cerr<<"exception caught "<<e.what()<<std::endl;
	}
}

