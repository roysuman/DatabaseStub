/*
// * =====================================================================================
// *
// *       Filename:  server.cpp
// *
// *    Description:  functions for creating and handeling dummy server that will act as a server with raw data.
// *
// *        Version:  1.0
// *        Created:  11/15/2013 06:45:31 PM
// *       Revision:  none
// *       Compiler:  gcc
// *
// *         Author:  SUMAN ROY (), email.suman.roy@gmail.com
// *   Organization:  SELF
// *
// * =====================================================================================
// */
#include "../include/server.hpp"
 actSeriesStruct *  server::currentConversationChunk = NULL;
 STUB_INT server::serverSockFd;
 STUB_INT server::clientSockFd;
 STUB_INT globalDynamicInt;
 server::DummyServer::DummyServer(){}
 server::DummyServer::~DummyServer(){}

 /* 
  * ===  FUNCTION  ======================================================================
  *         Name:  createServer
  *  Description:  create a tcp server on provided port and ip
  * =====================================================================================
  */

STUB_INT server::DummyServer::createServer( std::string serverIp , STUB_INT serverPort ){

	 std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		 <<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		 <<__TIME__<<"]\n";

	 struct sockaddr_in    servAddress;
	 STUB_INT              socketFd ;
	 std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		 <<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		 <<__TIME__<<"] [IP Address]:"<<serverIp.c_str()
		 <<"[port ]:"<<serverPort<<'\n';
	 if ( ( socketFd = socket ( AF_INET ,   SOCK_STREAM , 0 ) ) < 0 ){
		 std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			 <<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			 <<__TIME__<<"]"<<__FUNCTION__<<"socket failure\n";
		 exit (EXIT_FAILURE);
	 }
	 bzero( ( STUB_CHAR * ) &servAddress, sizeof( servAddress ) );
	 servAddress.sin_family = AF_INET;
	 servAddress.sin_port = htons ( serverPort );
	 servAddress.sin_addr.s_addr = inet_addr ( serverIp.c_str() ) ;// INADDR_ANY ;//inet_addr ( c_ip );
     if ( ( ::bind ( socketFd , ( struct sockaddr * )&servAddress , 
				     sizeof( struct sockaddr ) ) ) < 0 ) {
         std::cerr <<__FUNCTION__<<"Could not bind server at [ IP ]: " << serverIp <<
		 "[ Port]: " << serverPort <<'\n';
         return -1;
		    
         }
	 if ( ( listen ( socketFd , 10 ) ) < 0 ){
		 std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			 <<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			 <<__TIME__<<"] Listening Failure \n";
		 return -2;
		}
	 server::serverSockFd = socketFd;
	 return socketFd ;
 }

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  acceptClient
 *  Description:  accept client connection when a client wants to establish connection
 * =====================================================================================
 */

