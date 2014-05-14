/*
 * =====================================================================================
 *
 *       Filename:  newpacket.cpp
 *
 *    Description:  all the codes those are db related on creating new packet instance by user thnat will act as an original packets.
 *
 *        Version:  1.0
 *        Created:  Monday 09 December 2013 12:20:06  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy (), 
 *   Organization:  Cognizant Technological solutions
 *
 * =====================================================================================
 */
#include "newpacket.hpp"
#include "../newpacketDb.hpp"
#include <sstream>
#include <iostream>
#include <sqlite3.h>
#include <cstdlib>
#include "../../STRUCTURE/database_structure.hpp" // for variable dbCredentials;
using namespace std;
using namespace createPacketQuery;
GenarateRawPacketQuery::GenarateRawPacketQuery(){}
GenarateRawPacketQuery::~GenarateRawPacketQuery(){}

//function that will fetch a whole conversation from database regarding to conversation iD
actSeriesStruct * GenarateRawPacketQuery::getChunkPackets ( int conversationId ){
	int noPackets;
	actSeriesStruct *fetchedConversation;
	std::string queryString;
	sqlite3_stmt * statement;
        //have to know no of packets available for this conversation
        queryString = "select count ( * ) from PACKET_"+scenInfo.scenarioName +" where CONVERSATION_ID = "+static_cast <std::ostringstream *> ( & ( std::ostringstream () <<conversationId ) )->str()+";";
	std::cout<<"Query String : "<<queryString<<std::endl;
        if ( sqlite3_prepare ( dbCredentials.db , queryString.c_str() , -1 , &statement , 0 ) == SQLITE_OK ){
		if ( sqlite3_step( statement ) !=  SQLITE_ROW ) return NULL;
		noPackets = sqlite3_column_int ( statement , 0 );
		std::cout<<" no of packets  = "<<noPackets <<std::endl;
	}
//	sqlite3_finalize ( statement );
        sqlite3_reset( statement);
	try {
		fetchedConversation = new actSeriesStruct();
                fetchedConversation->converationId = conversationId;
                fetchedConversation ->noOfPacket = noPackets ;
		fetchedConversation->actRawData = new actRawDataStruct [ noPackets ];
	}
	catch ( std::bad_alloc &ba ){
//		std::cout<"exception caught at newpacket.cpp "<<ba.what()<<std::endl;
		return NULL;
		
	}
	queryString.clear();
        queryString = "SELECT PACKET_NO , APPDB  , LENGTH , DATA FROM PACKET_"+scenInfo.scenarioName+ " where CONVERSATION_ID = ? and LENGTH > 0";
        if ( sqlite3_prepare ( dbCredentials.db , queryString.c_str() , -1 , &statement , 0 ) != SQLITE_OK ){
		return NULL;
	}
	sqlite3_bind_int ( statement , 1 , conversationId );
	int currentFetchedNumber = -1;
//	int rowCount = -1;
	while ( ( sqlite3_step ( statement ) ) == SQLITE_ROW ){
		fetchedConversation->actRawData [ ++currentFetchedNumber ].packetNumber = sqlite3_column_int( statement , 0 );
		fetchedConversation->actRawData [ currentFetchedNumber ].appServer = sqlite3_column_int ( statement , 1);
		fetchedConversation->actRawData [ currentFetchedNumber ].length = sqlite3_column_int ( statement , 2 );
		try {
			fetchedConversation->actRawData [ currentFetchedNumber ].data = new char [ 5024 ];
		}
		catch ( std::bad_alloc &ba ){
			std::cout<<ba.what()<<std::endl;
		}
                memcpy (fetchedConversation->actRawData [ currentFetchedNumber ].data , ( char * ) sqlite3_column_blob ( statement , 3 ), fetchedConversation->actRawData [ currentFetchedNumber ].length );
		//no need to consider data coming from app of size 0
		//because those are acknowledge data
		if ( (sqlite3_column_bytes ( statement , 3 ) <= 0 ) && ( fetchedConversation->actRawData [ currentFetchedNumber ].appServer == 1 ) ) currentFetchedNumber --;
	}
	sqlite3_finalize ( statement  );
        fetchedConversation->noOfPacket = currentFetchedNumber ;
	return fetchedConversation ;
	
}


