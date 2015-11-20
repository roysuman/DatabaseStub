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
 *   Organization:  Cognizant Technological solutions
 *
 * =====================================================================================
 */

#include"proto_mysql.hpp"
#
#define NEWPACKET 0
int JSON = 1;
 std::fstream fileHandler;//("/home/chetana/TCPStub/jon.txt",std::ios::out);
int rowCount = 0;

 int mysqlPacketLength;
 int mysqlPacketNumber;
 int mysqlSchema;
 int mysqlPayload;
 int mysqlNumWarn;
 int mysqlStatementId;
 int mysqlQuery;
 int mysqlExecFlags;
 int mysqlExecIterations;
 int mysqlEOF;
 int mysqlFieldCatalog;
 int mysqlFieldDb;
 int mysqlFieldTable;
 int mysqlFieldOriginalTable;
 int mysqlFieldName;
 int mysqlFieldldOriginalName;
 int mysqlFieldCharsetNumber;
 int mysqlFieldLength;
 int mysqlFieldType;
 int mysqlFieldDecimals;
 int mysqlRowText;
 int prevQueryState;
 int colNoGlobal = 0;
 bool rowPacketOffsetFlag = true;
#ifdef NEWPACKET
 int rowPacketOffsetStart;
 int eofPacketOffsetStart;
 bool isFof;
 int prevPacketTillInserted;
 //actSeriesStruct *newConversationPack;
// actSeriesStruct *conversationPackets;
#endif
// FOR JSON
Json::Value event;
int noOfFielde = 0;

bool Mysql::initialize( void  ) {
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	std::cout<<__FUNCTION__<<"register mysql protocol\n";
	//initialize function pointer for dynamic binding
	proto::fpStruct functionStructure ;
	functionStructure.functionToInnitiateDissecton = &Mysql::dissectMysql;
	functionStructure.functionToGetClientRequest= &Mysql::getQueryOnly;
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
			
			};
    if ( ! ( (  proto::Proto::registerProto ( 3306 , &functionStructure , (sizeof ( pi ) / sizeof ( proto::packetInfo )) ) ) && ( proto::Proto::insertDissectorProto ( PORT_MYSQL ,( sizeof ( pi ) / sizeof ( proto::packetInfo ) ) , pi ) )) ) {
		std::cerr<<__FUNCTION__<<"Can't register myssql protocol \n";
		return false;
    }
    return true;
}

std::string responseDataTogetherForRow; //need to be in a proper way
//disset row packet
int Mysql::mysqlDissectRowPackets ( actRawDataStruct *rawDataPacket , int offset , proto::fieldInfo *fieldInfoData  ){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	guint64 lelen;
	guint8 isNull ;
	offset+=tvbGetFle( rawDataPacket, offset, & ( lelen = 0 ), & ( isNull = 0 ) );
	std::cout<<__FUNCTION__<<"length of data is "<<(int)lelen<<'\n';
	std::string rowText = boost::get < std::string > ( buff::Buffer< returnType >::Read ( rawDataPacket , fieldInfoData , mysqlRowText , &offset , ( int ) lelen , ENC_NA ) );
	if ( JSON != 1 ){
		responseDataTogetherForRow = responseDataTogetherForRow + rowText + ";" ;
	}
#ifdef DEBUG
	std::cout<<__FUNCTION__<<"offset = "<<offset<<'\n';
#endif
	return offset;
}


// dissect server status flags
int Mysql::mysqlDissectServerStatus (  int offset ){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<'\n';
	return ( offset + 2 );
}

