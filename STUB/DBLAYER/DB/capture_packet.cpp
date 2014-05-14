/*
 * =====================================================================================
 *
 *       Filename:  capture_packet.cpp
 *
 *    Description:  implementation of capture.hpp
 *
 *        Version:  1.0
 *        Created:  Wednesday 06 November 2013 01:53:32  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy (),
 *   Organization:  Cognizant Technological solutions
 *
 * =====================================================================================
 */

#include "capture_packet.hpp"
using namespace std;
captureQuery::CaptureDbSettingQuery::CaptureDbSettingQuery(){}
int captureQuery::rc;
int captureQuery::packetId = 0;
char *captureQuery::sql;
char *captureQuery::zErrMsg;
captureQuery::CaptureDbSettingQuery::~CaptureDbSettingQuery(){}

bool captureQuery::CaptureDbSettingQuery::insertCaptureConfiguration(  ){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	std::string sqlStatement = " INSERT INTO SCENARIO ( S_NAME , CATAGORY , PROTOCOL , SERVER_IP , PORT )"\
				    " VALUES ( "+ func::quotesql(scenInfo.scenarioName) + ","+ func::quotesql(scenInfo.catagory) + ","+ func::quotesql(scenInfo.protocol ) +","+func::quotesql( scenInfo.server)+","+scenInfo.portNo + ");";
	return (  ( func::executeStatus ( sqlite3_exec(dbCredentials.db, sqlStatement.c_str() , func::callback, 0, &zErrMsg )  , zErrMsg)) & ( createCaptureTable() ) );
}



bool captureQuery::CaptureDbSettingQuery::createCaptureTable( ){
	std::cout<<"FUNCTIONL:"<<__FUNCTION__<<std::endl;
	std::string sqlStatement="CREATE TABLE PACKET_SETTING_"+scenInfo.scenarioName  +" ( CONVERSATION_ID INTEGER PRIMARY KEY NOT NULL , PACKET_NO INTEGER NOT NULL , SEQ_NO INTEGER NOT NULL , ACK_NO INTEGER NOT NULL ,"\
				  " RAW_DATA BLOB , STATUS INTEGER , QUERY_TYPE TEXT , QUERY TEXT );";
	std::cout<<__FUNCTION__<<"sqlStatement="<<sqlStatement<<std::endl;
	std::string sqlStatement2 = "CREATE TABLE PACKET_"+ scenInfo.scenarioName +" ( CONVERSATION_ID INTEGER  NOT NULL ,PACKET_NO  INTEGER NOT NULL , DATA BLOB , APPDB INTEGER ,SEQ_NO INTEGER NOT NULL , ACK_NO INTEGER NOT NULL , LENGTH INTEGER );";
	std::cout<<__FUNCTION__<<"second sql statement:"<<sqlStatement2<<std::endl;
	std::string sqlStatement3="CREATE TABLE PACKET_DB_GREETING_"+scenInfo.scenarioName  +" ( CONVERSATION_ID INTEGER PRIMARY KEY NOT NULL , PACKET_NO INTEGER NOT NULL , SEQ_NO INTEGER NOT NULL , ACK_NO INTEGER NOT NULL ,"\
				   " DB_DATA BLOB  );";
	std::cout<<__FUNCTION__<<"sqlstatement three:"<<sqlStatement3<<std::endl;
	const char *zSql = "CREATE TABLE blobs(PACKET_NO INTEGER PRIMARY KEY, RAW_DATA BLOB)";
	//sqlite3_exec(db, zSql, 0, 0, 0);
	return (  ( func::executeStatus ( sqlite3_exec(dbCredentials.db, sqlStatement.c_str() , func::callback, 0, &zErrMsg )  , zErrMsg)) &  ( func::executeStatus ( sqlite3_exec ( dbCredentials.db , sqlStatement2.c_str() , func::callback , 0 , &zErrMsg ) , zErrMsg ) ) & ( func::executeStatus ( sqlite3_exec(dbCredentials.db, sqlStatement3.c_str() , func::callback, 0, &zErrMsg )  , zErrMsg)) & ( func::executeStatus ( sqlite3_exec ( dbCredentials.db , zSql , func::callback , 0 , &zErrMsg ) , zErrMsg ) ) );
}

//construcor
captureQuery::RemoteServerQuery::RemoteServerQuery(){}
//destructor
captureQuery::RemoteServerQuery::~RemoteServerQuery(){}
// add new server information into the database
bool captureQuery::RemoteServerQuery::addNewServerInfo( void ){
	std::cout<<"FUNCTION"<<__FUNCTION__<<std::endl;
	std::string sqlStatement = " INSERT INTO SERVER_INFO ( S_NAME , CATAGORY ,  SERVER_IP , PORT )"\
				    " VALUES ( "+ func::quotesql(serverCredentials.serverName) + ","+ func::quotesql(serverCredentials.serverType) + ","+ func::quotesql(serverCredentials.serverIp ) +","+serverCredentials.serverPort + ");";
	return ( func::executeStatus ( sqlite3_exec(dbCredentials.db, sqlStatement.c_str() , func::callback, 0, &zErrMsg )  , zErrMsg));
}

