/*
 * =====================================================================================
 *
 *       Filename:  buffer.hpp
 *
 *    Description:  buffer management for shared data between two threades
 *
 *        Version:  1.0
 *        Created:  Friday 01 May 2015 10:37:40  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  ROY (), email.suman.roy@gmail.com
 *   Organization:  NA
 *
 * =====================================================================================
 */
#ifndef BUFFER_HPP_
#define BUFFER_HPP_
#include<iostream>
#include <thread>
#include <list>
#include <algorithm>
#include <mutex>
#include<string.h>
#include "packetDataStructure.hpp"
extern pthread_mutex_t lock;
#define BUFFER_SIZE 100
//each tcp packet( network packet ) has some flags that helps to understand the type of packet. 
//        URG (1 bit) – indicates that the Urgent pointer field is significant
//        ACK (1 bit) – indicates that the Acknowledgment field is significant. All packets after the initial SYN packet sent by the client should have this flag set.
//        PSH (1 bit) – Push function. Asks to push the buffered data to the receiving application.
//        RST (1 bit) – Reset the connection
//        SYN (1 bit) – Synchronize sequence numbers. Only the first packet sent from each end should have this flag set. Some other flags change meaning based on this flag, and some are only valid for when it is set, and others when it is clear.
//        FIN (1 bit) – No more data from sender


typedef struct _netFlags_ netFlags;
struct _netFlags_{
	bool    URG;
	bool    ACK;
	bool    PSH;
	bool    RST;
	bool    SYN;
	bool    FIN;
};
typedef struct _rawNetData_ rawNetData;
struct _rawNetData_{
	std::string     sourceIp;
	std::string     destinationIp;
	uint16_t        sourcePort;
	uint16_t        destinationPort;
	uint32_t        sequenceNumber;
	uint32_t        acknowledgeNumber;
	netFlags        networkTcpFlags;
	const u_char    *data;
	uint32_t        dataLength;
	std::string     dateTime;

};
class Buffer{
	private:
		static bool              signal;
		static __rawNetData__    *buffer;
		static size_t            buff_obj_count;
		static int               read_head;
		static int               write_head;
		static bool              buffer_init;
		static std::mutex        buffer_mutex_lock;
		static size_t            buffer_read_count;
		static size_t            buffer_write_count;
		pthrad_t                 sniffing_thread;
		pthread_t                grouping_thread;  

	public:
		Buffer();
		~Buffer();
		bool init_buffer();
		bool give_signal();
		bool check_signal();
		int write_buffer( __rawNetData__ *& );
		int read_buffer( size_t , __rawNetData__*& );

};

#endif