conPacketNo * GenarateRawPacketQuery::getAssignedConPackNo(){
    std::ofstream file2( "log.log");
    file2<<"exit\n";


   conPacketNo *conpacketTemp;
    try{
        conpacketTemp = new conPacketNo ;
    }
    catch ( std::bad_alloc &ba){
        std::cout<<"exception cgt"<<ba.what()<<std::endl;
    }
//    sqlite3_close(dbCredentials.db);
//    initProject::Project a ;//= new initProject::Project();
//    a.createDb();


    //query to select the data from tables.
    sqlite3_stmt *statement;
    //const char* str = "select max ( PACKET_NO ) , max ( CONVERSATION_ID )from PACKET_q;";
    //scenarioInformation *allScenarioInformation;
    //int res;
    std::string Statement ="select max ( PACKET_NO ) , max ( CONVERSATION_ID )from PACKET_"+scenInfo.scenarioName+";";
    //std::cout<<"query statement="<<Statement<<std::endl;
    //std::cout<<"sqlite3 prepare="<<sqlite3_prepare ( dbCredentials.db , Statement.c_str() , -1 , &statement , 0 )<<std::endl;
    try{
        //NSLog(@"Error: %s", sqlite3_errmsg(_markerDatabase));
       // std::ofstream file2( "log.log");
        //sqlite3_free(dbCredentials.db);
        file2<<"db cred: "<< dbCredentials.databaseName<<" "<< dbCredentials.databasePath<<std::endl
                <<"statement char: "<<Statement.c_str()<<std::endl
                <<"statement str: "<<Statement<<std::endl;
        //file2<<"sqlite error: "<<sqlite3_errmsg(dbCredentials.db)<<std::endl;
       // file2<<"sqlite statement: "<<sqlite3_prepare( dbCredentials.db , Statement.c_str() , -1 , &statement , 0 );
        //file2<<"sqlite error: "<<sqlite3_errmsg(dbCredentials.db)<<std::endl;
        file2<<"statement: "<<statement<<std::endl;
       // sqlite3_free(statement);
        if ( sqlite3_prepare( dbCredentials.db , Statement.c_str() , -1 , &statement , 0 ) == SQLITE_OK  ){
            if ( sqlite3_step ( statement ) != SQLITE_ROW ){
                std::cout<<"can't fetch max conversationId && PacketNo\n";
                sqlite3_finalize(statement);
                exit(0);
            }
            conpacketTemp->packetNo = sqlite3_column_int ( statement , 0 );
            file2<<"packet no="<<conpacketTemp->packetNo<<std::endl;
            conpacketTemp->conversationNo =  sqlite3_column_int ( statement , 1 );
             sqlite3_finalize(statement);
            return conpacketTemp;

            }
            }
            catch ( std::exception &e ){
                std::cerr<<"exception cght"<<e.what()<<std::endl;

            }
    return NULL;
}


