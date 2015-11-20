/*
 * =====================================================================================
 *
 *       Filename:  proto-mysql.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Wednesday 11 Decembar 2013 12:41:30  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy (email.suman.roy@gmail.com), 
 *   Organization:  SELF
 *
 * =====================================================================================
 */
#ifndef PROTO_MYSQL_HPP_
#define PROTO_MYSQL_HPP_
//thanks wireshark

#include<iostream>
#include <bitset>
#include<string>
#include "proto.hpp"
#include "types.hpp"
#include "buffer.hpp"
#include "field.hpp"
#include "../STRUCTURE/include/globalDatatypes.hpp"
#include "../STRUCTURE/include/rawdata_structure.hpp"
#include "../CORE/DISSECTOR/include/shift_char.hpp"
#include<stdio.h>
#include "jsoncpp/json.h"
#include "jsoncpp/writer.h"
#include "../DBLAYER/DB/capture_packet.hpp"
#include <fstream>
#include "../../../SUPPORT/globalDatatypes.hpp"
#define no_dissector 1
#define PORT_MYSQL 3306
extern STUB_INT JSON;
extern std::string responseDataTogetherForRow;
// client/server capabilities 
#define MYSQL_CAPS_LP 0x0001
#define MYSQL_CAPS_FR 0x0002
#define MYSQL_CAPS_LF 0x0004
#define MYSQL_CAPS_CD 0x0008
#define MYSQL_CAPS_NS 0x0010
#define MYSQL_CAPS_CP 0x0020
#define MYSQL_CAPS_OB 0x0040
#define MYSQL_CAPS_LI 0x0080
#define MYSQL_CAPS_IS 0x0100
#define MYSQL_CAPS_CU 0x0200
#define MYSQL_CAPS_IA 0x0400
#define MYSQL_CAPS_SL 0x0800
#define MYSQL_CAPS_II 0x1000
#define MYSQL_CAPS_TA 0x2000
#define MYSQL_CAPS_RS 0x4000
#define MYSQL_CAPS_SC 0x8000

// field flags 
#define MYSQL_FLD_NOT_NULL_FLAG       0x0001
#define MYSQL_FLD_PRI_KEY_FLAG        0x0002
#define MYSQL_FLD_UNIQUE_KEY_FLAG     0x0004
#define MYSQL_FLD_MULTIPLE_KEY_FLAG   0x0008
#define MYSQL_FLD_BLOB_FLAG           0x0010
#define MYSQL_FLD_UNSIGNED_FLAG       0x0020
#define MYSQL_FLD_ZEROFILL_FLAG       0x0040
#define MYSQL_FLD_BINARY_FLAG         0x0080
#define MYSQL_FLD_ENUM_FLAG           0x0100
#define MYSQL_FLD_AUTO_INCREMENT_FLAG 0x0200
#define MYSQL_FLD_TIMESTAMP_FLAG      0x0400
#define MYSQL_FLD_SET_FLAG            0x0800

// extended capabilities: 4.1+ client only 
#define MYSQL_CAPS_MS 0x0001
#define MYSQL_CAPS_MR 0x0002


// status bitfield 
#define MYSQL_STAT_IT 0x0001
#define MYSQL_STAT_AC 0x0002
#define MYSQL_STAT_MR 0x0004
#define MYSQL_STAT_MU 0x0008
#define MYSQL_STAT_BI 0x0010
#define MYSQL_STAT_NI 0x0020
#define MYSQL_STAT_CR 0x0040
#define MYSQL_STAT_LR 0x0080
#define MYSQL_STAT_DR 0x0100
#define MYSQL_STAT_BS 0x0200

// bitfield for MYSQL_REFRESH 
#define MYSQL_RFSH_GRANT   1   // Refresh grant tables 
#define MYSQL_RFSH_LOG     2   // Start on new log file 
#define MYSQL_RFSH_TABLES  4   // close all tables 
#define MYSQL_RFSH_HOSTS   8   // Flush host cache 
#define MYSQL_RFSH_STATUS  16  // Flush status variables 
#define MYSQL_RFSH_THREADS 32  // Flush thread cache 
#define MYSQL_RFSH_SLAVE   64  // Reset master info and restart slave thread 
#define MYSQL_RFSH_MASTER  128 // Remove all bin logs in the index and truncate the index


/*  MySQL command codes */
#define COM_SLEEP               0  /*  not from client */
#define COM_QUIT                1
#define COM_INIT_DB             2
#define COM_QUERY               3
#define COM_FIELD_LIST          4
#define COM_CREATE_DB           5
#define COM_DROP_DB             6
#define COM_REFRESH             7
#define COM_SHUTDOWN            8
#define COM_STATISTICS          9
#define COM_PROCESS_INFO        10
#define COM_CONNECT             11 /*  not from client */
#define COM_PROCESS_KILL        12
#define COM_DEBUG               13
#define COM_PING                14
#define COM_TIME                15 /*  not from client */
#define COM_DELAY_INSERT        16 /*  not from client */
#define COM_CHANGE_USER         17
#define COM_BINLOG_DUMP         18 /*  replication */
#define COM_TABLE_DUMP          19 /*  replication */
#define COM_CONNECT_OUT         20 /*  replication */
#define COM_REGISTER_SLAVE      21 /*  replication */
#define COM_PREPARE             22
#define COM_EXECUTE             23
#define COM_LONG_DATA           24
#define COM_CLOSE_STMT          25
#define COM_RESET_STMT          26
#define COM_SET_OPTION          27
#define COM_STMT_FETCH          28

