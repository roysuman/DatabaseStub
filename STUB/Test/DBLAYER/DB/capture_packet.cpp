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
 *   Organization:  SELF
 *
 * =====================================================================================
 */
#include "capture_packet.hpp"
using namespace std;
captureQuery::CaptureDbSettingQuery::CaptureDbSettingQuery(){}
STUB_INT captureQuery::rc;
STUB_INT captureQuery::packetId = 0;
STUB_CHAR *captureQuery::sql;
STUB_CHAR *captureQuery::zErrMsg;
captureQuery::CaptureDbSettingQuery::~CaptureDbSettingQuery(){}

bool captureQuery::CaptureDbSettingQuery::insertCaptureConfiguration(  ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"]\n";
	std::string sqlStatement = " INSERT INTO SCENARIO ( S_NAME , CATAGORY ,\
				    PROTOCOL , SERVER_IP , PORT )"\
				    " VALUES ( "+ func::quotesql(scenInfo.scenarioName) +
				    ","+ func::quotesql(scenInfo.catagory) + ","+
				    func::quotesql(scenInfo.protocol ) +","+
				    func::quotesql( scenInfo.server)+","+
				    scenInfo.portNo + ");";
	return (  ( func::executeStatus ( sqlite3_exec(dbCredentials.db,
					       	sqlStatement.c_str() , func::callback,
					       	0, &zErrMsg )  , zErrMsg)) &
		       	( createCaptureTable() ) );
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  createCaptureTable
 *  Description:  create tables to store captured packets
 * =====================================================================================
 */

bool captureQuery::CaptureDbSettingQuery::createCaptureTable( ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"]\n";
	std::string sqlStatement="CREATE TABLE PACKET_SETTING_"+scenInfo.scenarioName
	      	+" ( CONVERSATION_ID INTEGER PRIMARY KEY NOT NULL , PACKET_NO INTEGER\
	       	NOT NULL , SEQ_NO INTEGER NOT NULL , ACK_NO INTEGER NOT NULL ,\
		 RAW_DATA BLOB , STATUS INTEGER , QUERY_TYPE TEXT , QUERY TEXT,\
		 PROTOCOL TEXT NOT NULL , DELTA_VALUE INTEGER , DELTA_VALUE2 INTEGER );";
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"] sqlStatement="<<sqlStatement<<std::endl;
	std::string sqlStatement2 = "CREATE TABLE PACKET_"+ scenInfo.scenarioName +
		" ( CONVERSATION_ID INTEGER  NOT NULL ,PACKET_NO  INTEGER NOT NULL ,\
	       	DATA BLOB , APPDB INTEGER NOT NULL,SEQ_NO INTEGER NOT NULL , ACK_NO\
	       	INTEGER NOT NULL , LENGTH INTEGER );";
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"] second sql statement:"<<sqlStatement2<<std::endl;
	//below two tables no use
	std::string sqlStatement3="CREATE TABLE PACKET_DB_GREETING_"+
		scenInfo.scenarioName  +" ( CONVERSATION_ID INTEGER PRIMARY KEY NOT NULL\
	       	, PACKET_NO INTEGER NOT NULL , SEQ_NO INTEGER NOT NULL , ACK_NO INTEGER\
	       	NOT NULL , DB_DATA BLOB  );";
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"] sqlstatement three:"<<sqlStatement3<<std::endl;
	std::string sqlStatementForCreatingSubPackets = "create table SUB_PACKETS_"+
		scenInfo.scenarioName +"( CONVERSATION_ID INTEGER PRIMARY KEY NOT NULL\
	       	, PACKET_NO INTEGER NOT NULL , QUERY TEXT , RAW_DATA blob , isClient INTEGER);";

	const STUB_CHAR *zSql = "CREATE TABLE blobs(PACKET_NO INTEGER PRIMARY KEY, RAW_DATA BLOB)";
	//sqlite3_exec(db, zSql, 0, 0, 0);
	return (  ( func::executeStatus ( sqlite3_exec(dbCredentials.db, sqlStatement.c_str() ,
					       	func::callback, 0, &zErrMsg )  , zErrMsg)) & 
		       	( func::executeStatus ( sqlite3_exec ( dbCredentials.db ,
							       sqlStatement2.c_str() ,
							       func::callback , 0 ,
							       &zErrMsg ) , zErrMsg ) ) &
		       	( func::executeStatus ( sqlite3_exec(dbCredentials.db, 
							     sqlStatement3.c_str() ,
							     func::callback, 0,
							     &zErrMsg )  ,zErrMsg)) &
		       	( func::executeStatus ( sqlite3_exec ( dbCredentials.db , zSql ,
							       func::callback , 0 ,
							       &zErrMsg ) , zErrMsg ) ) & 
			( func::executeStatus ( sqlite3_exec ( dbCredentials.db , 
							       sqlStatementForCreatingSubPackets.c_str()
							       , func::callback , 0 , &zErrMsg )
					       	, zErrMsg ) ) );
}

//construcor
captureQuery::RemoteServerQuery::RemoteServerQuery(){}
//destructor
captureQuery::RemoteServerQuery::~RemoteServerQuery(){}
// add new server information into the database
bool captureQuery::RemoteServerQuery::addNewServerInfo( void ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"]\n";
	std::string sqlStatement = " INSERT INTO SERVER_INFO ( S_NAME ,\
				    CATAGORY ,  SERVER_IP , PORT )\
				     VALUES ( "+
				     func::quotesql(serverCredentials.serverName)
				     + ","+ 
				     func::quotesql(serverCredentials.serverType)
				     + ","+ 
				     func::quotesql(serverCredentials.serverIp )
				     +","+
				     serverCredentials.serverPort + ");";
	return ( func::executeStatus ( sqlite3_exec(dbCredentials.db, 
					sqlStatement.c_str() , 
					func::callback, 0, &zErrMsg ) 
			       	, zErrMsg));
}

//
//display all information of TABLE SERVER_INFO

serverStruct* captureQuery::RemoteServerQuery::displayServerTable( void ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"]\n";
	//have to write the select query
    serverStruct    *serverList;

    serverList = NULL;
	try{
		serverList = new serverStruct [ 10 ];
	}
	catch ( std::bad_alloc exc ){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"] exception cgt\t"<<exc.what()<<std::endl;
	}
	return serverList;
}



//    CLASS StoreRawPacketQuery .......................................................................................................................
captureQuery::StoreRawPacketQuery::StoreRawPacketQuery(){
//	packetId = 0;
}

captureQuery::StoreRawPacketQuery::~StoreRawPacketQuery(){}

// function insert

STUB_INT captureQuery::StoreRawPacketQuery::selectPacketSetting( bool appDb ,
	       	rawDataStruct *rawData ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"]\n";
    sqlite3_stmt *statement;
    std::string sqlStatement ;
    if ( appDb ) // if it is a APP server Packet
        sqlStatement = "select PACKET_ID from PACKET_SETTING_"+
		scenInfo.scenarioName+" where SEQ_NO ="+
		static_cast<ostringstream*>( &(ostringstream() 
					<<rawData->sequenceNumber) )->str()
	       	+" AND ACK_NO =+"+static_cast<ostringstream*>( &(ostringstream()
				       	<< rawData->acknowledgeNumber) )->str()+
		" AND SERVER_STATUS = 0 AND DB_STATUS = 0";
    else
        sqlStatement = "select PACKET_ID from PACKET_SETTING_"+
		scenInfo.scenarioName+" where SEQ_NO ="+
		static_cast<ostringstream*>( &(ostringstream() 
					<<rawData->sequenceNumber) )->str()
	       	+" AND ACK_NO =+"+static_cast<ostringstream*>( &(ostringstream() 
					<< rawData->acknowledgeNumber) )->str()
		+" AND SERVER_STATUS = 1 AND DB_STATUS = 0";

    //std::string sqlStatement = "select PACKET_ID from PACKET_SETTING_"+scenInfo.scenarioName+" where SEQ_NO ="+seq_no +" AND ACK_NO =+"+ack_no +" AND SERVER_STATUS = 0 AND DB_STATUS = 0";
    if ( sqlite3_prepare ( dbCredentials.db , 
			    sqlStatement.c_str() , -1 , 
			    &statement , 0 ) == SQLITE_OK ){
        STUB_INT ctotal = sqlite3_column_count( statement );
        STUB_INT res = 0 ;
        while ( 1 ){
            res = sqlite3_step ( statement );
            if ( res == SQLITE_ROW ){
                return true ;
                for ( STUB_INT i=0 ; i<ctotal ; i++ ){
                    string s = ( STUB_CHAR * ) sqlite3_column_text ( statement , i );
                    return ( atoi ( s.c_str() ) );
                }
                std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";
            }
            if ( res == SQLITE_DONE || res==SQLITE_ERROR ){
                std::cout <<"done"<<std::endl;
                return 0;
            }
        }
    }
    return false;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  getPacket
 *  Description:  get the packet from a conversation with respect to packetId
 *  method parameters: onr flag for indecating client packet or server packet 
 *  --one parameter for packet no, have to find out conversation of that packet no
 *  and have to send bach client/server packet depending on the flag value
 *  
 * =====================================================================================
 */
actRawDataStruct* captureQuery::StoreRawPacketQuery::getPacket( STUB_INT packetNo , bool flag){
	
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"]\n";
    sqlite3_stmt    *statement ;
    STUB_INT         conversationId;
	actRawDataStruct *rawDataVariable;

    rawDataVariable = NULL;
    conversationId = 0;
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__
		<<"_"<<__TIME__<<"]"<<"PACKET NO:["<<packetNo<<"]\n";
	std::string queryString = "select CONVERSATION_ID from PACKET_"
		+scenInfo.scenarioName + " where PACKET_NO ="
		+static_cast< ostringstream*>( &(ostringstream()
					<<packetNo))->str()+";";
	if ( sqlite3_prepare ( dbCredentials.db , queryString.c_str() ,
			       	-1 , &statement , 0 ) == SQLITE_OK ){
		if (  sqlite3_step ( statement ) == SQLITE_ROW ){
			conversationId = sqlite3_column_int( statement  , 0 );
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "
				<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["
				<<__DATE__<<"_"<<__TIME__<<"]"<<"Conversation ID:["
				<<conversationId<<"]\n";
			
		}
	}
	else{ 
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"] Query"<<queryString <<" failed\n";
		exit ( 1 );
	}
	queryString.clear();
	if ( flag )//client packet
	queryString= "select DATA from PACKET_"+scenInfo.scenarioName +
	       	" WHERE CONVERSATION_ID = " +
		static_cast < ostringstream*>( &(ostringstream()<<conversationId ))->str() 
		+ " AND APPDB = "+
		static_cast< ostringstream*>( &(ostringstream()<<1))->str() 
		+" and LENGTH > 5;";
	else //server packet
	queryString= "select DATA from PACKET_"+scenInfo.scenarioName 
		+ " WHERE CONVERSATION_ID = " +
		static_cast < ostringstream*>( &(ostringstream()
					<<conversationId ))->str() 
		+ " AND APPDB = 0 and LENGTH > 5;";
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__
		<<"_"<<__TIME__<<"]"<<"QueryString["<<queryString<<"]\n";
	if ( sqlite3_prepare ( dbCredentials.db , queryString.c_str() , 
				-1 , &statement , 0 ) == SQLITE_OK ){
		if ( sqlite3_step ( statement ) == SQLITE_ROW ){
			rawDataVariable = new actRawDataStruct;
			rawDataVariable->length = 
				sqlite3_column_bytes( statement , 0 );
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"]"<<"SUAM LENGTH"<<rawDataVariable->length<<'\n';
		try{
			rawDataVariable->data = new STUB_CHAR [ rawDataVariable->length  + 1];
			memcpy( (STUB_CHAR*)rawDataVariable->data , 
					( STUB_CHAR *)sqlite3_column_blob ( statement , 0 )
				       	, sqlite3_column_bytes(statement , 0 ));
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
				<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__
				<<"_"<<__TIME__<<"]"<<"Memcpy done\n";
		}
		catch ( std::exception &ba ){
			std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
				<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
				<<__TIME__<<"] EXCEPTION :"<<ba.what()<<'\n';
			exit( 0 );
		}
		
		}
		else std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] ERRORL STEP\n";
	}
		
	else
	std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		<<"] binding error\n";
	return rawDataVariable;
}



//
//update packet settingt for function packet_handler ()
//

bool captureQuery::StoreRawPacketQuery::updatePacketSettingApp (  bool appDb , 
		STUB_INT packetId , STUB_INT status , rawDataStruct *rawData ){
    std::string sqlStatement ;
    if ( appDb ){ //if app
        sqlStatement = "UPDATE PACKET_SETTING_"+scenInfo.scenarioName+
		" SET SERVER_STATUS ="+static_cast<ostringstream*>( &(ostringstream() 
					<< status ) )->str()+", NO_APP_DATA = NO_APP_DATA\
	       	+ 1 , SEQ_NO ="+static_cast<ostringstream*>( &(ostringstream() 
		<<rawData->sequenceNumber) )->str()+ " , ACK_NO ="+
		static_cast<ostringstream*>( &(ostringstream() 
					<< rawData->acknowledgeNumber) )->str()+
		" WHERE PACKET_ID ="+ static_cast<ostringstream*>( &(ostringstream() 
					<< packetId ) )->str()+" ;";
    }
    else { // DB
	    sqlStatement = "UPDATE PACKET_SETTING_"+scenInfo.scenarioName+" SET DB_STATUS ="+
		    static_cast<ostringstream*>( &(ostringstream() << status ) )->str()+
		    ", NO_DB_DATA = NO_DB_DATA + 1, SEQ_NO ="+
		    static_cast<ostringstream*>( &(ostringstream() 
					    <<rawData->sequenceNumber) )->str()+ 
		    " , ACK_NO ="+static_cast<ostringstream*>( &(ostringstream() 
					    << rawData->acknowledgeNumber) )->str()+
		    " WHERE PACKET_ID ="+ 
		    static_cast<ostringstream*>( &(ostringstream() << packetId ) )->str()+" ;";
    }
    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
	    <<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"
	    <<sqlStatement<<std::endl;

//    return ( func::executeStatus ( sqlite3_exec(db_credentials.db, sqlStatement.c_str() , func::callback, 0, &zErrMsg )  , zErrMsg));
return false;

}

/*-----------------------------------------------------------------------------
 *  update the clientquery string along with qery type at PACKET_SETTING_scenarioName
 *-----------------------------------------------------------------------------*/
bool captureQuery::StoreRawPacketQuery::updatePacketSettingApp( queryData *& queryArray ,
	       	STUB_INT arraySize ){
    STUB_INT currentPacket = -1;
    STUB_INT deltaValue = -1;
    std::string sqlStatement ;


    while ( ++currentPacket < arraySize ){
#ifdef DEBUG
        std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"
		<<"current pack no="<<queryArray [currentPacket ].packetNo<<'\n';
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line\
	       	["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		<<"] [ DATA UPDATED]:"<<queryArray[currentPacket].query<<'\n';
#endif

	/*-----------------------------------------------------------------------------
	 *  if grouping is true for grouping againest mysql statement id
	 *  have to update deltaMapping value of previous packet query
	 *  and untill all packets coming with grouping flag true.
	 *-----------------------------------------------------------------------------*/
	if ( queryArray[ currentPacket ].flagForGrouping ){
		sqlStatement = "UPDATE PACKET_SETTING_"+scenInfo.scenarioName +
			" SET QUERY_TYPE="+
			func::quotesql ( queryArray [ currentPacket ].queryType ) +
			" , QUERY = "+func::quotesql ( queryArray [ currentPacket ].query )+
			" , DELTA_VALUE = " + 
			static_cast< ostringstream *>( &(ostringstream() 
						<< deltaValue ) )->str()+
			" , DELTA_VALUE2 = "+ 
			static_cast<ostringstream*>(&(ostringstream()
						<<queryArray[ currentPacket ].
						deltaValue ) )->str()+
			" WHERE PACKET_NO ="+
			static_cast < ostringstream *>( &(ostringstream() 
						<< queryArray [ currentPacket ].
						packetNo ) )->str()+" ; ";

	}
	else {
		sqlStatement = "UPDATE PACKET_SETTING_"+scenInfo.scenarioName+
			" SET QUERY_TYPE ="+
			func::quotesql ( queryArray [currentPacket ].queryType )+
			" , QUERY ="+
			func::quotesql( queryArray [currentPacket ].query) +
			" , DELTA_VALUE = 0 , DELTA_VALUE2 = 0 WHERE PACKET_NO ="+
		       	static_cast<std::ostringstream*>( &(std::ostringstream() 
						<< queryArray [currentPacket ].
						packetNo ) )->str()+" ;";
	deltaValue -- ;

	}
        std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"]"<<"[UPDATE QUERY STRING]:"
		<<sqlStatement<<std::endl;
         func::executeStatus ( sqlite3_exec(dbCredentials.db, 
				 sqlStatement.c_str() , func::callback,
				 0, &zErrMsg )  , zErrMsg);
        sqlStatement.clear();
    }
    return true;

}


STUB_INT captureQuery::StoreRawPacketQuery::insertPacketSetting( bool serverDb , 
		STUB_INT conversationId , STUB_INT packetNumber ,rawDataStruct *rawData){
    captureQuery::packetId ++;
    std::string data="will contail raw data";
    //data.append ( reinterpret_cast<const STUB_CHAR*>(rawData.data) );
    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
	    <<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"
	    <<" data = "<<data<<std::endl;
    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
	    <<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"
	    <<"Packet id = "<<captureQuery::packetId<<std::endl;

   // std::string sqlStatement ;
    //edited on 29_11
    std::string queryString = "insert into PACKET_SETTING_"+
	    scenInfo.scenarioName+" ( CONVERSATION_ID , PACKET_NO , SEQ_NO ,\
	    ACK_NO , RAW_DATA , STATUS , PROTOCOL ) values ( ?, ?, ? ,? , ? , ? , ? ) ";

    sqlite3_stmt *pStmt;
   // do{
	    STUB_INT rc = sqlite3_prepare ( dbCredentials.db , queryString.c_str() ,
			    -1 , &pStmt , 0);
	    if ( rc != SQLITE_OK ){
		    std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "
			    <<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["
			    <<__DATE__<<"_"<<__TIME__<<"]"
			    <<"initializing error "<<queryString<<std::endl;
                    return 0;
	    }
          sqlite3_bind_int ( pStmt , 1 , conversationId );
        sqlite3_bind_int ( pStmt , 2 , packetNumber );
        sqlite3_bind_int ( pStmt , 3 , rawData->sequenceNumber );
         sqlite3_bind_int ( pStmt , 4 , rawData->acknowledgeNumber );
            sqlite3_bind_blob ( pStmt , 5 ,rawData->data , rawData->length ,
			    SQLITE_STATIC );
	    sqlite3_bind_text(pStmt , 7 , rawData->protocolName.c_str(),
			    rawData->protocolName.length() , SQLITE_STATIC );

	    if ( serverDb )
            sqlite3_bind_int ( pStmt , 6 , 1 );
	    else 
           sqlite3_bind_int ( pStmt , 6 , 0 );

	    rc = sqlite3_step ( pStmt );
	    assert ( rc != SQLITE_ROW );
	    rc = sqlite3_finalize( pStmt );
	    
 //   }while ( rc != SQLITE_SCHEMA );

    if ( rc != SQLITE_OK ){
	    std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		    <<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		    <<__TIME__<<"]"<<"can't insert value\n";
            return 0;
    }
    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
	    <<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__
	    <<"_"<<__TIME__<<"]"<<"Successfuly inserted"<<'\n';
    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
	    <<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
	    <<__TIME__<<"]"<<"INSERT PACKET SETTING:[LENGTH]:"
	    <<rawData->length<<'\n';
for ( STUB_UINT i = 0 ; i < rawData->length ; ++i )
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"]"<<(rawData->data[ i]);
std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
	<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<'\n';


    return 1;

}

//function to insert raw data into PACKEt
bool captureQuery::StoreRawPacketQuery::insertPacket( bool appDb , STUB_INT conversationId ,
	       	STUB_INT packetNumber , rawDataStruct *rawData){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"
		<<"CONVERSATION ID["<<conversationId<<"]\n"
		<<"PACKET NO["<<packetNumber<<"]\n";

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__
		<<"_"<<__TIME__<<"]"<<"DATA[";
	for ( STUB_UINT i = 0 ; i < rawData->length ; ++ i )
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"]"<<rawData->data[i];
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"]"<<"]\n";
	std::string sqlStatement;
	sqlite3_stmt *statement;
	STUB_INT applicationDb = 0 , rc ;
	if ( appDb ) // packet coming from client
		applicationDb = 1;
	else applicationDb = 0;
	sqlStatement = "INSERT INTO PACKET_"+scenInfo.scenarioName+" ( CONVERSATION_ID , PACKET_NO\
		       	, SEQ_NO , ACK_NO, DATA , APPDB , LENGTH ) VALUES \
			( ? , ? , ? , ? , ? , ? , ? ) ;";
	do{
		if (  (sqlite3_prepare ( dbCredentials.db , sqlStatement.c_str() , -1 ,
						&statement , 0 ) ) != SQLITE_OK ){
			std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "
				<<__FUNCTION__<<"] Line ["<<__LINE__<<"] Dat\
				eTime ["<<__DATE__<<"_"<<__TIME__
				<<"] can't initialize database";
			return false;
			
		}
		sqlite3_bind_int ( statement , 1  , conversationId);
		sqlite3_bind_int( statement , 2 , packetNumber );
		sqlite3_bind_int( statement , 3 , rawData->sequenceNumber );
		sqlite3_bind_int( statement , 4 , rawData->acknowledgeNumber);
		sqlite3_bind_blob( statement, 5, rawData->data , rawData->length , 
				SQLITE_STATIC);
		sqlite3_bind_int( statement , 6 , applicationDb );
		sqlite3_bind_int( statement , 7 , rawData->length );
		rc = sqlite3_step ( statement ) ;
		assert ( rc != SQLITE_ROW );
		rc = sqlite3_finalize( statement);
		
	}while ( rc == SQLITE_SCHEMA );
	if ( rc != SQLITE_OK ){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "
			<<__FUNCTION__<<"] Line ["<<__LINE__<<"] Dat\
			eTime ["<<__DATE__<<"_"<<__TIME__
			<<"]can't insert blob data into PACKET\n";
		return false;
		
	}
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"] successfully inserted blov dat into PACKET\n";
	sqlStatement = "select data from PACKET_"+scenInfo.scenarioName+ " where\
		       	CONVERSATION_ID = "+static_cast< ostringstream *> 
			( &(ostringstream()<<conversationId ) )->str()+
			" and PACKET_NO="+
			static_cast<ostringstream*>
			( &(ostringstream()<<packetNumber) )->str() +";";
	if ( sqlite3_prepare ( dbCredentials.db , sqlStatement.c_str() ,-1 , 
				&statement , 0 ) == SQLITE_OK){
		if ( sqlite3_step( statement ) == SQLITE_ROW ){
			u_char *dataPart = 
				new u_char[sqlite3_column_bytes ( statement , 0 ) + 1];
			memcpy ( (u_char*)dataPart , 
					(u_char*)sqlite3_column_blob( statement, 0 ) , 
					sqlite3_column_bytes( statement , 0 ) );
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "
				<<__FUNCTION__<<"] Line ["<<__LINE__
				<<"] DateTime ["<<__DATE__<<"_"
				<<__TIME__<<"]"<<"READ DATA[";
			for ( STUB_INT i = 0 ; i<sqlite3_column_bytes( statement , 0) ;
				       	++i )
				std::cout<<" File Name ["<<__FILE__<<" ] Function [ "
					<<__FUNCTION__<<"] Line ["<<__LINE__
					<<"] DateTime ["<<__DATE__<<"_"
					<<__TIME__<<"]"<<dataPart[i];
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "
				<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["
				<<__DATE__<<"_"<<__TIME__<<"]"<<"]\n";
			
		}
		
	}
	return true;
}



bool captureQuery::StoreRawPacketQuery::insertDbGreeting ( STUB_INT conversationId ,
	       	STUB_INT packetNumber , rawDataStruct *rawData ){
	std::string data="db greeting";
	std::string sqlStatement = "INSERT INTO PACKET_DB_GREETING_"+
		scenInfo.scenarioName+" ( CONVERSATION_ID , PACKET_NO ,\
	       	SEQ_NO , ACK_NO, DB_DATA ) VALUES ("+ 
		static_cast < ostringstream * >( &( ostringstream () 
					<< conversationId ) ) ->str() +
		","+static_cast <ostringstream*>( &(ostringstream ()
					<< packetNumber ) )->str() +
		","+static_cast<ostringstream*>( &(ostringstream() 
					<< rawData->sequenceNumber ) )->str()+
		","+static_cast <ostringstream *> ( & ( ostringstream () 
					<< rawData->acknowledgeNumber) )->str() +
		"," +func::quotesql( data )+");";
	return ( func::executeStatus ( sqlite3_exec(dbCredentials.db, 
					sqlStatement.c_str() , func::callback, 0, &zErrMsg ) 
			       	, zErrMsg));
}


//function for geting all the packets from PACKET_SETTING_ for a certain scenario.


actRawDataStruct * captureQuery::StoreRawPacketQuery::selectPacketSetting ( ){
	STUB_INT noPackets;
	actRawDataStruct *rawDataArray;
	std::string queryString;
	sqlite3_stmt *sqlStatement;
	queryString = "select count ( * ) from PACKET_SETTING_"+
		scenInfo.scenarioName +";";
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__
		<<"_"<<__TIME__<<"]"<<"query string  "<<queryString <<std::endl;
    if ( sqlite3_prepare ( dbCredentials.db , queryString.c_str() , 
			    -1 , &sqlStatement , 0 ) != SQLITE_OK ){
        return NULL;
    }
    else {
        if ( sqlite3_step ( sqlStatement ) != SQLITE_ROW ) return NULL;
        else
            noPackets = sqlite3_column_int ( sqlStatement , 0 );
            
            }

            sqlite3_finalize ( sqlStatement );
            try{
                rawDataArray = 
			new actRawDataStruct  [ noPackets + 1  ];
            }
            catch ( std::bad_alloc &ba ){
                std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "
			<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTim\
			e ["<<__DATE__<<"_"<<__TIME__
			<<"] exception cought"<<ba.what()<<std::endl;
                return NULL;
            }
            queryString.clear();
            queryString = "SELECT PACKET_NO , RAW_DATA , STATUS , PROTOCOL from\
			   PACKET_SETTING_"+scenInfo.scenarioName + ";";
            if ( sqlite3_prepare ( dbCredentials.db , queryString.c_str() , -1 ,
				    &sqlStatement , 0 ) != SQLITE_OK ){
                return NULL;
            }
            STUB_INT currentPacket = -1;
            while ( ( sqlite3_step ( sqlStatement ) ) == SQLITE_ROW ){
                rawDataArray [ ++currentPacket ].packetNumber = 
			sqlite3_column_int ( sqlStatement , 0 );
                rawDataArray [ currentPacket ].length = 
			sqlite3_column_bytes ( sqlStatement , 1 );
                rawDataArray [ currentPacket ].appServer = 
			sqlite3_column_int( sqlStatement , 2);
		rawDataArray [ currentPacket ].protocolName = 
            std::string(reinterpret_cast<const STUB_CHAR*>(
					      sqlite3_column_text(
						      sqlStatement,  3 )));
                //get memory for storing data part
                try {
                    rawDataArray [ currentPacket ].data = 
			    new STUB_CHAR [ rawDataArray [ currentPacket ].length + 1 ];// +1
                    memcpy ( (u_char*)rawDataArray [ currentPacket ].data , 
				    ( u_char * ) sqlite3_column_blob ( sqlStatement , 1 ) ,
				    rawDataArray[ currentPacket ].length );
		    rawDataArray [  currentPacket ].data[ (rawDataArray [
				    currentPacket].length) ] = '\0';
		    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "
			    <<__FUNCTION__<<"] Line ["<<__LINE__<<"] Date\
			    Time ["<<__DATE__<<"_"<<__TIME__<<"]"
			    <<"READ BLOB:[Length]:"
			    <<rawDataArray[ currentPacket].length<<'\n';
		    for ( STUB_INT i = 0 ; i< rawDataArray[ currentPacket ].length ;++ i )
			    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "
				    <<__FUNCTION__<<"] Line ["<<__LINE__<<"] Date\
				    Time ["<<__DATE__<<"_"<<__TIME__<<"]"
				    <<rawDataArray [ currentPacket ].data[i];
		    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "
			    <<__FUNCTION__<<"] Line ["<<__LINE__<<"] Dat\
			    eTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";
		    
		}
                catch ( std::bad_alloc &ba ){
			std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "
				<<__FUNCTION__<<"] Line ["<<__LINE__<<"] Date\
				Time ["<<__DATE__<<"_"<<__TIME__
				<<"] cought exception "<<ba.what()<<std::endl;
                }

            }
            rawDataArray [ ++currentPacket ].packetNumber = -999;
            rawDataArray [ currentPacket ].length = -999;
            return rawDataArray;
}



STUB_INT captureQuery::StoreRawPacketQuery::getCountPacketSetting(){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"]\n";
	STUB_INT noPackets;

	sqlite3_stmt *sqlStatement;
	std::string queryString = "select count ( * ) from PACKET_SETTING_"
		+scenInfo.scenarioName +";";
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"]"<<"query string  "<<queryString <<'\n';
	if ( sqlite3_prepare ( dbCredentials.db , queryString.c_str() , -1 ,
			       	&sqlStatement , 0 ) != SQLITE_OK ) 
		return -1;
	else {
		if ( sqlite3_step ( sqlStatement ) != SQLITE_ROW ) 
			return -1;
		else
			noPackets = 
				sqlite3_column_int ( sqlStatement , 0 );
		
	}
	sqlite3_finalize ( sqlStatement );
	return noPackets;
}




