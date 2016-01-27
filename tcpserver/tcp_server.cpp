/*
 * =====================================================================================
 *
 *       Filename:  tcp_server.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Thursday 08 October 2015 12:22:51  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  ROY (), email.suman.roy@gmail.com
 *   Organization:  NA
 *
 * =====================================================================================
 */
#include "tcp_server.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  BaseTcpServer
 *  Description:  the constructor.. which will initialize some
 *                variables and will start the client acceptence loop
 * =====================================================================================
 */
BaseTcpServer::BaseTcpServer( uint32_t port){
	next_id =1;
	server_port = port;
	run_loop_stat = true;
	server_sock_id = 0;
	/* start the connection acceptence loop */
	pthread_t loop_thread;
	pthread_create( &loop_thread , nullptr,&BaseTcpServer::run_loop_to_accept_connection,this);
	return;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ~BaseTcpServer
 *  Description:  stop the server .. make sue all connections got close
 *                before closing the server
 * =====================================================================================
 */
BaseTcpServer::~BaseTcpServer(){
	stop_loop();
	return;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  stop_loop
 *  Description:  stop the connection accepting loop
 * =====================================================================================
 */
void
BaseTcpServer::stop_loop(void){
	//TODO add lcok
	if ( run_loop_stat ){
		run_loop_stat = false;
	}
	return;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  run_loop_to_accept_connection
 *  Description:  loop handler for accepting connection
 * =====================================================================================
 */
void*
BaseTcpServer::run_loop_to_accept_connection( void *temp){
	if ( temp == NULL ){
		return nullptr;
	}
	BaseTcpServer *tcp_ser = (BaseTcpServer *) temp;
	//TODO loop running lock
	while ( tcp_ser->run_loop_stat ){/* if run loop active */
		thread_sleep( LOOP_GRANULARITY ); /* call server sleep */
		tcp_ser->listen_new_connection();
	}
	return nullptr;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  listen_new_connection
 *  Description:  accept new connection
 * =====================================================================================
 */
void
BaseTcpServer::listen_new_connection(void){
	int   acp_sock;
	uint32_t   acp_port;
	size_t     from_len;
	struct sockaddr_in   from;
	struct in_addr    in_address;

	from.sin_family = AF_INET;
	from_len = sizeof( from );
	if ( server_sock_id == SOCKET_ERROR ) return;
	while ( ( acp_sock = accept( server_sock_id , (struct sockaddr*)&from,&from_len ) ) != SOCKET_ERROR ){
		int buf_size = 64 * 1024;
		setsockopt( acp_sock , SOL_SOCKET , SO_RECVBUF , (char*)&buf_size,sizeof(from.sin_port));
		/* create new connection using the accepted socket descriptor */
		create_new_connection( get_next_id , acp_sock , ntohs(from.sin_port));
	}
	return;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  create_server
 *  Description:  create the server 
 * =====================================================================================
 */
bool
BaseTcpServer::create_server( uint32_t port ){
	bool   return_val;
	struct sockaddr_in address;
	int addr_reuse;

	return_val = true;
	if ( server_sock_id != 0 ){
		std::cerr<<"Socket server already open\n";
		return_val = false;
	}
	if ( return_val ){
		if ( server_port != 0 ){
			server_port = port;
		}
		memset((char*)&address,0,sizeof(address));
		address.sin_family = AF_INET;
		address.sin_port = htons( server_port );
		address.sin_addr.s_addr = htonl( INADDR_ANY);
		/* create socket */
		server_sock_id = socket( AF_INET , SOCK_STREAM, 0 );
		setsockopt( server_sock_id , SOL_SOCKET , SO_REUSEADDR , (char*)&addr_reuse , sizeof(addr_reuse ) );
		if ( bind (server_sock_id , (struct sickaddr *)&address,sizeof(address)) == SOCKET_ERROR ){
			std::cerr<<"bind < 0 \n";
			close(server_sock_id);
			return_val = false;
			server_sock_id = 0;
		}else{
			int buff_size = 64 * 1024;
			setsockopt( server_sock_id, SOL_SOCKET , SO_RECVBUF , (char*)&buff_size , sizeof( buf_size));
			fcntl(server_sock_id , F_SETFL, O_NONBLOCK );
			if ( listen( server_sock_id , SOMAXCONN ) == -1 ){
				close(server_sock_id);
				std::cerr<<"Listen failed , Error[ "<<strerror( errno ) <<"] \n";
				server_sock_id = 0;
				return_val = false;
			}
		}
	}
	return return_val;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  close_socket
 *  Description:  close the socket
 * =====================================================================================
 */
void
BaseTcpServer::close_socket( void){
	stop_loop();
	if ( close( server_sock_id ) == SOCKET_ERROR ){
		std::cer<<"Socket close failed, Error [ "<<strerror(errno)<<"]\n";
	}
	server_sock_id = 0;
	return;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  is_server_active
 *  Description:  server is active or not?
 * =====================================================================================
 */
bool
BaseTcpServer::is_server_active( void){
	bool   return_val;
	return_val = (bool ) ( server_sock_id!= 0 );
	return return_val;
}
