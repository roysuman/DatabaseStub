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
#ifndef BUFFER_H_
#define BUFFER_H_
#include<iostream>
#include <thread>
#include <list>
#include <algorithm>
#include <mutex>
#include <string.h>
#include <pthread.h>

#include "packetDataStructure.hpp"
extern pthread_mutex_t lock;
#define BUFFER_SIZE 100
//each tcp packet( network packet ) has some flags that helps to understand the type of packet. 
//        URG (1 bit) – indicates that the Urgent poVS_INT32er field is significant
//        ACK (1 bit) – indicates that the Acknowledgment field is significant. All packets after the initial SYN packet sent by the client should have this flag set.
//        PSH (1 bit) – Push function. Asks to push the buffered data to the receiving application.
//        RST (1 bit) – Reset the connection
//        SYN (1 bit) – Synchronize sequence numbers. Only the first packet sent from each end should have this flag set. Some other flags change meaning based on this flag, and some are only valid for when it is set, and others when it is clear.
//        FIN (1 bit) – No more data from sender


typedef struct _net_flags_ net_flags;
struct _net_flags_{
	VS_BOOL    URG;
	VS_BOOL    ACK;
	VS_BOOL    PSH;
	VS_BOOL    RST;
	VS_BOOL    SYN;
	VS_BOOL    FIN;
};
typedef struct _rawNetData_ rawNetData;
struct _rawNetData_{
	std::string     sourceIp;
	std::string     destinationIp;
	VS_UINT16        sourcePort;
	VS_UINT16        destinationPort;
	VS_UINT32        sequenceNumber;
	VS_UINT32        acknowledgeNumber;
	net_flags        networkTcpFlags;
	const VS_UINT8    *data;
	VS_UINT32        dataLength;
	std::string     dateTime;

};
class Buffer{
	private:
		static VS_BOOL              signal;
		static raw_net_data_struct    *buffer;
		static VS_UINT64            buff_obj_count;
		static VS_INT32               read_head;
		static VS_INT32               write_head;
		static VS_BOOL              buffer_init;
		static std::mutex        buffer_mutex_lock;
		static VS_UINT64            buffer_read_count;
		static VS_UINT64            buffer_write_count;
		pthread_t                 sniffing_thread;
		pthread_t                grouping_thread;  

	public:
		Buffer();
		~Buffer();
		VS_BOOL init_buffer();
		VS_BOOL give_signal();
		VS_BOOL check_signal();
		VS_INT32 write_buffer( raw_net_data_struct *& );
		VS_INT32 read_buffer( VS_UINT64 , raw_net_data_struct*& );

};

#endif
