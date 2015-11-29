/*

 * =====================================================================================
 *
 *       Filename:  proto_mysql.cpp
 *
 *    Description:  definatuion of proto mysql.hpp
 *
 *        Version:  1.0
 *        Created:  Wednesday 11 December 2013 10:53:56  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy (), 
 *   Organization:  SELF
 *
 * =====================================================================================
 */

#include"../include/proto_mysql.hpp"

#define NEWPACKET 0
VS_INT32 JSON = 1;
 std::fstream file_handler;
VS_INT32 rowCount = 0;

 VS_INT32 mysql_packet_lengrh ;
 VS_INT32 mysql_packet_number;
 VS_INT32 mysql_schema;
 VS_INT32 mysql_pay_load;
 VS_INT32 mysql_num_warn;
 VS_INT32 mysql_statement_id;
 VS_INT32 mysql_query;
 VS_INT32 mysql_exec_flags;
 VS_INT32 mysql_exec_iterations;
 VS_INT32 mysql_eof;
 VS_INT32 mysql_field_catalog;
 VS_INT32 mysql_field_db;
 VS_INT32 mysql_field_table;
 VS_INT32 mysql_field_original_table;
 VS_INT32 mysql_field_name;
 VS_INT32 mysql_field_original_name;
 VS_INT32 mysql_field_char_set_number;
 VS_INT32 mysql_field_length;
 VS_INT32 mysql_field_type;
 VS_INT32 mysql_field_decimals;
 VS_INT32 mysql_row_text;
 VS_INT32 prev_query_state;
 VS_INT32 mysql_num_fields ;
 VS_INT32 mysql_exec_parameter;
 VS_INT32 mysql_exec_unsigned;
 VS_INT32 mysql_exec_field_long;
 VS_INT32 mysql_exec_field_float;
 VS_INT32 mysql_exec_field_double;
 VS_INT32 mysql_exec_field_string;
 VS_INT32 recent_statement_id = -1;
 VS_INT32 col_no_global = 0;
 bool row_packet_offset_flag = true;
#ifdef NEWPACKET
 VS_INT32 row_packet_offset_start;
 VS_INT32 prev_packet_till_inserted;
#endif
// FOR JSON
Json::Value event;
VS_INT32 noOfFielde = 0;
VS_INT32 Mysql::field_count= 0;
VS_INT32 Mysql::prev_packet_no_with_query = 0;
VS_INT32 Mysql::statement_id = 0;
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Mysql::initialize
 *  Description:  initialize the mysql protocol,by updateing it's field type , name datatype and run time methods.
 *  this is the first method which will be called from init().
 * =====================================================================================
 */
bool 
Mysql::initialize( void  ) {

#ifdef DEBUG
	std::cout<<PRINT<<"Register Mysql Protocol]n";
#endif


	proto::fp_struct    *function_ptr_structure;

	function_ptr_structure = new proto::fp_struct() ;
	function_ptr_structure->functionToInnitiateDissecton = &Mysql::disect_mysql;
	function_ptr_structure->functionToGetClientRequest= &Mysql::get_query_string;
		static proto::packetInfo pi[]={ //field_info_map_str

			{ &mysql_packet_lengrh,
				{ "Packet Length",types::UINT24,
				       	types::BASE_DECIMAL }},
			{ &mysql_packet_number,
					{ "Packet Number", types::UINT8,
					       	types::BASE_DECIMAL }},
			{ &mysql_schema,
					{ "Schema", types::STRING,
					       	types::BASE_NONE }},
			{ &mysql_pay_load,
					{ "Payload",types::BYTES,
					       	types::BASE_NONE}},
			{ &mysql_num_warn,
					{ "Warnings", types::UINT16,
					       	types::BASE_DECIMAL }},
			{ &mysql_statement_id,
					{ "Statement ID", types::UINT32,
					       	types::BASE_DECIMAL}},
			{ &mysql_query,
				{ "Query Statement", types::STRING,
				       	types::BASE_NONE }},
			{ &mysql_exec_flags,
					{ "Flags", types::UINT8,
					       	types::BASE_DECIMAL }},
			{ &mysql_exec_iterations,
					{ "Iterations (unused)",types::UINT32, 
						types::BASE_DECIMAL }},
			{ &mysql_eof,
					{ "EOF marker", types::UINT8,
					       	types::BASE_DECIMAL}},
			{ &mysql_field_catalog,
					{ "FIELD Catalog", types::STRING,
					       	types::BASE_NONE }},
			{ &mysql_field_db,

					{ "FIELD Database", types::STRING,
					       	types::BASE_NONE}},
			{ &mysql_field_table,
					{ "FIELD Table", types::STRING,
					       types::BASE_NONE }},
			{ &mysql_field_original_table,
					{ "Original table", types::STRING,
					       	types::BASE_NONE }},
			{ &mysql_field_name,
					{ "Name", types::STRING,
					       	types::BASE_NONE }},
			{ &mysql_field_original_name,
					{ "Original name", types::STRING,
					       	types::BASE_NONE }},
			{ &mysql_field_char_set_number,
					{ "Charset number", types::UINT16,
                            types::BASE_DECIMAL}},
			{ &mysql_field_length,
					{ "Field Length", types::UINT32,
                            types::BASE_DECIMAL }},
			{ &mysql_field_type,
				{ " FIeld Type", types::UINT8,
                        types::BASE_DECIMAL }},
			{ &mysql_field_decimals,
				{ " Field Decimals", types::UINT8,
                        types::BASE_DECIMAL }},
			{ &mysql_row_text,
				{ " Mysql Roe Text", types::STRING, 
					types::BASE_NONE }},
			{&mysql_num_fields,
				{"No of Fields" , types::UINT64,
					types::BASE_DECIMAL } },
			{&mysql_exec_parameter,
				{"Parameter" , types::NONE ,
					types::BASE_NONE} },
			{&mysql_exec_unsigned , 
				{"Unsigned" , types::UINT8 ,
					types::BASE_DECIMAL } },
			{&mysql_exec_field_long ,
				{"long VALUE", types::INT32,
					types::BASE_DECIMAL  } },
			{&mysql_exec_field_float ,
				{"Float VALUE" , types::FLOAT ,
					types::BASE_NONE } },
			{&mysql_exec_field_double ,
				{"Double VALUE", types::DOUBLE,
					types::BASE_NONE } },
			{&mysql_exec_field_string ,
				{"String VALUE",types::UINT_STRING ,
					types::BASE_NONE } },
			};

    if ( ! ( (  proto::Proto::register_proto ( "MYSQL" , function_ptr_structure , 
					    (sizeof ( pi ) / sizeof ( proto::packetInfo )) ) ) 
			    && ( proto::Proto::insert_dissector_proto ( "MYSQL" ,
					    ( sizeof ( pi ) / sizeof ( proto::packetInfo ) )
					    , pi ) )) ) {
	    std::cerr<<PRINT<<" Can't register myssql protocol \n";
	    return false;
    }
    return true;
}

std::string    response_data_together_row; //need to be in a proper way

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Mysql::mysqlDissectRowPacket
 *  Description:  dissect row packet protocol of mysql
 * =====================================================================================
 */
VS_INT32 
Mysql::disect_mysql_row_packets ( act_raw_dataStruct *raw_packet , VS_INT32 offset , 
		proto::field_info *field_info  ){

	VS_UNSIGNED_INT_64    lelen;
	VS_INT8               is_null;

	offset+=get_tvb_fle( raw_packet, offset, & ( lelen = 0 ), 
			& ( is_null = 0 ) );
	std::string rowText = boost::get < std::string > ( buff::Buffer< returnType >
			::Read ( raw_packet , field_info , mysql_row_text , 
				&offset , ( VS_INT32 ) lelen , ENC_NA ) );
	if ( JSON != 1 ){
		response_data_together_row = response_data_together_row + rowText + ";" ;
	}
	return offset;
}