//
//display all information of TABLE SERVER_INFO

serverStruct* captureQuery::RemoteServerQuery::displayServerTable( void ){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	//have to write the select query
	serverStruct * serverList;
	try{
		serverList = new serverStruct [ 10 ];
	}
	catch ( std::bad_alloc exc ){
		std::cerr<<__FUNCTION__<<"exception cgt\t"<<exc.what()<<std::endl;
	}
	return serverList;
}



//    CLASS StoreRawPacketQuery .......................................................................................................................
captureQuery::StoreRawPacketQuery::StoreRawPacketQuery(){
//	packetId = 0;
}

captureQuery::StoreRawPacketQuery::~StoreRawPacketQuery(){}

// function insert

int captureQuery::StoreRawPacketQuery::selectPacketSetting( bool appDb , rawDataStruct *rawData ){
	std::cout<<"FUNTION:"<<__FUNCTION__<<std::endl;
    sqlite3_stmt *statement;
    std::string sqlStatement ;
    if ( appDb ) // if it is a APP server Packet
        sqlStatement = "select PACKET_ID from PACKET_SETTING_"+scenInfo.scenarioName+" where SEQ_NO ="+static_cast<ostringstream*>( &(ostringstream() <<rawData->sequenceNumber) )->str() +" AND ACK_NO =+"+static_cast<ostringstream*>( &(ostringstream() << rawData->acknowledgeNumber) )->str()+" AND SERVER_STATUS = 0 AND DB_STATUS = 0";
    else
        sqlStatement = "select PACKET_ID from PACKET_SETTING_"+scenInfo.scenarioName+" where SEQ_NO ="+static_cast<ostringstream*>( &(ostringstream() <<rawData->sequenceNumber) )->str() +" AND ACK_NO =+"+static_cast<ostringstream*>( &(ostringstream() << rawData->acknowledgeNumber) )->str()+" AND SERVER_STATUS = 1 AND DB_STATUS = 0";

    //std::string sqlStatement = "select PACKET_ID from PACKET_SETTING_"+scenInfo.scenarioName+" where SEQ_NO ="+seq_no +" AND ACK_NO =+"+ack_no +" AND SERVER_STATUS = 0 AND DB_STATUS = 0";
    if ( sqlite3_prepare ( dbCredentials.db , sqlStatement.c_str() , -1 , &statement , 0 ) == SQLITE_OK ){
        int ctotal = sqlite3_column_count( statement );
        int res = 0 ;
        while ( 1 ){
            res = sqlite3_step ( statement );
            if ( res == SQLITE_ROW ){
                return true ;
                for ( int i=0 ; i<ctotal ; i++ ){
                    string s = ( char * ) sqlite3_column_text ( statement , i );
                    return ( atoi ( s.c_str() ) );
                }
                std::cout<<endl;
            }
            if ( res == SQLITE_DONE || res==SQLITE_ERROR ){
                std::cout <<"done"<<std::endl;
                return 0;
            }
        }
    }
    return false;
}

//
//update packet settingt for function packet_handler ()
//

bool captureQuery::StoreRawPacketQuery::updatePacketSettingApp (  bool appDb , int packetId , int status , rawDataStruct *rawData ){
    std::string sqlStatement ;
    if ( appDb ){ //if app
        sqlStatement = "UPDATE PACKET_SETTING_"+scenInfo.scenarioName+" SET SERVER_STATUS ="+static_cast<ostringstream*>( &(ostringstream() << status ) )->str()+", NO_APP_DATA = NO_APP_DATA + 1 , SEQ_NO ="+static_cast<ostringstream*>( &(ostringstream() <<rawData->sequenceNumber) )->str()+ " , ACK_NO ="+static_cast<ostringstream*>( &(ostringstream() << rawData->acknowledgeNumber) )->str()+" WHERE PACKET_ID ="+ static_cast<ostringstream*>( &(ostringstream() << packetId ) )->str()+" ;";
    }
    else { // DB
        sqlStatement = "UPDATE PACKET_SETTING_"+scenInfo.scenarioName+" SET DB_STATUS ="+static_cast<ostringstream*>( &(ostringstream() << status ) )->str()+", NO_DB_DATA = NO_DB_DATA + 1, SEQ_NO ="+static_cast<ostringstream*>( &(ostringstream() <<rawData->sequenceNumber) )->str()+ " , ACK_NO ="+static_cast<ostringstream*>( &(ostringstream() << rawData->acknowledgeNumber) )->str()+" WHERE PACKET_ID ="+ static_cast<ostringstream*>( &(ostringstream() << packetId ) )->str()+" ;";
    }
    std::cout<<sqlStatement<<std::endl;

//    return ( func::executeStatus ( sqlite3_exec(db_credentials.db, sqlStatement.c_str() , func::callback, 0, &zErrMsg )  , zErrMsg));
return false;

}

