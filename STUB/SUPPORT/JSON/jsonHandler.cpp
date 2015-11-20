/*
 *o =====================================================================================
 *
 *       Filename:  jsonHandler.cpp
 *
 R*    Description:  this code help to read and write dissector data to a JSON file , for user friendly input output
 *
 *        Version:  1.0
 *        Created:  Tuesday 04 March 2014 04:35:47  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy (), 
 *   Organization:  Cognizant Technological solutions
 *
 * =====================================================================================
 */

#include "jsonHandler.hpp"
bool Json::flagForGenerateQuery = false ; // flag that indicate -- new query or not.

std::fstream Json::JsonHandler::fileHandler ;

bool Json::JsonHandler::writeDataJson ( queryPacketJson * queryStruct , std::string fileName ){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<'\n';
	try{
		fileHandler.open( fileName.c_str() ,std::ios::out );
		if ( ! fileHandler.is_open() ){
			std::cerr<<__FUNCTION__<<"can't open file "<<fileName<<'\n';
			return false;
		}
		Json::Value event, event2;
		event["Query"]=queryStruct->query;
		for ( _colDetails::iterator it = queryStruct->colNames.begin() ; it !=queryStruct->colNames.end() ; ++ it )
			event["dataset" ] [ "columns" ] = it->second;
		// fileHandler<<event<<std::endl;
		int rowCount = 0;
                for ( _colInfo::iterator it = queryStruct->colInfo.begin() ; it != queryStruct->colInfo.end() ; ++ it){
			++rowCount;
                        std::string columNo = "column+";
                        //static_cast<std::ostringstream*>( &(std::ostringstream() << it->first )->str())
			event["Row"] [ static_cast<std::ostringstream*>( &(std::ostringstream() << rowCount ) )->str() ] = it->second;
		}
		// fileHandler<<event2<<std::endl;
		Json::Value event3;
		event["Rowcount"] = rowCount;
		// fileHandler<<event3<<std::endl;
		fileHandler<<event<<'\n';
		event.clear();
		event2.clear();
		event3.clear();
	}
	catch ( std::exception &e ){
		std::cerr<<__FUNCTION__<<"exception cgt \t"<<e.what()<<'\n';
	}
	fileHandler.close();
	return true;
}

bool Json::JsonHandler::readDataJson ( std::string inputFileName ){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<'\n';
	queryPacketJson packetQuery ;
	bool parsingSuccessful;
	try{
		fileHandler.open ( inputFileName.c_str() );
		if( !fileHandler.is_open() ){
			std::cerr<<__FUNCTION__<<"cabt open file for JSON persing\n";
                        return false;
		}
		Json::Value root;
		Json::Reader reader;
		if ( !reader.parse( fileHandler , root ) ){
			std::cerr<<__FUNCTION__<<"failed to parse JSON file\n";
                        return false;
		}
		Json::Value nodeValue = root ["Query"];
		if ( not nodeValue.isNull() ){
			std::cout<<__FUNCTION__<<"Json persing Read data= "<<
				nodeValue.asString()<<'\n';
			packetQuery.query =nodeValue.asString();
		}
		else {
			std::cerr<<__FUNCTION__<<"cant read JSON persing value Query\n";
			exit ( -1 );
		}
                nodeValue = root ["Rowcount"];
		int rowCount = 0;
		if ( not nodeValue.isNull() ){
			std::cout<<__FUNCTION__<<"Json persing read data for Rowcount="
				<<nodeValue.asInt()<<'\n';
			rowCount = nodeValue.asInt();
                        colByColDataTogether.totalRow = rowCount;
		}
		else{
			std::cerr<<__FUNCTION__<<"cant read Json for Rowcount\n";
		}
                for ( int i = 1 ; i<=rowCount ; i++){
                        nodeValue = root ["Row"] [static_cast<std::ostringstream*>( &(std::ostringstream() << i) )->str()];
			if ( not nodeValue.isNull() ){
                                std::cout<<__FUNCTION__<<"Json persing for read data [ Row] [ "<<i<< " ] "<<nodeValue.asString()<<std::endl;
				packetQuery.colInfo.insert ( std::make_pair ( i ,nodeValue.asString()  ) );
				
			}
			else{
				std::cerr<<__FUNCTION__<<"Json read error for [ Row ]["<<i <<" ]\n";
				exit ( 1 );
			}
		}
	}
	catch ( std::exception &e ){
		std::cerr<<__FUNCTION__<<"exception cgt at Json Read "<<e.what()<<std::endl;
                return false;
	}
	QueryPacket = packetQuery;
        return true;
}

int Json::JsonHandler::generateColByColData ( queryPacketJson * queryPacket ){
	int noRow = 0;
	try{
		colByColDataTogether.query = queryPacket->query ;
		int colByColCount = 0;
		for ( _colInfo::iterator it = queryPacket->colInfo.begin() ; it != queryPacket->colInfo.end() ; ++it ){
                    noRow ++;
			std::string valueTemp ;

			valueTemp.clear();
                        valueTemp = it->second;
                        colByColDataTogether.totalSize +=valueTemp.size();
			size_t pos = 0;
			std::string token;
			while ( ( pos = valueTemp.find( ";" ) )  != std::string::npos ) {
                colByColDataTogether.colInfo.insert ( std::make_pair ( ++ colByColCount , valueTemp.substr ( 0, pos ) ));
                valueTemp.erase ( 0 , pos + 1 ) ;
				/*
				token = s.substr(0, pos);
				std::cout << token << std::endl;
				s.erase(0, pos + delimiter.length());
				*/
			}
		}
	}
	catch ( std::exception &e){
		std::cerr<<__FUNCTION__<<"exception cgt at generateColByColData\n";
                exit(1 );
                return noRow;

	}
        std::cout<<__FUNCTION__<<"query ="<<colByColDataTogether.query<<std::endl;

        return noRow;


}

