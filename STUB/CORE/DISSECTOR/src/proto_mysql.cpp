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
STUB_INT JSON = 1;
 std::fstream fileHandler;
STUB_INT rowCount = 0;

 STUB_INT mysqlPacketLength ;
 STUB_INT mysqlPacketNumber;
 STUB_INT mysqlSchema;
 STUB_INT mysqlPayload;
 STUB_INT mysqlNumWarn;
 STUB_INT mysqlStatementId;
 STUB_INT mysqlQuery;
 STUB_INT mysqlExecFlags;
 STUB_INT mysqlExecIterations;
 STUB_INT mysqlEOF;
 STUB_INT mysqlFieldCatalog;
 STUB_INT mysqlFieldDb;
 STUB_INT mysqlFieldTable;
 STUB_INT mysqlFieldOriginalTable;
 STUB_INT mysqlFieldName;
 STUB_INT mysqlFieldldOriginalName;
 STUB_INT mysqlFieldCharsetNumber;
 STUB_INT mysqlFieldLength;
 STUB_INT mysqlFieldType;
 STUB_INT mysqlFieldDecimals;
 STUB_INT mysqlRowText;
 STUB_INT prevQueryState;
 STUB_INT mysqlNumFields ;
 STUB_INT mysqlExecParameter;
 STUB_INT mysqlExecUnsigned;
 STUB_INT mysqlExecFieldLong;
 STUB_INT mysqlExecFieldFloat;
 STUB_INT mysqlExecFieldDouble;
 STUB_INT mysqlExecFieldString;
 STUB_INT recentStatementId = -1;
 STUB_INT colNoGlobal = 0;
 bool rowPacketOffsetFlag = true;
#ifdef NEWPACKET
 STUB_INT rowPacketOffsetStart;
 STUB_INT eofPacketOffsetStart;
 bool isFof;
 STUB_INT prevPacketTillInserted;
#endif
// FOR JSON
Json::Value event;
STUB_INT noOfFielde = 0;
STUB_INT Mysql::noOFfield= 0;
STUB_INT Mysql::prevPacketNoWithQuery = 0;
STUB_INT Mysql::statementId = 0;
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Mysql::initialize
 *  Description:  initialize the mysql protocol,by updateing it's field type , name datatype and run time methods.
 *  this is the first method which will be called from init().
 * =====================================================================================
 */
bool Mysql::initialize( void  ) {

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		<<"] registering mysql protocol\n";

	proto::fpStruct    *functionStructure;

	functionStructure = new proto::fpStruct() ;
	functionStructure->functionToInnitiateDissecton = &Mysql::dissectMysql;
	functionStructure->functionToGetClientRequest= &Mysql::getQueryOnly;
		static proto::packetInfo pi[]={
			{ &mysqlPacketLength,
				{ "Packet Length",types::UINT24,
				       	types::BASE_DECIMAL }},
			{ &mysqlPacketNumber,
					{ "Packet Number", types::UINT8,
					       	types::BASE_DECIMAL }},
			{ &mysqlSchema,
					{ "Schema", types::STRING,
					       	types::BASE_NONE }},
			{ &mysqlPayload,
					{ "Payload",types::BYTES,
					       	types::BASE_NONE}},
			{ &mysqlNumWarn,
					{ "Warnings", types::UINT16,
					       	types::BASE_DECIMAL }},
			{ &mysqlStatementId,
					{ "Statement ID", types::UINT32,
					       	types::BASE_DECIMAL}},
			{ &mysqlQuery,
				{ "Query Statement", types::STRING,
				       	types::BASE_NONE }},
			{ &mysqlExecFlags,
					{ "Flags", types::UINT8,
					       	types::BASE_DECIMAL }},
			{ &mysqlExecIterations,
					{ "Iterations (unused)",types::UINT32, 
						types::BASE_DECIMAL }},
			{ &mysqlEOF,
					{ "EOF marker", types::UINT8,
					       	types::BASE_DECIMAL}},
			{ &mysqlFieldCatalog,
					{ "FIELD Catalog", types::STRING,
					       	types::BASE_NONE }},
			{ &mysqlFieldDb,

					{ "FIELD Database", types::STRING,
					       	types::BASE_NONE}},
			{ &mysqlFieldTable,
					{ "FIELD Table", types::STRING,
					       types::BASE_NONE }},
			{ &mysqlFieldOriginalTable,
					{ "Original table", types::STRING,
					       	types::BASE_NONE }},
			{ &mysqlFieldName,
					{ "Name", types::STRING,
					       	types::BASE_NONE }},
			{ &mysqlFieldldOriginalName,
					{ "Original name", types::STRING,
					       	types::BASE_NONE }},
			{ &mysqlFieldCharsetNumber,
					{ "Charset number", types::UINT16,
                            types::BASE_DECIMAL}},
			{ &mysqlFieldLength,
					{ "Field Length", types::UINT32,
                            types::BASE_DECIMAL }},
			{ &mysqlFieldType,
				{ " FIeld Type", types::UINT8,
                        types::BASE_DECIMAL }},
			{ &mysqlFieldDecimals,
				{ " Field Decimals", types::UINT8,
                        types::BASE_DECIMAL }},
			{ &mysqlRowText,
				{ " Mysql Roe Text", types::STRING, 
					types::BASE_NONE }},
			{&mysqlNumFields,
				{"No of Fields" , types::UINT64,
					types::BASE_DECIMAL } },
			{&mysqlExecParameter,
				{"Parameter" , types::NONE ,
					types::BASE_NONE} },
			{&mysqlExecUnsigned , 
				{"Unsigned" , types::UINT8 ,
					types::BASE_DECIMAL } },
			{&mysqlExecFieldLong ,
				{"long VALUE", types::INT32,
					types::BASE_DECIMAL  } },
			{&mysqlExecFieldFloat ,
				{"Float VALUE" , types::FLOAT ,
					types::BASE_NONE } },
			{&mysqlExecFieldDouble ,
				{"Double VALUE", types::DOUBLE,
					types::BASE_NONE } },
			{&mysqlExecFieldString ,
				{"String VALUE",types::UINT_STRING ,
					types::BASE_NONE } },
			};

    if ( ! ( (  proto::Proto::registerProto ( "MYSQL" , functionStructure , 
					    (sizeof ( pi ) / sizeof ( proto::packetInfo )) ) ) 
			    && ( proto::Proto::insertDissectorProto ( "MYSQL" ,
					    ( sizeof ( pi ) / sizeof ( proto::packetInfo ) )
					    , pi ) )) ) {
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
			__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
			"] Can't register myssql protocol \n";
exit ( 0);
		return false;
    }
// proto::Proto::initDissect ( 3306 , 1 );
//exit ( 0 );
    return true;
}

