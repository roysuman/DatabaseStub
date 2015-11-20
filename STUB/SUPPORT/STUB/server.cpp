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
// *         Author:  SUMAN ROY (), suman.roy@cognizant.com
// *   Organization:  COGNIZANT TECHNOLOGICAL SOLUTIONS
// *
// * =====================================================================================
// */
#include "server.hpp"
 actSeriesStruct *  server::currentConversationChunk = NULL;
 int server::serverSockFd;
 int server::clientSockFd;
 server::DummyServer::DummyServer(){}
 server::DummyServer::~DummyServer(){}
/*
// *Function that will create a server on provided port and will return the socketFd for server
 * */
 int server::DummyServer::createServer( std::string serverIp , int serverPort ){
	 std::cout<<"FUNCTION:"<<__FUNCTION__<<'\n';
	 std::cout<<__FUNCTION__<<"[IP Address]:"<<serverIp.c_str()<<"[port ]:"<<serverPort<<'\n';
	 struct sockaddr_in servAddress;
	 int socketFd  = 0 ;
	 if ( ( socketFd = socket ( AF_INET ,   SOCK_STREAM , 0 ) ) < 0 ){
		 std::cout<<__FUNCTION__<<"socket failure\n";
		 exit (EXIT_FAILURE);
	 }
	 bzero( ( char * ) &servAddress, sizeof( servAddress ) );
	 servAddress.sin_family = AF_INET;
	 servAddress.sin_port = htons ( serverPort );
	 servAddress.sin_addr.s_addr = inet_addr ( serverIp.c_str() ) ;// INADDR_ANY ;//inet_addr ( c_ip );
     if ( ( bind ( socketFd , ( struct sockaddr * )&servAddress , sizeof( struct sockaddr ) ) ) < 0 ) {
         std::cerr <<__FUNCTION__<<"Could not bind server at [ IP ]: " << serverIp << "[ Port]: " << serverPort <<'\n';
         // exit(EXIT_FAILURE );
         return -1;
		    
         }
	 if ( ( listen ( socketFd , 10 ) ) < 0 ){
		 std::cerr<<__FUNCTION__<<"Listening Failure \n";
		 return -2;
		}
	 server::serverSockFd = socketFd;
	 return socketFd ;
 }

///*
// *Function that will accep client request... and will return client socketFd
// * */


void * server::DummyServer::acceptClient( void * threadId ){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<'\n';
	pthread_t *thread = ( pthread_t * )threadId;
	void *status;
	int serverSockfd = server::serverSockFd ;
	sockaddr_in clientAddress;
	int clientFd;
	socklen_t size = sizeof (  sockaddr_in ) ;
	while ( 1 ){
		if ( ( clientFd = accept ( serverSockfd , ( struct sockaddr * )&clientAddress , &size ) ) < 0 ){
			std::cerr<<__FUNCTION__<<"can't accept client\n ";
			exit ( EXIT_FAILURE ) ;
		}
		std::cout<<__FUNCTION__<<"Server got connection from >>"<<inet_ntoa ( clientAddress.sin_addr )<<'\n';
		if ( clientFd > 0 ){
			server::clientSockFd = clientFd;
			int rc =pthread_join( *thread, &status);
			std::cout<<__FUNCTION__<<"Thread Join status="<<rc<<'\n';
			// after geting the connection play with data
			server::DummyServer *instance = new server::DummyServer();
			instance->actWithData();
		}
	}
}


///
void * server::playWithData( void * threadId ){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<'\n';
	server::DummyServer *instance = new server::DummyServer();
	instance->actWithData();
	return NULL;
}



/*
// *this function will start communication and data transfer between client and server
//
  */
