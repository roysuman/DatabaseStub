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
 *         Author:  Suman Roy( 346163 )  (roy.suman@cognizant.com), 
 *   Organization:  Cognizant Technological Solutions
 *
 * =====================================================================================
 */
#ifndef PROTO_MYSQL_HPP_
#define PROTO_MYSQL_HPP_

#include<iostream>
#include "proto.hpp"
#include "types.hpp"
#include "../../STRUCTURE/sumanGtkmm.hpp"
#include "buffer.hpp"
#include "field.hpp"
#define no_dissector 1
#define PORT_MYSQL 3306

#define server_version true


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

extern int hf_mysql_caps_server ;

extern int hf_mysql_caps_client ;

extern int hf_mysql_cap_long_password ;

extern int hf_mysql_cap_found_rows ;

extern int hf_mysql_cap_long_flag ;

extern int hf_mysql_cap_connect_with_db ;

extern int hf_mysql_cap_no_schema ;

extern int hf_mysql_cap_compress ;

extern int hf_mysql_cap_odbc ;

extern int hf_mysql_cap_local_files ;

extern int hf_mysql_cap_ignore_space ;

extern int hf_mysql_cap_change_user ;

extern int hf_mysql_cap_interactive ;

extern int hf_mysql_cap_ssl ;

extern int hf_mysql_cap_ignore_sigpipe ;

extern int hf_mysql_cap_transactions ;

extern int hf_mysql_cap_reserved ;

extern int hf_mysql_cap_secure_connect ;

extern int hf_mysql_extcaps_client ;

extern int hf_mysql_cap_multi_statements ;

extern int hf_mysql_cap_multi_results ;

extern int hf_mysql_server_language ;

extern int hf_mysql_server_status ;

extern int hf_mysql_stat_it ;

extern int hf_mysql_stat_ac ;

extern int hf_mysql_stat_mr ;

extern int hf_mysql_stat_mu ;

extern int hf_mysql_stat_bi ;

extern int hf_mysql_stat_ni ;

extern int hf_mysql_stat_cr ;

extern int hf_mysql_stat_lr ;

extern int hf_mysql_stat_dr ;

extern int hf_mysql_stat_bs ;

extern int hf_mysql_refresh ;

extern int hf_mysql_rfsh_grants ;

extern int hf_mysql_rfsh_log ;

extern int hf_mysql_rfsh_tables ;

extern int hf_mysql_rfsh_hosts ;

extern int hf_mysql_rfsh_status ;

extern int hf_mysql_rfsh_threads ;

extern int hf_mysql_rfsh_slave ;

extern int hf_mysql_rfsh_master ;

extern int hf_mysql_packet_length ;

extern int hf_mysql_packet_number ;

extern int hf_mysql_request ;

extern int hf_mysql_command ;

extern int hf_mysql_error_code ;

extern int hf_mysql_error_string ;

extern int hf_mysql_sqlstate ;

extern int hf_mysql_message ;

extern int hf_mysql_payload ;

extern int hf_mysql_server_greeting ;

extern int hf_mysql_protocol ;

extern int hf_mysql_version  ;

extern int hf_mysql_login_request ;

extern int hf_mysql_max_packet ;

extern int hf_mysql_user ;

extern int hf_mysql_table_name ;

extern int hf_mysql_schema ;

extern int hf_mysql_thread_id  ;

extern int hf_mysql_salt ;

extern int hf_mysql_salt2 ;

extern int hf_mysql_charset ;

extern int hf_mysql_passwd ;

extern int hf_mysql_unused ;

extern int hf_mysql_affected_rows ;

extern int hf_mysql_insert_id ;

extern int hf_mysql_num_warn ;

extern int hf_mysql_thd_id ;

extern int hf_mysql_stmt_id ;

extern int hf_mysql_query ;

extern int hf_mysql_shutdown ;

extern int hf_mysql_option ;

extern int hf_mysql_num_rows ;

extern int hf_mysql_param ;

extern int hf_mysql_num_params ;

extern int hf_mysql_exec_flags4 ;

