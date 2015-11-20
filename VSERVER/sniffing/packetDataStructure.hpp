#ifndef PACKETDATASTRUCTURE_H
#define PACKETDATASTRUCTURE_H 
#include<iostream>
#include<stdlib.h>
#include<string>
#include <unistd.h>
#include<stdint.h>
//#define PRINT DATE<<"_"<<TIME<<" [ "<<FILE<<" ] [ "<<FUNCTION<<" ] [ "<<LINE<<" ] "
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
	netFlags    networkTcpFlags;
//	const u_char    *data;
	uint32_t        dataLength;
	std::string     dateTime;

};
//all packets ar communicating between a client and a server, it's mainly a client server model.
//a client is sending a query to the server and server sending back the result set to the client.
//the query being sebd by the client or the response from server end may contain 1/2.. tcp packets. We are grooping this communication between 
//client and server by a unique conversation id.The following structure helps to perform the grooping of packets under a unique conversation id. 
typedef struct _prevNetPacket_ prevNetPacket;
struct _prevNetPacket_{
	uint32_t        sequenceNumber;
	uint32_t        acknowledgeNumber;
	uint32_t        dataLength;
	netFlags    networkTcpFlags;
};
//group all packets under a unique conversation id
typedef struct _conversation conversation;
struct _conversation{
	size_t    conversationId;
	prevNetPacket    *sourcePreviousPackets;//source meane... my machine
	prevNetPacket    *destinationPreviousPackets;
	size_t               currentIndexSourceArray;
	size_t               currentIndexDestinationArray;
};

//conversation converationDiary[ 1000];



#endif /* PACKETDATASTRUCTURE_HPP */
