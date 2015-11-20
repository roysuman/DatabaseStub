/*
 * =====================================================================================
 *
 *       Filename:  dummy_server.cpp
 *
 *    Description:  this is about dummy database server.. the data required to act dummy server as a real one will be handle by all source codes of
 *                  this file/. *
 *        Version:  1.0
 *        Created:  Friday 15 November 2013 11:28:46  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy (),
 *   Organization:  SELF
 *
 * =====================================================================================
 */

#include "dummy_server.hpp"
#include <string>
using namespace std;

/*
 * class OpenProjectQuery
 * */

serverQuery::OpenProjectQuery::OpenProjectQuery(){}
serverQuery::OpenProjectQuery::~OpenProjectQuery(){}

/*
 * the following function is for showing all available scenarios under this project
 * */

 scenarioInformation **  serverQuery::OpenProjectQuery::showScenarios( ) {
	 
    sqlite3_stmt           *statement;
    scenarioInformation    *allScenarioInformation;
    STUB_INT               res;
    std::string            sqlStatement;

    sqlStatement ="select count ( * ) from SCENARIO ";
    if ( sqlite3_prepare ( dbCredentials.db , 
			    sqlStatement.c_str() , -1 , 
			    &statement , 0 ) == SQLITE_OK  ){
        res = sqlite3_step ( statement );
        if ( res != SQLITE_ROW ) return NULL ;
        STUB_INT rowCount = 
		sqlite3_column_int ( statement , 0 ) + 1;
               
        //read no of
        try {
            allScenarioInformation = 
		    new scenarioInformation [ rowCount ] ;
        }
        catch ( std::bad_alloc &ba ){
            std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "
		    <<__FUNCTION__<<"] Line ["<<__LINE__<<
		    "] DateTime ["<<__DATE__<<"_"<<__TIME__
		    <<"]"<<" exception catched to create \
		    scenarioInformation array for storing scena\
		    rio information \n "<<ba.what()<<std::endl;
	    return NULL;
        }
    }

    sqlStatement.clear();

    //statement.clear();

    std::string sqlStatement2 = 
	    "select S_NAME , CATAGORY , PROTOCOL ,\
	    SERVER_IP , PORT  from SCENARIO ";
    if ( sqlite3_prepare ( dbCredentials.db , sqlStatement2.c_str() ,
			    -1 , &statement , 0 ) == SQLITE_OK ) {
  //      STUB_INT ctotal = sqlite3_column_count( statement );
        STUB_INT initRowCount = 0 ;

        while ( 1 ){
            res = sqlite3_step ( statement );
            if ( res == SQLITE_ROW ){
//                allScenarioInformation [ initRowCount].scenarioName = sqlite3_column_text(statement , 0);


//                allScenarioInformation [ initRowCount ].scenarioName = std::string(reinterpret_cast<const STUB_CHAR*> sqlite3_column_text ( statement , 0 ) );
//            allScenarioInformation [ initRowcount ].catagory = sqlite3_column_text ( statement , 1 );
//            allScenarioInformation [ initRowCount ].protocol = sqlite3_column_text ( statement , 2 );
//            allScenarioInformation [ initRowCount ].server = sqlite3_column_text ( statement , 3 );
//            allScenarioInformation [ ++initRowCount ].portNo = sqlite3_column_int( statement , 4 );

            }
            if ( res == SQLITE_DONE || res == SQLITE_ERROR ){
                allScenarioInformation [ initRowCount ] .scenarioName = "NULL";
                return &allScenarioInformation;
            }


        }
    }
    return &allScenarioInformation;

}

/*
 *The following function is for opening project ( NEW ) , database
 * */

bool serverQuery::OpenProjectQuery::openProject( std::string databaseName ) {

    STUB_INT rc = 
	    sqlite3_open ( databaseName.c_str() , &dbCredentials.db );
    if ( rc ){
	    std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "
		    <<__FUNCTION__<<"] Line ["<<__LINE__<<"] Date\
		    Time ["<<__DATE__<<"_"<<__TIME__<<"]"
		    <<"Cant load project ( databse ) "
		    <<databaseName<<std::endl;
	    return false;
	    
    }
    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "
	    <<__FUNCTION__<<"] Line ["<<__LINE__
	    <<"] DateTime ["<<__DATE__<<"_"<<__TIME__
	    <<"]"<<"Database/project loaded \n";
    return true;

}