extern int hf_mysql_exec_flags5 ;

extern int hf_mysql_exec_iter ;

extern int hf_mysql_binlog_position ;

extern int hf_mysql_binlog_flags ;

extern int hf_mysql_binlog_server_id ;

extern int hf_mysql_binlog_file_name ;

extern int hf_mysql_eof ;

extern int hf_mysql_num_fields ;

extern int hf_mysql_extra ;

extern int hf_mysql_fld_catalog  ;

extern int hf_mysql_fld_db ;

extern int hf_mysql_fld_table ;

extern int hf_mysql_fld_org_table ;

extern int hf_mysql_fld_name ;

extern int hf_mysql_fld_org_name ;

extern int hf_mysql_fld_charsetnr ;

extern int hf_mysql_fld_length ;

extern int hf_mysql_fld_type ;

extern int hf_mysql_fld_flags ;

extern int hf_mysql_fld_not_null ;

extern int hf_mysql_fld_primary_key ;

extern int hf_mysql_fld_unique_key ;

extern int hf_mysql_fld_multiple_key ;

extern int hf_mysql_fld_blob ;

extern int hf_mysql_fld_unsigned ;

extern int hf_mysql_fld_zero_fill ;

extern int hf_mysql_fld_binary ;

extern int hf_mysql_fld_enum ;

extern int hf_mysql_fld_auto_increment ;

extern int hf_mysql_fld_timestamp ;

extern int hf_mysql_fld_set ;

extern int hf_mysql_fld_decimals ;

extern int hf_mysql_fld_default ;

extern int hf_mysql_row_text ;

extern int hf_mysql_new_parameter_bound_flag ;

extern int hf_mysql_exec_param ;

extern int hf_mysql_exec_unsigned ;

extern int hf_mysql_exec_field_longlong ;

extern int hf_mysql_exec_field_string ;

extern int hf_mysql_exec_field_double ;

extern int hf_mysql_exec_field_datetime_length ;

extern int hf_mysql_exec_field_year ;

extern int hf_mysql_exec_field_month ;

extern int hf_mysql_exec_field_day ;

extern int hf_mysql_exec_field_hour ;

extern int hf_mysql_exec_field_minute ;

extern int hf_mysql_exec_field_second ;

extern int hf_mysql_exec_field_second_b ;

extern int hf_mysql_exec_field_long ;

extern int hf_mysql_exec_field_tiny ;

extern int hf_mysql_exec_field_short ;

extern int hf_mysql_exec_field_float ;

extern int hf_mysql_exec_field_time_length ;

extern int hf_mysql_exec_field_time_sign ;

extern int hf_mysql_exec_field_time_days ;
extern int noOfFielde;

class Mysql{
		public:
			//declare constructor
//			Mysql( void );
			//this method will initialize mysql protocols into the mapping structure 
			//by calling functions which are at proto.hpp
			static bool initialize ( void );
			//this function is called to dissect raW DATA  by mysql dissector
			//this is called by dynamic function call
                        static bool dissect_mysql( actRawDataStruct * , int );
			
			//dissect mysql client request
                        static gint mysql_dissect_request ( actRawDataStruct * , gint , proto::field_info  *);
                        //print error dissection protocol
                        static void print_error ( proto::field_info * ,  int );

                        //dissect response
                        static gint mysql_dissect_response ( actRawDataStruct *, gint , proto::field_info * );
                        //for fle
                        static int tvb_get_fle(actRawDataStruct *, int , guint64 *, guint8 *);

                        //dissect result/response from db header
                        static int mysql_dissect_result_header( actRawDataStruct *, int );
                        //read length encoded string
                        static int mysql_field_add_lestring( actRawDataStruct *, int  , proto::field_info *);

                        //dissect field packet
                        static int mysql_dissect_field_packet ( actRawDataStruct * , int  ,  proto::field_info *);

                        //dissect flag server status
                        static int mysql_dissect_server_status( actRawDataStruct * , int );

                        //dissect row packets
                        static int mysql_dissect_row_packets(actRawDataStruct * , int , proto::field_info * );


			
};


#endif


