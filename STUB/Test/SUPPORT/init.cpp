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
 *         Author:  SUMAN ROY (), email.suman.roy@gmail.com
 *   Organization:  SELF 
 *
 * =====================================================================================
 */

#include "init.hpp"



//init method that will be frst called from main

bool init(){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";


	//Register mysql protocol
        Mysql::initialize();
	

	//register ldap protocol
	Ldap::initialize();
        initDataStructure();

        return true;

}
//delete all the element 
void finishingTouch(){
	proto::_protoMap::iterator    protoMapIterator;
	for ( protoMapIterator = proto::protoMap.begin() ; protoMapIterator != 
			proto::protoMap.end() ; ++ protoMapIterator ){
		try{
			delete [] (protoMapIterator->second).first ;
			delete (protoMapIterator->second).second;
		}
		catch ( std::exception &e ){
			std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "
				<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateT\
				ime ["<<__DATE__<<"_"<<__TIME__<<"]Exception"
				<<e.what()<<'\n';
			exit ( 0 );
		}
	}


}


std::ifstream LoadConfig::configFileHandler;
void LoadConfig::initConfig(){
	
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	Json::Value     root;   // will contains the root value after parsing.
	Json::Reader    reader;
	try{
		configFileHandler.open("../CONFIG/tcpstub.config", std::ios::in);
	}
	catch ( std::ifstream::failure &e){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"]Exception"<<e.what()<<std::endl; 
		exit ( 0);
		
	}
        if ( !reader.parse( configFileHandler , root ) ){
		std::cerr  << "Failed to parse configuration\n";
		exit ( 1 );
		
	}
	//read the JSON value from .json file
	Json::Value nodeValue = root [ "traceLog" ];
	if ( not nodeValue.isNull() ){
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"]"<<"traceLog= "
			<<nodeValue.asString()<<'\n';
		configTcpFile.traceLog =( bool )strcmp( nodeValue.asString().c_str(), 
				"false" );
		
	}else{
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"]"<<"can't read traceLog\n";
		exit ( 1 );		
	}
	nodeValue = root [ "errorLog" ];
	if ( not nodeValue.isNull() ){
        std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"]"<<"errorLog="
            <<nodeValue.asString()
            <<std::endl;
                configTcpFile.errorLog = ( bool ) strcmp 
			( nodeValue.asString().c_str() , "false" );
	}else{
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"]"<<"can't read errorLog\n";
		exit ( 1 );
	}
	nodeValue = root [ "log" ];
	if ( not nodeValue.isNull() ){
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"]"<<"log="
			<<nodeValue.asString()<<'\n';
		configTcpFile.log = ( bool ) strcmp 
			( nodeValue.asString().c_str() , "false" );
	}else{
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__
			<<"_"<<__TIME__<<"]"<<"can't read log\n";
		exit ( -1  );

	}
	nodeValue = root ["MYSQL"];
	if ( not nodeValue.isNull () ) {
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"]"<<nodeValue.asInt()<<'\n';
		if ( proto::ports.insert( std::make_pair <  STUB_INT , std::string > 
					(  nodeValue.asInt () , "MYSQL") ).second ) 
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
				<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
				<<__TIME__<<"]"<<"INSERTED MYSQL INTO MAP\n";
	}else 	
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"]"<<"can't read MYSQL\n";
	
	nodeValue = root [ "LDAP" ];
	if ( not nodeValue.isNull () ) {
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"]"<<nodeValue.asInt()<<'\n';
		if ( proto::ports.insert( std::make_pair <STUB_INT ,  std::string  > 
					( nodeValue.asInt (), "LDAP" ) ).second ) 
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "
				<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["
				<<__DATE__<<"_"<<__TIME__<<"]"<<"INSERTED MYSQL INTO MAP\n";
	}else std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"]"<<"Cant read LDAp\n";
		

}

LoadConfig::LoadConfig(){}
LoadConfig::~LoadConfig(){
	try{
		configFileHandler.close();
	}
	catch ( std::exception &e ){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"]"<<"exception caught "<<e.what()<<std::endl;
	}
}