typedef enum mysql_state {
	UNDEFINED,
	LOGIN,
	REQUEST,
	RESPONSE_OK,
	RESPONSE_MESSAGE,
	RESPONSE_TABULAR,
	RESPONSE_SHOW_FIELDS,
	FIELD_PACKET,
	ROW_PACKET,
	RESPONSE_PREPARE,
	PREPARED_PARAMETERS,
	PREPARED_FIELDS
} mysql_state_t;


//mysql protocol fiields  
//this variables are used for easy indexing  ..

extern STUB_INT mysqlPacketLength;
extern STUB_INT mysqlPacketNumber;
extern STUB_INT mysqlSchema;
extern STUB_INT mysqlPayload;
extern STUB_INT mysqlNumWarn;
extern STUB_INT mysqlStatementId;
extern STUB_INT mysqlQuery;
extern STUB_INT mysqlExecFlags;
extern STUB_INT mysqlExecIterations;
extern STUB_INT mysqlEOF;
extern STUB_INT mysqlFieldCatalog;
extern STUB_INT mysqlFieldDb;
extern STUB_INT mysqlFieldTable;
extern STUB_INT mysqlFieldOriginalTable;
extern STUB_INT mysqlFieldName;
extern STUB_INT mysqlFieldldOriginalName;
extern STUB_INT mysqlFieldCharsetNumber;
extern STUB_INT mysqlFieldLength;
extern STUB_INT mysqlFieldType;
extern STUB_INT mysqlFieldDecimals;
extern STUB_INT mysqlRowText;
extern STUB_INT mysqlNumFields;
extern STUB_INT mysqlExecParameter;
extern STUB_INT mysqlExecUnsigned;
extern STUB_INT mysqlExecFieldLong;
extern STUB_INT mysqlExecFieldFloat;
extern STUB_INT mysqlExecFieldDouble;
extern STUB_INT mysqlExecFieldString;
extern STUB_INT recentStatementId;

//structure for holding mysql execute dissector field
typedef struct _mysqlExecuteDissector  mysqlExecuteDissector;
struct _mysqlExecuteDissector{
	STUB_UCHAR type;
	STUB_UCHAR flagUnsigned;
	boost::any dissectorMethod;
	STUB_INT   dataType ;
	STUB_INT   length;
};
//extern  mysqlExecuteDissector executeDissectors[ 8 ];



class Mysql{
		public:
			Mysql(){}
			~Mysql(){}
			//current statement id
			static STUB_INT statementId;
			//previous packet no
			static STUB_INT prevPacketNoWithQuery;
			//no of field present at packet response
			static STUB_INT noOFfield;
			//this method will initialize mysql protocols into the mapping structure 
			//by calling functions which are at proto.hpp
			static bool initialize ( void );
			//this function is called to dissect raW DATA  by mysql dissector
			//this is called by dynamic function call
                        static bool dissectMysql( actRawDataStruct * , STUB_INT , actSeriesStruct*);
			
			//dissect mysql client request
                        static STUB_INT mysqlDissectRequest ( actRawDataStruct * , STUB_INT , 
					proto::fieldInfo  * , STUB_INT , actSeriesStruct *);

                        //dissect response
                        static STUB_INT mysqlDissectResponse ( actRawDataStruct *, STUB_INT ,
				       	proto::fieldInfo * , STUB_INT , actSeriesStruct *);
                        //for fle
                        static STUB_INT tvbGetFle(actRawDataStruct *, STUB_INT , 
					STUB_UINT64 *, STUB_UINT8 *);

                        //dissect result/response from db header
                        static STUB_INT mysqlDissectResultHeader( actRawDataStruct *, STUB_INT );
                        //read length encoded string
                        static STUB_INT mysqlFieldAddLestring( actRawDataStruct *, STUB_INT 
				       	, proto::fieldInfo *);

                        //dissect field packet
                        static STUB_INT mysqlDissectFieldPacket ( actRawDataStruct * ,
				       	STUB_INT  ,  proto::fieldInfo *);

                        //dissect flag server status
                        static STUB_INT mysqlDissectServerStatus(  STUB_INT );

                        //dissect row packets
                        static STUB_INT mysqlDissectRowPackets(actRawDataStruct * , STUB_INT ,
				       	proto::fieldInfo * );
                        static STUB_INT getQueryOnly( actRawDataStruct * , queryData *& 
				       	, STUB_INT , STUB_INT );
			//to generate mysqlrequest packet.
			static STUB_INT mysqlGenerateResponsePacket ( actRawDataStruct * 
					, STUB_INT , STUB_INT , STUB_INT , STUB_INT , actSeriesStruct* );
			//to generate mysql respose packet.
			static STUB_INT mysqlGenerateRequestPacket ( STUB_INT , STUB_INT, STUB_INT 
					, actSeriesStruct* );
			//dissect response prepare statement
			static bool mysqlDissectResponsePrepare ( actRawDataStruct * 
					, STUB_INT * );
			//mysql dissect execute statement
			static std::string mysqlDissectRequestExecuteStatement ( 
					actRawDataStruct * , STUB_INT * , proto::fieldInfo * , STUB_INT );
			static std::string mysqlDissectExecParameter( actRawDataStruct * 
					, STUB_INT * , proto::fieldInfo * , STUB_INT );
			//mysql dissection for datatype ( long ,STUB_DOUBLE , STUB_FLOAT )
			static std::string dissectDatatype( actRawDataStruct* , 
					STUB_INT * , proto::fieldInfo * , STUB_INT  , STUB_INT );
			static std::string dissectExecString ( actRawDataStruct * , STUB_INT *);// , proto::fieldInfo * , STUB_INT , STUB_INT );
			static STUB_INT modifyResponse( actSeriesStruct * , STUB_INT );

};


#endif


