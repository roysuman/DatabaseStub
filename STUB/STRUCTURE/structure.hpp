#ifndef STRUCTURE_HPP_
#define STRUCTURE_HPP_
#include "iostream"
#include <sqlite3.h>
#include<string.h>
#include<stdlib.h>
#include <stdint.h>
#include <unordered_map>
#include <typeinfo>
//configstruct_hpp
//structure for json.cofig file
typedef struct _configTcpStub configTcpStub;
struct _configTcpStub {
	bool traceLog;
	bool errorLog;
	bool log;
	std::string dummyServerIp;
	int dummyServerPort;
	std::string sniffingIp;
	int sniffingPort;
};

extern configTcpStub configTcpFile;

// database_struct.hpp

//Structure for dtoring database information , like db pointer, database name and path(location) of the database in local machine.
typedef struct _database databaseStruct;
struct _database{
	sqlite3 *db;
	std::string databaseName;
	std::string databasePath;
	
};
//varibale for stroting information of open sqlite3 database.
extern databaseStruct dbCredentials;
//during capture mode of this tool, we are going to filter network packets regarding to the server IP/Port. 
//suppose we are going to capture mysql packets coming from mysql server x.x.x.x and port 3306. This server struct holds the informations of 
//client/source of server that is our source of packets.

typedef struct _serverStructure serverStruct;
struct _serverStructure{
	std::string serverName;
	std::string serverType;
	std::string serverIp;
	std::string serverPort;
};

//one variable, that will hold the server information.
extern serverStruct serverCredentials;


//rawdatastructure.hpp

extern bool initDataStructure ();
//each tcp packet( network packet ) has some flags that helps to understand the type of packet. 
//        URG (1 bit) – indicates that the Urgent pointer field is significant
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
	uint16_t sourcePort; // source port of the packet( from where the packet is coming)
	uint16_t destinationPort; //destination port of tha packet ( where the packet is going)
	uint32_t sequenceNumber; // sequence no. of this packet
	uint32_t acknowledgeNumber;// acknowledge no. of this packet
	tcpFlagStruct tcpFlag;//containdall the flag information mentioned above
	const u_char * data; //the real datagram.
	uint32_t length;// length of the data

};
//extern rawDataStruct rawData;
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
	int conversationId;
	prevPacket *allPreviousPacketApp  ;
	prevPacket *allPreviousPacketDb ;
	int currentPositionAppArray ;
	int currentPositionDbArray ;
};

extern conversation conversationDiary[ 1000 ]; // conversation diary can be maximum 1000

//some init function
extern bool init();

extern void  printData( int );

//the following structures for managing dummy server
//the following structure holds a single raw packet.
	
typedef struct _actRawDataStruct actRawDataStruct;

struct _actRawDataStruct{
        int appServer ; // to indicte this data is for server or db
        int packetNumber; // on which number this packet came
        char *data; //the raw dat
        int length ; // length of the data
};

//the following structure holds all the raw packets under a conversationId.
typedef struct _actSeriesStruct actSeriesStruct;
struct _actSeriesStruct {
	int converationId;
	int seqNumber; // basically
	int noOfPacket;
	actRawDataStruct *actRawData; // array of actRawDataStruct to hold all the raw packets for a particular conversation.
};
extern actSeriesStruct actConversationDiary [ 1000 ];
extern actSeriesStruct *newConversationPack;
//to generate new packet data from a captured data, we need to coppy some relevant bits from the captured packet to newlly gen packet.
//the following method helps to implement that coppy part.--it's a typical method 
extern bool copyConversationPartially(actSeriesStruct *& ,  actSeriesStruct* , int , int , int , int); // conversation id , from packet , to packet , last packet until offset.

//after grooping the packets under a conversation id--we need to know the query type and the query body( human readable stringformat)
//this information we can know only after dissecting the query.We will store the raw packet into the db along with these informations.
//thus this query boyd will help to match the appropriate response when dummy serer will be in action.
typedef struct _queryData queryData;

struct _queryData {
	int packetNo;
	std::string queryType;
	std::string query;
	
};

//map for storing query data
typedef std::unordered_map < int , std::string > _colDetails ;
//another map to store _colDetails with respect to filed name.
typedef std::unordered_map < int ,std::string  > _colInfo;

//structure needed to handle query for update and insert new quety using Json
typedef struct _queryPacketJson queryPacketJson;
struct _queryPacketJson{
        std::string query;
	std::string queryType;
        int rowCount;
	int flag;  // if  needed in furture
        _colDetails colNames;
        _colInfo  colInfo;

};
extern queryPacketJson QueryPacket;
//the following structure for all the columns data that will be insert one by one.
//as my mysql genarate packet code is old one, and was taking data from console one
//by one, so we will store one by one data ito a STL map colInfo.
typedef struct _insertRowValues insertRowValues;
struct  _insertRowValues{
	int totalRow; //total no or row at response data
        int totalSize; //total size of data
	std::string query; // the query

	_colInfo colInfo; 
};

extern insertRowValues colByColDataTogether;

extern bool flagForGenerateQuery;


//scenariostruct.hpp
//under a project there may be different scenarios--this structure for storing scenario information
typedef struct _scenarioInformation scenarioInformation;

struct _scenarioInformation{
	std::string scenarioName;
	std::string catagory;
	std::string protocol;
	std::string server;
	std::string portNo;
};
//one global variable for holding scenario information
extern scenarioInformation scenInfo;
extern template < class T > deleteStruct( T structVariable );


#endif
