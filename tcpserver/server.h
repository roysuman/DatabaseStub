/*
 * =====================================================================================
 *
 *       Filename:  server.h
 *
 *    Description:  server manager
 *
 *        Version:  1.0
 *        Created:  Thursday 08 October 2015 03:50:50  IST
 *       Revision:  none
 *       Compiler:  g++4.7
 *
 *         Author:  Suman Roy (), suman.roy@cognizant.com
 *   Organization:  Cognizant Technological Solutions
 *
 * =====================================================================================
 */
#ifndef SERVER_H
#define SERVER_H
#include <iostrea>
#include "tcp_server.h"
#include "tcp_connection.h"

class Server:public TcpServer<TcpConnection>{
	public:
		bool create_server( uint32_t port=8080);
		bool close_server(void);
};


#endif
