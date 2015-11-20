/*
 * =====================================================================================
 *
 *       Filename:  rawdata_structure.hpp
 *
 *    Description:  Most iportant structures are defined in this file.These structures are responcible for temporary 
  		  storing packets information for further processing.
 *
 *        Version:  1.0
 *        Created:  Thursday 07 November 2013 03:24:16  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy (), 
 *   Organization:  SELF
 *
 * =====================================================================================
 */

#ifndef RAWDATA_STRUCTURE_HPP_
#define RAWDATA_STRUCTURE_HPP_
#include <iostream>
#include<string.h>
#include<stdlib.h>
#include <stdint.h>
#include <unordered_map>
#include <typeinfo>
#include "../../SUPPORT/globalDatatypes.hpp"

extern bool initDataStructure ();
extern bool deleteConversationDiary();
//each tcp packet( network packet ) has some flags that helps to understand the type of packet. 
//        URG (1 bit) – indicates that the Urgent poSTUB_INTer field is significant
//        ACK (1 bit) – indicates that the Acknowledgment field is significant. All packets after the initial SYN packet sent by the client should have this flag set.
//        PSH (1 bit) – Push function. Asks to push the buffered data to the receiving application.
//        RST (1 bit) – Reset the connection
//        SYN (1 bit) – Synchronize sequence numbers. Only the first packet sent from each end should have this flag set. Some other flags change meaning based on this flag, and some are only valid for when it is set, and others when it is clear.
//        FIN (1 bit) – No more data from sender


typedef struct _tcpFlag tcpFlagStruct;
struct _tcpFlag{
	bool URG;
	bool ACK;
	bool PSH;
	bool RST;
	bool SYN;
	bool FIN ;

};
//the following structure that stores a raw packet information(captured by lpcap) in a structured way, it'shelpful for further processing.

typedef struct _rawData rawDataStruct;
struct _rawData{
	std::string protocolName; // protocol name
	uint16_t sourcePort; // source port of the packet( from where the packet is coming)
	uint16_t destinationPort; //destination port of tha packet ( where the packet is going)
	uint32_t sequenceNumber; // sequence no. of this packet
	uint32_t acknowledgeNumber;// acknowledge no. of this packet
	tcpFlagStruct tcpFlag;//containdall the flag information mentioned above
    const u_char * data; //the real datagram.
	uint32_t length;// length of the data

};
extern rawDataStruct rawData;
//


//all packets ar communicating between a client and a server, it's mainly a client server model.
//a client is sending a query to the server and server sending back the result set to the client.
//the query being sebd by the client or the response from server end may contain 1/2.. tcp packets. We are grooping this communication between 
//client and server by a unique conversation id.The following structure helps to perform the grooping of packets under a unique conversation id. 
typedef struct _prevPacket prevPacket;
struct _prevPacket{
	uint32_t prevSequenceNumber;
	uint32_t prevAcknowledgeNumber;
	uint32_t prevLength;
	tcpFlagStruct tcpFlag;
};
//a variable of _prevPacket
extern prevPacket pastData;

//groop all packets under a single conversationID
typedef struct _conversation conversation;
struct _conversation{
	STUB_INT conversationId;
	prevPacket *allPreviousPacketClient  ;
	prevPacket *allPreviousPacketServer ;
	STUB_INT currentPositionClientArray ;
	STUB_INT currentPositionServerArray ;
};

extern conversation conversationDiary[ 1000 ]; // conversation diary can be maximum 1000

//some init function
extern bool init();

extern void  printData( STUB_INT );

//the following structures for managing dummy server
//the following structure holds a single raw packet.
	
typedef struct _actRawDataStruct actRawDataStruct;

struct _actRawDataStruct{
	std::string protocolName;
	STUB_INT portNumber;
        STUB_INT appServer ; // to indicte this data is for server or db
        STUB_INT packetNumber; // on which number this packet came
        STUB_CHAR *data; //the raw dat
        STUB_INT length ; // length of the data
};

//the following structure holds all the raw packets under a conversationId.
typedef struct _actSeriesStruct actSeriesStruct;
struct _actSeriesStruct {
	STUB_INT converationId;
	STUB_INT seqNumber; // basically
	STUB_INT noOfPacket;
	actRawDataStruct *actRawData; // array of actRawDataStruct to hold all the raw packets for a particular conversation.
	STUB_INT dynamicFlagValue; //indicates presence of dynamic value
	STUB_INT deltaValue2;


};
extern actSeriesStruct actConversationDiary [ 1000 ];
extern actSeriesStruct *newConversationPack;
extern bool deleteActSeriesStruct( actSeriesStruct *&);
//to generate new packet data from a captured data, we need to coppy some relevant bits from the captured packet to newlly gen packet.
//the following method helps to implement that coppy part.--it's a typical method 
extern bool copyConversationPartially(actSeriesStruct *& ,  actSeriesStruct* , STUB_INT , STUB_INT , STUB_INT , STUB_INT); // conversation id , from packet , to packet , last packet until offset.

//after grooping the packets under a conversation id--we need to know the query type and the query body( human readable stringformat)
//this information we can know only after dissecting the query.We will store the raw packet into the db along with these informations.
//thus this query boyd will help to match the appropriate response when dummy serer will be in action.
typedef struct _queryData queryData;

struct _queryData {
	STUB_INT packetNo;
	std::string queryType;
	std::string query;
	bool flagForGrouping; //this flag used to group packets under one statement id ( specially for MYSQL )
	STUB_INT deltaValue;
};

//map for storing query data
typedef std::unordered_map < STUB_INT , std::string > _colDetails ;
//another map to store _colDetails with respect to filed name.
typedef std::unordered_map < STUB_INT ,std::string  > _colInfo;

//structure needed to handle query for update and insert new quety using Json
typedef struct _queryPacketJson queryPacketJson;
struct _queryPacketJson{
        std::string query;
	std::string queryType;
        STUB_INT rowCount;
	STUB_INT flag;  // if  needed in furture
        _colDetails colNames;
        _colInfo  colInfo;

};
extern queryPacketJson QueryPacket;
//the following structure for all the columns data that will be insert one by one.
//as my mysql genarate packet code is old one, and was taking data from console one
//by one, so we will store one by one data ito a STL map colInfo.
typedef struct _insertRowValues insertRowValues;
struct  _insertRowValues{
	STUB_INT totalRow; //total no or row at response data
        STUB_INT totalSize; //total size of data
	std::string query; // the query

	_colInfo colInfo; 
};

extern insertRowValues colByColDataTogether;

extern bool flagForGenerateQuery;

#endif

