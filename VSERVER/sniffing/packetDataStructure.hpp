#ifndef PACKETDATASTRUCTURE_H
#define PACKETDATASTRUCTURE_H 
#include<iostream>
#include<stdlib.h>
#include<string>
#include <unistd.h>
#include<stdint.h>
#include "../common/vserver_datatype.h"
//each tcp packet( network packet ) has some flags that helps to understand the type of packet. 
//        URG (1 bit) – indicates that the Urgent pointer field is significant
//        ACK (1 bit) – indicates that the Acknowledgment field is significant. All packets after the initial SYN packet sent by the client should have this flag set.
//        PSH (1 bit) – Push function. Asks to push the buffered data to the receiving application.
//        RST (1 bit) – Reset the connection
//        SYN (1 bit) – Synchronize sequence numbers. Only the first packet sent from each end should have this flag set. Some other flags change meaning based on this flag, and some are only valid for when it is set, and others when it is clear.
//        FIN (1 bit) – No more data from sender


typedef struct _net_flags_struct_ net_flags_struct;
struct _net_flags_struct_{
	VS_BOOL    URG;
	VS_BOOL    ACK;
	VS_BOOL    PSH;
	VS_BOOL    RST;
	VS_BOOL    SYN;
	VS_BOOL    FIN;
};
typedef struct _raw_net_data_struct_ raw_net_data_struct;
struct _raw_net_data_struct_{
	std::string         source_ip;
	std::string         destination_ip;
	VS_UINT16           source_port;
	VS_UINT16           destination_port;
	VS_UINT32           sequence_number;
	VS_UINT32           acknowledge_number;
	net_flags_struct    tcp_flags;
//	const u_char    *data;
	VS_UINT32           data_length;
	std::string         date_time;

};
//all packets ar communicating between a client and a server, it's mainly a client server model.
//a client is sending a query to the server and server sending back the result set to the client.
//the query being sebd by the client or the response from server end may contain 1/2.. tcp packets. We are grooping this communication between 
//client and server by a unique conversation_struct id.The following structure helps to perform the grooping of packets under a unique conversation_struct id. 
typedef struct _prev_net_packet_struct_ prev_net_packet_struct;
struct _prev_net_packet_struct_{
	VS_UINT32           sequence_number;
	VS_UINT32           acknowledge_number;
	VS_UINT32           data_length;
	net_flags_struct    tcp_flags;
};
//group all packets under a unique conversation_struct id
typedef struct _conversation_struct conversation_struct;
struct _conversation_struct{
	VS_UINT64                 conversation_id;
	prev_net_packet_struct    *source_previous_packets;//source meane... my machine
	prev_net_packet_struct    *destination_previous_packets;
	VS_UINT64                 current_index_source_array;
	VS_UINT64                 current_index_destination_array;
};

//conversation_struct converationDiary[ 1000];



#endif /* PACKETDATASTRUCTURE_HPP */