// dissect server status flags
VS_INT32 
Mysql::disect_mysql_server_status (  VS_INT32 offset ){

	return ( offset + 2 );
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Mysql::disect_mysql_field_packet
 *  Description:  dissect mysql field packet information of response packet
 * =====================================================================================
 */

VS_INT32 Mysql::disect_mysql_field_packet( act_raw_dataStruct *raw_packet , VS_INT32 offset , 
		proto::field_info * field_info ){

	VS_UNSIGNED_INT_64    lelen;
	VS_INT8               is_null ;

	is_null = 0;

	offset += get_tvb_fle( raw_packet, offset, &( lelen = 0 ), &( is_null = 0 ) );
	buff::Buffer< returnType >::Read ( raw_packet, field_info , 
			mysql_field_catalog , &offset , (VS_INT32)lelen , ENC_NA );
	offset += get_tvb_fle( raw_packet, offset, &( lelen = 0 ),
		       	&( is_null = 0 ));
	buff::Buffer< returnType >::Read ( raw_packet, field_info ,  
			mysql_field_db, &offset , (VS_INT32)lelen , ENC_NA );
	offset += get_tvb_fle( raw_packet, offset, &( lelen = 0 ) ,
		       	&( is_null = 0 ) );
	buff::Buffer< returnType >::Read( raw_packet, field_info ,
		      	mysql_field_table, &offset , (VS_INT32)lelen , ENC_NA );
	offset += get_tvb_fle( raw_packet, offset, & ( lelen = 0 ),
		       	&( is_null = 0 ) );
	buff::Buffer < returnType >::Read( raw_packet, field_info ,
		      	mysql_field_original_table , &offset , (VS_INT32)lelen , ENC_NA );
	offset += get_tvb_fle( raw_packet, offset, &( lelen = 0 ), 
			&( is_null = 0 ) );
	buff::Buffer< returnType > ::Read ( raw_packet, field_info ,  
			mysql_field_name , &offset , (VS_INT32)lelen , ENC_NA );
	offset += get_tvb_fle( raw_packet, offset, &( lelen = 0 ),
		       	&( is_null = 0 ) );
	std::string fieldOriginalName =boost::get < std::string > ( buff::Buffer< returnType >
		       	::Read( raw_packet, field_info ,  mysql_field_original_name ,
			       	&offset , (VS_INT32)lelen , ENC_NA ) ); 
		fieldOriginalName +=  ";";
		QueryPacket.colNames.insert ( std::make_pair ( 
					Mysql::field_count ++ , fieldOriginalName ) );
	event["PACKET/MySQL"]["Query"]="ENTER NEW QUERY";
	event["PACKET/MySQL"]["Response"][fieldOriginalName]="ENTER NEW VALUE";
	offset ++ ; //filler
	buff::Buffer< returnType >::Read ( raw_packet , field_info , mysql_field_char_set_number
		       	, &offset , 2 , ENC_LITTLE_INDIAN );
	buff::Buffer< returnType >::Read ( raw_packet , field_info , mysql_field_length , 
			&offset , 4 , ENC_LITTLE_INDIAN );
	VS_INT32 fieldType =boost::get < VS_INT32 > ( buff::Buffer< returnType >::Read ( raw_packet 
				, field_info , mysql_field_type , &offset , 1 , ENC_NA ) );
	switch ( fieldType ){ // read types and dissect it
		case  0x00 :
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
				"] FIELD_TYPE_DECIMAL\n";
			break;

        case 0x01:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<
				__TIME__<<"] FIELD_TYPE_TINY\n";
			break;
        case  0x02 :
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] FIELD_TYPE_SHORT\n";
			break;
        case 0x03 : 
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] FIELD_TYPE_LONG\n";
			break;
        case 0x04 :
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<
				__TIME__<<"] FIELD_TYPE_FLOAT\n";
			break;
        case 0x05:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] FIELD_TYPE_DOUBLE\n";
			break;
        case 0x06 :
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] FIELD_TYPE_NULL\n";
			break;
        case 0x07 :
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] FIELD_TYPE_TIMESTAMP\n";
			break;
			
  	case  0x08 :
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] FIELD_TYPE_LONGLONG\n";
			break;
        case 0x09  :
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
				"] FIELD_TYPE_INT24\n";
			break;
        case 0x0a :
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] FIELD_TYPE_DATE\n";
			break;
        case 0x0b  :
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] FIELD_TYPE_TIME\n";
			break;
        case  0x0c :
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
				"] FIELD_TYPE_DATETIME\n";
			break;
        case 0x0d :
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] FIELD_TYPE_YEAR\n";
			break;
        case 0x0e:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] FIELD_TYPE_NEWDATE\n";
			break;
        case  0x0f:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
				"] FIELD_TYPE_VARCHAR (new in MySQL 5.0)\n";
			break;
        case  0x10  :
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] FIELD_TYPE_BIT (new in MySQL 5.0)\n";
			break;

        case  0xf6:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] FIELD_TYPE_NEWDECIMAL (new in MYSQL 5.0)\n";
			break;

        case 0xf7 :
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] FIELD_TYPE_ENUM\n";
			break;
        case  0xf8  :
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] FIELD_TYPE_SET\n";
			break;
        case  0xf9 :
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] FIELD_TYPE_TINY_BLOB\n";
			break;
        case  0xfa  :
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] FIELD_TYPE_MEDIUM_BLOB\n";
			break;
        case 0xfb :
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] FIELD_TYPE_LONG_BLOB\n";
			break;
			
     	case   0xfc :
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] FIELD_TYPE_BLOB\n";
			break;
        case 0xfd: 
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] FIELD_TYPE_VAR_STRING\n";
			break;
        case  0xfe:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] FIELD_TYPE_STRING\n";
			break;

        case 0xff :
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] FIELD_TYPE_GEOMETRY \n";
			break;
		}

	//dissect each flags
	switch ( types::get_guVS_INT32 ( ( u_char *)raw_packet->data , raw_packet->length , 
			    offset , 2 , ENC_LITTLE_INDIAN ) ){

		case 0001 :
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
				"] NOT_NULL_FLAG\n";
			break;
			
		case 0002:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] PRI_KEY_FLAG\n";
			break;
		case 0004 :
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] UNIQUE_KEY_FLAG\n";
			break;
			
//		case 0008:
			// std::xout<<"MULTIPLE_KEY_FLAG"<<std::endl;
			// break;
			
		case 0010 :
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"]"<<__FUNCTION__<<"BLOB_FLAG\n";
			break;
		case 0020:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] UNSIGNED_FLAG\n";
			break;
		case 0040:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<
				__TIME__<<"] ZEROFILL_FLAG\n";
			break;
			
		//case 0080 :
		//       std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		//       "] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		//       <<"]BINARY_FLAG"<<std::endl;
		//       break;
			
		case 0100:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
				"]  ENUM_FLAG\n";
			break;
			
		case 0200:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<
				__TIME__<<"] AUTO_INCREMENT_FLAG\n";
			break;
			
		case 0400:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] TIMESTAMP_FLAG\n";
			break;
			
//		case 0800 :
			// std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			// <<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
			// <<"]"<<"SET_FLAG"<<std::endl;
			// break;
			
		default:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] combination of 8 creating prob\n";
			break;
		}
	buff::Buffer < returnType >::Read( raw_packet , field_info , 
			mysql_field_decimals , &( offset +=  2 )  , 1 , ENC_NA );
	offset +=2; // filler

    if ( buff::Buffer< void >::return_remaining_length( offset ) )
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<" ] SOME EXTRA DATA\n";
	return offset;
	
}

