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
 *   Organization:  Cognizant Technological solutions
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

    sqlite3_stmt *statement;
    scenarioInformation *allScenarioInformation;
    int res;
    std::string sqlStatement ="select count ( * ) from SCENARIO ";
    if ( sqlite3_prepare ( dbCredentials.db , sqlStatement.c_str() , -1 , &statement , 0 ) == SQLITE_OK  ){
        res = sqlite3_step ( statement );
        if ( res != SQLITE_ROW ) return NULL ;
        int rowCount = sqlite3_column_int ( statement , 0 ) + 1;
               
        //read no of
        try {
            allScenarioInformation = new scenarioInformation [ rowCount ] ;
        }
        catch ( std::bad_alloc &ba ){
            std::cerr<<" exception catched to create scenarioInformation array for storing scenario information \n "<<ba.what()<<std::endl;
            return NULL;
        }
    }

    sqlStatement.clear();

    //statement.clear();

    std::string sqlStatement2 = "select S_NAME , CATAGORY , PROTOCOL , SERVER_IP , PORT  from SCENARIO ";
    if ( sqlite3_prepare ( dbCredentials.db , sqlStatement2.c_str() , -1 , &statement , 0 ) == SQLITE_OK ) {
  //      int ctotal = sqlite3_column_count( statement );
        int initRowCount = 0 ;

        while ( 1 ){
            res = sqlite3_step ( statement );
            if ( res == SQLITE_ROW ){
//                allScenarioInformation [ initRowCount].scenarioName = sqlite3_column_text(statement , 0);


//                allScenarioInformation [ initRowCount ].scenarioName = std::string(reinterpret_cast<const char*> sqlite3_column_text ( statement , 0 ) );
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

    int rc = sqlite3_open ( databaseName.c_str() , &dbCredentials.db );
    if ( rc ){
        std::cerr<<"Cant load project ( databse ) "<<databaseName<<std::endl;
        return false;
    }
    std::cout<<"Database/project loaded \n";
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

bool serverQuery::DummyServerQuery::readConversation ( int conversationNumber ){
   // std::ostringstream temp ;
    //temp << conversationNumber ;
    //std::string =  temp.str();//static_cast < ostringstream * > ( & ( ostringstream () <<conversationNumber) )->str();

    std::string  sqlStatement = "select PACKET_NO from PACKET_SETTING_"+scenInfo.scenarioName+" where CONVERSATION_ID = "+
            static_cast < ostringstream * > ( & ( ostringstream () << conversationNumber))->str() +";";

    sqlite3_stmt *statement;
    if ( sqlite3_prepare ( dbCredentials.db , sqlStatement.c_str() , -1 , &statement , 0 ) == SQLITE_OK ){
        int ctotal = sqlite3_column_count( statement );
        int rowCount = -1;
        int packetNumber;
        int res = 0 ;
        //int bolbNumber;
        sqlite3_stmt *pStmt;
        int rc;
        
        while ( 1 ){
            res = sqlite3_step ( statement );

            if ( res == SQLITE_ROW ){
                return true ;
                for ( int i=0 ; i<ctotal ; i++ ){//it will be only one column

                    packetNumber = sqlite3_column_int ( statement , i );
                    //code to read packet information.... ( raw packet length , data )

                    const char *sqlFetchQuery ="select RAW_DATA from blobs WHERE PACKET_NO = ?";
                   //int tempPacknumber = sqlite3_column_int( statement , i);
                    actConversationDiary [ conversationNumber].actRawData [++rowCount].packetNumber = sqlite3_column_int( statement , i);
                    
                      //  actConversationDiary [ conversationNumber ].actRawData [ ++rowCount ].packetNummber = sqlite3_column_int ( statement , i );
                        //compilr the select statement into a virtual machine
                        res = sqlite3_prepare ( dbCredentials.db , sqlFetchQuery , -1 , &pStmt , 0 );
                        if ( rc != SQLITE_OK ){
                            return false;
                        }
                        //bind the key to the sql variable
                        sqlite3_bind_int ( pStmt , 1 , packetNumber );

                        res = sqlite3_step ( pStmt );
                        if ( res == SQLITE_ROW ){

                            actConversationDiary [ conversationNumber ].actRawData [ rowCount ].length =  sqlite3_column_bytes ( pStmt , 0 );
                            actConversationDiary [ conversationNumber ].actRawData [ rowCount ].data = new  char [ actConversationDiary [ conversationNumber ] .actRawData [ rowCount ].length ]();
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

int serverQuery::DummyServerQuery:: getLastConversationId (){
    sqlite3_stmt *statement;
    std::string sqlStatement = "select max( CONVERSATION_ID ) from PACKET_"+scenInfo.scenarioName+");";
    if ( sqlite3_prepare ( dbCredentials.db , sqlStatement.c_str() , -1 , &statement , 0 ) == SQLITE_OK ){
        //int ctotal = sqlite3_column_count ( statement );
        int res;
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

// function to  read a chuck of packets
actSeriesStruct * serverQuery::DummyServerQuery::getChunckPackets(  const char * buffer , int bufferLength , queryData *& queryDataArray ){

    std::cout<<"query string"<<func::quotesql ( queryDataArray [ 0 ].query) <<std::endl;

    int conversationId = 0;
    int noPacket ;
    actSeriesStruct *fetchedConversation;
    std::string queryString;
    sqlite3_stmt *statement;
    int rc;
    if ( bufferLength == -1 ) conversationId = 0; // this is for the first packet that is db greetings.
        else {
            std::cout<<"query type"<<queryDataArray [ 0 ].query
                    <<"queryDataArray [ 0 ].query.compare ( \"login\" ) ="<<queryDataArray [ 0 ].query.compare ( "login" )
                    <<"queryDataArray[ 0 ].query . compare ( \"response\" )"<<queryDataArray[ 0 ].query . compare ( "response" )<<std::endl;
            if ( ( ( queryDataArray [ 0 ].query.compare ( "login" ) == 0 ) & ( queryDataArray[ 0 ].query . compare ( "response" ) == 0 ) & ( queryDataArray [ 0 ].query . compare ( "greetins") == 0 ) )){
                 // execute the following query if bufferLength != -1 , -1 indicates that have to read the first conversationi
                 bool checkFlag = false;
                 char *tempBuffer = new char [ 5000 ];
                 queryString ="select DATA , CONVERSATION_ID from PACKET_"+scenInfo.scenarioName +" where LENGTH = ? ;";
                 if ( ( sqlite3_prepare( dbCredentials.db , queryString.c_str() , -1 , &statement , 0 ) ) != SQLITE_OK ){
                     std::cerr<<"error\n";
                     return NULL;
                 }
                 sqlite3_bind_int( statement ,1 , bufferLength  );
                 while ( (sqlite3_step( statement ) == SQLITE_ROW ) && !checkFlag ){
                     if ( bufferLength == sqlite3_column_bytes( statement , 0 ) ){
                         conversationId = sqlite3_column_int(statement , 1 );
                         // std::cout<<"blob : "<<(  char * )sqlite3_column_blob ( statement , 0 )<<std::endl;
                         memcpy (  tempBuffer ,
                                 ( const char * )sqlite3_column_blob ( statement , 0 ) ,sqlite3_column_bytes( statement , 0 ) );
                         for ( int i = 0 ; i<sqlite3_column_bytes( statement , 0 ); ++ i){
                             if (  tempBuffer [ i] ==  buffer [ i] ){
                                 checkFlag = true;
                                 }else{
                                     checkFlag = false;
                                     
                                 }
                             
                         }
                        
                    }
                    
                }
                      sqlite3_finalize ( statement );
                delete [] tempBuffer;

        queryString.clear();
        std::cout<<"inside if\n";
    }
    else {
        std::cout<<"inside else\n";
        queryString ="select CONVERSATION_ID from PACKET_SETTING_"+scenInfo.scenarioName +" where query ="+ func::quotesql(queryDataArray[0].query )+" ;";
	std::cerr<<"this is not an error: QUERY searching= "<<func::quotesql ( queryDataArray [ 0 ].query) <<std::endl;
        std::cerr<<"querystring"<<queryString <<std::endl;
        if ( ( sqlite3_prepare( dbCredentials.db , queryString.c_str() , -1 , &statement , 0 ) ) != SQLITE_OK ){
            std::cerr<<"error\n";
            return NULL;
            
        }
       // sqlite3_bind_text ( statement , 1 , queryDataArray [0 ].query );
        while ( (sqlite3_step( statement ) == SQLITE_ROW ) ){

            conversationId = sqlite3_column_int ( statement , 0 );
        }
             sqlite3_finalize ( statement );
        queryString.clear();
    }
        }

        std::cout<<"conversation ID ="<<conversationId<<std::endl;

        //niw conversation id for  the incoming packet is available
        //now fetch whole conversation



    std::cout<<"database opened ?? "<<dbCredentials.db<<std::endl;
                queryString = "select count ( * ) from PACKET_"+scenInfo.scenarioName +" where CONVERSATION_ID ="+static_cast <ostringstream *> ( & ( ostringstream () << conversationId ) )->str()+";";
                 std::cout<<"query string is "<<queryString<<std::endl;
                std::cout<<"check"<<std::endl;
                if ( sqlite3_prepare ( dbCredentials.db , queryString.c_str() , -1 , &statement , 0 ) == SQLITE_OK ){
                    std::cout<<"hes I am r8"<<std::endl;
			rc = sqlite3_step ( statement );
			if ( rc != SQLITE_ROW ) return NULL ;
                        noPacket = sqlite3_column_int ( statement , 0 );
                        std::cout<<"No of packet is :"<<noPacket<<std::endl;

		}
                sqlite3_finalize ( statement );
               // sqlite3_close ( dbCredentials.db );

		try {
                        fetchedConversation = new actSeriesStruct() ;
                        fetchedConversation->converationId = conversationId;
                        fetchedConversation->noOfPacket = noPacket ;
                        fetchedConversation->actRawData = new actRawDataStruct [ noPacket ];
		}
                catch ( std::bad_alloc &ba ){
                        std::cout<<"Exception caught "<<":"<<ba.what()<<std::endl;
		}

		//now fetch all the blob datas for the current conversation from PACKEt
		queryString.clear();
                queryString = "SELECT PACKET_NO , APPDB  , LENGTH , DATA FROM PACKET_"+scenInfo.scenarioName+ " where CONVERSATION_ID = ?";

               std::cout<<"query string"<<queryString<<std::endl;
                sqlite3_stmt *statement2;

                rc = sqlite3_prepare ( dbCredentials.db , queryString.c_str() , -1 , &statement2 , 0 );
		if ( rc != SQLITE_OK ) {
			std::cerr<<" error on reading packet information from PACKET ";
			return NULL;
		}
                std::cout<<"conversation Id" <<conversationId<<std::endl;
		//bind the keys to the sql VARIABLE;
                sqlite3_bind_int ( statement2 , 1 ,  conversationId  );

                int currentFetchNumber = -1;
                //int rowCount = -1;
                while (  ( sqlite3_step ( statement2 ) ) == SQLITE_ROW   ){
                        fetchedConversation->actRawData[ ++currentFetchNumber ].packetNumber = sqlite3_column_int ( statement2 , 0 );
                        fetchedConversation->actRawData [ currentFetchNumber ].appServer = sqlite3_column_int ( statement2 , 1 );
                        fetchedConversation->actRawData [ currentFetchNumber ].length =   sqlite3_column_int ( statement2 , 2 );
			try {
				fetchedConversation->actRawData [ currentFetchNumber ].data = new  char [ 5024 ];
			}
			catch ( std::bad_alloc &ba ){
				std::cout<<"exception caught "<<ba.what()<<std::endl;

			}
                       // fetchedConversation->actRawData [ currentFetchNumber ].data = (  char * )sqlite3_column_blob ( statement2 , 3 );

                        memcpy (  fetchedConversation->actRawData [ currentFetchNumber ].data ,
                                  (  char * )sqlite3_column_blob ( statement2 , 3 ) ,
                                  fetchedConversation->actRawData [ currentFetchNumber ].length  );
                         if ( ( sqlite3_column_bytes(statement2 , 3) <= 0 ) && ( fetchedConversation->actRawData [ currentFetchNumber ].appServer ==  1) ) currentFetchNumber --;

                       std::cout<<"packet number = "<< fetchedConversation->actRawData[ currentFetchNumber ].packetNumber<<std::endl;
                        std::cout<<"appdb"<< ( fetchedConversation->actRawData [ currentFetchNumber ].appServer )<<std::endl;
                       std::cout<<"length = "<< ( fetchedConversation->actRawData [ currentFetchNumber ].length )<<std::endl;
                       std::cout<<"blob data ="<<( fetchedConversation->actRawData [ currentFetchNumber].data)<<std::endl;


                    }
                sqlite3_finalize ( statement2 );
                //sqlite3_close ( dbCredentials.db );

                fetchedConversation->noOfPacket = currentFetchNumber;
                std::cout<<"print data of position 1\n";
                for ( int kk= 0 ; kk <fetchedConversation->actRawData[1].length ; ++kk){
                    std::cerr<<fetchedConversation->actRawData[1].data[kk];
                }


                return fetchedConversation;


}