//update the packet_setting with the value of query( string )

bool captureQuery::StoreRawPacketQuery::updatePacketSettingApp( queryData *& queryArray , int arraySize ){
    int currentPacket = -1;
    std::string sqlStatement ;
    while ( ++currentPacket < arraySize ){
        std::cout<<"current pack no="<<queryArray [currentPacket ].packetNo<<std::endl;
        sqlStatement = "UPDATE PACKET_SETTING_"+scenInfo.scenarioName+" SET QUERY_TYPE ="+func::quotesql ( queryArray [currentPacket ].queryType )+" , QUERY ="+ func::quotesql ( queryArray [currentPacket ].query )+" WHERE PACKET_NO ="+ static_cast<ostringstream*>( &(ostringstream() << queryArray [currentPacket ].packetNo ) )->str()+" ;";
        std::cout<<"update query="<<sqlStatement<<std::endl;
        //func::executeStatus ( sqlite3_exec(db_credentials.db, sqlStatement.c_str() , func::callback, 0, &zErrMsg )  , zErrMsg )  ;
         func::executeStatus ( sqlite3_exec(dbCredentials.db, sqlStatement.c_str() , func::callback, 0, &zErrMsg )  , zErrMsg);
        sqlStatement.clear();
        std::cout<<"@@@@="<< queryArray [currentPacket ].query<<std::endl;
    }
    return true;

}


int captureQuery::StoreRawPacketQuery::insertPacketSetting( bool serverDb , int conversationId , int packetNumber ,rawDataStruct *rawData){
    captureQuery::packetId ++;
    std::string data="will contail raw data";
    //data.append ( reinterpret_cast<const char*>(rawData.data) );
    std::cout<<" data = "<<data<<std::endl;
    std::cout<<"Packet id = "<<captureQuery::packetId;

   // std::string sqlStatement ;
    //edited on 29_11
    std::string queryString = "insert into PACKET_SETTING_"+scenInfo.scenarioName+" ( CONVERSATION_ID , PACKET_NO , SEQ_NO , ACK_NO , RAW_DATA , STATUS ) values ( ?, ?, ? ,? , ? , ? ) ";

    sqlite3_stmt *pStmt;
   // do{
	    int rc = sqlite3_prepare ( dbCredentials.db , queryString.c_str() , -1 , &pStmt , 0);
	    if ( rc != SQLITE_OK ){
		    std::cerr<<"initializing error "<<queryString<<std::endl;
                    return 0;
	    }
	    sqlite3_bind_int ( pStmt , 1 , conversationId );
	    sqlite3_bind_int ( pStmt , 2 , packetNumber );
	    sqlite3_bind_int ( pStmt , 3 , rawData->sequenceNumber );
            sqlite3_bind_int ( pStmt , 4 , rawData->acknowledgeNumber );
            sqlite3_bind_blob ( pStmt , 5 ,rawData->data , rawData->length , SQLITE_STATIC );
	    if ( serverDb )
		    sqlite3_bind_int ( pStmt , 6 , 1 );
	    else 
		    sqlite3_bind_int ( pStmt , 6 , 0 );

	    rc = sqlite3_step ( pStmt );
	    assert ( rc != SQLITE_ROW );
	    rc = sqlite3_finalize( pStmt );
	    
 //   }while ( rc != SQLITE_SCHEMA );

    if ( rc != SQLITE_OK ){
	    std::cerr<<"can't insert value\n";
            return 0;
    }
    std::cout<<"Successfuly inserted"<<std::endl;


    return 1;

}

