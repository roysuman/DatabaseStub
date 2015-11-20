/*
 * =====================================================================================
 *
 *       Filename:  tcp_connection.h
 *
 *    Description:  method for handling all connection socket of server
 *
 *        Version:  1.0
 *        Created:  Tuesday 06 October 2015 11:25:25  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  ROY (), email.suman.roy@gmail.com
 *   Organization:  NA
 *
 * =====================================================================================
 */
#ifndef TCP_CONNECTION_H
#define TCP_CONNECTION_H

#include<iostream>
#include <pthread.h>                                               
#include <sys/socket.h>
#include <netinet/in.h>                                            
#include <arpa/inet.h>
#include <netdb.h>                                                 
#include <unistd.h>                                                
#include <errno.h>                                                 
#include <fcntl.h>

class TcpConnection{
	protected:
		typedef enum{
			connection_open = 1,
			connection_closing =2,
			connection_closed = 3,
			connection_error = 4
		}connection_state_types;
	public:
		TcpConnection(uint32_t connection_id , int socket,uint32_t port);
		virtual ~TcpConnection();
		bool send(const unsigned char*, size_t length);
		void disconnect(void);
	protected:
		 
		inline uint32_t return_id(void) const { return connection_id;}
		inline int return_socket_id(void) const { return socket_id;}
		inline uint32_t return_port(void) const { return bind_port;}
		inline bool is_connected() const { return ( tcp_con_type == connection_open ); }

		/* connection state variable */
		connection_state_types    tcp_con_state;

		bool process_receive_data(void);
		bool recv_data(void);
		bool send_data(void);
		void buffer_make_empty(void);
		uint32_t   connection_id;
		int socket_id;
		uint32_t bind_port;

		/*-----------------------------------------------------------------------------
		 *  send buffer variables
		 *-----------------------------------------------------------------------------*/
		unsigned char* send_buffer;
		size_t         send_buffer_capacity;
		size_t         send_buffer_used;
		void   send_buffer_push( const unsigned char *data,size_t length);
		void   send_buffer_push_front( const unsigned char *data,size_t length);
		bool   send_buffer_pop(unsigned char**,size_t *length);

		/*-----------------------------------------------------------------------------
		 *  recv buffer variables
		 *-----------------------------------------------------------------------------*/

		unsigned char* recv_buffer;
		size_t recv_buffer_capacity;
		size_t recv_buffer_used;
		/* process connection loop */
		virtual void process( void );
		bool connection_is_active;
		static void* run_loop_process_connection(void *temp);



		
	private:
		void disconnect_connection(void);
		pthread_t loop_thread;
};
#endif