VS_INT32 Mysql::get_tvb_fle(act_raw_dataStruct * raw_packet, VS_INT32 offset , VS_UNSIGNED_INT_64 *res, 
		VS_INT8 *is_null){

	VS_INT32    prefix;
	
	
	prefix = buff::Buffer< void >::get_guVS_INT328 ( raw_packet , offset++ );
	if (is_null)
		*is_null = 0;
	switch (prefix) {
		case 251:
			if (res)
				*res = 0;
			if (is_null)
				*is_null = 1;
			break;
			case 252:
			if (res)
                *res = buff::Buffer< void >::getLetohs( raw_packet, offset );
			return 3;
			case 253:
			if (res)
                *res = buff::Buffer< void >::getLetohl (raw_packet, offset );
			return 5;
			case 254:
			if (res)
                *res =buff::Buffer< void >::getLetoh64( raw_packet, offset );
			return 9;
			default:
			if (res)
				*res = prefix;
		}
	return 1;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Mysql::dissect_mysql_result_header
 *  Description:  dissect the result header field
 * =====================================================================================
 */

VS_INT32 Mysql::dissect_mysql_result_header( act_raw_dataStruct *raw_packet , VS_INT32 offset ){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	VS_INT32       fle;
	VS_UNSINED_INT_64    numFields;

	fle = get_tvb_fle( raw_packet , offset , &numFields , NULL );
	noOfFielde = numFields;
#ifdef DEBUG
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		<<"]"<<"[OFFSET]:[NO OF FIELD]:"<<offset<<"::"
		<<noOfFielde<<'\n';
#endif
    if ( numFields   )field::prevQuery.prev_query_state = FIELD_PACKET;
	else field::prevQuery.prev_query_state = ROW_PACKET ;
	offset += fle;
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		<<"]"<<"RETURN OFFSET:"<<offset<<'\n';
	return (offset );
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Mysql::dissect_mysql_response_prepare
 *  Description:  dissect response prepare packet for mysql
 * =====================================================================================
 */
bool Mysql::dissect_mysql_response_prepare ( act_raw_dataStruct *raw_packet , 
		VS_INT32 *offset){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	VS_INT32    noOfParam;
	VS_INT32    noOfFields;
	VS_INT32    statement_id;

	//read statement ID
	statement_id = buff::Buffer< void >::getLetohl ( raw_packet, *offset );
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
		"] [STATEMENT ID]:"<<statement_id<<'\n';
	*offset += 4;
	noOfFields = buff::Buffer< void >::getLetohs ( raw_packet , *offset );
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
		"] [no of Fields]:"<<noOfFields<<'\n';
	*offset += 2;
	noOfParam = buff::Buffer< void >::getLetohs ( raw_packet , *offset );
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
		"] [No of PARAM]:"<<noOfParam<<'\n';
	*offset += 2;
	//filler
	*offset = *offset + 1 ;
	if ( noOfParam > 0 ) field::prevQuery.prev_query_state = PREPARED_PARAMETERS ;
	else if( noOfFields > 0 ) field::prevQuery.prev_query_state = PREPARED_FIELDS;
	else field::prevQuery.prev_query_state = REQUEST;
	*offset += buff::Buffer < void >::return_remaining_length ( *offset );

	return true;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Mysql::disect_mysql_response
 *  Description:  dissect mysql response packet ( Response packet of a query)
 * =====================================================================================
 */
VS_INT32 Mysql::disect_mysql_response ( act_raw_dataStruct *rawdataPacket , VS_INT32 offset , 
		proto::field_info * field_info, VS_INT32 packetNo , 
		actSeriesStruct *conversation_packets){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	VS_INT32    columnCount;
	VS_INT32    responseCode; 
	VS_INT32    eofLengthPrevious;


#ifdef DEBUG
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<
		"{PREVIOUS QUERY:}"<<field::prevQuery.prev_query_state<<'\n';
#endif
    responseCode = buff::Buffer< VS_INT32 >::get_guVS_INT328 ( rawdataPacket ,  offset );
    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
	    <<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"response code:"
	    <<responseCode<<"::"<<( VS_INT32)(rawdataPacket->data[offset] ) <<'\n';
	if ( responseCode == 0xff ) {
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
			"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
			<<"] Error packet at mysql_dissect_response --\n";

		return offset;
	}
        else {
        if ( responseCode == 0xfe  && 
			( buff::Buffer< void > ::return_remaining_length( offset ) < 9 ) ) {
			eofLengthPrevious = (rawdataPacket->length - ( offset - 4 ) ) ;
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] eoflengthPrevious="<<eofLengthPrevious<<std::endl;
             buff::Buffer< returnType >::Read ( rawdataPacket, field_info , 
			     mysql_eof , &offset , 1 , ENC_NA ) ;
			 //pre 4.1 packet ends here
            if ( buff::Buffer< void >::return_remaining_length( offset ) ){
		    buff::Buffer< returnType >::Read (rawdataPacket, field_info , 
				    mysql_num_warn , &offset , 2 , ENC_LITTLE_INDIAN ) ;
				//now dissect server header flags
				offset = disect_mysql_server_status ( offset );
			}
			if ( field::prevQuery.prev_query_state == FIELD_PACKET ){
				file_handler<<event<<std::endl;
				field::prevQuery.prev_query_state = ROW_PACKET;
			}
	
//#ifdef NEWPACKET
			else if ( ( field::prevQuery.prev_query_state == ROW_PACKET )
				       	&& Json::flag_for_generate_query ){
				generate_mysql_response_packet(rawdataPacket , row_packet_offset_start , 
						noOfFielde ,packetNo, eofLengthPrevious , 
						conversation_packets );
				return 999;
            }

//#endif
	}else if ( responseCode == 0 ){
		if ( field::prevQuery.prev_query_state == RESPONSE_PREPARE ) 
			dissect_mysql_response_prepare( rawdataPacket , &offset  );
	}


		else {
			switch (  field::prevQuery.prev_query_state ) {
				std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
					"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
					<<"]"<<"INSIDE SWITCH!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
				case RESPONSE_TABULAR:
#ifdef DEBUG
					std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<
						__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["
						<<__DATE__<<"_"<<__TIME__<<"] RESPOSE TABULAR\n";
#endif
					offset = 
						dissect_mysql_result_header ( rawdataPacket , offset );
					break;
					
				case FIELD_PACKET:
					
				case RESPONSE_SHOW_FIELDS:
					
				case RESPONSE_PREPARE:
					
				case PREPARED_PARAMETERS:
					offset = disect_mysql_field_packet( rawdataPacket, 
							offset , field_info);
					break;
					
				case ROW_PACKET:
#ifdef DEBUG
					std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<
						__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["
						<<__DATE__<<"_"<<__TIME__<<
						"] row count offset="<<offset<<std::endl;
#endif
					if ( row_packet_offset_flag ) {
						row_packet_offset_start = offset - 4 ;
						row_packet_offset_flag = false ;
					}
					columnCount = noOfFielde ;
					while ( columnCount != 0 ){
						columnCount --;
						offset = disect_mysql_row_packets ( rawdataPacket ,
							       	offset , field_info );
#ifdef DEBUG
						std::cout<<PRINT<<columnCount<<std::endl;
#endif
					}
					QueryPacket.rowCount = ++rowCount ;
					QueryPacket.colInfo.insert ( std::make_pair ( QueryPacket.rowCount ,
								response_data_together_row ) );
					break;
				}
		}
	
    }
	return offset;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Mysql::disect_mysql_datatype
 *  Description:  dissect datatype of execute statement packet
 * =====================================================================================
 */
//extraxt valu from specified datatype( long , VS_DOUBLE ,STUB_FLOAT )
std::string 
Mysql::disect_mysql_datatype( act_raw_dataStruct * rawdataPacket , VS_INT32 *offset , 
		proto::field_info *field_info , VS_INT32 data_type , VS_INT32 lengthDatatype ){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	std::string    parameter_value;
	//now read the data with respect to datatype
	if ( data_type ==  mysql_exec_field_long ){
		parameter_value = std::to_string ( static_cast< long long >( boost::get< VS_INT32 >
					(buff::Buffer< returnType > ::Read( rawdataPacket , 
									    field_info , 
									    data_type , 
									    &(*offset) ,
									    4 , 
									    ENC_LITTLE_INDIAN 
									    )) ) );
	}
	else{ if ( data_type ==  mysql_exec_field_float)
		parameter_value = std::to_string( static_cast< long long> ( boost::get< STUB_FLOAT >
					(buff::Buffer< returnType > ::Read( rawdataPacket , 
									    field_info , 
									    data_type , 
									    &(*offset) , 
									    lengthDatatype , 
									    ENC_LITTLE_INDIAN 
									    )) ) );

	else {if ( data_type == mysql_exec_field_double )
		parameter_value = std::to_string ( static_cast < long long > (boost::get< VS_DOUBLE >
					(buff::Buffer< returnType > ::Read( rawdataPacket , 
									    field_info , 
									    data_type , 
									    &(*offset) , 
									    lengthDatatype , 
									    ENC_LITTLE_INDIAN 
									    )) ));
	else
		parameter_value = "No SPECIFIED DATATYPE";
	}
	}
	return parameter_value;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Mysql::disect_mysql_exec_string
 *  Description:  dissect the string datatype of execute statement packet
 * =====================================================================================
 */
std::string Mysql::disect_mysql_exec_string( act_raw_dataStruct *rawdataPacket , VS_INT32 *offset ){ 
//		proto::field_info *field_info , VS_INT32 data_type , VS_INT32 lengthDatatype){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	std::string   data; 
	VS_INT32      parameterLength;


	//return "done";
	parameterLength = buff::Buffer< void >::get_guVS_INT328 ( rawdataPacket ,
		       	*offset );
	*offset += 1;
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<
		"Param Length["<<parameterLength<<"]\n";
	data = types::getString ( (u_char*)rawdataPacket->data , 
			rawdataPacket->length, *offset , parameterLength ) ;
	*offset +=parameterLength;
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"data["<<data<<"]\n";
	return data;
/* 	exit(0);
	for ( VS_INT32 ii = 0 ; ii< parameterLength ; ++ ii )
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<(STUB_CHAR)rawdataPacket->data[ii]<<std::endl;
	exit(0);
	STUB_UINT32 parameterLength32;
	STUB_UINT32 fieldString;
	switch ( parameterLength ){
		case 0xfc:
			*offset += 1;
			parameterLength32 = buff::Buffer < void >::getLetohs( rawdataPacket , *offset );
			fieldString = boost::get< STUB_UINT32 > (buff::Buffer< returnType > ::Read( rawdataPacket , field_info , mysql_exec_field_string , &(*offset) , 2 , ENC_NA ) );
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<"[FIELD STRING]:"<<fieldString<<'\n';
			* offset += parameterLength32  + 2 ;
			break;
		case 0xfd:
			*offset ++;
			parameterLength32 = buff::Buffer < void >::getLetoh24(rawdataPacket , *offset );
			fieldString = boost::get< STUB_UINT32 >( buff::Buffer < returnType >::Read ( rawdataPacket , field_info , mysql_exec_field_string ,&(*offset) , 3 , ENC_NA) );
			*offset += parameterLength32 + 3 ;
		default:
			fieldString = boost::get< STUB_UINT32 > (buff::Buffer< returnType > ::Read( rawdataPacket , field_info , mysql_exec_field_string , &(*offset) , 1 , ENC_NA ) );
			*offset += parameterLength + 1;
	}return std::to_string ( static_cast<long long>( fieldString ) );	
	*/
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Mysql::disect_mysql_requestExecParameter
 *  Description:  dissect parameter , datatype, value...tail part of execute statement
 * =====================================================================================
 */
std::string Mysql::disect_mysql_exec_parameter ( act_raw_dataStruct * rawdataPacket , 
		VS_INT32 *offset , proto::field_info *field_info, 
		VS_INT32 noParameters =1 ){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		<<"]\n";

	bool           pass;
	VS_INT32       index;
	VS_INT32       *paramType;
	std::string    returnString;
	VS_INT32       *paramUnsigned;

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		<<"]"<<"[PARAMETER COUNT]:"<<noParameters<<"]\n";

	//initialize execute dissectors structure array field
	mysqlExecuteDissector executeDissectors[ 8 ] ={
//	    { 0x01, 0, mysql_dissect_exec_tiny },
//	    { 0x02, 0, mysql_dissect_exec_short },
	    { 0x03, 0, &Mysql::disect_mysql_datatype , mysql_exec_field_long , 4 },
	    { 0x04, 0, &Mysql::disect_mysql_datatype , mysql_exec_field_float , 4 },
	    { 0x05, 0, &Mysql::disect_mysql_datatype , mysql_exec_field_double , 8},
//	    { 0x06, 0, mysql_dissect_exec_null },
//	    { 0x07, 0, mysql_dissect_exec_datetime },
//	    { 0x08, 0, mysql_dissect_exec_lonSTUB_LONG },
//	    { 0x0a, 0, mysql_dissect_exec_datetime },
//	    { 0x0b, 0, mysql_dissect_exec_time },
//	    { 0x0c, 0, mysql_dissect_exec_datetime },
	    { 0xf6, 0, &Mysql::disect_mysql_exec_string , mysql_exec_field_string, 0 },
	    { 0xfc, 0, &Mysql::disect_mysql_exec_string , mysql_exec_field_string , 0},
	    { 0xfd, 0, &Mysql::disect_mysql_exec_string , mysql_exec_field_string , 0},
	    { 0xfe, 0, &Mysql::disect_mysql_exec_string , mysql_exec_field_string , 0},
	    { 0x00, 0, NULL , 0, 0},
    };
	try {
		paramType = new VS_INT32[noParameters ];
		paramUnsigned = new VS_INT32 [ noParameters ];
	}
	catch ( std::exception &ba ){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
			"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
			<<"]"<<"exception["<<ba.what()<<
			"] on creating paramType and paramUnsigned\n";
		exit(0);
	}
	for ( VS_INT32 i = 0 ; i< noParameters ;++i ){
		paramType[i] = boost::get< VS_INT32 > (buff::Buffer< returnType > ::
				Read( rawdataPacket , field_info , 
					mysql_field_type , &(*offset) ,
				       	1 , ENC_NA ) );
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<
			__TIME__<<"] [PARAM TYPE]:"<<paramType[i]<<'\n';
		paramUnsigned[i] = boost::get< VS_INT32 > (buff::Buffer< returnType > ::
				Read( rawdataPacket , field_info , 
					mysql_exec_unsigned , &(*offset) ,
				       	1 , ENC_NA ) );
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
			"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
			<<"] [PARAM UNSIGNED]:"<<paramUnsigned[i]<<'\n';
	}
	for ( VS_INT32 i = 0 ; i< noParameters ; ++i){
	  index = 0;
	  pass = false;
	  while ( ( executeDissectors[ index].type != 0 ) & ( !pass ))  {
		  if ( ( executeDissectors[index].type == paramType[i] ) 
				  &&  ( executeDissectors[index ].flag_unsigned 
					  ==paramUnsigned[i] ) ){
			  pass = true;
			  
#ifdef DEBUG
			  std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<
				  __FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime\
				  ["<<__DATE__<<"_"<<__TIME__<<"]"<<"SEARCH \
				  ATCHED:["<<index<<"]\n"<<"datatype:["<<
				  executeDissectors[ index ].data_type
				  <<"]\n"<<"Length:["<<executeDissectors[ index ].
				  length<<"]\n";
			  
#endif
	//		  *offset += 2;
			  returnString +=boost::any_cast< std::string ( * )
				  ( act_raw_dataStruct * , VS_INT32* , proto::field_info * ,
				    VS_INT32 , VS_INT32 )>( executeDissectors[ index].dissectorMethod)
				  ( rawdataPacket ,  &(*offset ) , field_info , 
				    executeDissectors[ index].data_type , 
				    executeDissectors[ index ].length) +";";
			  
			  std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				  "] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				  <<"]"<<"return String["<<returnString<<"]\n";
		  }
		  ++index;
	  }
 }
	
  try {
	  delete []paramUnsigned;
	  delete []paramType;
  }
  catch ( std::exception &ba ){
	  std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__
		  <<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"] Exception["<<ba.what()<<"]\n";
	  exit ( 1 );
  }
	return returnString;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Mysql::disect_mysql_requestExecuteStatement
 *  Description:  dissect execute statement request that contains STATEMENT ID , ITERATION
 * =====================================================================================
 */
std::string Mysql::disect_mysql_requestExecuteStatement ( act_raw_dataStruct *rawdataPacket ,
	       	VS_INT32 *offset , proto::field_info *field_info , VS_INT32 noParameters = 0 ){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
		"] INITIAL OFFSET:"<<*offset<<'\n';
	recent_statement_id = boost::get<  VS_INT32 > (buff::Buffer< returnType > ::
			Read( rawdataPacket , field_info , mysql_statement_id,
			       	&(*offset) , 4 , ENC_LITTLE_INDIAN ) );

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		<<"]"<<"[STATEMENT ID]"<<recent_statement_id;
	Mysql::statement_id = recent_statement_id;
#ifdef DEBUG

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		<<"] OFFSET AFTER STATEMENT ID:"<<*offset<<'\n';
#endif
	//FLAG
	*offset +=  1;
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		<<"]"<<"[ITERATIONS]:"<< boost::get< VS_INT32 > (buff::Buffer< returnType > 
				::Read( rawdataPacket , field_info , 
					mysql_exec_iterations ,
				       	&(*offset) ,
				       	4 , 
					ENC_LITTLE_INDIAN ) )<<'\n'; 
	/*-----------------------------------------------------------------------------
	*  sometime this packet does not contains parameter part, 
	 *  so check remaing length remaining
       *-----------------------------------------------------------------------------*/
	if(  buff::Buffer <VS_INT32>::return_remaining_length ( *offset ) < 2 )  
		return "NO PARAMETER";
	//have to dissect for the offsets 
	*offset += 2;
	 return ( disect_mysql_exec_parameter( rawdataPacket , &(*offset) , 
				 field_info , noParameters ) ); 
/*	while ( !(buff::Buffer < VS_INT32 >::return_remaining_length ( *offset ) < 2 ))
		returnString  disect_mysql_exec_parameter( rawdataPacket , &(*offset) , field_info ) ;
	return returnString;
	*/
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Mysql::disect_mysql_request
 *  Description:  dissect the request packet, packet which are going to mysql server are getting dissected 
 *  by the following method.
 * =====================================================================================
 */
 VS_INT32 Mysql::disect_mysql_request ( act_raw_dataStruct *rawdataPacket , VS_INT32 offset , 
		 proto::field_info * field_info , VS_INT32 currentPacket , 
		 actSeriesStruct * conversation_packets){

	 std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		 "] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		 <<"]\n";

	 VS_INT32    opcode;
	 VS_INT32    newDataSetOffsetPosition;

	 //1st read teh oppcode from the packet
         opcode = (VS_INT32)buff::Buffer< void > ::get_guVS_INT328(rawdataPacket  ,  offset++ ) ;

#ifdef ERROR
	 opcode = 3;
	 std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		 __LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"
		 <<"[OPCODE]:"<<opcode<<'\n';
#endif
	 newDataSetOffsetPosition = offset;
	 switch ( opcode ){
		 case COM_PREPARE:
                 case COM_QUERY:{ // tells the server to run the query
					std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<
						__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["
						<<__DATE__<<"_"<<__TIME__<<"] COMQUERY\n";
					std::string mysql_queryString =boost::get < std::string>
						(buff::Buffer< returnType >::Read (rawdataPacket 
										   , field_info 
										   , mysql_query 
										   , &offset 
										   , 0 
										   , ENC_NA ) );
					if ( JSON ){
						QueryPacket.query = mysql_queryString;
						QueryPacket.query_type = COM_QUERY;
#ifdef DEBUG
						std::cout<<" File Name ["<<__FILE__<<" ] Function [ "
							<<__FUNCTION__<<"] Line ["<<__LINE__<<
							"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
							"] QueryPacket.query = "<<QueryPacket.query<<'\n';
						std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<
							__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["
							<<__DATE__<<"_"<<__TIME__<<"]"<<"[OFFSET]:"<<
							offset<<'\n';
#endif
					
						JSON = 2;
					}
					
					if ( Json::flag_for_generate_query ){
						prev_query_state = RESPONSE_TABULAR;
						generate_mysql_request_packet( newDataSetOffsetPosition ,
							       	opcode , currentPacket ,
							       	conversation_packets);
						row_packet_offset_flag = true ;
					}

					opcode = COM_QUERY ?( field::prevQuery.prev_query_state = 
							RESPONSE_TABULAR ): (field::prevQuery.prev_query_state 
								= RESPONSE_PREPARE );
				
				}
				break;
		 case COM_EXECUTE :
				std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
					"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<
					__TIME__<<"]"<<"BEFORE OFFSET_______"<<offset<<'\n';
				Mysql::disect_mysql_requestExecuteStatement( rawdataPacket , 
						&offset , field_info );
				field::prevQuery.prev_query_state = RESPONSE_TABULAR;
				std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
					<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<
					__TIME__<<"]"<<"AFTER OFFSET-------------"<<offset<<'\n';
				break;
		 case COM_CLOSE_STMT:
				std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<
					__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<
					__DATE__<<"_"<<__TIME__<<"] [STATEMENT ID]:"<< 
					boost::get<  VS_INT32 > (buff::Buffer< returnType > ::
							Read( rawdataPacket , field_info , 
								mysql_statement_id, &(offset) , 
								4 , ENC_LITTLE_INDIAN ) )
					<<'\n';
				exit ( 0 );
				break;
		 case COM_QUIT:
				std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
					"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
					<<"]"<<"COMMAND QUIT\n";
				break;
		 default:
				std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
					"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
					<<"] DEFAULT REQUEST\n";

         }
         return offset;

 }

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Mysql::disect_mysql
 *  Description:  method to dissect mysql query packet( REQUEST + RESPONSE )
 * =====================================================================================
 */
bool Mysql::disect_mysql( act_raw_dataStruct *rawdataPacket , VS_INT32 totalPacketLength , 
		actSeriesStruct * conversation_packets ){
#ifdef DEBUG
	std::cout<<PRINT<<" MYSQL TOTAL_PACKET_LENGTH :"<<totalPacketLength<<std::endl;
	VS_INT32            offset;
	proto::field_info    *field_info;
	bool                isResponse;
	proto::mapkey       tempKeyPair;


	//open file for Json ,this file will take input for new query
	file_handler.open("../STUB/json.js",std::ios::out); 
	if ( !file_handler.is_open() ){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
			<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
			"] can't open json input file\n";
		exit(EXIT_FAILURE);
	}
	//for adding row at tree view initiLIZE THE NEW ROOTrOW fLAAG	
	buff::Buffer< bool >::rootRowPass = true ;

	//set the length flag
	buff::Buffer<bool>::pass = false ;

	/*-----------------------------------------------------------------------------
	 *  find the appropriate array of field info from proto_map;
	 *  have to pass this value by function error , now geting error
	 *  create an proto field info refernce and initialize it by appropriate protocol from map.
	 *-----------------------------------------------------------------------------*/
	proto::_protoMap::iterator protomapIterator = proto::protoMap.find ( "MYSQL" );
	if ( protomapIterator == proto::protoMap.end () ){

		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
			"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<
			__TIME__<<"] :Protocol didnot registered / but it must\
		       	be registered because after searching registered proto\
		       	only dynamic function will  be clled\n ";
		exit ( EXIT_FAILURE );
	}
	tempKeyPair = protomapIterator->second;
	field_info = tempKeyPair.second;
	//know the length of the packet
        offset=0;
        while ( offset < totalPacketLength ){
        buff::Buffer<bool>::pass = false;
		//read the packet length
#ifdef DEBUG
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		<<"]"<<"[OFFSET]:"<<offset<<'\n';

#endif
        std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		<<"]"<<"[PACKET LENGTH]:"<<boost::get< VS_INT32 > 
		(buff::Buffer< returnType > ::Read( rawdataPacket , field_info 
						    , mysql_packet_lengrh , 
						    &offset , 
						    3 , 
						    ENC_LITTLE_INDIAN 
						    ) )<<'\n';
		//update the packet length by 4 manualy
        buff::Buffer<VS_INT32>::tvb_length +=4;
		// read the packet number 
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<
		__TIME__<<"]"<<"[OFFSET]:"<<offset<<'\n';
        VS_INT32 packetNumber =boost::get < VS_INT32 > (  buff::Buffer< returnType >::
			Read ( rawdataPacket , field_info , mysql_packet_number
			       	, &offset , 1 , ENC_NA ) );
#ifdef DEBUG
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<
		"[PACKET NUMBER]:"<<packetNumber<<'\n';
#endif

		//try to manage the followig method by implementing template
	//	VS_INT32 packetNumber = buff::Buffer::get_VS_INT8 ( rawdataPacket , offset - 1 );
	    //std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"packet no: "<<packet_number;
	    isResponse= false;
//	    offset +=1;
	    //check the destination port
#ifdef DEBUG
	    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		    "] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		    <<"]"<<"[IS RESPONSE ]:"<<rawdataPacket->appServer<<'\n';
#endif
	    if ( !rawdataPacket->appServer )	isResponse = true;
	    else isResponse = false ;
	    if ( isResponse ) {// packet going to APP
		    if ( packetNumber == 0  ){ //then it is server greetings
			    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "
				    <<__FUNCTION__<<"] Line ["<<__LINE__<<"] Date\
				    Time ["<<__DATE__<<"_"<<__TIME__<<
				    "] no need to dissect greetings\n";
			    return true;
			   }
		    else offset = disect_mysql_response( rawdataPacket,  offset   , 
				    field_info , rawdataPacket->packetNumber , 
				    conversation_packets) ;
		    }else { //packet going to Db
			    if ( packetNumber == 1 ) //it's a login request
				    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "
					    <<__FUNCTION__<<"] Line ["<<__LINE__<<"] Date\
					    Time ["<<__DATE__<<"_"<<__TIME__<<
					    "] no need to dissect login request\n";
			    else
				    //normal request from client to server
				    offset = Mysql::disect_mysql_request ( rawdataPacket, 
						    offset , field_info , 
						    rawdataPacket->packetNumber , 
						    conversation_packets );
#ifdef DEBUG
			    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
				    <<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<
				    __TIME__<<"]"<<"TOTAL TVB LENGTH:"<<
				    buff::Buffer<VS_INT32>::tvb_length<<'\n';
#endif
			    
		    }
	   
	}
	//for a same mainly for response of a select query 
	// offset +=4; chngd on 13/12 -- 6.16
	//Remaining payload indicates an error
    if ( buff::Buffer<VS_INT32>::return_remaining_length ( offset ) )
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
			"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<
			__TIME__<<"] ******DISSECTOR INCOMPLETE*****\n";
	//exit ( EXIT_FAILURE );
	file_handler.close();

	return true;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Mysql::generate_mysql_request_packet
 *  Description:  this method for creating new query request packet
 * =====================================================================================
 */

//function to genarate Request packets
VS_INT32 Mysql::generate_mysql_request_packet(  VS_INT32 offset ,  VS_INT32 oppcode , VS_INT32 currentPacket ,
	       	actSeriesStruct *conversation_packets){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		<<"]\n";
	std::string    query;

#ifdef DEBUG
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		<<"]"<<"{CURRENT PACKET}"<<currentPacket<<'\n';

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		<<"]"<<"opcode is=\t"<<oppcode<<"offset="<<offset<<std::endl;
#endif
	switch ( oppcode ){
		
		case COM_QUERY :{
#ifdef DEBUG
					std::cout<<" File Name ["<<__FILE__<<
						" ] Function [ "<<__FUNCTION__<<
						"] Line ["<<__LINE__<<"] DateTi\
						me ["<<__DATE__<<"_"<<__TIME__<<
						"] now enter new queryread query\
					       	from colByColDataTogether\n"
						<<"query is"<<
						colByColDataTogether.query
						<<"length is"<<
						colByColDataTogether.query.length()
						<<"size="<<
						colByColDataTogether.query.size()
						<<std::endl;
#endif
					//increase offset for oppcode
					offset ++;// ( copy data untill oppcode)
					copyConversationPartially ( newConversationPack ,  
							conversation_packets , 0 , 
							currentPacket  , offset  , 
							offset + 
							colByColDataTogether.query.size() 
							+ 1 ); // added 1 on 23 // 2
					memcpy ( ( newConversationPack->act_raw_data 
								[ currentPacket ].data + offset -1    ) //-1
						       	, colByColDataTogether.query.c_str() , 
						       	( colByColDataTogether.query.size() ) );//-1
std::cout<<"\nPrVS_INT32ing coppied data\n";
for ( STUB_UINT i = 0 ; i< offset + colByColDataTogether.query.size() ;++ i)
std::cout<<newConversationPack->act_raw_data[ currentPacket ].data[i];
//exit(0);
					offset +=colByColDataTogether.query.size();// - 1 ;//
#ifdef DEBUG
					std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<
						__FUNCTION__<<"] Line ["<<__LINE__<<
						"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
						"]  buffer length = "<<
						newConversationPack->act_raw_data [ currentPacket ].length
						<<std::endl;
					std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
						"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<
						__TIME__<<"] offset = "<<offset<<std::endl;
#endif
					newConversationPack->act_raw_data [ currentPacket ].data [ offset ] =
					       	'\0';
					newConversationPack->act_raw_data [ currentPacket ].length = 
						offset + 1; // -1 have to provide
					offset ++;
					//update the  length part of the packet.
					nth24 ( newConversationPack->act_raw_data [ currentPacket ].data   , 
							0 ,  colByColDataTogether.query.size() + 1  );

					std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
						"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
						<<"] size == "<<colByColDataTogether.query.size()<<std::endl;
					// std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"data = "<< newConversationPack->act_raw_data [ currentPacket ].data <<std::endl;
					offset +=colByColDataTogether.query.length();
					break;
				}
				default:
				std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
					__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
					"] for this packet type no genarate packet is available\n";
				break;
	}
	return offset;
}
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Mysql::generate_mysql_response_packet
 *  Description:  this method is responsible tgenerate new query packet.( RESPONSE PACKET)
 * =====================================================================================
 */
VS_INT32 Mysql::generate_mysql_response_packet ( act_raw_dataStruct * raw_packet , VS_INT32 offset ,
		VS_INT32 noOfColumn ,  VS_INT32 currentPacket , VS_INT32 eofLength , 
		actSeriesStruct *conversation_packets){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";
	
        std::string    data;
	VS_INT32       tempOffset;
        VS_INT32       storeOffset;
	VS_INT32       packetNumber;
	STUB_CHAR      *genDatatemp;
        VS_INT32       updatedOffset;
	VS_INT32       lengthUpdateOffset;


	tempOffset = 0;
	storeOffset = 0;
	updatedOffset = 0;
	lengthUpdateOffset = 0;

#ifdef DEBUG
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"][CURRENT PACKET]:"<<
		currentPacket<<'\n';
#endif
	//copy the data of this packet
        try {
#ifdef DEBUG
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
			"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
			"]total row="<<colByColDataTogether.totalSize<<std::endl;
#endif
                genDatatemp = 
			new STUB_CHAR [ ( colByColDataTogether.totalRow * 4 )
		       	+ colByColDataTogether.totalSize ];

        }
        catch ( std::bad_alloc &ba ){
                std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
			__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
			"]Exception is ="<<ba.what()<<std::endl;
		exit ( -1);
        }
        offset+=3;
        //know the current packet no
        packetNumber = buff::Buffer<VS_INT32>::get_guVS_INT328 ( raw_packet , offset ++ );
        for ( VS_INT32 rowCount = 1 ; rowCount <= colByColDataTogether.totalRow; rowCount ++ ){
            tempOffset += 4;
            storeOffset = tempOffset;
            for ( VS_INT32 column = 1 ; column <=noOfColumn ; ++ column ){
			_colInfo::iterator it = colByColDataTogether.colInfo.find( ++ col_no_global );
			if ( it == colByColDataTogether.colInfo.end() )	
				std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
					"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
					<<"]"<<"Function name[can't find column valu from STL map\
				       	colByColDataTogether->colinfo\n";
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<
				__TIME__<<"]inserted data is ["<<rowCount<<"]"<<
				" column["<<column<<"]"<<it->second<<std::endl;
			genDatatemp [ tempOffset++ ] = it->second.length() & 0xff;
			memcpy (  ( genDatatemp + tempOffset ) , it->second.c_str()
				       	, it->second.length() );
			tempOffset += it->second.length() ;
			
		}

                //update the length part of the data
            //for row data first three bits will contain data length( excluding first 4bits)
                nth24 ( genDatatemp , lengthUpdateOffset , tempOffset - storeOffset);//( storeOffset - 2 )  ); // copy the length

                genDatatemp [ lengthUpdateOffset+3 ] = packetNumber;// & 0xff;
                packetNumber ++;
                lengthUpdateOffset = tempOffset;
		
	}
	updatedOffset = tempOffset - 1; // bites of new created rows
	copyConversationPartially ( newConversationPack ,  conversation_packets ,
		       	prev_packet_till_inserted + 1 , currentPacket   , offset - 5 ,
		       	(offset - 4) + updatedOffset + eofLength + 1); //( offset + updatedOffset  + eofLength - 5 ));
	memcpy ( newConversationPack->act_raw_data[ currentPacket ].data + 
			offset - 4   , genDatatemp , tempOffset  );
	memcpy ( newConversationPack->act_raw_data [ currentPacket ].data + 
			(offset - 4 ) + tempOffset  , raw_packet->data +
		       	( raw_packet->length - eofLength   ) , eofLength + 1 );
	newConversationPack->act_raw_data [ currentPacket ].data [offset-4+tempOffset+3] = 
		packetNumber;
	newConversationPack->act_raw_data [ currentPacket ].length =
	       	(offset - 4) + updatedOffset + eofLength + 1 ;
	return ( ( offset - 4 ) + updatedOffset + eofLength + 1) ;
}


/* 
 * ===  FUNCTION  ==============================================================================
 *         Name:  Mysql::get_query_string
 *  Description:  get the query field from the raw packet.This method dissectes queries, those needed to generate new packet.
 *
 * =====================================================================================
 */
VS_INT32  Mysql::get_query_string( act_raw_dataStruct *packet_setting_data_array , queryData *& query_data_array ,
	       	VS_INT32 current_count , VS_INT32 noParam = 0 ){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<
		__TIME__<<"]"<<"FUNCTION:"<<__FUNCTION__<<'\n';
	
	VS_INT32                      offset;
	VS_INT32                      opcode;
	bool                          isResponse;
	proto::mapkey                 tempKeyPair;
	VS_INT32                      packetNumber;
	proto::field_info              *field_info;
	proto::_protoMap::iterator    protomapIterator;
	VS_INT32                      totalPacketLength;


	buff::Buffer< VS_INT32 >::tvb_length  = 0;
	offset = 0;
	isResponse = false ;
	//now for each packet do dissection and put the dissected value VS_INT32o querydataArray.
	if ( ( protomapIterator= proto::protoMap.find ( "MYSQL" ) ) == 
			proto::protoMap.end () ){
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
			"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
			"]Protocol didnot registered / but it must be registered because\
		       	after searching registered proto only dynamic function will  be clled \n";
		return false;
		
	}
	tempKeyPair = protomapIterator->second;
	field_info = tempKeyPair.second;
	//first update the packet no to querydataArray
	query_data_array [ current_count ].packetNo = 
		packet_setting_data_array [ current_count ].packetNumber ;
	//know the length of the packet
	totalPacketLength = packet_setting_data_array[ current_count ].length;
	while ( offset < totalPacketLength ){
		buff::Buffer<bool >::pass = false;
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
			__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]PACKET_LENGTH:"<<
			boost::get<VS_INT32> ( buff::Buffer< returnType >::Read 
					( &packet_setting_data_array [ current_count ] , field_info 
					  , mysql_packet_lengrh , &offset , 3 , ENC_LITTLE_INDIAN ));
		//update the packet length by 4 manualy
		buff::Buffer<VS_INT32>::tvb_length +=4;
		// read the packet number 
		packetNumber =boost::get < VS_INT32 > (  buff::Buffer<returnType >::Read (
				       	&packet_setting_data_array [ current_count ] , field_info
				       	, mysql_packet_number , &offset , 1 , ENC_NA) );
#ifdef DEBUG
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<
			__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<
			__DATE__<<"_"<<__TIME__<<"]"<<"[PACKET NUMBER]:"<<packetNumber<<'\n';
#endif
		
		//check the destination port
		if (  packet_setting_data_array [ current_count].appServer == 0 )	isResponse = false;
		else isResponse = true ;
#ifdef DEBUG
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
			"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<
			__FUNCTION__<<packet_setting_data_array [ current_count].appServer<<
			"::"<<isResponse<<std::endl;
#endif
		query_data_array [ current_count ].flagForGrouping = false;
		if ( !isResponse ) {// packet going to APP
			if ( packetNumber == 0  ){ //then it is server greetings
				//offset = mysql_dissect_greetings ( offset , field_info );
#ifdef DEBUG
				std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
					"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
					"]"<<"SERVER GREETINGS\n";
#endif
				query_data_array [ current_count].query_type = "server greetings";
				query_data_array [ current_count ].query ="greetins";
#ifdef DEBUG
				std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
					"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
					"]no need to dissect greetings\n";
#endif
				offset +=999;
				//return true;
			}
			else{
				query_data_array [ current_count ].query_type = "response";
				query_data_array [ current_count ].query="response";
				Json::flag_for_generate_query = false; // VS_DOUBLE check
//				actSeriesStruct *conversation_packets;
				//			offset = disect_mysql_response( &packet_setting_data_array [ current_count ] , offset  , field_info , packetNumber ,  conversation_packets ) ;
				offset += 999;
				
			}
			
		}else {
#ifdef DEBUG
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "
				<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<
				__DATE__<<"_"<<__TIME__<<"]"<<"packet going to Db\n";
#endif
			if ( packetNumber == 1 ){ //it's a login request
				query_data_array [ current_count].query_type = "login Request";
				query_data_array [ current_count ].query ="login";
#ifdef DEBUG
				std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<
					__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["
					<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<
					"no need to dissect login request\n";
#endif
				offset += 999;

			}else{
#ifdef DEBUG
				std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<
					__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime\
				       	["<<__DATE__<<"_"<<__TIME__<<"]"<<"GENERAL packet---\n";
#endif
			opcode = buff::Buffer<void>::get_guVS_INT328 ( &packet_setting_data_array [ current_count ]  , offset ) ;
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
				__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"][OPCODE]"<<opcode<<'\n';

			offset ++ ;
			switch ( opcode ){
				case  COM_EXECUTE :{
#ifdef DEBUG
							   std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<
								   __FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<
								   __DATE__<<"_"<<__TIME__<<"]"<<"COM EXECUTE\n";
#endif
							   query_data_array[ current_count].query_type = "EXECUTE QUERY";
							   /*-----------------------------------------------------------------------------
							    *  dissect previous request queries response packet to get the no of parameters
I							    *  read packet from PACKET_scenarioName by providing packet no
							    *-----------------------------------------------------------------------------*/
							   if ( noParam == 0){
								   captureQuery::StoreRawPacketQuery *instance ;
								   try{
									   instance = new captureQuery::StoreRawPacketQuery();
								   }
								   catch( std::exception &ea ){
									   std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
										   "] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
										   "]"<<"Exception:"<<ea.what()<<'\n';
exit ( 0 );
								   }
								   act_raw_dataStruct *dataPacket = instance->getPacket
									   ( packet_setting_data_array[ Mysql::prev_packet_no_with_query ].packetNumber 
									     , false );
								   std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
									   "] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
									   "]"<<"Read Data";
								   for ( VS_INT32 i = 0 ; i<dataPacket->length ; ++ i )
									   std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
										   "] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<
										   __TIME__<<"]"<<dataPacket->data[i];
								   std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
									   "] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
									   "]"<<"]\n";
								   noParam = buff::Buffer< void >::getLetohs ( dataPacket , 11 );
								   std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
									   "] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
									   "]"<<"[param]"<<noParam<<'\n';
								   query_data_array[ current_count ].deltaValue = noParam;
								   query_data_array[ Mysql::prev_packet_no_with_query].deltaValue = noParam;

								   std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
									   "] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
									   "]"<<__FUNCTION__<<"[No of PARAM]:"<<noParam<<'\n';
								   try{
									   delete []dataPacket->data;
									   delete dataPacket;
								   }
								   catch ( std::exception &ea ){
									   std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
										   "] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
										   "]Exception:"<<ea.what()<<'\n';
									   exit(0);
								   }
							   }
							   query_data_array[ current_count].query = 
								   Mysql::disect_mysql_requestExecuteStatement( &packet_setting_data_array
										   [ current_count ] , &offset , field_info , noParam);
							   query_data_array[ current_count - 1 ].flagForGrouping = true;
							   query_data_array [ current_count ].flagForGrouping = true;
							   offset += 999;// buff::Buffer< void >::return_remaining_length( offset );
							  return  Mysql::statement_id;

							   break;
						   }
						   
				case COM_CLOSE_STMT:{
#ifdef DEBUG
							    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
								    "] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
								    "]close statement\n";
#endif
							    query_data_array [ current_count].query_type = "REquest close statement";
							    query_data_array [ current_count ].query ="NOT SUPPORTED";
							    // + static_cast<ostringstream*>( &(ostringstream() << boost::get < VS_INT32 > ( buff::Buffer < returnType >::Read( &packet_setting_data_array[current_count] , &field_info ,mysql_statement_id , &offset , 4 , ENC_LITTLE_INDIAN) ) ))->str();
							    offset +=4;
							   offset += 999;// buff::Buffer< void >::return_remaining_length( offset );
							    break;
						    }
						    
				case COM_QUIT:{
#ifdef DEBUG
						      std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
							      __LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"COMMAND QUIT\n";
#endif
						      query_data_array [ current_count].query_type = "QUIT CONNECTION";
						      query_data_array[current_count ].query = "CONNECTION QUIT";
							   offset += 999;// buff::Buffer< void >::return_remaining_length( offset );
						      break;
						      
					      }
					      
				case COM_QUERY:
					      
				case COM_PREPARE:{

							 Mysql::prev_packet_no_with_query = current_count;
#ifdef DEBUG
							 std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
								 "] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
								 "]opcode is "<<(VS_INT32)opcode<<"::"<<packet_setting_data_array
								 [ current_count].data[4]<<'\n';
#endif
							 query_data_array [ current_count ].query =
							       types::getString ( ( u_char * ) packet_setting_data_array 
									       [ current_count ].data ,
									       buff::Buffer<VS_INT32>::tvb_length , offset , 0) ;
#ifdef DEBUG
							 std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
								 __LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]storage value\t"<<
								 query_data_array [ 0 ].query<<'\n';
							 std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
								 __LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]Storage Value"<<
								 query_data_array [ current_count ].query <<'\n';
							        
#endif
							 //offset +=buff::Buffer< void >::return_remaining_length( offset );
offset +=999;
							 break;
							 
						 }
				default:
						 query_data_array [ current_count ].query =  
							 types::getString ( ( u_char * ) packet_setting_data_array [ current_count ].data ,
									 buff::Buffer<VS_INT32>::tvb_length , offset , 0) ;
							   offset += 999;// buff::Buffer< void >::return_remaining_length( offset );
						 query_data_array [ current_count].query_type = "NOT SUPPORTED";
//						 query_data_array[ current_count ].query = "query request from client";
offset +=999;
						 break;
			}
			}

		}
	}
	//Remaining payload indicates an error
	if ( buff::Buffer<VS_INT32>::return_remaining_length( offset ) )
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
			"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<
			__TIME__<<"]"<<__FUNCTION__<<"******DISSECTOR INCOMPLETE*****\n";
	return 0;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  modify_mysql_response
 *  Description:  modify the response packet by updateing statement ID
 * =====================================================================================
 */
VS_INT32 Mysql::modify_mysql_response( actSeriesStruct *conversation_packets , VS_INT32 statement_id ){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		<<"]\n";

	for ( VS_INT32 i = 0 ; i<conversation_packets->no_of_packet ; ++ i ){
		if ( conversation_packets[ i ].act_raw_data->appServer && 
				conversation_packets[ i ].act_raw_data->length > 8 ){
			nth32( conversation_packets[i].act_raw_data->data , 5 , 
					statement_id );
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<
				__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<
				__DATE__<<"_"<<__TIME__<<"]"<<"modified statement iD["
				<<types::get_guVS_INT32( (u_char*)conversation_packets[i].act_raw_data->data
					       	, 15 , 5 , 4 , 1 )<<"]\n";
			//modify the statement id

		}
	}
	return 0;

}