bool GenarateRawPacketQuery::insertGeneratedPacket( actSeriesStruct *& conversationPacket ){
    std::cout<<"GenarateRawPacketQuery::insertGeneratedPacket\n";
    int rc;
    std::string queryString = "insert into PACKET_SETTING_"+scenInfo.scenarioName+" ( CONVERSATION_ID , PACKET_NO , SEQ_NO , ACK_NO , RAW_DATA , STATUS ) values ( ?, ?, ? ,? , ? , ? ) ";
    std::cout<<"query string to insert datat into PACKET_SETTING\t"<<queryString<<std::endl;
    sqlite3_stmt *pStmt , *statement;
    try{
        if (  sqlite3_prepare ( dbCredentials.db , queryString.c_str() , -1 , &pStmt , 0) != SQLITE_OK ){
            std::cerr<<"initializing error\n";
            return false;
        }
        sqlite3_bind_int ( pStmt , 1 , conversationPacket->converationId);
        sqlite3_bind_int ( pStmt , 2 , conversationPacket->actRawData[ 0 ].packetNumber );
        sqlite3_bind_int ( pStmt , 3 , conversationPacket->seqNumber );
        sqlite3_bind_int ( pStmt , 4 , conversationPacket->seqNumber );
        sqlite3_bind_blob ( pStmt , 5 ,conversationPacket->actRawData [ 0 ].data , conversationPacket->actRawData[ 0 ].length , SQLITE_STATIC );
//have to insert dissected query as well
        if ( conversationPacket->actRawData [ 0 ].appServer ){
            sqlite3_bind_int ( pStmt , 6 , 1 );
        }
        else {
            sqlite3_bind_int ( pStmt , 6 , 0 );
        }
        std::cout<<"conversationId"<<conversationPacket->converationId
                <<"packNO"<<conversationPacket->actRawData [ 0].packetNumber
                <<"seq"<<conversationPacket->seqNumber
                <<"blob data"<<conversationPacket->actRawData [ 0].data<<std::endl;

       // std::cout<<"PSTATEM"<<pStmt<<std::endl;
        rc = sqlite3_step ( pStmt );

        assert ( rc != SQLITE_ROW );
        if ( sqlite3_finalize( pStmt ) != SQLITE_OK ){
            std::cerr<<"can't insert value\n";
            sqlite3_finalize(pStmt);
            return 0;

        }
        std::cout<<"Successfuly inserted"<<std::endl;
        //noe insert information into PACKET
        queryString.clear();
        queryString = "INSERT INTO PACKET_"+scenInfo.scenarioName+" ( CONVERSATION_ID , PACKET_NO , SEQ_NO , ACK_NO, DATA , APPDB , LENGTH ) VALUES ( ? , ? , ? , ? , ? , ? , ? ) ;";
	for ( int i = 0 ; i<conversationPacket->noOfPacket ; ++i ){
		do{
			if (  (sqlite3_prepare ( dbCredentials.db , queryString.c_str() , -1 , &statement , 0 ) ) != SQLITE_OK ){
				std::cerr<<"can't initialize database";
				return false;
				
			}
			sqlite3_bind_int( statement , 1  , conversationPacket->converationId );
                        sqlite3_bind_int( statement , 2 , conversationPacket->actRawData[ 0 ].packetNumber + i );
			sqlite3_bind_int( statement , 3 , conversationPacket->seqNumber );
			sqlite3_bind_int( statement , 4 , conversationPacket->seqNumber); // acknowledge no not needed
                        sqlite3_bind_blob( statement, 5, conversationPacket->actRawData[ i ].data  , conversationPacket->actRawData[ i ].length  , SQLITE_STATIC);
                        sqlite3_bind_int( statement , 6 , conversationPacket->actRawData [ i ].appServer );
                        sqlite3_bind_int( statement , 7 , conversationPacket->actRawData [ i ].length  );
			rc = sqlite3_step ( statement ) ;
			assert ( rc != SQLITE_ROW );
			rc = sqlite3_finalize( statement);
			
		}while ( rc == SQLITE_SCHEMA );
		if ( rc != SQLITE_OK ){
			std::cerr<<"can't insert blob data into PACKET"<<std::endl;

			return false;
			
		}
	}
	std::cout<<"successfully inserted blov dat into PACKET"<<std::endl;




	return true;
    }
    catch ( std::exception &e ){
        std::cerr<<"exception cgt"<<e.what()<<std::endl;

        return false;

    }
}

//function that will take input as a conversation id and will delete all the packets from
//PaCKET_scenarioname and PACKET_SETTING_scenario name, where scenario name is variable.

bool GenarateRawPacketQuery::deletePacketRegardingConversationId( int conversationId ){
    std::cerr<<"insie final update query place\n";
        std::string sqlStatement = "DELETE from PACKET_SETTING_"+scenInfo.scenarioName+" where CONVERSATION_ID = " +	static_cast < std::ostringstream * >( &( std::ostringstream () << conversationId ) ) ->str()+ ";" ;
        std::string sqlStatement2 = " DELETE FROM PACKET_" + scenInfo.scenarioName + " where CONVERSATION_ID = " + static_cast < std::ostringstream *> ( & ( std::ostringstream() << conversationId ) ) ->str()+ ";";


        char *zErrMsg= 0;
        char *zErrMsg2= 0;
        return ( ( func::executeStatus ( sqlite3_exec(dbCredentials.db, sqlStatement.c_str() , func::callback, 0, &zErrMsg )  , zErrMsg))  && ( func::executeStatus ( sqlite3_exec(dbCredentials.db, sqlStatement2.c_str() , func::callback, 0, &zErrMsg2 )  , zErrMsg2) ) );

}

