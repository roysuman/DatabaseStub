/*
 * =====================================================================================
 *
 *       Filename:  tcp_server.h
 *
 *    Description:  base tcp server code
 *
 *        Version:  1.0
 *        Created:  Wednesday 07 October 2015 11:14:08  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  ROY (), email.suman.roy@gmail.com
 *   Organization:  NA
 *
 * =====================================================================================
 */
#ifndef TCP_SERVER_H
#define TCP_SERVER_H
#include <iostream>
#include<vector.h>
#include<queue.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>

#define SOCKET_ERROR -1
class BaseTcpServer{
	public:
		BaseTcpServer(uint32_t port);
		virtual ~BaseTcpServer();
		bool create_server(uint32_t port=0);
		void close_socket(void );
		bool is_server_active( void );
		inline uint32_t get_port( void ) const{ return server_port;}
		inline uint32_t get_next_id(void ) const { return next_id++;}
	protected:
		virtual void create_new_connection( size_t conection_id,int acp_socket , uint32_t port) =0;
		static void* run_loop_to_accept_connection( void* );
		void stop_loop(void);
		void listen_new_connection(void);
		size_t next_id;
		bool run_loop_stat;
		int  server_sock_id;
		uint32_t    server_port;
};
//TODO to register a connection .. search for a free
// free connection... if a free connection is available
// then use that else create a new TcpConnection Object.
// 

template< class T>
class TcpServer : public BaseTcpServer{
	protected:
		std::vector < T *> connection_store;
		std::vector< T*>::iterator store_ite;

	public:
		TcpServer()( uint32_t port){
			BaseTcpServer::BaseTcpServer(port);
		}
		virtual ~TcpServer(){
			stop_loop();


		}
	protected:
		//TODO maintain some queue for accepted connections.
		void register_connection(T *connection){
			//FIXME introduce lock
			connection_store.push_back(connection);
		}
		virtual void process(void){
			/* iterate through the vector and terminate connection */
			for ( store_ite = connection_store.begin(); store_ite != connection_store.end(); ++store_ite;){
				T *con = *store_ite;
				con->change_state(connection_closing);
				delete con;
			}

		}
};

#endif
