/*
 * =====================================================================================
 *
 *       Filename:  packet_mysql.cpp
 *
 *    Description:  this is for creating new packet for mysql.
 *
 *        Version:  1.0
 *        Created:  12/18/2013 07:17:33 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  SUMAN ROY (), suman.roy@cognizant.com
 *   Organization:  COGNIZANT TECHNOLOGICAL SOLUTIONS 
 *
 * =====================================================================================
 */
#include "packet_mysql.hpp"
#include <iostream>
#include "../STRUCTURE/sumanGtkmm.hpp"
#include "shift_char.hpp"
int prevQueryState=0;
/*
 * create RESPONSE PACKET
 */

int colNoGlobal = 0;
bool rowPacketOffsetFlag = true;



//generate the new response packet
int CreatePacketMysql::mysqlGenarateResponsePacket ( actRawDataStruct * rawDataPacket , gint offset ,int noOfColumn ,  int currentPacket , int eofLength){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
//	int tillCoppy = offset; //from where new data length will be inserted for row.
	//copy the data of this packet
	char *genDatatemp;
	int tempOffset = 0;
        try {
		std::cout<<__FUNCTION__<<"total size="<<colByColDataTogether.totalSize<<"total row="<<colByColDataTogether.totalSize<<std::endl;
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
        guint8 packetNumber = buff::Buffer::get_guint8 ( rawDataPacket , offset ++ );


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
	copyConversationPartially ( newConversation ,  conversationPackets , prevPacketTillInserted + 1 , currentPacket   , offset - 5 , (offset - 4) + updatedOffset + eofLength + 1); //( offset + updatedOffset  + eofLength - 5 ));
	memcpy ( newConversation->actRawData[ currentPacket ].data + offset - 4   , genDatatemp , tempOffset  );
	memcpy ( newConversation->actRawData [ currentPacket ].data + (offset - 4 ) + tempOffset  , rawDataPacket->data + ( rawDataPacket->length - eofLength   ) , eofLength + 1 );
	newConversation->actRawData [ currentPacket ].data [offset-4+tempOffset+3] = packetNumber;
	newConversation->actRawData [ currentPacket ].length = (offset - 4) + updatedOffset + eofLength + 1 ;
	return ( ( offset - 4 ) + updatedOffset + eofLength + 1) ;
}


//
//Dissect response
//
//
//
gint CreatePacketMysql::mysqlDissectResponse ( actRawDataStruct *rawdataPacket , gint offset , proto::field_info * fieldInfo , int packetNo ){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
//	std::cout<<"field::prev_query.prev_query_state = RESPONSE_TABULAR2;="<<field::prev_query.prev_query_state<<std::endl;
//	std::cout<<"offset:"<<offset<<std::endl;
//	std::cout<<"packet no"<<packetNo<<std::endl;
//	std::cout<<"***"<<rawdataPacket->length<<std::endl;
	gint response_code = buff::Buffer::get_guint8 ( rawdataPacket ,  offset );
	//std::cout<<std::endl<<"response code is ###"<<response_code<<std::endl;
	if ( response_code == 0xff ) {
		std::cerr<<__FUNCTION__<<" Error packet at mysql_dissect_response --\n";
                return offset;
        }
        else {
                if ( response_code == 0xfe  && ( buff::Buffer::return_remaining_length ( offset ) < 9 ) ) {
                    std::cout<<__FUNCTION__<<"offset ="<<offset<<"Packet NO"<<packetNo<<std::endl;
		    int eofLength = (rawdataPacket->length - ( offset - 4 ) ) ;
		    if ( !buff::Buffer::Read ( rawdataPacket, fieldInfo , hf_mysql_eof ,offset , 1 , ENC_NA ) ){
			    std::cerr<<__FUNCTION__<<" error --- hf_mysql_eof \n";
			    return offset ;
		    }
		    offset ++;
		    //pre 4.1 packet ends here
		    if ( buff::Buffer::get_remaining_length ( offset ) ){
			    if ( !buff::Buffer::Read (rawdataPacket, fieldInfo , hf_mysql_num_warn , offset , 2 , ENC_LITTLE_INDIAN ) ){
				    std::cerr<<__FUNCTION__<<" --error hf_mysql_num_warn \n";
				    return offset;
			    }
			    offset += 2;
			    //now dissect server header flags
                offset = Mysql::mysql_dissect_server_status (  offset );
		    }
		    if ( field::prev_query.prev_query_state == FIELD_PACKET ){
			    field::prev_query.prev_query_state = ROW_PACKET;
		    }
		    // previous packet was a row packet then perform creating new response part
		    else if ( field::prev_query.prev_query_state == ROW_PACKET ){
			    std::cout<<__FUNCTION__<<"eof count ="<<eofLength<<"::"<<offset<<"::"<<rawdataPacket->length<<std::endl;
                mysqlGenarateResponsePacket ( rawdataPacket , rowPacketOffsetStart , noOfFielde ,  packetNo , eofLength  );
			    return 9999;
		    }
		}
		else {
			switch (  field::prev_query.prev_query_state ) {//field::prev_query.prev_query_state
				case RESPONSE_TABULAR:
					offset = Mysql::mysql_dissect_result_header ( rawdataPacket , offset );
					break;
					
				case FIELD_PACKET:
					
				case RESPONSE_SHOW_FIELDS:
					
				case RESPONSE_PREPARE:
					
				case PREPARED_PARAMETERS:
					offset = Mysql::mysql_dissect_field_packet( rawdataPacket, offset , fieldInfo);
                    std::cout<<__FUNCTION__<<"after dissecting field packet offset is:"<<rowPacketOffsetStart<<std::endl;
					break;
					
				case ROW_PACKET:
					std::cout<<__FUNCTION__<<"rowPacketOffsetFlag"<<rowPacketOffsetFlag<<std::endl;
					if ( rowPacketOffsetFlag ){
						rowPacketOffsetStart = offset -4 ;
						rowPacketOffsetFlag = false;
					}
					std::cout<<__FUNCTION__<<"rowPacketOffsetStart"<<rowPacketOffsetStart<<std::endl;
					//rowPacketOffsetStart = offset ;
					int columnCount = noOfFielde ;
					while ( columnCount != 0 ){
						columnCount --;
						offset = Mysql::mysql_dissect_row_packets ( rawdataPacket , offset , fieldInfo );
						//  std::cout<<columnCount<<std::endl;
					}
					break;
			}
		}
		return offset;
	}
}
//function to genarate Request packets
int CreatePacketMysql::mysqlGenarateRequestPacket(  gint offset ,  gint oppcode , int currentPacket ){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	std::cout<<"opcode is=\t"<<oppcode<<"offset="<<offset<<std::endl;
	std::string query;
	switch ( oppcode ){
		
		case COM_QUERY :{
					std::cout<<__FUNCTION__<<"now enter new queryread query from colByColDataTogether\n"
						<<"query is"<<colByColDataTogether.query
						<<"length is"<<colByColDataTogether.query.length()
						<<"size="<<colByColDataTogether.query.size()
						<<std::endl;
					//increase offset for oppcode
					offset ++;// ( copy data untill oppcode)
					copyConversationPartially ( newConversation ,  conversationPackets , 0 , currentPacket  , offset  , offset + colByColDataTogether.query.size() + 2 ); // added 1 on 23
					memcpy ( ( newConversation->actRawData [ currentPacket ].data + offset    ) , colByColDataTogether.query.c_str() ,  ( colByColDataTogether.query.size() ) );//-1
					offset +=colByColDataTogether.query.size();// - 1 ;//
					std::cout<<__FUNCTION__<<" buffer length = "<<newConversation->actRawData [ currentPacket ].length<<std::endl;
					std::cout<<__FUNCTION__<<"offset = "<<offset<<std::endl;
					newConversation->actRawData [ currentPacket ].data [ offset ] = '\0';
					newConversation->actRawData [ currentPacket ].length = offset + 1; // -1 have to provide
					offset ++;
					//update the  length part of the packet.
					nth24 ( newConversation->actRawData [ currentPacket ].data   , 0 ,  colByColDataTogether.query.size() + 1  );
					std::cout<<__FUNCTION__<<"size == "<<colByColDataTogether.query.size()<<std::endl;
					// std::cout<<"data = "<< newConversation->actRawData [ currentPacket ].data <<std::endl;
					offset +=colByColDataTogether.query.length();
					break;
				}
				default:
				std::cout<<__FUNCTION__<<"for this packet type no genarate packet is available\n";
				break;
	}
	//    std::cout<<"dissect for test\n";
	//    Mysql::dissect_mysql( &newConversation->actRawData[ 0 ] , newConversation->actRawData [ 0].length );
	//exit(0);
	return offset;
}

//dissect request packet

gint CreatePacketMysql::mysqlDissectRequest ( actRawDataStruct * rawDataPacket , gint offset , proto::field_info * fieldInfo , int currentPacket ){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	gint opcode = buff::Buffer::get_guint8 (rawDataPacket , offset ) ;
	int prevOffset = offset ++;
	switch ( opcode ){
		case COM_QUIT : // no argument , tells the server end of session
			break ;
			
		case COM_PROCESS_INFO :// tells the server to send back a report on the status of all remaining thread
			field::prev_query.prev_query_state = RESPONSE_TABULAR ;
			break;
			
		case COM_DEBUG:// tells the server to reponse with an ok packet .If the server is alive and reachable it will.
			
		case COM_PING:
			field::prev_query.prev_query_state = RESPONSE_OK ;
			break;
			
		case COM_STATISTICS: // tell the server to send back a string containing a big status report.
			field::prev_query.prev_query_state = RESPONSE_MESSAGE ;
			break;
			
		case COM_INIT_DB://tell the server to change the default database
			//for the sesion to the one specified by the argument
			
		case COM_CREATE_DB: // tells the server to create a DB with a specified name.
			
		case COM_DROP_DB: // tells the server to drop a DB
			if ( !buff::Buffer::Read (rawDataPacket , fieldInfo , hf_mysql_schema , offset , 0 , ENC_NA ) ){
				std::cerr<<__FUNCTION__<<" error --- hf_mysql_schema @ mysql_dissect_request--\n";
				return offset;
			}
			offset +=buff::Buffer::get_string_length ( rawDataPacket ,  offset  ) ;
			field::prev_query.prev_query_state = RESPONSE_OK;
			break ;
			
		case COM_QUERY: // tells the server to run the query
			//std::cout<<"com query"<<std::endl;
			//exit ( 0 );
			if( !buff::Buffer::Read (rawDataPacket , fieldInfo , hf_mysql_query , offset , 0 , ENC_NA ) ){
				std::cerr<<__FUNCTION__<<"-- error hf_mysql_query --\n";
				return offset ;
			}
			std::cout<<__FUNCTION__<<"query is ="<<types::get_string ( (u_char*)rawDataPacket->data , buff::Buffer::tvb_length , offset , 0 )
				<<"Length="<<buff::Buffer::get_string_length ( rawDataPacket , offset ) <<std::endl;
			//   std::cout<<"after printing value"<<std::endl;
			offset +=buff::Buffer::get_string_length ( rawDataPacket , offset ) ;
			field::prev_query.prev_query_state = RESPONSE_TABULAR;
			prevQueryState = RESPONSE_TABULAR;
			//call the function to enter new REQUEST packet
            mysqlGenarateRequestPacket( prevOffset , opcode, currentPacket);
			rowPacketOffsetFlag = true;
			break;
			
		case COM_PREPARE: // tells the server to prepare the statement specified by the argument.
			if( !buff::Buffer::Read ( rawDataPacket , fieldInfo , hf_mysql_query , offset , 0 , ENC_NA ) ){
				std::cerr<<__FUNCTION__<<"-- error hf_mysql_query part 2-- \n";
				return offset ;
			}
			offset +=buff::Buffer::get_string_length (rawDataPacket , offset ) ;
			field::prev_query.prev_query_state = RESPONSE_PREPARE;
			break;
			
		case COM_CLOSE_STMT:// tells the server to close the prepare statement. specified by statement ID
			if( !buff::Buffer::Read (rawDataPacket , fieldInfo , hf_mysql_stmt_id , offset , 4 , ENC_LITTLE_INDIAN ) ){
				std::cerr<<__FUNCTION__<<"-- error hf_mysql_stmt_id-- \n";
				return offset ;
			}
			offset += 4 ;
			field::prev_query.prev_query_state = REQUEST ;
			break ;
			
		case COM_RESET_STMT:// tells the server to disscurd the current parameter valus in the prepared statement spe
			//cified by the statement ID
			if( !buff::Buffer::Read (rawDataPacket , fieldInfo , hf_mysql_stmt_id , offset , 4 , ENC_LITTLE_INDIAN ) ){
				std::cerr<<__FUNCTION__<<"-- error hf_mysql_stmt_id--  part 2\n";
				return offset ;
			}
			offset += 4 ;
			field::prev_query.prev_query_state = RESPONSE_OK;
			break ;
			
		case COM_FIELD_LIST: // tells the server to retirn a list of fields for the specified table
			if( !buff::Buffer::Read (rawDataPacket , fieldInfo , hf_mysql_table_name , offset , 0 , ENC_NA ) ){
				std::cerr<<__FUNCTION__<<"-- error hf_mysql_table_name -- \n";
				return offset ;
			}
			offset +=buff::Buffer::get_string_length (rawDataPacket , offset ) ;
			field::prev_query.prev_query_state = RESPONSE_SHOW_FIELDS;
			break;
			
		case COM_PROCESS_KILL :// tells the server to kill the thread identified by the argument.
			if( !buff::Buffer::Read (rawDataPacket , fieldInfo , hf_mysql_thd_id , offset , 4 , ENC_LITTLE_INDIAN ) ){
				std::cerr<<__FUNCTION__<<"-- error hf_mysql_thd_id--  part 2\n";
				return offset ;
			}
			offset += 4 ;
			field::prev_query.prev_query_state = RESPONSE_OK;
			break ;
			
		case COM_CHANGE_USER://tells the server that the client wants to chanfe the user. associated with the seeion
			//zero terminated user name , encrypted password , zero termonated defaukt db name
			if( !buff::Buffer::Read (rawDataPacket , fieldInfo , hf_mysql_user , offset , 0 , ENC_NA ) ){
				std::cerr<<__FUNCTION__<<"-- error hf_mysql_user -- \n";
				return offset ;
			}
			offset +=buff::Buffer::get_string_length (rawDataPacket , offset ) ;
			if( !buff::Buffer::Read (rawDataPacket , fieldInfo , hf_mysql_passwd , offset , 0 , ENC_NA ) ){
				std::cerr<<__FUNCTION__<<"-- error hf_mysql_passwd -- \n";
				return offset ;
			}
			offset +=buff::Buffer::get_string_length ( rawDataPacket ,offset ) ;
			if( !buff::Buffer::Read (rawDataPacket , fieldInfo , hf_mysql_schema , offset , 0 , ENC_NA ) ){
				std::cerr<<__FUNCTION__<<"-- error hf_mysql_schema -- \n";
				return offset ;
			}
			offset +=buff::Buffer::get_string_length (rawDataPacket , offset ) ;
			field::prev_query.prev_query_state = RESPONSE_OK;
			break;
			//tells the server to refresh the table cache , rotate the logs , reread the access cintrol table.
			//clear the host name lookup control cache , reset the status variable to 0 , clear the replication
			//master logs , or reset the replication slave depending on the options in the bit mask.
			
		case COM_REFRESH :
			//have to write logic to read all the flags
			offset ++ ;
			field::prev_query.prev_query_state = RESPONSE_OK;
			break ;
			
		case COM_SHUTDOWN: // tells the server to shutdown
			if( !buff::Buffer::Read (rawDataPacket , fieldInfo , hf_mysql_shutdown , offset , 1 , ENC_LITTLE_INDIAN ) ){// this will be ENC_NA
				std::cerr<<__FUNCTION__<<":hf_mysql_shutdown\n";
				return offset ;
			}
			offset += 1 ;
			field::prev_query.prev_query_state = RESPONSE_OK;
			break ;
			//tells the server to disable the options specified by the code.At this point , seems to be used only to
			//enable or disable the support of multiple statements in one query string
			
		case COM_SET_OPTION:
			if( !buff::Buffer::Read (rawDataPacket , fieldInfo , hf_mysql_option , offset , 2 , ENC_LITTLE_INDIAN ) ){// this will be ENC_NA
				std::cerr<<__FUNCTION__<<"-- error hf_mysql_option--  part 2\n";
				return offset ;
			}
			offset += 2 ;
			field::prev_query.prev_query_state = RESPONSE_OK;
			break ;
			
		case COM_STMT_FETCH :
			if( !buff::Buffer::Read (rawDataPacket , fieldInfo , hf_mysql_stmt_id , offset , 4 , ENC_LITTLE_INDIAN ) ){// this will be ENC_NA
				std::cerr<<__FUNCTION__<<"-- error hf_mysql_stmt_id--  part 2\n";
				return offset ;
			}
			offset += 4 ;
			if( !buff::Buffer::Read (rawDataPacket , fieldInfo , hf_mysql_num_rows , offset , 4 , ENC_LITTLE_INDIAN ) ){// this will be ENC_NA
				std::cerr<<__FUNCTION__<<"-- error hf_mysql_stmt_thd_id--  part 2\n";
				return offset ;
			}
			offset += 4 ;
			field::prev_query.prev_query_state = RESPONSE_TABULAR ;
			break ;

			//tells the server that the packet contains the data for one bound parameter in a prepared statement ,used to avoid unnecessary copying of
			//lafge amount of data when the value of the bound parameter is very large - 4 byte statement ID , two byte parameter number , parameter
			//string , LBF
			
		case COM_LONG_DATA:
			if( !buff::Buffer::Read ( rawDataPacket ,fieldInfo , hf_mysql_stmt_id , offset , 4 , ENC_LITTLE_INDIAN ) ){// this will be ENC_NA
				std::cerr<<__FUNCTION__<<"-- error hf_mysql_stmt_id--  part 2\n";
				return offset ;
			}
			offset += 4 ;
			if( !buff::Buffer::Read (rawDataPacket , fieldInfo , hf_mysql_param , offset , 4 , ENC_LITTLE_INDIAN ) ){// this will be ENC_NA
				std::cerr<<__FUNCTION__<<"-- error hf_mysql_param--  part 2\n";
				return offset ;
			}
			offset += 2 ;
			//check more data is available or not
			if ( buff::Buffer::get_remaining_length( offset ) ){
				if( !buff::Buffer::Read ( rawDataPacket ,fieldInfo , hf_mysql_payload, offset , 0 , ENC_NA ) ){
					std::cerr<<__FUNCTION__<<"-- error hf_mysql_payload -- \n";
					return offset ;
				}
				offset +=buff::Buffer::get_string_length (rawDataPacket , offset ) ;
			}
			field::prev_query.prev_query_state = REQUEST;
			break ;
			//tels the server to execute the statement , identified by statement ID : ( 4byte statement ID , 1 byte for flags , 4 byte iteration cound.
			
		case COM_EXECUTE:
			if( !buff::Buffer::Read ( rawDataPacket , fieldInfo , hf_mysql_stmt_id , offset , 4 , ENC_LITTLE_INDIAN ) ){// this will be ENC_NA
				std::cerr<<__FUNCTION__<<"-- error hf_mysql_stmt_id--  part 2\n";
				return offset ;
			}
			offset += 4 ;
			if ( !buff::Buffer::Read (rawDataPacket , fieldInfo , hf_mysql_exec_flags5 , offset , 1 , ENC_NA ) ){
				std::cerr<<__FUNCTION__<<" error at hf_mysql_exec_flags5--- \n";
				return offset;
			}
			offset ++ ;
			if ( !buff::Buffer::Read( rawDataPacket ,fieldInfo , hf_mysql_exec_iter , offset , 4 , ENC_LITTLE_INDIAN ) ){
				std::cerr<<__FUNCTION__<<" error at hf_mysql_exec_iter \n";
				return offset;
			}
			offset +=4 ;
			//check remaing length remaining or not
			if ( buff::Buffer::get_remaining_length ( offset ) ){
				if ( !buff::Buffer::Read(rawDataPacket , fieldInfo , hf_mysql_payload , offset , 0 , ENC_NA ) ){
					std::cerr<<__FUNCTION__<<"error hf_mysql_payload---\n";
					return offset;
				}
				offset +=buff::Buffer::get_string_length (rawDataPacket , offset );
			}
			field::prev_query.prev_query_state = RESPONSE_TABULAR;
			//return offset ;
			break ;
			//4 byte int for the offset , 2 byte integer for the flag , 4 byte int for the slave server ID
			//a string for the long name
			
		case COM_BINLOG_DUMP :
			if ( !buff::Buffer::Read ( rawDataPacket ,fieldInfo , hf_mysql_binlog_position , offset , 4 , ENC_LITTLE_INDIAN ) ){
				Mysql::print_error ( fieldInfo , hf_mysql_binlog_position );
				return offset;
			}
			offset +=4;
			if ( !buff::Buffer::Read (rawDataPacket , fieldInfo , hf_mysql_binlog_flags , offset , 2 , ENC_NA ) ){
				Mysql::print_error ( fieldInfo , hf_mysql_binlog_flags );
				return offset ;
			}
			offset +=2;
			if ( !buff::Buffer::Read ( rawDataPacket ,fieldInfo , hf_mysql_binlog_server_id , offset , 4 , ENC_LITTLE_INDIAN ) ){
				Mysql::print_error ( fieldInfo , hf_mysql_binlog_server_id );
				return offset;
			}
			offset +=4;
			//binlog filem name
			if ( buff::Buffer::get_remaining_length( offset ) ){
				if ( !buff::Buffer::Read (rawDataPacket , fieldInfo , hf_mysql_binlog_file_name , offset , 0 , ENC_NA ) ){
					Mysql::print_error( fieldInfo , hf_mysql_binlog_file_name );
					return offset;
				}
				offset +=buff::Buffer::get_string_length (rawDataPacket , offset );
			}
			field::prev_query.prev_query_state = REQUEST;
			// return offset;
			break;
			//implement replication packet , tells the server the table defination and the data to the cliennt in row format , 1 byte for database name length
			//database name , 1byte for table name length , then table name.
			
		case COM_TABLE_DUMP:
			
		case COM_CONNECT_OUT: // never sent by client used for iternal purpose
			
		case COM_REGISTER_SLAVE:
			offset +=buff::Buffer::return_remaining_length ( offset );
			field::prev_query.prev_query_state = REQUEST;
			break ;
			
		default:
			offset += buff::Buffer::return_remaining_length ( offset );
			field::prev_query.prev_query_state = UNDEFINED;
	}
	// std::cout<<"return offset"<<std::endl;
	//  std::cout<<"offset "<<offset<<std::endl;
	return offset;
}

//####################################################################


bool CreatePacketMysql::dissectMysql ( actRawDataStruct *rawDataPacket , int totalPacketLength , int packetNo ){
    std::cout<<"CreatePacketMysql::dissectMysql\n";
    //for adding row at tree view initiLIZE THE NEW ROOTrOW fLAAG	
	buff::rootRowPass = true ;
    //buff::Buffer::add_heading ( "MySql" , "MySql" );
    //set the length flag
	buff::Buffer::pass = false ;
	std::cout<<"Inside dissector for packeet creating \n";
	//find the appropriate array of field info from proto_map;
	//have to pass this value by function error , now geting error
	//create an proto field info refernce and initialize it by appropriate protocol from map.
	proto::_proto_map::iterator protomap_iterator = proto::proto_map.find ( PORT_MYSQL );
	if ( protomap_iterator == proto::proto_map.end () ){
		std::cout<<"Protocol didnot registered / but it must be registered because after searching registered proto only dynamic function will  be clled "<<std::endl;
	}

	proto::mapkey temp_key_pair = protomap_iterator->second;
	proto::field_info *fieldInfo = temp_key_pair.second;
	//know the length of the packet
        int offset=0;
        while ( offset < totalPacketLength ){
          //  std::cout<<"totalPacketLength"<<std::endl;
            buff::Buffer::pass = false;
            //read the packet length
        //    std::cout<<"hf_mysql_packet_length"<<hf_mysql_packet_length<<std::endl;
            if ( !buff::Buffer::Read ( rawDataPacket , fieldInfo , hf_mysql_packet_length , offset , 3 , ENC_LITTLE_INDIAN )){
                std::cerr<<"can't read hf_mysql_packet_length"<<std::endl;
                return false;
            }
		    //update offset by 3
		    offset += 3;
            //update the packet length by 4 manualy
            buff::Buffer::tvb_length +=4;

		    // read the packet number 
		    if ( !buff::Buffer::Read ( rawDataPacket , fieldInfo , hf_mysql_packet_number , offset , 1 , ENC_NA )){
			    std::cerr<<"cant read  proto-mysql.hpp -- hf_mysql_packet_number"<<std::endl;
			    return false ;
			    
            }
		    gint packet_number = buff::Buffer::get_guint8 ( rawDataPacket , offset );
                    //std::cout<<"packet no: "<<packet_number;
		    bool is_response= false;
		    offset +=1;
		    //check the destination port
		    if ( !rawDataPacket->appServer )	is_response = true;
		    else is_response = false ;
		    if ( is_response ) {// packet going to APP
			    if ( packet_number == 0  ){ //then it is server greetings
				    //offset = mysql_dissect_greetings ( offset , fieldInfo );
				    std::cout<<"no need to dissect greetings\n";
				    return true;
			    }
			    else{
                    offset = mysqlDissectResponse ( rawDataPacket , offset , fieldInfo , packetNo );
                                   // std::cout<<"offset after response dis"<<offset<<std::endl;
				    
			    }
			    }else { //packet going to Db
				    if ( packet_number == 1 ){ //it's a login request
					    std::cout<<"no need to dissect login request\n";
					    
				    }
				    else
					    //normal request from client to server
					    offset = mysqlDissectRequest ( rawDataPacket, offset , fieldInfo , packetNo );
				    }

	    }
	    

	//Remaining payload indicates an error
	if ( buff::Buffer::get_remaining_length ( offset ) )
		std::cout<<"******DISSECTOR INCOMPLETE*****"<<std::endl;
	return true;
}