bool server::DummyServer::actWithData(){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<'\n';
	while ( 1 ){
		char *buffer;
		int receivedByte;
		try{
			buffer= new char [ 5000 ];
		}
		catch ( std::bad_alloc &ba ){
			std::cout<<__FUNCTION__<<"exception catched"<<ba.what()<<'\n';
			exit ( 1);
		}
		int number = -1 ;
		//create a instance of  actSeriesStruct * getChunckPackets( const u_char * , int  );
		serverDb::DummyServer *dummyServerInstance = new serverDb::DummyServer();
		queryData *temp;
		server::currentConversationChunk = dummyServerInstance->getChunckPackets( buffer , -1 , temp);
		std::cout<<__FUNCTION__<<"[No of p-acket]"<< (server::currentConversationChunk->noOfPacket + 1 )<<'\n';
		while ( 1 ){
			for ( int i = 0 ; i <= server::currentConversationChunk->noOfPacket ; ++ i){
				std::cout<<__FUNCTION__<<"[ PACKET NO]: "<<server::currentConversationChunk->actRawData [ i ].packetNumber<<'\n'
					<<"[APP-DB]:"<<server::currentConversationChunk->actRawData[ i ].appServer<<'\n'
					<<"[LENGTH ]:"<<server::currentConversationChunk->actRawData[ i ].length<<'\n'
					<<"[appServer]:"<<server::currentConversationChunk->actRawData[ i ].appServer<<'\n';
				//   <<"raw packet "<<i<<" ="<<server::currentConversationChunk->actRawData[ i ].data <<std::endl;
				//cheack wheather the data is being sent from db or not ??
				if ( server::currentConversationChunk->actRawData[ i ].appServer == 0 ){ // sent from DB
					//send data to app
					std::cerr<<__FUNCTION__<<"send data; i ="<<i<<"of length="<<server::currentConversationChunk->actRawData[ i ].length<<'\n';
					if (  ( send ( server::clientSockFd , server::currentConversationChunk->actRawData[ i ].data , server::currentConversationChunk->actRawData[ i ].length , 0 ) ) < 0 ) {
						std::cerr<<__FUNCTION__<<"Failure sending message \n";
						close ( server::clientSockFd ) ;
						break ;
					}
					std::cout<<__FUNCTION__<<"send data="<<server::currentConversationChunk->actRawData[ i ].data
						<<"-- of length="<<server::currentConversationChunk->actRawData[ i ].length<<'\n';
					//          for ( int j = 0 ; j< server::currentConversationChunk->actRawData[ i ].length ; ++j ){
					//                 //std::cout<<server::currentConversationChunk->actRawData[ i ].data[j];
					//             }
					
				}
				else {
					if ( i == 0) ;
					else {
						if ( server::currentConversationChunk->actRawData[ i - 1 ].appServer == 1 ) i++;
						if ( ( receivedByte = recv ( server::clientSockFd  ,( void * ) buffer , 5000 , 0 ) ) < 0 ){
							std::cerr<<__FUNCTION__<<"ERROR AT RECVDATA\n";
							exit ( EXIT_FAILURE ) ;
						}
						std::cout<<__FUNCTION__<<"[Receive byte]:" <<receivedByte<<'\n';
					}
				}
			}
			std::cout<<__FUNCTION__<<"now read 1st packet from db\n";
			buffer[0]='/0';
			if ( ( receivedByte = recv ( server::clientSockFd  ,( void * ) buffer , 5000 , 0 ) ) < 0 ){
				std::cerr<<__FUNCTION__<<"Error at receive data\n";
				exit ( EXIT_FAILURE ) ;
			}
			 std::cout<<__FUNCTION__<<"receive byte:" <<receivedByte<<'\n';
			  //modification done hear depending on protocol the appropriate dissector have to call through run time mechanism that will dissect the raw data and will give the query part as 
			 //a string data , and that will be sent for matching with database query to get a significant result.
			 actRawDataStruct * rawData ;
			 queryData *queryDataArray;
			 try{
				 rawData = new actRawDataStruct [ 2 ] ;
				 rawData[0].appServer = 1;
				 rawData[0].packetNumber = 0 ;
				 rawData[0].data = new char [ receivedByte + 1 ];
				 memcpy ( rawData[0].data , buffer , receivedByte );
				 rawData[0].data [ receivedByte ] = '\0';
				 for ( int ii=0 ; ii<receivedByte ; ++ ii)  std::cout<<rawData[0].data[ii]<<"::";
				 rawData[0].length = receivedByte - 1 ;
				 rawData[1].length = -999;
				 rawData[1].appServer = -999;
				 queryDataArray = new queryData [ 1 ] ;
				
			 }
			 catch ( std::bad_alloc &ba ){
				 std::cerr<<__FUNCTION__<<"exception caught ="<<ba.what()<<std::endl;
				 
			 }
			 Mysql::getQueryOnly( rawData , queryDataArray );
			 std::cout<<__FUNCTION__<<"coming queryis="<<queryDataArray->query<<std::endl;
			 server::currentConversationChunk = dummyServerInstance->getChunckPackets( buffer , receivedByte , queryDataArray );
			 std::cout<<__FUNCTION__<<"No of p-acket "<<server::currentConversationChunk->noOfPacket<<'\n';
			 try{
				 delete rawData;
			 }
			 catch ( std::exception &e ){
				 std::cerr<<__FUNCTION__<<"[Exception]:"<<e.what()<<'\n';
			 }
			 
		}
		
	}
	return true;
	
}


