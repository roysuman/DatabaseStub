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
 *   Organization:  SELF
 *
 * =====================================================================================
 */

#include "../include/jsonHandler.hpp"
bool Json::flagForGenerateQuery = false ; // flag that indicate -- new query or not.

std::fstream Json::JsonHandler::fileHandler ;

bool Json::JsonHandler::writeDataJson ( queryPacketJson * queryStruct ,
	       	std::string fileName ){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"]\n";

		Json::Value    event3;
		std::string    columNo;
		STUB_INT       rowCount;
		Json::Value    event, event2;

		rowCount = 0;
	try{
		fileHandler.open( fileName.c_str() ,std::ios::out );
		if ( ! fileHandler.is_open() ){
			std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "
				<<__FUNCTION__<<"] Line ["<<__LINE__
				<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"]can't open file "<<fileName<<'\n';
			return false;
		}
		event["Query"]=queryStruct->query;
		for ( _colDetails::iterator it = queryStruct->colNames.begin() ; 
				it !=queryStruct->colNames.end() ; ++ it )
			event["dataset" ] [ "columns" ] = it->second;
                for ( _colInfo::iterator it = queryStruct->colInfo.begin() ; 
				it != queryStruct->colInfo.end() ; ++ it){
			++rowCount;
                        columNo = "column+";
			event["Row"] [ static_cast<std::ostringstream*>
				( &(std::ostringstream() << rowCount ) )->str() ] = it->second;
		}
		event["Rowcount"] = rowCount;
		fileHandler<<event<<'\n';
		event.clear();
		event2.clear();
		event3.clear();
	}
	catch ( std::exception &e ){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"] Exception"<<e.what()<<'\n';
	}
	fileHandler.close();
	return true;
}

bool Json::JsonHandler::readDataJson ( std::string inputFileName ){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	Json::Value        root;
	Json::Reader       reader;
	STUB_INT           rowCount ;
	Json::Value        nodeValue;
	queryPacketJson    packetQuery ;

	rowCount = 0;

	try{
		fileHandler.open ( inputFileName.c_str() );
		if( !fileHandler.is_open() ){
			std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
				<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
				<<__TIME__<<"] cant open file for JSON persing\n";
                        return false;
		}
		if ( !reader.parse( fileHandler , root ) ){
			std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
				<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
				<<__TIME__<<"]failed to parse JSON file\n";
                        return false;
		}
		nodeValue = root ["Query"];
		if ( not nodeValue.isNull() ){
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
				<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
				<<__TIME__<<"] Json persing Read data= "<<
				nodeValue.asString()<<'\n';
			packetQuery.query =nodeValue.asString();
		}
		else {
			std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
				<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
				<<__TIME__<<"]cant read JSON persing value Query\n";
			exit ( -1 );
		}
                nodeValue = root ["Rowcount"];
		if ( not nodeValue.isNull() ){
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
				<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
				<<__TIME__<<"]Json persing read data for Rowcount="
				<<nodeValue.asInt()<<'\n';
			rowCount = nodeValue.asInt();
                        colByColDataTogether.totalRow = rowCount;
		}
		else{
			std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
				<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
				<<__TIME__<<"] cant read Json for Rowcount\n";
		}
                for ( STUB_INT i = 1 ; i<=rowCount ; i++){
                        nodeValue = root ["Row"] [static_cast<std::ostringstream*>
				( &(std::ostringstream() << i) )->str()];
			if ( not nodeValue.isNull() ){
                                std::cout<<" File Name ["<<__FILE__<<" ] Function [ "
					<<__FUNCTION__<<"] Line ["<<__LINE__
					<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
					<<"]Json persing for read data [ Row] [ "
					<<i<< " ] "<<nodeValue.asString()<<std::endl;
				packetQuery.colInfo.insert (
					       	std::make_pair ( i ,nodeValue.asString()  ) );
				
			}
			else{
				std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "
					<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["
					<<__DATE__<<"_"<<__TIME__
					<<"] Json read error for [ Row ]["<<i <<" ]\n";
				exit ( 1 );
			}
		}
	}
	catch ( std::exception &e ){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"] EXception"<<e.what()<<std::endl;
                return false;
	}
	QueryPacket = packetQuery;
        return true;
}

STUB_INT Json::JsonHandler::generateColByColData ( queryPacketJson * queryPacket ){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	size_t         pos;
	STUB_INT       noRow;
	std::string    token;
	std::string    valueTemp;

	pos = noRow = 0;
	try{
		colByColDataTogether.query = queryPacket->query ;
		STUB_INT colByColCount = 0;
		for ( _colInfo::iterator it = queryPacket->colInfo.begin() ; 
				it != queryPacket->colInfo.end() ; ++it ){
                    noRow ++;

			valueTemp.clear();
                        valueTemp = it->second;
                        colByColDataTogether.totalSize +=valueTemp.size();
			while ( ( pos = valueTemp.find( ";" ) )  != std::string::npos ) {
                colByColDataTogether.colInfo.insert ( std::make_pair 
				( ++ colByColCount , valueTemp.substr ( 0, pos ) ));
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
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"]Exception"<<e.what()<<'\n';
                exit(1 );
                return noRow;

	}
        std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]query ="
		<<colByColDataTogether.query<<std::endl;

        return noRow;


}