/*
 *class DummyServerQuery
 * */
serverQuery::DummyServerQuery::DummyServerQuery(){}
serverQuery::DummyServerQuery::~DummyServerQuery(){}



/*
 *function to read packet numbers for a corresponding conversation ,
 it will store all the packets no , into an array and then will insert that packet numbers with packet data.
 *
    std::string sqlStatement = "INSERT INTO PACKET_DB_GREETING_"+scenInfo.scenarioName+" ( CONVERSATION_ID ,
 PACKET_NO , SEQ_NO , ACK_NO, DB_DATA ) VALUES ("+ static_cast < ostringstream * >( &( ostringstream () << conversationId ) ) ->str() +","+static_cast <ostringstream*>( &(ostringstream ()<< packetNumber ) )->str() +","+static_cast<ostringstream*>( &(ostringstream() << rawData.sequenceNumber ) )->str()+","
+static_cast <ostringstream *> ( & ( ostringstream () << rawData.acknowledgeNumber) )->str() +"," +func::quotesql( data )+");";
    re
*/

bool serverQuery::DummyServerQuery::readConversation ( STUB_INT conversationNumber ){
   // std::ostringstream temp ;
    //temp << conversationNumber ;
    //std::string =  temp.str();//static_cast < ostringstream * > ( & ( ostringstream () <<conversationNumber) )->str();

    std::string  sqlStatement = "select PACKET_NO from PACKET_SETTING_"
	    +scenInfo.scenarioName+" where CONVERSATION_ID = "+
            static_cast < ostringstream * > ( & ( ostringstream () 
				    << conversationNumber))->str() +";";

    sqlite3_stmt *statement;
    if ( sqlite3_prepare ( dbCredentials.db , sqlStatement.c_str() ,
			    -1 , &statement , 0 ) == SQLITE_OK ){
        STUB_INT ctotal = sqlite3_column_count( statement );
        STUB_INT rowCount = -1;
        STUB_INT packetNumber;
        STUB_INT res = 0 ;
        //STUB_INT bolbNumber;
        sqlite3_stmt *pStmt;
        STUB_INT rc;
        
        while ( 1 ){
            res = sqlite3_step ( statement );

            if ( res == SQLITE_ROW ){
                return true ;
                for ( STUB_INT i=0 ; i<ctotal ; i++ ){//it will be only one column

                    packetNumber = sqlite3_column_int ( statement , i );
                    //code to read packet information.... ( raw packet length , data )

                    const STUB_CHAR *sqlFetchQuery ="select RAW_DATA from \
						blobs WHERE PACKET_NO = ?";
                   //STUB_INT tempPacknumber = sqlite3_column_int( statement , i);
                    actConversationDiary [ conversationNumber].
			    actRawData [++rowCount].packetNumber = 
			    sqlite3_column_int( statement , i);
                    
                      //  actConversationDiary [ conversationNumber ].actRawData [ ++rowCount ].packetNummber = sqlite3_column_int ( statement , i );
                        //compilr the select statement into a virtual machine
                        res = sqlite3_prepare ( dbCredentials.db , 
					sqlFetchQuery , -1 , &pStmt , 0 );
                        if ( rc != SQLITE_OK ){
                            return false;
                        }
                        //bind the key to the sql variable
                        sqlite3_bind_int ( pStmt , 1 , packetNumber );

                        res = sqlite3_step ( pStmt );
                        if ( res == SQLITE_ROW ){

                            actConversationDiary [ conversationNumber ].
				    actRawData [ rowCount ].length =
				    sqlite3_column_bytes ( pStmt , 0 );
                            actConversationDiary [ conversationNumber ].
				    actRawData [ rowCount ].data = 
				    new  STUB_CHAR [ actConversationDiary [ conversationNumber ] .
				    actRawData [ rowCount ].length ]();
                           // memcpy have to implement
                         //   memcpy ( actConversationDiary [ conversationNumber ].actRawData [ rowCount ].data , ( const u_char * ) sqlite3_column_blob ( pStmt , 0 ) , actConversationDiary [ conversationNumber ].actRawData [ rowCount ].length );
                            //ibwrt(actConversationDiary [ conversationNumber ].actRawData [ rowCount ].data , sqlite3_column_blob ( pStmt , 0 ) , actConversationDiary [ conversationNumber ].actRawData [ rowCount ].length);
                            sqlite3_finalize(pStmt);
                            
                            }
                        
                    }
                }
            }
        if ( res == SQLITE_DONE || res==SQLITE_ERROR ){
                //when all the packet no has been read , then put it into structure.
                

                std::cout <<"done"<<std::endl;
                return true;
            }
        }
	
    return false;
}