//dissect field packet
int Mysql::mysqlDissectFieldPacket( actRawDataStruct *rawDataPacket , int offset , proto::fieldInfo * fieldInfoData ){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<'\n';
	guint64 lelen;
	guint8 isNull = 0;
	offset += tvbGetFle( rawDataPacket, offset, &( lelen = 0 ), &( isNull = 0 ) );
	buff::Buffer< returnType >::Read ( rawDataPacket, fieldInfoData , mysqlFieldCatalog , &offset , (int)lelen , ENC_NA );
	offset += tvbGetFle( rawDataPacket, offset, &( lelen = 0 ), &( isNull = 0 ));
	buff::Buffer< returnType >::Read ( rawDataPacket, fieldInfoData ,  mysqlFieldDb, &offset , (int)lelen , ENC_NA );
	offset += tvbGetFle( rawDataPacket, offset, &( lelen = 0 ) , &( isNull = 0 ) );
	buff::Buffer< returnType >::Read( rawDataPacket, fieldInfoData ,  mysqlFieldTable, &offset , (int)lelen , ENC_NA );
	offset += tvbGetFle( rawDataPacket, offset, & ( lelen = 0 ), &( isNull = 0 ) );
	buff::Buffer < returnType >::Read( rawDataPacket, fieldInfoData ,  mysqlFieldOriginalTable , &offset , (int)lelen , ENC_NA );
	offset += tvbGetFle( rawDataPacket, offset, &( lelen = 0 ), &( isNull = 0 ) );
	buff::Buffer< returnType > ::Read ( rawDataPacket, fieldInfoData ,  mysqlFieldName , &offset , (int)lelen , ENC_NA );
	offset += tvbGetFle( rawDataPacket, offset, &( lelen = 0 ), &( isNull = 0 ) );
	std::string fieldOriginalName =boost::get < std::string > ( buff::Buffer< returnType > ::Read( rawDataPacket, fieldInfoData ,  mysqlFieldldOriginalName , &offset , (int)lelen , ENC_NA ) ); 
	/*
	//edited on 27, for json
	std::string dataValue1;
	dataValue1.clear();
	std::cout<<__FUNCTION__<<"for json = "<<dataValue1<<std::endl;
	dataValue1 = types::get_string ( (u_char*)rawDataPacket->data , buff::Buffer::tvb_length , offset , (int)lelen );
	std::cout<<__FUNCTION__<<"data = "<<dataValue1<<std::endl;
	*/
	//for json
//	if ( Json::flagForGenerateQuery ){
		fieldOriginalName +=  ";";
		QueryPacket.colNames.insert ( std::make_pair ( 1 , fieldOriginalName ) );
//	}
	event["PACKET/MySQL"]["Query"]="ENTER NEW QUERY";
	event["PACKET/MySQL"]["Response"][fieldOriginalName]="ENTER NEW VALUE";
	offset ++ ; //filler
	buff::Buffer< returnType >::Read ( rawDataPacket , fieldInfoData , mysqlFieldCharsetNumber , &offset , 2 , ENC_LITTLE_INDIAN );
	buff::Buffer< returnType >::Read ( rawDataPacket , fieldInfoData , mysqlFieldLength , &offset , 4 , ENC_LITTLE_INDIAN );
	int fieldType =boost::get < int > ( buff::Buffer< returnType >::Read ( rawDataPacket , fieldInfoData , mysqlFieldType , &offset , 1 , ENC_NA ) );
	// guint8 types = (guint8)buff::Buffer::get_guint8( rawDataPacket , offset  );
	// std::cout<<"TYPES = "<<types <<std::endl;
	//dissect each flags 
	switch ( fieldType ){ // read types and dissect it
		case  0x00 :
			std::cout<<__FUNCTION__<<" FIELD_TYPE_DECIMAL\n";
			break;

        case 0x01:
			std::cout<<__FUNCTION__<<"FIELD_TYPE_TINY\n";
			break;
        case  0x02 :
			std::cout<<__FUNCTION__<<"FIELD_TYPE_SHORT\n";
			break;
        case 0x03 : 
			std::cout<<__FUNCTION__<<"FIELD_TYPE_LONG\n";
			break;
        case 0x04 :
			std::cout<<__FUNCTION__<<"FIELD_TYPE_FLOAT\n";
			break;
        case 0x05:
			std::cout<<__FUNCTION__<<"FIELD_TYPE_DOUBLE\n";
			break;
        case 0x06 :
			std::cout<<__FUNCTION__<<"FIELD_TYPE_NULL\n";
			break;
        case 0x07 :
			std::cout<<__FUNCTION__<<"FIELD_TYPE_TIMESTAMP\n";
			break;
			
  	case  0x08 :
			std::cout<<__FUNCTION__<<"FIELD_TYPE_LONGLONG\n";
			break;
        case 0x09  :
			std::cout<<__FUNCTION__<<"FIELD_TYPE_INT24\n";
			break;
        case 0x0a :
			std::cout<<__FUNCTION__<<"FIELD_TYPE_DATE\n";
			break;
        case 0x0b  :
			std::cout<<__FUNCTION__<<"FIELD_TYPE_TIME\n";
			break;
        case  0x0c :
			std::cout<<__FUNCTION__<<"FIELD_TYPE_DATETIME\n";
			break;
        case 0x0d :
			std::cout<<__FUNCTION__<<"FIELD_TYPE_YEAR\n";
			break;
        case 0x0e:
			std::cout<<__FUNCTION__<<"FIELD_TYPE_NEWDATE\n";
			break;
        case  0x0f:
			std::cout<<__FUNCTION__<<"FIELD_TYPE_VARCHAR (new in MySQL 5.0)\n";
			break;
        case  0x10  :
			std::cout<<__FUNCTION__<<"FIELD_TYPE_BIT (new in MySQL 5.0)\n";
			break;

        case  0xf6:
			std::cout<<__FUNCTION__<<"FIELD_TYPE_NEWDECIMAL (new in MYSQL 5.0)\n";
			break;

        case 0xf7 :
			std::cout<<__FUNCTION__<<"FIELD_TYPE_ENUM\n";
			break;
        case  0xf8  :
			std::cout<<__FUNCTION__<<"FIELD_TYPE_SET\n";
			break;
        case  0xf9 :
			std::cout<<__FUNCTION__<<"FIELD_TYPE_TINY_BLOB\n";
			break;
        case  0xfa  :
			std::cout<<__FUNCTION__<<"FIELD_TYPE_MEDIUM_BLOB\n";
			break;
        case 0xfb :
			std::cout<<__FUNCTION__<<"FIELD_TYPE_LONG_BLOB\n";
			break;
			
     	case   0xfc :
			std::cout<<__FUNCTION__<<"FIELD_TYPE_BLOB\n";
			break;
        case 0xfd: 
			std::cout<<__FUNCTION__<<"FIELD_TYPE_VAR_STRING\n";
			break;
        case  0xfe:
			std::cout<<__FUNCTION__<<"FIELD_TYPE_STRING\n";
			break;

        case 0xff :
			std::cout<<__FUNCTION__<<"FIELD_TYPE_GEOMETRY \n";
			break;
		}
	//read flags 2 bytes                                                            
//	guint32 flagValue = types::get_guint ( (u_char * )rawDataPacket->data , rawDataPacket->length , offset , 2 , ENC_LITTLE_INDIAN );
//	std::cout<<__FUNCTION__<<"FLAGVALUE"<<flagValue<<std::endl;
	//dissect each flags
    switch ( types::getGuint ( ( u_char *)rawDataPacket->data , rawDataPacket->length , offset , 2 , ENC_LITTLE_INDIAN ) ){
		case 0001 :
			std::cout<<__FUNCTION__<<"NOT_NULL_FLAG\n";
			break;
			
		case 0002:
			std::cout<<__FUNCTION__<<"PRI_KEY_FLAG\n";
			break;
		case 0004 :
			std::cout<<__FUNCTION__<<"UNIQUE_KEY_FLAG\n";
			break;
			//        case 0008:
			//            std::xout<<"MULTIPLE_KEY_FLAG"<<std::endl;
			//            break;
			
		case 0010 :
			std::cout<<__FUNCTION__<<"BLOB_FLAG\n";
			break;
		case 0020:
			std::cout<<__FUNCTION__<<"UNSIGNED_FLAG\n";
			break;
		case 0040:
			std::cout<<__FUNCTION__<<"ZEROFILL_FLAG\n";
			break;
			//        case 0080 :
			//            std::cout<<"BINARY_FLAG"<<std::endl;
			//            break;
			
		case 0100:
			std::cout<<__FUNCTION__<<" ENUM_FLAG\n";
			break;
			
		case 0200:
			std::cout<<__FUNCTION__<<"AUTO_INCREMENT_FLAG\n";
			break;
			
		case 0400:
			std::cout<<__FUNCTION__<<"TIMESTAMP_FLAG\n";
			break;
			//       case 0800 :
			//            std::cout<<"SET_FLAG"<<std::endl;
			//            break;
			
		default:
			std::cout<<__FUNCTION__<<"combination of 8 creating prob\n";
			break;
		}
    buff::Buffer < returnType >::Read( rawDataPacket , fieldInfoData , mysqlFieldDecimals , &( offset +=  2 )  , 1 , ENC_NA );
	offset +=2; // filler
    if ( buff::Buffer< void >::returnRemainingLength( offset ) )
		std::cout<<__FUNCTION__<<"SOME EXTRA DATA\n";
	return offset;
	
}
int Mysql::tvbGetFle(actRawDataStruct * rawDataPacket, int offset , guint64 *res, guint8 *isNull){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	int prefix;
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



int Mysql::mysqlDissectResultHeader( actRawDataStruct *rawDataPacket , int offset ){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	int fle;
	guint64 numFields;
	fle = tvbGetFle( rawDataPacket , offset , &numFields , NULL );
	noOfFielde = numFields;
    if ( numFields   )field::prevQuery.prevQueryState = FIELD_PACKET;
	else field::prevQuery.prevQueryState = ROW_PACKET ;
	return (offset + fle);
}

//dissect query response
gint Mysql::mysqlDissectResponse ( actRawDataStruct *rawdataPacket , int offset , proto::fieldInfo * fieldInfoData, int packetNo , actSeriesStruct *conversationPackets){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
    gint responseCode = buff::Buffer< void >::getGuint8 ( rawdataPacket ,  offset );
	if ( responseCode == 0xff ) {
		std::cout<<__FUNCTION__<<" Error packet at mysql_dissect_response --\n";
		return offset;
	}
        else {
        if ( responseCode == 0xfe  && ( buff::Buffer< void > ::returnRemainingLength( offset ) < 9 ) ) {
			int eofLengthPrevious = (rawdataPacket->length - ( offset - 4 ) ) ;
			std::cout<<__FUNCTION__<<"eoflengthPrevious="<<eofLengthPrevious<<std::endl;
             buff::Buffer< returnType >::Read ( rawdataPacket, fieldInfoData , mysqlEOF , &offset , 1 , ENC_NA ) ;
			 //pre 4.1 packet ends here
            if ( buff::Buffer< void >::returnRemainingLength( offset ) ){
            buff::Buffer< returnType >::Read (rawdataPacket, fieldInfoData , mysqlNumWarn , &offset , 2 , ENC_LITTLE_INDIAN ) ;
				//now dissect server header flags
				offset = mysqlDissectServerStatus ( offset );
			}
			if ( field::prevQuery.prevQueryState == FIELD_PACKET ){
				fileHandler<<event<<std::endl;
				field::prevQuery.prevQueryState = ROW_PACKET;
			}
//#ifdef NEWPACKET
			else if ( ( field::prevQuery.prevQueryState == ROW_PACKET ) && Json::flagForGenerateQuery ){
                mysqlGenerateResponsePacket(rawdataPacket , rowPacketOffsetStart , noOfFielde ,packetNo, eofLengthPrevious , conversationPackets);
				return 999;
            }
//#endif


		else {
			switch (  field::prevQuery.prevQueryState ) {
				case RESPONSE_TABULAR:
					offset = mysqlDissectResultHeader ( rawdataPacket , offset );
					break;
					
				case FIELD_PACKET:
					
				case RESPONSE_SHOW_FIELDS:
					
				case RESPONSE_PREPARE:
					
				case PREPARED_PARAMETERS:
					offset = mysqlDissectFieldPacket( rawdataPacket, offset , fieldInfoData);
					break;
					
				case ROW_PACKET:
#ifdef DEBUG
					std::cout<<__FUNCTION__<<"row count offset="<<offset<<std::endl;
#endif
					if ( rowPacketOffsetFlag ) {
						rowPacketOffsetStart = offset - 4 ;
						rowPacketOffsetFlag = false ;
					}
					int columnCount = noOfFielde ;
					//    std::cout<<"now learn to dissect row packet ::"<<noOfFielde<<std::endl;
					while ( columnCount != 0 ){
						// std::cout<<"column no :"<<columnCount--<<std::endl;
						columnCount --;
						offset = mysqlDissectRowPackets ( rawdataPacket , offset , fieldInfoData );
						std::cout<<__FUNCTION__<<columnCount<<std::endl;
					}
					QueryPacket.rowCount = ++rowCount ;
					QueryPacket.colInfo.insert ( std::make_pair ( QueryPacket.rowCount ,responseDataTogetherForRow ) );
					break;
				}
		}
	}
    }
	return offset;
}

//
//
//Mysql dissect client request
//once authontication is done client engine sends command packates to the
//server
//
 int Mysql::mysqlDissectRequest ( actRawDataStruct *rawdataPacket , gint offset , proto::fieldInfo * fieldInfoData , int currentPacket , actSeriesStruct * conversationPackets){
	 std::cout<<"FUNCTION:"<<__FUNCTION__<<'\n';
	 //1st read teh oppcode from the packet
         int opcode = buff::Buffer< void > ::getGuint8(rawdataPacket  ,  offset++ ) ;
	 int newDataSetOffsetPosition = offset;
	 switch ( opcode ){
                 case COM_QUERY:{ // tells the server to run the query
					std::string mysqlQueryString =boost::get < std::string>(buff::Buffer< returnType >::Read (rawdataPacket , fieldInfoData , mysqlQuery , &offset , 0 , ENC_NA ) );
					if ( JSON ){
						QueryPacket.query = mysqlQueryString;
#ifdef DEBUG
						std::cout<<__FUNCTION__<<"QueryPacket.query = "<<QueryPacket.query<<'\n';
#endif
						QueryPacket.queryType = COM_QUERY;
						JSON = 2;
					}
					if ( Json::flagForGenerateQuery ){
						prevQueryState = RESPONSE_TABULAR;
						mysqlGenerateRequestPacket( newDataSetOffsetPosition , opcode , currentPacket , conversationPackets);
						rowPacketOffsetFlag = true ;
					}

					field::prevQuery.prevQueryState = RESPONSE_TABULAR;
				
				}
				break;
				defult:
				std::cout<<__FUNCTION__<<"DEFAULT REQUEST\n";

         }
         return offset;

 }

//dissect mysql

//define function 
//this will dissect the massage part by part..yup go through this interesting algo

bool Mysql::dissectMysql( actRawDataStruct *rawdataPacket , int totalPacketLength , actSeriesStruct * conversationPackets){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	std::cout<<"[TOTAL_PACKET_LENGTH]:"<<totalPacketLength<<std::endl;
	//open file for Json ,this file will take input for new query
	fileHandler.open("/home/suman/TCPStub/jon.txt",std::ios::out); 
	if ( !fileHandler.is_open() ){
		std::cerr<<__FUNCTION__<<"can't open json input file\n";
		exit(EXIT_FAILURE);
	}
	//for adding row at tree view initiLIZE THE NEW ROOTrOW fLAAG	
	buff::Buffer< bool >::rootRowPass = true ;

	//set the length flag
	buff::Buffer<bool>::pass = false ;
	//find the appropriate array of field info from proto_map;
	//have to pass this value by function error , now geting error
	//create an proto field info refernce and initialize it by appropriate protocol from map.
	proto::_protoMap::iterator protomapIterator = proto::protoMap.find ( PORT_MYSQL );
	if ( protomapIterator == proto::protoMap.end () ){

		std::cout<<__FUNCTION__<<":Protocol didnot registered / but it must be registered because after searching registered proto only dynamic function will  be clled "<<std::endl;
		exit ( EXIT_FAILURE );
	}
	proto::mapkey tempKeyPair = protomapIterator->second;
	proto::fieldInfo *fieldInfo = tempKeyPair.second;
	//know the length of the packet
        int offset=0;
        while ( offset < totalPacketLength ){
        buff::Buffer<bool>::pass = false;
		//read the packet length
        buff::Buffer< returnType > ::Read( rawdataPacket , fieldInfo , mysqlPacketLength , &offset , 3 , ENC_LITTLE_INDIAN );
		//update the packet length by 4 manualy
        buff::Buffer<int>::tvbLength +=4;
		// read the packet number 
        int packetNumber =boost::get < int > (  buff::Buffer< returnType >::Read ( rawdataPacket , fieldInfo , mysqlPacketNumber , &offset , 1 , ENC_NA ) );
		//try to manage the followig method by implementing template
	//	gint packetNumber = buff::Buffer::get_guint8 ( rawdataPacket , offset - 1 );
	    //std::cout<<"packet no: "<<packet_number;
	    bool isResponse= false;
//	    offset +=1;
	    //check the destination port
	    if ( !rawdataPacket->appServer )	isResponse = true;
	    else isResponse = false ;
	    if ( isResponse ) {// packet going to APP
		    if ( packetNumber == 0  ){ //then it is server greetings
			    std::cout<<__FUNCTION__<<"no need to dissect greetings\n";
			    return true;
			   }
            else offset = mysqlDissectResponse( rawdataPacket,  offset   , fieldInfo , packetNumber , conversationPackets) ;
		    }else { //packet going to Db
			    if ( packetNumber == 1 ) //it's a login request
				    std::cout<<__FUNCTION__<<"no need to dissect login request\n";
			    else
				    //normal request from client to server
                    offset = Mysql::mysqlDissectRequest ( rawdataPacket, offset , fieldInfo , packetNumber , conversationPackets );
		    }
	   
	}
	//for a same mainly for response of a select query 
	// offset +=4; chngd on 13/12 -- 6.16
	//Remaining payload indicates an error
    if ( buff::Buffer<int>::returnRemainingLength ( offset ) )
		std::cout<<__FUNCTION__<<"******DISSECTOR INCOMPLETE*****\n";
	//exit ( EXIT_FAILURE );
	fileHandler.close();

	return true;
}



//function to genarate Request packets
int Mysql::mysqlGenerateRequestPacket(  int offset ,  int oppcode , int currentPacket , actSeriesStruct *conversationPackets){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
#ifdef DEBUG
	std::cout<<"opcode is=\t"<<oppcode<<"offset="<<offset<<std::endl;
#endif
	std::string query;
	switch ( oppcode ){
		
		case COM_QUERY :{
#ifdef DEBUG
					std::cout<<__FUNCTION__<<"now enter new queryread query from colByColDataTogether\n"
						<<"query is"<<colByColDataTogether.query
						<<"length is"<<colByColDataTogether.query.length()
						<<"size="<<colByColDataTogether.query.size()
						<<std::endl;
#endif
					//increase offset for oppcode
					offset ++;// ( copy data untill oppcode)
					copyConversationPartially ( newConversationPack ,  conversationPackets , 0 , currentPacket  , offset  , offset + colByColDataTogether.query.size() + 2 ); // added 1 on 23
					memcpy ( ( newConversationPack->actRawData [ currentPacket ].data + offset    ) , colByColDataTogether.query.c_str() ,  ( colByColDataTogether.query.size() ) );//-1
					offset +=colByColDataTogether.query.size();// - 1 ;//
#ifdef DEBUG
					std::cout<<__FUNCTION__<<" buffer length = "<<newConversationPack->actRawData [ currentPacket ].length<<std::endl;
					std::cout<<__FUNCTION__<<"offset = "<<offset<<std::endl;
#endif
					newConversationPack->actRawData [ currentPacket ].data [ offset ] = '\0';
					newConversationPack->actRawData [ currentPacket ].length = offset + 1; // -1 have to provide
					offset ++;
					//update the  length part of the packet.
					nth24 ( newConversationPack->actRawData [ currentPacket ].data   , 0 ,  colByColDataTogether.query.size() + 1  );
					std::cout<<__FUNCTION__<<"size == "<<colByColDataTogether.query.size()<<std::endl;
					// std::cout<<"data = "<< newConversationPack->actRawData [ currentPacket ].data <<std::endl;
					offset +=colByColDataTogether.query.length();
					break;
				}
				default:
				std::cout<<__FUNCTION__<<"for this packet type no genarate packet is available\n";
				break;
	}
	//    std::cout<<"dissect for test\n";
	//    Mysql::dissect_mysql( &newConversationPack->actRawData[ 0 ] , newConversation->actRawData [ 0].length );
	//exit(0);
	return offset;
}







//generate the new response packet
int Mysql::mysqlGenerateResponsePacket ( actRawDataStruct * rawDataPacket , int offset ,int noOfColumn ,  int currentPacket , int eofLength , actSeriesStruct *conversationPackets){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	//copy the data of this packet
	char *genDatatemp;
	int tempOffset = 0;
        try {
#ifdef DEBUG
		std::cout<<__FUNCTION__<<"total size="<<colByColDataTogether.totalSize<<"total row="<<colByColDataTogether.totalSize<<std::endl;
#endif
                genDatatemp = new char [ ( colByColDataTogether.totalRow * 4 ) + colByColDataTogether.totalSize ];

        }
        catch ( std::bad_alloc &ba ){
                std::cerr<<__FUNCTION__<<"Exception is ="<<ba.what()<<std::endl;
		exit ( -1);
        }
        std::string data;
        int storeOffset =0;
        int updatedOffset= 0;

        int lengthUpdateOffset = 0;
        offset+=3;
        //know the current packet no
        guint8 packetNumber = buff::Buffer<void>::getGuint8 ( rawDataPacket , offset ++ );
        for ( int rowCount = 1 ; rowCount <= colByColDataTogether.totalRow; rowCount ++ ){
            tempOffset += 4;
            storeOffset = tempOffset;
            for ( int column = 1 ; column <=noOfColumn ; ++ column ){
			_colInfo::iterator it = colByColDataTogether.colInfo.find( ++ colNoGlobal );
			if ( it == colByColDataTogether.colInfo.end() )	std::cerr<<__FUNCTION__<<"can't find column valu from STL map colByColDataTogether->colinfo\n";
			std::cout<<__FUNCTION__<<"inserted data is ["<<rowCount<<"]"<<" column["<<column<<"]"<<it->second<<std::endl;
			genDatatemp [ tempOffset++ ] = it->second.length() & 0xff;
			memcpy (  ( genDatatemp + tempOffset ) , it->second.c_str() , it->second.length() );
			tempOffset += it->second.length() ;
			
		}

                //update the length part of the data
            //for row data first three bits will contain data length( excluding first 4bits)
                nth24 ( genDatatemp , lengthUpdateOffset , tempOffset - storeOffset);//( storeOffset - 2 )  ); // copy the length

                genDatatemp [ lengthUpdateOffset+3 ] = packetNumber;// & 0xff;
                //std::cerr<<"gendatatemp3"<<genDatatemp [ lengthUpdateOffset+3 ]<<std::endl;
                packetNumber ++;
                lengthUpdateOffset = tempOffset;
		
	}
	updatedOffset = tempOffset - 1; // bites of new created rows
	copyConversationPartially ( newConversationPack ,  conversationPackets , prevPacketTillInserted + 1 , currentPacket   , offset - 5 , (offset - 4) + updatedOffset + eofLength + 1); //( offset + updatedOffset  + eofLength - 5 ));
	memcpy ( newConversationPack->actRawData[ currentPacket ].data + offset - 4   , genDatatemp , tempOffset  );
	memcpy ( newConversationPack->actRawData [ currentPacket ].data + (offset - 4 ) + tempOffset  , rawDataPacket->data + ( rawDataPacket->length - eofLength   ) , eofLength + 1 );
	newConversationPack->actRawData [ currentPacket ].data [offset-4+tempOffset+3] = packetNumber;
	newConversationPack->actRawData [ currentPacket ].length = (offset - 4) + updatedOffset + eofLength + 1 ;
	return ( ( offset - 4 ) + updatedOffset + eofLength + 1) ;
}


//this method will dissect only quey part
bool Mysql::getQueryOnly( actRawDataStruct *packetSettingDataArray , queryData *& queryDataArray ){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<'\n';
	exit ( 0 );
	int currentCount = -1 ;
	int totalPacketLength;
	//now for each packet do dissection and put the dissected value into querydataArray.
    proto::_protoMap::iterator protomapIterator = proto::protoMap.find ( PORT_MYSQL );
    if ( protomapIterator == proto::protoMap.end () ) std::cout<<__FUNCTION__<<"Protocol didnot registered / but it must be registered because after searching registered proto only dynamic function will  be clled \n";
    proto::mapkey tempKeyPair = protomapIterator->second;
    proto::fieldInfo *fieldInfoData = tempKeyPair.second;
	while ( packetSettingDataArray [ ++currentCount ].length != -999 ){
		std::cout<<__FUNCTION__<<"NOW DISSECT QUERY ***********************************************************##############################\n";
		std::cout<<__FUNCTION__<<"current count\t"<<currentCount<<std::endl;
		//first update the packet no to querydataArray
		queryDataArray [ currentCount ].packetNo = packetSettingDataArray [ currentCount ].packetNumber ;
		//know the length of the packet
		int offset=0;
		totalPacketLength = packetSettingDataArray[ currentCount ].length;
		while ( offset < totalPacketLength ){
			//  std::cout<<"totalPacketLength"<<std::endl;
            buff::Buffer<bool >::pass = false;
            buff::Buffer< returnType >::Read ( &packetSettingDataArray [ currentCount ] , fieldInfoData , mysqlPacketLength , &offset , 3 , ENC_NA);


			//update the packet length by 4 manualy
            buff::Buffer<int>::tvbLength +=4;
			// read the packet number 
            int packetNumber =boost::get < int > (  buff::Buffer<returnType >::Read ( &packetSettingDataArray [ currentCount ] , fieldInfoData , mysqlPacketNumber , &offset , 1 , ENC_NA) );
            bool isResponse= false;
			//check the destination port
            if (  packetSettingDataArray [ currentCount].appServer == 0 )	isResponse = false;
            else isResponse = true ;
            std::cout<<__FUNCTION__<<packetSettingDataArray [ currentCount].appServer<<"::"<<isResponse<<std::endl;
            if ( !isResponse ) {// packet going to APP
                if ( packetNumber == 0  ){ //then it is server greetings
					//offset = mysql_dissect_greetings ( offset , field_info );
					queryDataArray [ currentCount].queryType = "server greetings";
					queryDataArray [ currentCount ].query ="greetins";
					std::cout<<__FUNCTION__<<"no need to dissect greetings\n";
					offset +=999;
					//return true;
				}
				else{
					queryDataArray [ currentCount ].queryType = "response";
					queryDataArray [ currentCount ].query="response";
					Json::flagForGenerateQuery = false; // double check
					actSeriesStruct *conversationPackets;
					offset = mysqlDissectResponse( &packetSettingDataArray [ currentCount ] , offset  , fieldInfoData , packetNumber ,  conversationPackets ) ;
					
				}
			}else { //packet going to Db
                if ( packetNumber == 1 ){ //it's a login request
					queryDataArray [ currentCount].queryType = "login Request";
					queryDataArray [ currentCount ].query ="login";
					std::cout<<__FUNCTION__<<"no need to dissect login request\n";
					offset +=999;
				}
				else{
					//normal request from client to server
					//    offset = Mysql::mysql_dissect_request ( &packetSettingDataArray [ currentCount ] , offset , field_info );
					queryDataArray [ currentCount].queryType = "query request from client";
                    int opcode = buff::Buffer<void>::getGuint8 ( &packetSettingDataArray [ currentCount ]  , offset ) ;
					offset ++ ;
					std::cout<<__FUNCTION__<<"opcode is "<<opcode<<std::endl;
					//types::get_string ( (u_char*)rawdataPacket->data , buff::Buffer::tvb_length , offset , 0 );
					queryDataArray [ currentCount ].query =  types::getString ( ( u_char * ) packetSettingDataArray [ currentCount ].data , buff::Buffer<int>::tvbLength , offset , 0) ;
					//   std::cout<<"get only query \t"<<types::get_string ( ( u_char * ) packetSettingDataArray [ currentCount ].data , buff::Buffer::tvb_length , offset , 0)
					std::cout<<__FUNCTION__<<"storage value\t"<<queryDataArray [ 0 ].query<<std::endl;
					std::cout<<__FUNCTION__<<queryDataArray [ currentCount ].query <<std::endl;
					offset +=999;
				}
			}
		}
		//Remaining payload indicates an error
        if ( buff::Buffer<int>::returnRemainingLength( offset ) )	std::cout<<__FUNCTION__<<"******DISSECTOR INCOMPLETE*****\n";
	}
	return true;
}
