/*
 * this is for creating new data for mysql protocol
 */
#ifndef PACKET_MYSQL_HPP_
#define PACKET_MYSQL_HPP_
#include <iostream>
#include "../DISSECTOR/proto.hpp"
#include "../DISSECTOR/types.hpp"
#include "../DISSECTOR/buffer.hpp"
#include "../DISSECTOR/field.hpp"
#include "../../STRUCTURE/sumanGtkmm.hpp"
#include "../DISSECTOR/proto_mysql.hpp"


#define PORT_MYSQL 3306
extern int colNoGlobal;
extern int noOfFields;
extern bool rowPacketOffsetFlag;

class CreatePacketMysql{
        public:
		int rowPacketOffsetStart;
		int eofPacketOffsetStart;
	        bool isFof;
		int prevPacketTillInserted;
		actSeriesStruct *newConversation;

		actSeriesStruct *conversationPackets;
		bool initialize(  void );
		bool dissectMysql( actRawDataStruct * , int , int);
		//dissect mysql client request
        gint mysqlDissectRequest( actRawDataStruct * , int , proto::fieldInfo * , int );
		//dissect response 
        gint mysqlDissectResponse ( actRawDataStruct * , int , proto::fieldInfo * , int );
		//for fle 
		int tvbGetFle ( actRawDataStruct * , int , guint64 * );
		//dissect result/response from db header
		int mysqlDissectResultHeader ( actRawDataStruct * , int );
		//dissect field packet
        int mysqlDissectFieldPacket ( actRawDataStruct * , int , proto::fieldInfo * );
		//dissect flag server status
		int mysqlDissectServerStatus ( actRawDataStruct * , int );
		// Dissect row packet
        int mysqlDissectRowPacket ( actRawDataStruct * , int , proto::fieldInfo * );
		//for generating new packet
                int mysqlGenarateRequestPacket ( int , int , int );
		//generate response packet for query
         int mysqlGenarateResponsePacket ( actRawDataStruct * , int , int ,   int , int );
        
};
extern int prevQueryState;


#endif