void  server::DummyServer::acceptClient(  ){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"]\n";

	socklen_t      size;
	STUB_INT       clientFd;
	STUB_INT       serverSockfd ;
	sockaddr_in    clientAddress;

	serverSockfd = server::serverSockFd ;
	size = sizeof (  sockaddr_in ) ;
	while ( 1 ){
		if ( ( clientFd = accept ( serverSockfd , ( struct sockaddr * )&clientAddress , 
						&size ) ) < 0 ){
			std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
				<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
				<<__TIME__<<"] can't accept client\n ";
			exit ( EXIT_FAILURE ) ;
		}
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"] Server got connection from >>"
			<<inet_ntoa ( clientAddress.sin_addr )<<'\n';
		if ( clientFd > 0 ){
			server::clientSockFd = clientFd;
			// after geting the connection play with data
			server::DummyServer *instance = new server::DummyServer();
			instance->actWithData();
		}
	}
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  actWithData
 *  Description:  start communication and datatransfer between client & server
 * =====================================================================================
 */

bool server::DummyServer::actWithData(){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"]\n";

	queryData                *query;
	STUB_CHAR                *buffer;
	STUB_INT                 noParam;
	actRawDataStruct         *rawData;
	STUB_INT                 receivedByte;
	queryData                *queryDataArray;
	STUB_INT                 storedDynamicValue;
	STUB_INT                 currentDynamicValue;
	serverDb::DummyServer    *dummyServerInstance;

	storedDynamicValue = currentDynamicValue = noParam = 0;
	while ( 1 ){
		try{
			buffer= new STUB_CHAR [ 5000 ]; // maximum length of data received/sent can be 5000bits
		}
		catch ( std::bad_alloc &ba ){
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
				<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
				<<__TIME__<<"] exception catched"<<ba.what()<<'\n';
			exit ( 1);
		}
		//create a instance of  actSeriesStruct * getChunckPackets( const u_char * , STUB_INT  );
		dummyServerInstance = new serverDb::DummyServer();
		server::currentConversationChunk = dummyServerInstance->getChunckPackets
			( buffer , -1 , query , 0); //-1 indecates read server greetings packet 
		while ( 1 ){
std::cout<<"Inside Inner While\n";
			for ( STUB_INT i = 0 ; i <= server::currentConversationChunk->noOfPacket ; ++ i){
#ifdef DEBUG
				std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
					<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<
					__TIME__<<"]"<<__FUNCTION__<<"[ PACKET NO]: "<<
					server::currentConversationChunk->actRawData [ i ].
					packetNumber<<'\n'
					<<"[APP-DB]:"<<server::currentConversationChunk->
					actRawData[ i ].appServer<<'\n'
					<<"[LENGTH ]:"<<server::currentConversationChunk->
					actRawData[ i ].length<<'\n'
					<<"[appServer]:"<<server::currentConversationChunk->
					actRawData[ i ].appServer<<'\n';
#endif
				//cheack wheather the data is being sent from SERVER or not ??
				if ( server::currentConversationChunk->actRawData[ i ].appServer
					       	== 0 ){ 
					// if ( flag appServer == 0 , then this a server packet
					//send data to client
					std::cout<<" File Name ["<<__FILE__<<" ] Function [ "
						<<__FUNCTION__<<"] Line ["<<__LINE__<<"] Date\
						Time ["<<__DATE__<<"_"<<__TIME__
						<<"] SENDING DATA :"
						<<server::currentConversationChunk->
						actRawData[ i ].data
						<<"  -- of length="<<
						server::currentConversationChunk->
						actRawData[ i ].length;
					if (  ( send ( server::clientSockFd ,
								       server::currentConversationChunk->
								       actRawData[ i ].data ,
								       	server::currentConversationChunk->
									actRawData[ i ].length ,
								       	0 ) ) < 0 ) {
						std::cout<<" File Name ["<<__FILE__<<" ] Function [ "
							<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["
							<<__DATE__<<"_"<<__TIME__<<"]"<<"...FAILED\n";
						std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "
							<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["
							<<__DATE__<<"_"<<__TIME__
							<<"]Failure sending message \n";
						close ( server::clientSockFd ) ;
						break ;
					}
					std::cout<<" ...DONE\n";
				}
				else {
					if ( i == 0) ; //if the packet is not a greeting packet, then it must be a packet from client
					else {
						if ( server::currentConversationChunk->actRawData[ i - 1 ].appServer
							       	== 1 ) i++;
						if ( ( receivedByte = recv ( server::clientSockFd  ,
										( void * ) buffer , 4999 , 0 ) )
							       	< 0 ){
							std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "
								<<__FUNCTION__<<"] Line ["<<__LINE__<<"] Date\
								Time ["<<__DATE__<<"_"<<__TIME__
								<<"] ERROR AT RECVDATA\n";
							exit ( EXIT_FAILURE ) ;
						}
						std::cout<<" File Name ["<<__FILE__<<" ] Function [ "
							<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["
							<<__DATE__<<"_"<<__TIME__
							<<"] [Receive byte]:" <<receivedByte<<'\n';
					}
				}
			}
			//currntDynamicValueForDatabase = 0;

			//noedelete server::currentConversationChunk 
			try {
		//		delete []server::currentConversationChunk->actRawData;
		//		delete server::currentConversationChunk;
			}
			catch ( std::exception &e ){
				std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
					<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
					<<__TIME__<<"]"<<"EXCEPTION-:"<<e.what()<<'\n';
				exit ( -1 );
			}

			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
				<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
				<<__TIME__<<"]"<<__FUNCTION__<<
				"now read 1st packet from client\n";
			buffer[0]='\0';
			if ( ( receivedByte = recv ( server::clientSockFd  ,
							( void * ) buffer , 5000 , 0 ) ) < 0 ){
				std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "
					<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["
					<<__DATE__<<"_"<<__TIME__<<"]"<<"Error at receive\
				       	data\n";
				exit ( EXIT_FAILURE ) ;
			}
			 std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
				 <<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
				 <<__TIME__<<"]length of receive bytes:" <<receivedByte<<'\n';
			  //modification done hear depending on protocol the appropriate dissector have to call through 
			  //run time mechanism that will dissect the raw data and will give the query part as 
			 //a string data , and that will be sent for matching with database query to get a significant result.
			 try{
				 rawData = new actRawDataStruct [ 2 ] ;
				 rawData[0].appServer = 1;
				 rawData[0].packetNumber = 0 ;
				 rawData[0].data = new STUB_CHAR [ receivedByte + 1 ];
				 memcpy ( rawData[0].data , buffer , receivedByte );
				 rawData[0].data [ receivedByte ] = '\0';
				 std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
					 <<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
					 <<__TIME__<<"]PrSTUB_INTing received data\n";

				 for ( STUB_INT ii=0 ; ii<receivedByte ; ++ ii)  
					 std::cout<<rawData[0].data[ii]<<"::";
				 rawData[0].length = receivedByte - 1 ;
			//	 rawData[1].length = -999;
			//	 rawData[1].appServer = -999;
				 queryDataArray = new queryData [ 1 ] ;
				
			 }
			 catch ( std::bad_alloc &ba ){
				 std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
					 <<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
					 <<__TIME__<<"]"<<"exception \
					 caught ="<<ba.what()<<std::endl;
				 
			 }
			 
			 /*-----------------------------------------------------------------------------
			  *  if protocol is mysql there may be some query with dynamic field( statement id)
			  *  the dynamic data sent from client may be varies with respect to protocols
			  *  hence different logic for each protocol--as present only mysql still am using --
			  *  switch case for protocols differ
			  *-----------------------------------------------------------------------------*/
//			 switch ( protocol ){
//				 case MYSQL:
				

			 /*-----------------------------------------------------------------------------
			  *  current dynamic value( is statement id ), 
			  *  returns 0 -- no dynamic value
			  *  >0 dynamic value
			  *-----------------------------------------------------------------------------*/

					currentDynamicValue =  Mysql::getQueryOnly( rawData , queryDataArray ,
						       	0 , noParam );
					std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
						"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
						"]"<<__FUNCTION__<<"CLIENT WANT'S REPLY FOR QUERY["<<
						queryDataArray->query<<"]\n";
					if ( currentDynamicValue == 0 ){ // no dynamic value
						storedDynamicValue = 0;
						server::currentConversationChunk = 
							dummyServerInstance->getChunckPackets
							( buffer , receivedByte , queryDataArray ,
							  storedDynamicValue);
						noParam = server::currentConversationChunk->deltaValue2;
					/*	if ( server::currentConversationChunk->dynamicFlagValue < 0 ){
							storedDynamicValue = 
								server::currentConversationChunk->dynamicFlagValue;
*/

							/*-----------------------------------------------------
							 * ------------------------
							 *  modify response packet by pushing new statement id
							 *----------------------------------------------------
							 -------------------------*/
			//				createResponseWIthDynamicValue(queryDataArray ,
			//				dynamicValueGlobal  );
	//					}
					} else if ( currentDynamicValue > 0 ){
						server::currentConversationChunk = 
							dummyServerInstance->getChunckPackets
							( buffer , receivedByte , queryDataArray ,
							  storedDynamicValue );
					}
						
					std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
						<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
						<<__TIME__<<"]"<<"No of p-acket "<<
						server::currentConversationChunk->noOfPacket<<'\n';
//			 }
			 try{
		//		 delete []rawData;
		//		 delete []queryDataArray;

			 }
			 catch ( std::exception &e ){
				 std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
					 <<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<
					 __TIME__<<"]"<<"[Exception]:"<<e.what()<<'\n';
			 }
			 
		}
		
	}
	return true;
	
}