std::string    responseDataTogetherForRow; //need to be in a proper way

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Mysql::mysqlDissectRowPacket
 *  Description:  dissect row packet protocol of mysql
 * =====================================================================================
 */
STUB_INT Mysql::mysqlDissectRowPackets ( actRawDataStruct *rawDataPacket , STUB_INT offset , 
		proto::fieldInfo *fieldInfoData  ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		<<"]\n";

	STUB_UINT64    lelen;
	STUB_UINT8     isNull;

	offset+=tvbGetFle( rawDataPacket, offset, & ( lelen = 0 ), 
			& ( isNull = 0 ) );
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		<<"] length of data is "<<(STUB_INT)lelen<<'\n';
	std::string rowText = boost::get < std::string > ( buff::Buffer< returnType >
			::Read ( rawDataPacket , fieldInfoData , mysqlRowText , 
				&offset , ( STUB_INT ) lelen , ENC_NA ) );
	if ( JSON != 1 ){
		responseDataTogetherForRow = responseDataTogetherForRow + rowText + ";" ;
	}
#ifdef DEBUG
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"] offset = "
		<<offset<<'\n';
#endif
	return offset;
}


// dissect server status flags
STUB_INT Mysql::mysqlDissectServerStatus (  STUB_INT offset ){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	return ( offset + 2 );
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Mysql::mysqlDissectFieldPacket
 *  Description:  dissect mysql field packet information of response packet
 * =====================================================================================
 */

STUB_INT Mysql::mysqlDissectFieldPacket( actRawDataStruct *rawDataPacket , STUB_INT offset , 
		proto::fieldInfo * fieldInfoData ){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	STUB_UINT64    lelen;
	STUB_UINT8     isNull ;

	isNull = 0;

	offset += tvbGetFle( rawDataPacket, offset, &( lelen = 0 ), &( isNull = 0 ) );
	buff::Buffer< returnType >::Read ( rawDataPacket, fieldInfoData , 
			mysqlFieldCatalog , &offset , (STUB_INT)lelen , ENC_NA );
	offset += tvbGetFle( rawDataPacket, offset, &( lelen = 0 ),
		       	&( isNull = 0 ));
	buff::Buffer< returnType >::Read ( rawDataPacket, fieldInfoData ,  
			mysqlFieldDb, &offset , (STUB_INT)lelen , ENC_NA );
	offset += tvbGetFle( rawDataPacket, offset, &( lelen = 0 ) ,
		       	&( isNull = 0 ) );
	buff::Buffer< returnType >::Read( rawDataPacket, fieldInfoData ,
		      	mysqlFieldTable, &offset , (STUB_INT)lelen , ENC_NA );
	offset += tvbGetFle( rawDataPacket, offset, & ( lelen = 0 ),
		       	&( isNull = 0 ) );
	buff::Buffer < returnType >::Read( rawDataPacket, fieldInfoData ,
		      	mysqlFieldOriginalTable , &offset , (STUB_INT)lelen , ENC_NA );
	offset += tvbGetFle( rawDataPacket, offset, &( lelen = 0 ), 
			&( isNull = 0 ) );
	buff::Buffer< returnType > ::Read ( rawDataPacket, fieldInfoData ,  
			mysqlFieldName , &offset , (STUB_INT)lelen , ENC_NA );
	offset += tvbGetFle( rawDataPacket, offset, &( lelen = 0 ),
		       	&( isNull = 0 ) );
	std::string fieldOriginalName =boost::get < std::string > ( buff::Buffer< returnType >
		       	::Read( rawDataPacket, fieldInfoData ,  mysqlFieldldOriginalName ,
			       	&offset , (STUB_INT)lelen , ENC_NA ) ); 
		fieldOriginalName +=  ";";
		QueryPacket.colNames.insert ( std::make_pair ( 
					Mysql::noOFfield ++ , fieldOriginalName ) );
	event["PACKET/MySQL"]["Query"]="ENTER NEW QUERY";
	event["PACKET/MySQL"]["Response"][fieldOriginalName]="ENTER NEW VALUE";
	offset ++ ; //filler
	buff::Buffer< returnType >::Read ( rawDataPacket , fieldInfoData , mysqlFieldCharsetNumber
		       	, &offset , 2 , ENC_LITTLE_INDIAN );
	buff::Buffer< returnType >::Read ( rawDataPacket , fieldInfoData , mysqlFieldLength , 
			&offset , 4 , ENC_LITTLE_INDIAN );
	STUB_INT fieldType =boost::get < STUB_INT > ( buff::Buffer< returnType >::Read ( rawDataPacket 
				, fieldInfoData , mysqlFieldType , &offset , 1 , ENC_NA ) );
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
	switch ( types::getGuint ( ( u_char *)rawDataPacket->data , rawDataPacket->length , 
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
	buff::Buffer < returnType >::Read( rawDataPacket , fieldInfoData , 
			mysqlFieldDecimals , &( offset +=  2 )  , 1 , ENC_NA );
	offset +=2; // filler

    if ( buff::Buffer< void >::returnRemainingLength( offset ) )
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<" ] SOME EXTRA DATA\n";
	return offset;
	
}

STUB_INT Mysql::tvbGetFle(actRawDataStruct * rawDataPacket, STUB_INT offset , STUB_UINT64 *res, 
		STUB_UINT8 *isNull){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	STUB_INT    prefix;
	
	
	prefix = buff::Buffer< void >::getGuint8 ( rawDataPacket , offset++ );
	if (isNull)
		*isNull = 0;
	switch (prefix) {
		case 251:
			if (res)
				*res = 0;
			if (isNull)
				*isNull = 1;
			break;
			case 252:
			if (res)
                *res = buff::Buffer< void >::getLetohs( rawDataPacket, offset );
			return 3;
			case 253:
			if (res)
                *res = buff::Buffer< void >::getLetohl (rawDataPacket, offset );
			return 5;
			case 254:
			if (res)
                *res =buff::Buffer< void >::getLetoh64( rawDataPacket, offset );
			return 9;
			default:
			if (res)
				*res = prefix;
		}
	return 1;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Mysql::mysqlDissectResultHeader
 *  Description:  dissect the result header field
 * =====================================================================================
 */

STUB_INT Mysql::mysqlDissectResultHeader( actRawDataStruct *rawDataPacket , STUB_INT offset ){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	STUB_INT       fle;
	STUB_UINT64    numFields;

	fle = tvbGetFle( rawDataPacket , offset , &numFields , NULL );
	noOfFielde = numFields;
#ifdef DEBUG
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		<<"]"<<"[OFFSET]:[NO OF FIELD]:"<<offset<<"::"
		<<noOfFielde<<'\n';
#endif
    if ( numFields   )field::prevQuery.prevQueryState = FIELD_PACKET;
	else field::prevQuery.prevQueryState = ROW_PACKET ;
	offset += fle;
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		<<"]"<<"RETURN OFFSET:"<<offset<<'\n';
	return (offset );
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Mysql::mysqlDissectResponsePrepare
 *  Description:  dissect response prepare packet for mysql
 * =====================================================================================
 */
bool Mysql::mysqlDissectResponsePrepare ( actRawDataStruct *rawDataPacket , 
		STUB_INT *offset){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	STUB_INT    noOfParam;
	STUB_INT    noOfFields;
	STUB_INT    statementId;

	//read statement ID
	statementId = buff::Buffer< void >::getLetohl ( rawDataPacket, *offset );
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
		"] [STATEMENT ID]:"<<statementId<<'\n';
	*offset += 4;
	noOfFields = buff::Buffer< void >::getLetohs ( rawDataPacket , *offset );
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
		"] [no of Fields]:"<<noOfFields<<'\n';
	*offset += 2;
	noOfParam = buff::Buffer< void >::getLetohs ( rawDataPacket , *offset );
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
		"] [No of PARAM]:"<<noOfParam<<'\n';
	*offset += 2;
	//filler
	*offset = *offset + 1 ;
	if ( noOfParam > 0 ) field::prevQuery.prevQueryState = PREPARED_PARAMETERS ;
	else if( noOfFields > 0 ) field::prevQuery.prevQueryState = PREPARED_FIELDS;
	else field::prevQuery.prevQueryState = REQUEST;
	*offset += buff::Buffer < void >::returnRemainingLength ( *offset );

	return true;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Mysql::mysqlDissectResponse
 *  Description:  dissect mysql response packet ( Response packet of a query)
 * =====================================================================================
 */
STUB_INT Mysql::mysqlDissectResponse ( actRawDataStruct *rawdataPacket , STUB_INT offset , 
		proto::fieldInfo * fieldInfoData, STUB_INT packetNo , 
		actSeriesStruct *conversationPackets){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	STUB_INT    columnCount;
	STUB_INT    responseCode; 
	STUB_INT    eofLengthPrevious;


#ifdef DEBUG
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<
		"{PREVIOUS QUERY:}"<<field::prevQuery.prevQueryState<<'\n';
#endif
    responseCode = buff::Buffer< STUB_INT >::getGuint8 ( rawdataPacket ,  offset );
    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
	    <<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"response code:"
	    <<responseCode<<"::"<<( STUB_INT)(rawdataPacket->data[offset] ) <<'\n';
	if ( responseCode == 0xff ) {
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
			"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
			<<"] Error packet at mysql_dissect_response --\n";

		return offset;
	}
        else {
        if ( responseCode == 0xfe  && 
			( buff::Buffer< void > ::returnRemainingLength( offset ) < 9 ) ) {
			eofLengthPrevious = (rawdataPacket->length - ( offset - 4 ) ) ;
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] eoflengthPrevious="<<eofLengthPrevious<<std::endl;
             buff::Buffer< returnType >::Read ( rawdataPacket, fieldInfoData , 
			     mysqlEOF , &offset , 1 , ENC_NA ) ;
			 //pre 4.1 packet ends here
            if ( buff::Buffer< void >::returnRemainingLength( offset ) ){
		    buff::Buffer< returnType >::Read (rawdataPacket, fieldInfoData , 
				    mysqlNumWarn , &offset , 2 , ENC_LITTLE_INDIAN ) ;
				//now dissect server header flags
				offset = mysqlDissectServerStatus ( offset );
			}
			if ( field::prevQuery.prevQueryState == FIELD_PACKET ){
				fileHandler<<event<<std::endl;
				field::prevQuery.prevQueryState = ROW_PACKET;
			}
	
//#ifdef NEWPACKET
			else if ( ( field::prevQuery.prevQueryState == ROW_PACKET )
				       	&& Json::flagForGenerateQuery ){
				mysqlGenerateResponsePacket(rawdataPacket , rowPacketOffsetStart , 
						noOfFielde ,packetNo, eofLengthPrevious , 
						conversationPackets );
				return 999;
            }

//#endif
	}else if ( responseCode == 0 ){
		if ( field::prevQuery.prevQueryState == RESPONSE_PREPARE ) 
			mysqlDissectResponsePrepare( rawdataPacket , &offset  );
	}


		else {
			switch (  field::prevQuery.prevQueryState ) {
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
						mysqlDissectResultHeader ( rawdataPacket , offset );
					break;
					
				case FIELD_PACKET:
					
				case RESPONSE_SHOW_FIELDS:
					
				case RESPONSE_PREPARE:
					
				case PREPARED_PARAMETERS:
					offset = mysqlDissectFieldPacket( rawdataPacket, 
							offset , fieldInfoData);
					break;
					
				case ROW_PACKET:
#ifdef DEBUG
					std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<
						__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["
						<<__DATE__<<"_"<<__TIME__<<
						"] row count offset="<<offset<<std::endl;
#endif
					if ( rowPacketOffsetFlag ) {
						rowPacketOffsetStart = offset - 4 ;
						rowPacketOffsetFlag = false ;
					}
					columnCount = noOfFielde ;
					//    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"now learn to dissect row packet ::"<<noOfFielde<<std::endl;
					while ( columnCount != 0 ){
						// std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"column no :"<<columnCount--<<std::endl;
						columnCount --;
						offset = mysqlDissectRowPackets ( rawdataPacket ,
							       	offset , fieldInfoData );
						std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<
							__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<
							__DATE__<<"_"<<__TIME__<<"]"<<columnCount<<std::endl;
					}
					QueryPacket.rowCount = ++rowCount ;
					QueryPacket.colInfo.insert ( std::make_pair ( QueryPacket.rowCount ,
								responseDataTogetherForRow ) );
					break;
				}
		}
	
    }
	return offset;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Mysql::dissectDatatype
 *  Description:  dissect datatype of execute statement packet
 * =====================================================================================
 */
//extraxt valu from specified datatype( long , STUB_DOUBLE ,STUB_FLOAT )
std::string Mysql::dissectDatatype( actRawDataStruct * rawdataPacket , STUB_INT *offset , 
		proto::fieldInfo *fieldInfoData , STUB_INT dataType , STUB_INT lengthDatatype ){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	std::string    parameterValue;
	//now read the data with respect to datatype
	if ( dataType ==  mysqlExecFieldLong ){
		parameterValue = std::to_string ( static_cast< long long >( boost::get< STUB_INT >
					(buff::Buffer< returnType > ::Read( rawdataPacket , 
									    fieldInfoData , 
									    dataType , 
									    &(*offset) ,
									    4 , 
									    ENC_LITTLE_INDIAN 
									    )) ) );
	}
	else{ if ( dataType ==  mysqlExecFieldFloat)
		parameterValue = std::to_string( static_cast< long long> ( boost::get< STUB_FLOAT >
					(buff::Buffer< returnType > ::Read( rawdataPacket , 
									    fieldInfoData , 
									    dataType , 
									    &(*offset) , 
									    lengthDatatype , 
									    ENC_LITTLE_INDIAN 
									    )) ) );

	else {if ( dataType == mysqlExecFieldDouble )
		parameterValue = std::to_string ( static_cast < long long > (boost::get< STUB_DOUBLE >
					(buff::Buffer< returnType > ::Read( rawdataPacket , 
									    fieldInfoData , 
									    dataType , 
									    &(*offset) , 
									    lengthDatatype , 
									    ENC_LITTLE_INDIAN 
									    )) ));
	else
		parameterValue = "No SPECIFIED DATATYPE";
	}
	}
	return parameterValue;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Mysql::dissectExecString
 *  Description:  dissect the string datatype of execute statement packet
 * =====================================================================================
 */
std::string Mysql::dissectExecString( actRawDataStruct *rawdataPacket , STUB_INT *offset ){ 
//		proto::fieldInfo *fieldInfoData , STUB_INT dataType , STUB_INT lengthDatatype){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	std::string   data; 
	STUB_INT      parameterLength;


	//return "done";
	parameterLength = buff::Buffer< void >::getGuint8 ( rawdataPacket ,
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
	for ( STUB_INT ii = 0 ; ii< parameterLength ; ++ ii )
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<(STUB_CHAR)rawdataPacket->data[ii]<<std::endl;
	exit(0);
	STUB_UINT32 parameterLength32;
	STUB_UINT32 fieldString;
	switch ( parameterLength ){
		case 0xfc:
			*offset += 1;
			parameterLength32 = buff::Buffer < void >::getLetohs( rawdataPacket , *offset );
			fieldString = boost::get< STUB_UINT32 > (buff::Buffer< returnType > ::Read( rawdataPacket , fieldInfoData , mysqlExecFieldString , &(*offset) , 2 , ENC_NA ) );
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<"[FIELD STRING]:"<<fieldString<<'\n';
			* offset += parameterLength32  + 2 ;
			break;
		case 0xfd:
			*offset ++;
			parameterLength32 = buff::Buffer < void >::getLetoh24(rawdataPacket , *offset );
			fieldString = boost::get< STUB_UINT32 >( buff::Buffer < returnType >::Read ( rawdataPacket , fieldInfoData , mysqlExecFieldString ,&(*offset) , 3 , ENC_NA) );
			*offset += parameterLength32 + 3 ;
		default:
			fieldString = boost::get< STUB_UINT32 > (buff::Buffer< returnType > ::Read( rawdataPacket , fieldInfoData , mysqlExecFieldString , &(*offset) , 1 , ENC_NA ) );
			*offset += parameterLength + 1;
	}return std::to_string ( static_cast<long long>( fieldString ) );	
	*/
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Mysql::mysqlDissectRequestExecParameter
 *  Description:  dissect parameter , datatype, value...tail part of execute statement
 * =====================================================================================
 */
std::string Mysql::mysqlDissectExecParameter ( actRawDataStruct * rawdataPacket , 
		STUB_INT *offset , proto::fieldInfo *fieldInfoData, 
		STUB_INT noParameters =1 ){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		<<"]\n";

	bool           pass;
	STUB_INT       index;
	STUB_INT       *paramType;
	std::string    returnString;
	STUB_INT       *paramUnsigned;

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		<<"]"<<"[PARAMETER COUNT]:"<<noParameters<<"]\n";

	//initialize execute dissectors structure array field
	mysqlExecuteDissector executeDissectors[ 8 ] ={
//	    { 0x01, 0, mysql_dissect_exec_tiny },
//	    { 0x02, 0, mysql_dissect_exec_short },
	    { 0x03, 0, &Mysql::dissectDatatype , mysqlExecFieldLong , 4 },
	    { 0x04, 0, &Mysql::dissectDatatype , mysqlExecFieldFloat , 4 },
	    { 0x05, 0, &Mysql::dissectDatatype , mysqlExecFieldDouble , 8},
//	    { 0x06, 0, mysql_dissect_exec_null },
//	    { 0x07, 0, mysql_dissect_exec_datetime },
//	    { 0x08, 0, mysql_dissect_exec_lonSTUB_LONG },
//	    { 0x0a, 0, mysql_dissect_exec_datetime },
//	    { 0x0b, 0, mysql_dissect_exec_time },
//	    { 0x0c, 0, mysql_dissect_exec_datetime },
	    { 0xf6, 0, &Mysql::dissectExecString , mysqlExecFieldString, 0 },
	    { 0xfc, 0, &Mysql::dissectExecString , mysqlExecFieldString , 0},
	    { 0xfd, 0, &Mysql::dissectExecString , mysqlExecFieldString , 0},
	    { 0xfe, 0, &Mysql::dissectExecString , mysqlExecFieldString , 0},
	    { 0x00, 0, NULL , 0, 0},
    };
	try {
		paramType = new STUB_INT[noParameters ];
		paramUnsigned = new STUB_INT [ noParameters ];
	}
	catch ( std::exception &ba ){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
			"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
			<<"]"<<"exception["<<ba.what()<<
			"] on creating paramType and paramUnsigned\n";
		exit(0);
	}
	for ( STUB_INT i = 0 ; i< noParameters ;++i ){
		paramType[i] = boost::get< STUB_INT > (buff::Buffer< returnType > ::
				Read( rawdataPacket , fieldInfoData , 
					mysqlFieldType , &(*offset) ,
				       	1 , ENC_NA ) );
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<
			__TIME__<<"] [PARAM TYPE]:"<<paramType[i]<<'\n';
		paramUnsigned[i] = boost::get< STUB_INT > (buff::Buffer< returnType > ::
				Read( rawdataPacket , fieldInfoData , 
					mysqlExecUnsigned , &(*offset) ,
				       	1 , ENC_NA ) );
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
			"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
			<<"] [PARAM UNSIGNED]:"<<paramUnsigned[i]<<'\n';
	}
	for ( STUB_INT i = 0 ; i< noParameters ; ++i){
	  index = 0;
	  pass = false;
	  while ( ( executeDissectors[ index].type != 0 ) & ( !pass ))  {
		  if ( ( executeDissectors[index].type == paramType[i] ) 
				  &&  ( executeDissectors[index ].flagUnsigned 
					  ==paramUnsigned[i] ) ){
			  pass = true;
			  
#ifdef DEBUG
			  std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<
				  __FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime\
				  ["<<__DATE__<<"_"<<__TIME__<<"]"<<"SEARCH \
				  ATCHED:["<<index<<"]\n"<<"datatype:["<<
				  executeDissectors[ index ].dataType
				  <<"]\n"<<"Length:["<<executeDissectors[ index ].
				  length<<"]\n";
			  
#endif
	//		  *offset += 2;
			  returnString +=boost::any_cast< std::string ( * )
				  ( actRawDataStruct * , STUB_INT* , proto::fieldInfo * ,
				    STUB_INT , STUB_INT )>( executeDissectors[ index].dissectorMethod)
				  ( rawdataPacket ,  &(*offset ) , fieldInfoData , 
				    executeDissectors[ index].dataType , 
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
 *         Name:  Mysql::mysqlDissectRequestExecuteStatement
 *  Description:  dissect execute statement request that contains STATEMENT ID , ITERATION
 * =====================================================================================
 */
std::string Mysql::mysqlDissectRequestExecuteStatement ( actRawDataStruct *rawdataPacket ,
	       	STUB_INT *offset , proto::fieldInfo *fieldInfoData , STUB_INT noParameters = 0 ){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
		"] INITIAL OFFSET:"<<*offset<<'\n';
	recentStatementId = boost::get<  STUB_INT > (buff::Buffer< returnType > ::
			Read( rawdataPacket , fieldInfoData , mysqlStatementId,
			       	&(*offset) , 4 , ENC_LITTLE_INDIAN ) );

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		<<"]"<<"[STATEMENT ID]"<<recentStatementId;
	Mysql::statementId = recentStatementId;
#ifdef DEBUG

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		<<"] OFFSET AFTER STATEMENT ID:"<<*offset<<'\n';
#endif
	//FLAG
	*offset +=  1;
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		<<"]"<<"[ITERATIONS]:"<< boost::get< STUB_INT > (buff::Buffer< returnType > 
				::Read( rawdataPacket , fieldInfoData , 
					mysqlExecIterations ,
				       	&(*offset) ,
				       	4 , 
					ENC_LITTLE_INDIAN ) )<<'\n'; 
	/*-----------------------------------------------------------------------------
	*  sometime this packet does not contains parameter part, 
	 *  so check remaing length remaining
       *-----------------------------------------------------------------------------*/
	if(  buff::Buffer <STUB_INT>::returnRemainingLength ( *offset ) < 2 )  
		return "NO PARAMETER";
	//have to dissect for the offsets 
	*offset += 2;
	 return ( mysqlDissectExecParameter( rawdataPacket , &(*offset) , 
				 fieldInfoData , noParameters ) ); 
/*	while ( !(buff::Buffer < STUB_INT >::returnRemainingLength ( *offset ) < 2 ))
		returnString  mysqlDissectExecParameter( rawdataPacket , &(*offset) , fieldInfoData ) ;
	return returnString;
	*/
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Mysql::mysqlDissectRequest
 *  Description:  dissect the request packet, packet which are going to mysql server are getting dissected 
 *  by the following method.
 * =====================================================================================
 */
 STUB_INT Mysql::mysqlDissectRequest ( actRawDataStruct *rawdataPacket , STUB_INT offset , 
		 proto::fieldInfo * fieldInfoData , STUB_INT currentPacket , 
		 actSeriesStruct * conversationPackets){

	 std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		 "] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		 <<"]\n";

	 STUB_INT    opcode;
	 STUB_INT    newDataSetOffsetPosition;

	 //1st read teh oppcode from the packet
         opcode = (STUB_INT)buff::Buffer< void > ::getGuint8(rawdataPacket  ,  offset++ ) ;

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
					std::string mysqlQueryString =boost::get < std::string>
						(buff::Buffer< returnType >::Read (rawdataPacket 
										   , fieldInfoData 
										   , mysqlQuery 
										   , &offset 
										   , 0 
										   , ENC_NA ) );
					if ( JSON ){
						QueryPacket.query = mysqlQueryString;
						QueryPacket.queryType = COM_QUERY;
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
					
					if ( Json::flagForGenerateQuery ){
						prevQueryState = RESPONSE_TABULAR;
						mysqlGenerateRequestPacket( newDataSetOffsetPosition ,
							       	opcode , currentPacket ,
							       	conversationPackets);
						rowPacketOffsetFlag = true ;
					}

					opcode = COM_QUERY ?( field::prevQuery.prevQueryState = 
							RESPONSE_TABULAR ): (field::prevQuery.prevQueryState 
								= RESPONSE_PREPARE );
				
				}
				break;
		 case COM_EXECUTE :
				std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
					"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<
					__TIME__<<"]"<<"BEFORE OFFSET_______"<<offset<<'\n';
				Mysql::mysqlDissectRequestExecuteStatement( rawdataPacket , 
						&offset , fieldInfoData );
				field::prevQuery.prevQueryState = RESPONSE_TABULAR;
				std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
					<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<
					__TIME__<<"]"<<"AFTER OFFSET-------------"<<offset<<'\n';
				break;
		 case COM_CLOSE_STMT:
				std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<
					__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<
					__DATE__<<"_"<<__TIME__<<"] [STATEMENT ID]:"<< 
					boost::get<  STUB_INT > (buff::Buffer< returnType > ::
							Read( rawdataPacket , fieldInfoData , 
								mysqlStatementId, &(offset) , 
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
 *         Name:  Mysql::dissectMysql
 *  Description:  method to dissect mysql query packet( REQUEST + RESPONSE )
 * =====================================================================================
 */
bool Mysql::dissectMysql( actRawDataStruct *rawdataPacket , STUB_INT totalPacketLength , 
		actSeriesStruct * conversationPackets ){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<
		"[TOTAL_PACKET_LENGTH]:"<<totalPacketLength<<std::endl;
	STUB_INT            offset;
	proto::fieldInfo    *fieldInfo;
	bool                isResponse;
	proto::mapkey       tempKeyPair;


	//open file for Json ,this file will take input for new query
	fileHandler.open("../STUB/json.js",std::ios::out); 
	if ( !fileHandler.is_open() ){
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
	fieldInfo = tempKeyPair.second;
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
		<<"]"<<"[PACKET LENGTH]:"<<boost::get< STUB_INT > 
		(buff::Buffer< returnType > ::Read( rawdataPacket , fieldInfo 
						    , mysqlPacketLength , 
						    &offset , 
						    3 , 
						    ENC_LITTLE_INDIAN 
						    ) )<<'\n';
		//update the packet length by 4 manualy
        buff::Buffer<STUB_INT>::tvbLength +=4;
		// read the packet number 
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<
		__TIME__<<"]"<<"[OFFSET]:"<<offset<<'\n';
        STUB_INT packetNumber =boost::get < STUB_INT > (  buff::Buffer< returnType >::
			Read ( rawdataPacket , fieldInfo , mysqlPacketNumber
			       	, &offset , 1 , ENC_NA ) );
#ifdef DEBUG
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<
		"[PACKET NUMBER]:"<<packetNumber<<'\n';
#endif

		//try to manage the followig method by implementing template
	//	STUB_INT packetNumber = buff::Buffer::get_STUB_UINT8 ( rawdataPacket , offset - 1 );
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
		    else offset = mysqlDissectResponse( rawdataPacket,  offset   , 
				    fieldInfo , rawdataPacket->packetNumber , 
				    conversationPackets) ;
		    }else { //packet going to Db
			    if ( packetNumber == 1 ) //it's a login request
				    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "
					    <<__FUNCTION__<<"] Line ["<<__LINE__<<"] Date\
					    Time ["<<__DATE__<<"_"<<__TIME__<<
					    "] no need to dissect login request\n";
			    else
				    //normal request from client to server
				    offset = Mysql::mysqlDissectRequest ( rawdataPacket, 
						    offset , fieldInfo , 
						    rawdataPacket->packetNumber , 
						    conversationPackets );
#ifdef DEBUG
			    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
				    <<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<
				    __TIME__<<"]"<<"TOTAL TVB LENGTH:"<<
				    buff::Buffer<STUB_INT>::tvbLength<<'\n';
#endif
			    
		    }
	   
	}
	//for a same mainly for response of a select query 
	// offset +=4; chngd on 13/12 -- 6.16
	//Remaining payload indicates an error
    if ( buff::Buffer<STUB_INT>::returnRemainingLength ( offset ) )
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
			"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<
			__TIME__<<"] ******DISSECTOR INCOMPLETE*****\n";
	//exit ( EXIT_FAILURE );
	fileHandler.close();

	return true;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Mysql::mysqlGenerateRequestPacket
 *  Description:  this method for creating new query request packet
 * =====================================================================================
 */

//function to genarate Request packets
STUB_INT Mysql::mysqlGenerateRequestPacket(  STUB_INT offset ,  STUB_INT oppcode , STUB_INT currentPacket ,
	       	actSeriesStruct *conversationPackets){

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
							conversationPackets , 0 , 
							currentPacket  , offset  , 
							offset + 
							colByColDataTogether.query.size() 
							+ 1 ); // added 1 on 23 // 2
					memcpy ( ( newConversationPack->actRawData 
								[ currentPacket ].data + offset -1    ) //-1
						       	, colByColDataTogether.query.c_str() , 
						       	( colByColDataTogether.query.size() ) );//-1
std::cout<<"\nPrSTUB_INTing coppied data\n";
for ( STUB_UINT i = 0 ; i< offset + colByColDataTogether.query.size() ;++ i)
std::cout<<newConversationPack->actRawData[ currentPacket ].data[i];
//exit(0);
					offset +=colByColDataTogether.query.size();// - 1 ;//
#ifdef DEBUG
					std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<
						__FUNCTION__<<"] Line ["<<__LINE__<<
						"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
						"]  buffer length = "<<
						newConversationPack->actRawData [ currentPacket ].length
						<<std::endl;
					std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
						"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<
						__TIME__<<"] offset = "<<offset<<std::endl;
#endif
					newConversationPack->actRawData [ currentPacket ].data [ offset ] =
					       	'\0';
					newConversationPack->actRawData [ currentPacket ].length = 
						offset + 1; // -1 have to provide
					offset ++;
					//update the  length part of the packet.
					nth24 ( newConversationPack->actRawData [ currentPacket ].data   , 
							0 ,  colByColDataTogether.query.size() + 1  );

					std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
						"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
						<<"] size == "<<colByColDataTogether.query.size()<<std::endl;
					// std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"data = "<< newConversationPack->actRawData [ currentPacket ].data <<std::endl;
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
 *         Name:  Mysql::mysqlGenerateResponsePacket
 *  Description:  this method is responsible tgenerate new query packet.( RESPONSE PACKET)
 * =====================================================================================
 */
STUB_INT Mysql::mysqlGenerateResponsePacket ( actRawDataStruct * rawDataPacket , STUB_INT offset ,
		STUB_INT noOfColumn ,  STUB_INT currentPacket , STUB_INT eofLength , 
		actSeriesStruct *conversationPackets){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";
	
        std::string    data;
	STUB_INT       tempOffset;
        STUB_INT       storeOffset;
	STUB_INT       packetNumber;
	STUB_CHAR      *genDatatemp;
        STUB_INT       updatedOffset;
	STUB_INT       lengthUpdateOffset;


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
        packetNumber = buff::Buffer<STUB_INT>::getGuint8 ( rawDataPacket , offset ++ );
        for ( STUB_INT rowCount = 1 ; rowCount <= colByColDataTogether.totalRow; rowCount ++ ){
            tempOffset += 4;
            storeOffset = tempOffset;
            for ( STUB_INT column = 1 ; column <=noOfColumn ; ++ column ){
			_colInfo::iterator it = colByColDataTogether.colInfo.find( ++ colNoGlobal );
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
	copyConversationPartially ( newConversationPack ,  conversationPackets ,
		       	prevPacketTillInserted + 1 , currentPacket   , offset - 5 ,
		       	(offset - 4) + updatedOffset + eofLength + 1); //( offset + updatedOffset  + eofLength - 5 ));
	memcpy ( newConversationPack->actRawData[ currentPacket ].data + 
			offset - 4   , genDatatemp , tempOffset  );
	memcpy ( newConversationPack->actRawData [ currentPacket ].data + 
			(offset - 4 ) + tempOffset  , rawDataPacket->data +
		       	( rawDataPacket->length - eofLength   ) , eofLength + 1 );
	newConversationPack->actRawData [ currentPacket ].data [offset-4+tempOffset+3] = 
		packetNumber;
	newConversationPack->actRawData [ currentPacket ].length =
	       	(offset - 4) + updatedOffset + eofLength + 1 ;
	return ( ( offset - 4 ) + updatedOffset + eofLength + 1) ;
}


/* 
 * ===  FUNCTION  ==============================================================================
 *         Name:  Mysql::getQueryOnly
 *  Description:  get the query field from the raw packet.This method dissectes queries, those needed to generate new packet.
 *
 * =====================================================================================
 */
STUB_INT Mysql::getQueryOnly( actRawDataStruct *packetSettingDataArray , queryData *& queryDataArray ,
	       	STUB_INT currentCount , STUB_INT noParam = 0 ){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<
		__TIME__<<"]"<<"FUNCTION:"<<__FUNCTION__<<'\n';
	
	STUB_INT                      offset;
	STUB_INT                      opcode;
	bool                          isResponse;
	proto::mapkey                 tempKeyPair;
	STUB_INT                      packetNumber;
	proto::fieldInfo              *fieldInfoData;
	proto::_protoMap::iterator    protomapIterator;
	STUB_INT                      totalPacketLength;


	buff::Buffer< STUB_INT >::tvbLength  = 0;
	offset = 0;
	isResponse = false ;
	//now for each packet do dissection and put the dissected value into querydataArray.
	if ( ( protomapIterator= proto::protoMap.find ( "MYSQL" ) ) == 
			proto::protoMap.end () ){
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
			"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
			"]Protocol didnot registered / but it must be registered because\
		       	after searching registered proto only dynamic function will  be clled \n";
		return false;
		
	}
	tempKeyPair = protomapIterator->second;
	fieldInfoData = tempKeyPair.second;
	//first update the packet no to querydataArray
	queryDataArray [ currentCount ].packetNo = 
		packetSettingDataArray [ currentCount ].packetNumber ;
	//know the length of the packet
	totalPacketLength = packetSettingDataArray[ currentCount ].length;
	while ( offset < totalPacketLength ){
		buff::Buffer<bool >::pass = false;
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
			__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]PACKET_LENGTH:"<<
			boost::get<STUB_INT> ( buff::Buffer< returnType >::Read 
					( &packetSettingDataArray [ currentCount ] , fieldInfoData 
					  , mysqlPacketLength , &offset , 3 , ENC_LITTLE_INDIAN ));
		//update the packet length by 4 manualy
		buff::Buffer<STUB_INT>::tvbLength +=4;
		// read the packet number 
		packetNumber =boost::get < STUB_INT > (  buff::Buffer<returnType >::Read (
				       	&packetSettingDataArray [ currentCount ] , fieldInfoData
				       	, mysqlPacketNumber , &offset , 1 , ENC_NA) );
#ifdef DEBUG
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<
			__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<
			__DATE__<<"_"<<__TIME__<<"]"<<"[PACKET NUMBER]:"<<packetNumber<<'\n';
#endif
		
		//check the destination port
		if (  packetSettingDataArray [ currentCount].appServer == 0 )	isResponse = false;
		else isResponse = true ;
#ifdef DEBUG
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
			"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<
			__FUNCTION__<<packetSettingDataArray [ currentCount].appServer<<
			"::"<<isResponse<<std::endl;
#endif
		queryDataArray [ currentCount ].flagForGrouping = false;
		if ( !isResponse ) {// packet going to APP
			if ( packetNumber == 0  ){ //then it is server greetings
				//offset = mysql_dissect_greetings ( offset , field_info );
#ifdef DEBUG
				std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
					"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
					"]"<<"SERVER GREETINGS\n";
#endif
				queryDataArray [ currentCount].queryType = "server greetings";
				queryDataArray [ currentCount ].query ="greetins";
#ifdef DEBUG
				std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
					"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
					"]no need to dissect greetings\n";
#endif
				offset +=999;
				//return true;
			}
			else{
				queryDataArray [ currentCount ].queryType = "response";
				queryDataArray [ currentCount ].query="response";
				Json::flagForGenerateQuery = false; // STUB_DOUBLE check
//				actSeriesStruct *conversationPackets;
				//			offset = mysqlDissectResponse( &packetSettingDataArray [ currentCount ] , offset  , fieldInfoData , packetNumber ,  conversationPackets ) ;
				offset += 999;
				
			}
			
		}else {
#ifdef DEBUG
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "
				<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<
				__DATE__<<"_"<<__TIME__<<"]"<<"packet going to Db\n";
#endif
			if ( packetNumber == 1 ){ //it's a login request
				queryDataArray [ currentCount].queryType = "login Request";
				queryDataArray [ currentCount ].query ="login";
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
			opcode = buff::Buffer<void>::getGuint8 ( &packetSettingDataArray [ currentCount ]  , offset ) ;
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
							   queryDataArray[ currentCount].queryType = "EXECUTE QUERY";
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
								   actRawDataStruct *dataPacket = instance->getPacket
									   ( packetSettingDataArray[ Mysql::prevPacketNoWithQuery ].packetNumber 
									     , false );
								   std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
									   "] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
									   "]"<<"Read Data";
								   for ( STUB_INT i = 0 ; i<dataPacket->length ; ++ i )
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
								   queryDataArray[ currentCount ].deltaValue = noParam;
								   queryDataArray[ Mysql::prevPacketNoWithQuery].deltaValue = noParam;

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
							   queryDataArray[ currentCount].query = 
								   Mysql::mysqlDissectRequestExecuteStatement( &packetSettingDataArray
										   [ currentCount ] , &offset , fieldInfoData , noParam);
							   queryDataArray[ currentCount - 1 ].flagForGrouping = true;
							   queryDataArray [ currentCount ].flagForGrouping = true;
							   offset += 999;// buff::Buffer< void >::returnRemainingLength( offset );
							  return  Mysql::statementId;

							   break;
						   }
						   
				case COM_CLOSE_STMT:{
#ifdef DEBUG
							    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
								    "] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
								    "]close statement\n";
#endif
							    queryDataArray [ currentCount].queryType = "REquest close statement";
							    queryDataArray [ currentCount ].query ="NOT SUPPORTED";
							    // + static_cast<ostringstream*>( &(ostringstream() << boost::get < STUB_INT > ( buff::Buffer < returnType >::Read( &packetSettingDataArray[currentCount] , &fieldInfoData ,mysqlStatementId , &offset , 4 , ENC_LITTLE_INDIAN) ) ))->str();
							    offset +=4;
							   offset += 999;// buff::Buffer< void >::returnRemainingLength( offset );
							    break;
						    }
						    
				case COM_QUIT:{
#ifdef DEBUG
						      std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
							      __LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"COMMAND QUIT\n";
#endif
						      queryDataArray [ currentCount].queryType = "QUIT CONNECTION";
						      queryDataArray[currentCount ].query = "CONNECTION QUIT";
							   offset += 999;// buff::Buffer< void >::returnRemainingLength( offset );
						      break;
						      
					      }
					      
				case COM_QUERY:
					      
				case COM_PREPARE:{

							 Mysql::prevPacketNoWithQuery = currentCount;
#ifdef DEBUG
							 std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
								 "] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
								 "]opcode is "<<(STUB_INT)opcode<<"::"<<packetSettingDataArray
								 [ currentCount].data[4]<<'\n';
#endif
							 queryDataArray [ currentCount ].query =
							       types::getString ( ( u_char * ) packetSettingDataArray 
									       [ currentCount ].data ,
									       buff::Buffer<STUB_INT>::tvbLength , offset , 0) ;
#ifdef DEBUG
							 std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
								 __LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]storage value\t"<<
								 queryDataArray [ 0 ].query<<'\n';
							 std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
								 __LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]Storage Value"<<
								 queryDataArray [ currentCount ].query <<'\n';
							        
#endif
							 //offset +=buff::Buffer< void >::returnRemainingLength( offset );
offset +=999;
							 break;
							 
						 }
				default:
						 queryDataArray [ currentCount ].query =  
							 types::getString ( ( u_char * ) packetSettingDataArray [ currentCount ].data ,
									 buff::Buffer<STUB_INT>::tvbLength , offset , 0) ;
							   offset += 999;// buff::Buffer< void >::returnRemainingLength( offset );
						 queryDataArray [ currentCount].queryType = "NOT SUPPORTED";
//						 queryDataArray[ currentCount ].query = "query request from client";
offset +=999;
						 break;
			}
			}

		}
	}
	//Remaining payload indicates an error
	if ( buff::Buffer<STUB_INT>::returnRemainingLength( offset ) )
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
			"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<
			__TIME__<<"]"<<__FUNCTION__<<"******DISSECTOR INCOMPLETE*****\n";
	return 0;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  modifyResponse
 *  Description:  modify the response packet by updateing statement ID
 * =====================================================================================
 */
STUB_INT Mysql::modifyResponse( actSeriesStruct *conversationPackets , STUB_INT statementId ){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		<<"]\n";

	for ( STUB_INT i = 0 ; i<conversationPackets->noOfPacket ; ++ i ){
		if ( conversationPackets[ i ].actRawData->appServer && 
				conversationPackets[ i ].actRawData->length > 8 ){
			nth32( conversationPackets[i].actRawData->data , 5 , 
					statementId );
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<
				__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<
				__DATE__<<"_"<<__TIME__<<"]"<<"modified statement iD["
				<<types::getGuint( (u_char*)conversationPackets[i].actRawData->data
					       	, 15 , 5 , 4 , 1 )<<"]\n";
			//modify the statement id

		}
	}
	return 0;

}

