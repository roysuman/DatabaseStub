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

#include <iostream>
#include <bitset>
#include <string>
#include <stdio.h>
#include <fstream>

#include "proto.h"
#include "types.h"
#include "buffer.h"
#include "field.h"
#include "jsoncpp/json.h"
#include "jsoncpp/writer.h"

#define no_dissector 1
#define PORT_MYSQL 3306
extern int JSON;
extern std::string response_data_together_row;
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

extern int mysqlPacketLength;
extern int mysqlPacketNumber;
extern int mysqlSchema;
extern int mysqlPayload;
extern int mysqlNumWarn;
extern int mysqlStatementId;
extern int mysqlQuery;
extern int mysqlExecFlags;
extern int mysqlExecIterations;
extern int mysqlEOF;
extern int mysqlFieldCatalog;
extern int mysqlFieldDb;
extern int mysqlFieldTable;
extern int mysqlFieldOriginalTable;
extern int mysqlFieldName;
extern int mysqlFieldldOriginalName;
extern int mysqlFieldCharsetNumber;
extern int mysqlFieldLength;
extern int mysqlFieldType;
extern int mysqlFieldDecimals;
extern int mysqlRowText;
extern int mysqlNumFields;
extern int mysqlExecParameter;
extern int mysqlExecUnsigned;
extern int mysqlExecFieldLong;
extern int mysqlExecFieldFloat;
extern int mysqlExecFieldDouble;
extern int mysqlExecFieldString;
extern int recentStatementId;

//structure for holding mysql execute dissector field
typedef struct _mysqlExecuteDissector  mysqlExecuteDissector;
struct _mysqlExecuteDissector{
	unsigned char type;
	unsigned char flag_unsigned;
	boost::any dissectorMethod;
	int   data_type ;
	int   length;
};



class Mysql{
	public:
		Mysql(){}
		~Mysql(){}
		//current statement id
		int statement_id;
		//previous packet no
		int prev_packet_no_with_query;
			//no of field present at packet response
			 int field_count;
			//this method will initialize mysql protocols into the mapping structure 
			//by calling functions which are at proto.hpp
			 bool initialize ( void );
			//this function is called to dissect raW DATA  by mysql dissector
			//this is called by dynamic function call
                         bool disect_mysql( actRawDataStruct * , int , actSeriesStruct*);
			
			//dissect mysql client request
                         int disect_mysql_request ( actRawDataStruct * , int , 
					proto::fieldInfo  * , int , actSeriesStruct *);

                        //dissect response
                         int disect_mysql_response ( actRawDataStruct *, int ,
				       	proto::fieldInfo * , int , actSeriesStruct *);
                        //for fle
                         int get_tvb_fle(actRawDataStruct *, int , 
					STUB_UINT64 *, STUB_UINT8 *);

                        //dissect result/response from db header
                         int dissect_mysql_result_header( actRawDataStruct *, int );
                        //read length encoded string
                         int read_mysql_length_enc_string( actRawDataStruct *, int 
				       	, proto::fieldInfo *);

                        //dissect field packet
                         int disect_mysql_field_packet ( actRawDataStruct * ,
				       	int  ,  proto::fieldInfo *);

                        //dissect flag server status
                         int disect_mysql_server_status(  int );

                        //dissect row packets
                         int disect_mysql_row_packets(actRawDataStruct * , int ,
				       	proto::fieldInfo * );
                         int get_query_string( actRawDataStruct * , queryData *& 
				       	, int , int );
			//to generate mysqlrequest packet.
			 int generate_mysql_response_packet ( actRawDataStruct * 
					, int , int , int , int , actSeriesStruct* );
			//to generate mysql respose packet.
			 int generate_mysql_request_packet ( int , int, int 
					, actSeriesStruct* );
			//dissect response prepare statement
			 bool dissect_mysql_response_prepare ( actRawDataStruct * 
					, int * );
			//mysql dissect execute statement
			 std::string disect_mysql_requestExecuteStatement ( 
					actRawDataStruct * , int * , proto::fieldInfo * , int );
			 std::string disect_mysql_exec_parameter( actRawDataStruct * 
					, int * , proto::fieldInfo * , int );
			//mysql dissection for datatype ( long ,STUB_DOUBLE , STUB_FLOAT )
			 std::string disect_mysql_datatype( actRawDataStruct* , 
					int * , proto::fieldInfo * , int  , int );
			 std::string disect_mysql_exec_string ( actRawDataStruct * , int *);// , proto::fieldInfo * , int , int );
			 int modify_mysql_response( actSeriesStruct * , int );

};


#endif