STUB_INT serverQuery::DummyServerQuery:: getLastConversationId (){
    sqlite3_stmt *statement;
    std::string sqlStatement = 
	    "select max( CONVERSATION_ID ) from PACKET_"+
	    scenInfo.scenarioName+");";
    if ( sqlite3_prepare ( dbCredentials.db , sqlStatement.c_str() , 
			    -1 , &statement , 0 ) == SQLITE_OK ){
        //STUB_INT ctotal = sqlite3_column_count ( statement );
        STUB_INT res;
        while ( 1 ){
            res = sqlite3_column_count ( statement );
            if ( res == SQLITE_ROW ){
                return ( sqlite3_column_int( statement , 0 ) );
            }
            return 0;
                
            }
        }
    return -1;

}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  getChunckPackets
 *  Description:  read chunck packets which matches with the incoming query
 * =====================================================================================
 */
actSeriesStruct * serverQuery::DummyServerQuery::getChunckPackets( 
	       	const STUB_CHAR * buffer , STUB_INT bufferLength , 
		queryData *& queryDataArray , STUB_INT statementId = 0 ){
	STUB_INT conversationId = 0 , tempFLag = 0;
	STUB_INT noPacket ;
	actSeriesStruct *fetchedConversation;
	std::string queryString;
	sqlite3_stmt *statement;
    STUB_INT rc;

    fetchedConversation = NULL;
    if ( bufferLength == -1 ) conversationId = 0; // server greeting
        else {
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "
			<<__FUNCTION__<<"] Line ["<<__LINE__
			<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
			<<"]"<<"query type"<<
			queryDataArray [ 0 ].query
			<<"queryDataArray [ 0 ].query.compare ( \"login\" ) ="
			<<queryDataArray [ 0 ].query.compare ( "login" )
			<<"queryDataArray[ 0 ].query . compare ( \"response\" )"
			<<queryDataArray[ 0 ].query . compare ( "response" )
			<<std::endl;
            if ( ( ( queryDataArray [ 0 ].query.compare ( "login" ) == 0 ) & 
				    ( queryDataArray[ 0 ].query . 
				      compare ( "response" ) == 0 ) &
				    ( queryDataArray [ 0 ].query . 
				      compare ( "greetins") == 0 ) )){
                 // execute the following query if bufferLength != -1 , -1 indicates that have to read the first conversationi
                 bool checkFlag = 
			 false;
                 STUB_CHAR *tempBuffer = 
			 new STUB_CHAR [ 5000 ];
                 queryString =
			 "select DATA , CONVERSATION_ID from PACKET_"+
			 scenInfo.scenarioName +" where LENGTH = ? ;";
                 if ( ( sqlite3_prepare( dbCredentials.db , queryString.c_str() ,
						 -1 , &statement , 0 ) ) !=
				 SQLITE_OK ){
                     std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "
			     <<__FUNCTION__<<"] Line ["<<__LINE__<<
			     "] DateTime ["<<__DATE__<<"_"<<__TIME__
			     <<"] error\n";
                     return NULL;
                 }
                 sqlite3_bind_int( statement ,1 , bufferLength  );
                 while ( (sqlite3_step( statement ) == SQLITE_ROW ) &&
				 !checkFlag ){
                     if ( bufferLength == 
				     sqlite3_column_bytes( statement , 0 ) ){
                         conversationId = 
				 sqlite3_column_int(statement , 1 );
                         memcpy (  tempBuffer ,
                                 ( const STUB_CHAR * )sqlite3_column_blob ( statement , 0 ) ,
				 sqlite3_column_bytes( statement , 0 ) );
                         for ( STUB_INT i = 0 ;
					 i<sqlite3_column_bytes( statement , 0 );
					 ++ i){
                             if (  tempBuffer [ i] ==
					     buffer [ i] ){
                                 checkFlag = true;
                                 }else{
                                     checkFlag = false;}
                         }
                    }
                }
                      sqlite3_finalize ( statement );
                delete [] tempBuffer;

        queryString.clear();
        std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<
		"] DateTime ["<<__DATE__<<"_"<<__TIME__
		<<"]"<<"inside if\n";
    }
    else {
	    if ( statementId == 0 ){
		    std::cout<<"Statement Id = 0\n";
		    queryString =
			    "select CONVERSATION_ID , DELTA_VALUE from PACKET_SETTING_"+
			    scenInfo.scenarioName +" where query ="+ 
			    func::quotesql(queryDataArray[0].query )+" ;";
	    }
	    
	    else 
		    queryString ="select CONVERSATION_ID , DELTA_VALUE from PACKET_SETTING_"+
			    scenInfo.scenarioName +
			    " where query ="+ func::quotesql(queryDataArray[0].query )+
			    " and DELTA_VALUE = "+
			    static_cast<ostringstream*>( &(ostringstream() 
						    <<statementId ) )->str() +";";
	    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "
		    <<__FUNCTION__<<"] Line ["<<__LINE__<<
		    "] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"
		    <<"QueryString["<<queryString<<'\n';

		    if ( ( sqlite3_prepare( dbCredentials.db , 
						    queryString.c_str() , -1 
						    , &statement , 0 ) ) 
				    != SQLITE_OK ){
            std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "
		    <<__FUNCTION__<<"] Line ["<<__LINE__<<
		    "] DateTime ["<<__DATE__<<"_"<<__TIME__<<"] error\n";
            return NULL;
            
        }

       // sqlite3_bind_text ( statement , 1 , queryDataArray [0 ].query );
        while ( (sqlite3_step( statement ) == SQLITE_ROW ) ){

            conversationId = sqlite3_column_int ( statement , 0 );
	    tempFLag = sqlite3_column_int( statement , 1 );
        }
             sqlite3_finalize ( statement );
        queryString.clear();
    }
        }

        std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"]"<<"conversation ID ="<<
		conversationId<<std::endl;

        //niw conversation id for  the incoming packet is available
        //now fetch whole conversation



//    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<
//	    "] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"database opened ?? "<<
//	    dbCredentials.db<<std::endl;
                queryString = "select count ( * ) from PACKET_"+scenInfo.scenarioName +
			" where CONVERSATION_ID ="+static_cast <ostringstream *> ( & ( 
						ostringstream () 
						<< conversationId ) )->str()+";";
                 std::cout<<" File Name ["<<__FILE__<<" ] Function [ "
			 <<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__
			 <<"_"<<__TIME__<<"]"<<"query["<<queryString<<"]\n";
                if ( sqlite3_prepare ( dbCredentials.db , queryString.c_str() , -1 ,
				       	&statement , 0 ) == SQLITE_OK ){
			rc = sqlite3_step ( statement );
			if ( rc != SQLITE_ROW ) return NULL ;
                        noPacket = sqlite3_column_int ( statement , 0 );
                        std::cout<<" File Name ["<<__FILE__<<" ] Function [ "
				<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["
				<<__DATE__<<"_"<<__TIME__<<"]"<<
				"No of packet is :"<<noPacket<<'\n';

		}
		else {
			std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "
				<<__FUNCTION__<<"] Line ["<<
				__LINE__<<"] DateTime ["<<__DATE__<<"_"
				<<__TIME__<<"]"<<"error on query\n";
			exit(0);
		}


                sqlite3_finalize ( statement );
               // sqlite3_close ( dbCredentials.db );

		try {
                        fetchedConversation = 
				new actSeriesStruct() ;
			fetchedConversation->dynamicFlagValue = 
				tempFLag;
                        fetchedConversation->converationId = 
				conversationId;
                        fetchedConversation->noOfPacket = 
				noPacket ;
                        fetchedConversation->actRawData = 
				new actRawDataStruct [ noPacket ];
		}
                catch ( std::bad_alloc &ba ){
                        std::cout<<" File Name ["<<__FILE__<<" ] Function [ "
				<<__FUNCTION__<<"] Line ["<<__LINE__<<"] Date\
				Time ["<<__DATE__<<"_"
				<<__TIME__<<"] Exception caught "
				<<":"<<ba.what()<<std::endl;
		}

		//now fetch all the blob datas for the current conversation from PACKEt
		queryString.clear();
                queryString = "SELECT PACKET_NO , APPDB  , LENGTH , DATA FROM PACKET_"+
			scenInfo.scenarioName+" where CONVERSATION_ID = ?";
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"]"<<"query string"<<queryString<<std::endl;
                sqlite3_stmt *statement2;

                rc = sqlite3_prepare ( dbCredentials.db , queryString.c_str() ,
			       	-1 , &statement2 , 0 );
                std::cout<<" File Name ["<<__FILE__<<" ] Function [ "
			<<__FUNCTION__<<"] Line ["<<__LINE__<<
			"] DateTime ["<<__DATE__<<"_"<<__TIME__
			<<"]"<<"conversation Id" <<
			conversationId<<std::endl;
		if ( rc != SQLITE_OK ) {
			std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "
				<<__FUNCTION__<<"] Line ["<<
				__LINE__<<"] DateTime ["<<__DATE__
				<<"_"<<__TIME__<<"]"<<
				" error on reading packet information from PACKET ";
			return NULL;
		}
		//bind the keys to the sql VARIABLE;
                sqlite3_bind_int ( statement2 , 1 ,  conversationId  );

                STUB_INT currentFetchNumber = -1;
                //STUB_INT rowCount = -1;
                while (  ( sqlite3_step ( statement2 ) ) == SQLITE_ROW   ){
                        fetchedConversation->actRawData[ ++currentFetchNumber ].
				packetNumber = 
				sqlite3_column_int ( statement2 , 0 );
                        fetchedConversation->actRawData [ currentFetchNumber ].
				appServer = 
				sqlite3_column_int ( statement2 , 1 );
                        fetchedConversation->actRawData [ currentFetchNumber ].length =   
				sqlite3_column_int ( statement2 , 2 );
			try {
				fetchedConversation->actRawData [ currentFetchNumber ].
					data = new  STUB_CHAR [ 5024 ];
			}
			catch ( std::bad_alloc &ba ){
				std::cout<<" File Name ["<<__FILE__<<" ] Function [ "
					<<__FUNCTION__<<"Line ["<<__LINE__
					<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
					<<"]"<<"exception caught "<<ba.what()<<std::endl;

			}
                       // fetchedConversation->actRawData [ currentFetchNumber ].data = (  STUB_CHAR * )sqlite3_column_blob ( statement2 , 3 );

                        memcpy (  fetchedConversation->actRawData [ currentFetchNumber ].data ,
                                  (  STUB_CHAR * )sqlite3_column_blob ( statement2 , 3 ) ,
                                  fetchedConversation->actRawData [ currentFetchNumber ].length  );

                       std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
			       __LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"packet number = "
			       << fetchedConversation->actRawData[ currentFetchNumber ].packetNumber<<
			       std::endl;
                        std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
				__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"appdb"<<
			       	( fetchedConversation->actRawData [ currentFetchNumber ].appServer )<<
				std::endl;
                       std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
			       __LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"length = "<<
			       ( fetchedConversation->actRawData [ currentFetchNumber ].length )<<
			       std::endl;
                       std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
			       "] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"\
			       ]"<<"blob data ="<<( fetchedConversation->actRawData
			       [ currentFetchNumber].data)<<std::endl;
		       //remove packets of length <=0 and which are not a response packets
		       if ( ( sqlite3_column_bytes(statement2 , 3) <= 0 ) && 
				       ( fetchedConversation->actRawData [ currentFetchNumber ].appServer 
					 ==  1) ) currentFetchNumber --;


                    }
                sqlite3_finalize ( statement2 );
                //sqlite3_close ( dbCredentials.db );

                fetchedConversation->noOfPacket = currentFetchNumber ;
                std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
			__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<
			"print data of position 1\n";
		/* 
                for ( STUB_INT kk= 0 ; kk <fetchedConversation->actRawData[1].length ; ++kk){
                    std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
			    "] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
			    "]"<<fetchedConversation->actRawData[1].data[kk];
                }*/


                return fetchedConversation;


}