//function to insert raw data into PACKEt
bool captureQuery::StoreRawPacketQuery::insertPacket( bool appDb , int conversationId , int packetNumber , rawDataStruct *rawData){
    std::string sqlStatement;
     sqlite3_stmt *statement;
    int applicationDb = 0 , rc ;
    if ( appDb ) // packet coming from application server
        applicationDb = 1;
    sqlStatement = "INSERT INTO PACKET_"+scenInfo.scenarioName+" ( CONVERSATION_ID , PACKET_NO , SEQ_NO , ACK_NO, DATA , APPDB , LENGTH ) VALUES ( ? , ? , ? , ? , ? , ? , ? ) ;";
    do{
    if (  (sqlite3_prepare ( dbCredentials.db , sqlStatement.c_str() , -1 , &statement , 0 ) ) != SQLITE_OK ){
        std::cerr<<"can't initialize database";
        return false;
    }
    sqlite3_bind_int( statement , 1  , conversationId);
    sqlite3_bind_int( statement , 2 , packetNumber );
    sqlite3_bind_int( statement , 3 , rawData->sequenceNumber );
    sqlite3_bind_int( statement , 4 , rawData->acknowledgeNumber);
    sqlite3_bind_blob( statement, 5, rawData->data , rawData->length , SQLITE_STATIC);
    sqlite3_bind_int( statement , 6 , applicationDb );
    sqlite3_bind_int( statement , 7 , rawData->length );
    rc = sqlite3_step ( statement ) ;
    assert ( rc != SQLITE_ROW );
    rc = sqlite3_finalize( statement);
    }while ( rc == SQLITE_SCHEMA );
    if ( rc != SQLITE_OK ){
        std::cerr<<"can't insert blob data into PACKET"<<std::endl;
        return false;
    }
    std::cout<<"successfully inserted blov dat into PACKET"<<std::endl;
    return true;



}



bool captureQuery::StoreRawPacketQuery::insertDbGreeting ( int conversationId , int packetNumber , rawDataStruct *rawData ){
    std::string data="db greeting";
    std::string sqlStatement = "INSERT INTO PACKET_DB_GREETING_"+scenInfo.scenarioName+" ( CONVERSATION_ID , PACKET_NO , SEQ_NO , ACK_NO, DB_DATA ) VALUES ("+ static_cast < ostringstream * >( &( ostringstream () << conversationId ) ) ->str() +","+static_cast <ostringstream*>( &(ostringstream ()<< packetNumber ) )->str() +","+static_cast<ostringstream*>( &(ostringstream() << rawData->sequenceNumber ) )->str()+","+static_cast <ostringstream *> ( & ( ostringstream () << rawData->acknowledgeNumber) )->str() +"," +func::quotesql( data )+");";
    return ( func::executeStatus ( sqlite3_exec(dbCredentials.db, sqlStatement.c_str() , func::callback, 0, &zErrMsg )  , zErrMsg));
}


//function for geting all the packets from PACKET_SETTING_ for a certain scenario.


actRawDataStruct * captureQuery::StoreRawPacketQuery::selectPacketSetting ( ){
	int noPackets;
	actRawDataStruct *rawDataArray;
	std::string queryString;
	sqlite3_stmt *sqlStatement;
	queryString = "select count ( * ) from PACKET_SETTING_"+scenInfo.scenarioName +";";
	std::cout<<"query string  "<<queryString <<std::endl;
    if ( sqlite3_prepare ( dbCredentials.db , queryString.c_str() , -1 , &sqlStatement , 0 ) != SQLITE_OK ){
        return NULL;
    }
    else {
        if ( sqlite3_step ( sqlStatement ) != SQLITE_ROW ) return NULL;
        else
            noPackets = sqlite3_column_int ( sqlStatement , 0 );
            
            }

            sqlite3_finalize ( sqlStatement );
            try{
                rawDataArray = new actRawDataStruct  [ noPackets + 1  ];
            }
            catch ( std::bad_alloc &ba ){
                std::cerr<<"exception cought"<<ba.what()<<std::endl;
                return NULL;
            }
            queryString.clear();
            queryString = "SELECT PACKET_NO , RAW_DATA , STATUS from PACKET_SETTING_"+scenInfo.scenarioName + ";";
            if ( sqlite3_prepare ( dbCredentials.db , queryString.c_str() , -1 , &sqlStatement , 0 ) != SQLITE_OK ){
                return NULL;
            }
            int currentPacket = -1;
            while ( ( sqlite3_step ( sqlStatement ) ) == SQLITE_ROW ){
                rawDataArray [ ++currentPacket ].packetNumber = sqlite3_column_int ( sqlStatement , 0 );
                rawDataArray [ currentPacket ].length = sqlite3_column_bytes ( sqlStatement , 1 );
                rawDataArray [ currentPacket ].appServer = sqlite3_column_int( sqlStatement , 2);
                //get memory for storing data part
                try {
                    rawDataArray [ currentPacket ].data = new char [ rawDataArray [ currentPacket ].length + 1 ];
                    memcpy ( rawDataArray [ currentPacket ].data , ( char * ) sqlite3_column_blob ( sqlStatement , 1 ) , rawDataArray[ currentPacket ].length );
                }
                catch ( std::bad_alloc &ba ){
                    std::cerr<<"cought exception "<<ba.what()<<std::endl;
                }

            }
            rawDataArray [ ++currentPacket ].packetNumber = -999;
            rawDataArray [ currentPacket ].length = -999;
            return rawDataArray;
}






