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

/*
 * create RESPONSE PACKET
 */

int CreatePacketMysql::mysqlGenarateResponsePacket ( actRawDataStruct * rawDataPacket , gint offset ,int noOfColumn , proto::field_info *fieldInfo  , int currentPacket , int eofLength){
    std::cout<<"offset: "<<offset<<std::endl;
   // exit ( 0 );


	//copy the data of this packet 
    char *genDatatemp;
    int tempOffset = 0;
	try {
                genDatatemp = new char [ 100 ];

	}
	catch ( std::bad_alloc &ba ){
		std::cout<<"Exception is ="<<ba.what()<<std::endl;
	}
        std::string data;
	tempOffset += 4;
        for ( int column = 1 ; column <=noOfColumn ; ++ column ){
           // std::cin.ignore();
		std::cout<<"enter the column value :"<<column<<std::endl;
		std::getline( std::cin , data );
        std::cout<<"data length"<<data.length()<<std::endl;
        genDatatemp [ tempOffset++ ] = data.length() & 0xff;
                memcpy (  ( genDatatemp + tempOffset ) , data.c_str() , data.length() );
		tempOffset += data.length();
        data.clear();

	}
	//update the length part of the data
	nth24 ( genDatatemp , 0 , tempOffset  ); // copy the length 
	memcpy ( genDatatemp + 3 , rawDataPacket->data + offset + 3 , 1 ); // coppy the data after length

	//have to copy data for thisc conversation packet
        copyConversationPartially ( newConversation ,  conversationPackets , prevPacketTillInserted + 1 , currentPacket   , offset - 1 ,  ( offset + tempOffset + eofLength ));
    memcpy ( newConversation->actRawData[ currentPacket ].data + offset   , genDatatemp , tempOffset );
    //copy EOF packet
    memcpy ( newConversation->actRawData [ currentPacket ].data + offset + tempOffset , rawDataPacket->data + ( rawDataPacket->length - eofLength   ) , eofLength );

        //now dissect all packets
//        std::cout<<"########DISSECTION FOR TESTING######"<<std::endl;
        
//        for ( int packetNo = 0 ; packetNo <newConversation->noOfPacket ; ++packetNo ){
//            std::cout<<"*********DISSECT PACKET ******* " <<packetNo<<std::endl;
//             //now for each packet do dissection and create a new new table.
//            std::cout<<"APP_DB"<<newConversation->actRawData [ packetNo].appServer<<std::endl;
//            std::cout<<"DATA ="<<newConversation->actRawData [ packetNo].data<<"length ="<<newConversation->actRawData [ packetNo].length<<std::endl;
//            std::cout<<"packet no for dissection ="<<packetNo<<std::endl;
//            Mysql::dissect_mysql( &newConversation->actRawData [ packetNo ], newConversation->actRawData [ packetNo ].length  );
            
//            }
//exit (0);
	


//        std::cout<<"length ="<< (offset + tempOffset + eofLength )<<std::endl;


    return offset + tempOffset;

}



//
//Dissect response
//
//
//
gint CreatePacketMysql::mysqlDissectResponse ( actRawDataStruct *rawdataPacket , gint offset , proto::field_info * fieldInfo , int packetNo ){
    std::cout<<"offset&&"<<offset<<std::endl;
    std::cout<<"packet no"<<packetNo<<std::endl;
    std::cout<<"***"<<rawdataPacket->length<<std::endl;

          gint response_code = buff::Buffer::get_guint8 ( rawdataPacket ,  offset );
        std::cout<<std::endl<<"response code is ###"<<response_code<<std::endl;
        if ( response_code == 0xff ) {
                std::cout<<" Error packet at mysql_dissect_response --\n"<<std::endl;
                return offset;
        }
        else {
                if ( response_code == 0xfe  && ( buff::Buffer::return_remaining_length ( offset ) < 9 ) ) {
                    std::cout<<"offset ="<<offset<<"Packet NO"<<packetNo<<std::endl;

                        int eofLength = (rawdataPacket->length - ( offset - 4 ) ) ;

                    if ( !buff::Buffer::Read ( rawdataPacket, fieldInfo , hf_mysql_eof ,offset , 1 , ENC_NA ) ){
                        std::cerr<<" error --- hf_mysql_eof "<<std::endl;
                        return offset ;

                    }

                    offset ++;
                    //pre 4.1 packet ends here
                    if ( buff::Buffer::get_remaining_length ( offset ) ){
                        if ( !buff::Buffer::Read (rawdataPacket, fieldInfo , hf_mysql_num_warn , offset , 2 , ENC_LITTLE_INDIAN ) ){
                            std::cerr<<" --error hf_mysql_num_warn "<<std::endl;
                            return offset;

                        }
                        offset += 2;
                        //now dissect server header flags
                        offset = Mysql::mysql_dissect_server_status ( rawdataPacket , offset );


                    }
                        if ( field::prev_query.prev_query_state == FIELD_PACKET ){
                            field::prev_query.prev_query_state = ROW_PACKET;


                        }
			//now if previous packet was a row packet then perform creating new response part
                        else if ( field::prev_query.prev_query_state == ROW_PACKET ){
                        std::cout<<"eof count ="<<eofLength<<"::"<<offset<<"::"<<rawdataPacket->length<<std::endl;
//                        exit ( 0 );
                                int newOffset =mysqlGenarateResponsePacket ( rawdataPacket , rowPacketOffsetStart , noOfFielde , fieldInfo , packetNo , eofLength  );


                                return 9999;


				
			}

                }
                else {
                        switch (  field::prev_query.prev_query_state ) {

                                    case RESPONSE_TABULAR:

					    offset = Mysql::mysql_dissect_result_header ( rawdataPacket , offset );
					    break;

				    case FIELD_PACKET:
                               case RESPONSE_SHOW_FIELDS:

                                    case RESPONSE_PREPARE:

                                    case PREPARED_PARAMETERS:



                                         offset = Mysql::mysql_dissect_field_packet( rawdataPacket, offset , fieldInfo);
                                         std::cout<<"after dissecting field packet offset is\:"<<rowPacketOffsetStart<<std::endl;

                                         break;

                                    case ROW_PACKET:
                                         rowPacketOffsetStart = offset - 4 ;
                                    //rowPacketOffsetStart = offset ;
                                         int columnCount = noOfFielde ;
					 //now add the new row packet
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
int CreatePacketMysql::mysqlGenarateRequestPacket( actRawDataStruct *rawDataPacket , gint offset ,  gint oppcode , proto::field_info * fieldInfo , int currentPacket ){
    std::cout<<"inside generate request packet\n"<<std::endl;
    std::string query;
    switch ( oppcode ){
        case COM_QUERY :{// now take a new query
        //actSeriesStruct  *newConversation;
        std::cin.ignore();
        std::cout<<"now enter new query";

        std::getline( std::cin , query , '\n');
       // std::cout<<"\nyou inserted query :"<<query<<std::endl;
       // std::cout<<"length = "<<query.size()<<"current packet"<<currentPacket<<std::endl;
        copyConversationPartially ( newConversation ,  conversationPackets , 0 , currentPacket  , offset , offset + query.size() );
        //std::cout<<" buffer length = "<<newConversation->actRawData [ currentPacket ].length<<std::endl;
        newConversation->actRawData [ currentPacket ].data [ offset ]= 3 & 0xff;
        memcpy ( ( newConversation->actRawData [ currentPacket ].data + offset + 1   ) , query.c_str() , query.size()+1 );
	//update the  length part of the packet.
	
        nth24 ( newConversation->actRawData [ currentPacket ].data   , 0 , query.size() );

       // std::cout<<"data = "<< newConversation->actRawData [ currentPacket ].data <<std::endl;
        offset += query.length();
        break;
         
         }
        default:
                        std::cout<<"for this packet type no genarate packet is available"<<std::endl;
                        break;

    }
    
    return offset;
    

}

gint CreatePacketMysql::mysqlDissectRequest ( actRawDataStruct * rawDataPacket , gint offset , proto::field_info * fieldInfo , int currentPacket ){
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
                          break;;
                 case COM_STATISTICS: // tell the server to send back a string containing a big status report.
                         field::prev_query.prev_query_state = RESPONSE_MESSAGE ;
                          break;
                 case COM_INIT_DB://tell the server to change the default database
                          //for the sesion to the one specified by the argument
                 case COM_CREATE_DB: // tells the server to create a DB with a specified name.
                 case COM_DROP_DB: // tells the server to drop a DB
                          if ( !buff::Buffer::Read (rawDataPacket , fieldInfo , hf_mysql_schema , offset , 0 , ENC_NA ) ){
                                  std::cerr<<" error --- hf_mysql_schema @ mysql_dissect_request--"<<std::endl;
                                  return offset;
                          }
                          offset +=buff::Buffer::get_string_length ( rawDataPacket ,  offset  ) ;
                         field::prev_query.prev_query_state = RESPONSE_OK;
                          break ;
                 case COM_QUERY: // tells the server to run the query
                          //std::cout<<"com query"<<std::endl;
                          //exit ( 0 );


                          if( !buff::Buffer::Read (rawDataPacket , fieldInfo , hf_mysql_query , offset , 0 , ENC_NA ) ){
                                  std::cerr<<"-- error hf_mysql_query -- "<<std::endl;
                                  return offset ;
                          }
                       //   std::cout<<"after printing value"<<std::endl;
                         offset +=buff::Buffer::get_string_length ( rawDataPacket , offset ) ;
                         field::prev_query.prev_query_state = RESPONSE_TABULAR;
                         //call the function to enter new REQUEST packet
                         mysqlGenarateRequestPacket( rawDataPacket , prevOffset , opcode  , fieldInfo , currentPacket);

                          break;
                 case COM_PREPARE: // tells the server to prepare the statement specified by the argument.
                     std::cout<<"prepare"<<std::endl;

                          if( !buff::Buffer::Read ( rawDataPacket , fieldInfo , hf_mysql_query , offset , 0 , ENC_NA ) ){
                                  std::cerr<<"-- error hf_mysql_query part 2-- "<<std::endl;
                                  return offset ;
                          }
                          offset +=buff::Buffer::get_string_length (rawDataPacket , offset ) ;
                         field::prev_query.prev_query_state = RESPONSE_PREPARE;
                          break;
                 case COM_CLOSE_STMT:// tells the server to close the prepare statement. specified by statement ID
                          if( !buff::Buffer::Read (rawDataPacket , fieldInfo , hf_mysql_stmt_id , offset , 4 , ENC_LITTLE_INDIAN ) ){
                                  std::cerr<<"-- error hf_mysql_stmt_id-- "<<std::endl;
                                  return offset ;
                          }
                          offset += 4 ;
                         field::prev_query.prev_query_state = REQUEST ;
                          break ;
                 case COM_RESET_STMT:// tells the server to disscurd the current parameter valus in the prepared statement spe
                          //cified by the statement ID
                          if( !buff::Buffer::Read (rawDataPacket , fieldInfo , hf_mysql_stmt_id , offset , 4 , ENC_LITTLE_INDIAN ) ){
                                  std::cerr<<"-- error hf_mysql_stmt_id--  part 2"<<std::endl;
                                  return offset ;
                          }
                          offset += 4 ;
                         field::prev_query.prev_query_state = RESPONSE_OK;
                          break ;
                 case COM_FIELD_LIST: // tells the server to retirn a list of fields for the specified table
                          if( !buff::Buffer::Read (rawDataPacket , fieldInfo , hf_mysql_table_name , offset , 0 , ENC_NA ) ){
                                  std::cerr<<"-- error hf_mysql_table_name -- "<<std::endl;
                                  return offset ;
                          }
                         offset +=buff::Buffer::get_string_length (rawDataPacket , offset ) ;
                         field::prev_query.prev_query_state = RESPONSE_SHOW_FIELDS;
                          break;
                 case COM_PROCESS_KILL :// tells the server to kill the thread identified by the argument.

                          if( !buff::Buffer::Read (rawDataPacket , fieldInfo , hf_mysql_thd_id , offset , 4 , ENC_LITTLE_INDIAN ) ){
                                  std::cerr<<"-- error hf_mysql_thd_id--  part 2"<<std::endl;
                                  return offset ;
                          }
                          offset += 4 ;
                         field::prev_query.prev_query_state = RESPONSE_OK;
                          break ;
                 case COM_CHANGE_USER://tells the server that the client wants to chanfe the user. associated with the seeion
                          //zero terminated user name , encrypted password , zero termonated defaukt db name
                          if( !buff::Buffer::Read (rawDataPacket , fieldInfo , hf_mysql_user , offset , 0 , ENC_NA ) ){
                                  std::cerr<<"-- error hf_mysql_user -- "<<std::endl;
                                  return offset ;
                          }
                         offset +=buff::Buffer::get_string_length (rawDataPacket , offset ) ;
                         if( !buff::Buffer::Read (rawDataPacket , fieldInfo , hf_mysql_passwd , offset , 0 , ENC_NA ) ){
                                  std::cerr<<"-- error hf_mysql_passwd -- "<<std::endl;
                                  return offset ;
                          }
                         offset +=buff::Buffer::get_string_length ( rawDataPacket ,offset ) ;
                          if( !buff::Buffer::Read (rawDataPacket , fieldInfo , hf_mysql_schema , offset , 0 , ENC_NA ) ){
                                  std::cerr<<"-- error hf_mysql_schema -- "<<std::endl;
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
                                  std::cerr<<"-- error hf_mysql_shutdown--  part 2"<<std::endl;
                                  return offset ;
                          }
                          offset += 1 ;
                         field::prev_query.prev_query_state = RESPONSE_OK;
                          break ;
                          //tells the server to disable the options specified by the code.At this point , seems to be used only to
                          //enable or disable the support of multiple statements in one query string
                 case COM_SET_OPTION:
                          if( !buff::Buffer::Read (rawDataPacket , fieldInfo , hf_mysql_option , offset , 2 , ENC_LITTLE_INDIAN ) ){// this will be ENC_NA
                                  std::cerr<<"-- error hf_mysql_option--  part 2"<<std::endl;
                                  return offset ;
                          }
                          offset += 2 ;
                         field::prev_query.prev_query_state = RESPONSE_OK;
                          break ;

                 case COM_STMT_FETCH :
                          if( !buff::Buffer::Read (rawDataPacket , fieldInfo , hf_mysql_stmt_id , offset , 4 , ENC_LITTLE_INDIAN ) ){// this will be ENC_NA
                                  std::cerr<<"-- error hf_mysql_stmt_id--  part 2"<<std::endl;
                                  return offset ;
                          }
                          offset += 4 ;
                          if( !buff::Buffer::Read (rawDataPacket , fieldInfo , hf_mysql_num_rows , offset , 4 , ENC_LITTLE_INDIAN ) ){// this will be ENC_NA
                                  std::cerr<<"-- error hf_mysql_stmt_thd_id--  part 2"<<std::endl;
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
                                  std::cerr<<"-- error hf_mysql_stmt_id--  part 2"<<std::endl;
                                  return offset ;
                          }
                          offset += 4 ;
                          if( !buff::Buffer::Read (rawDataPacket , fieldInfo , hf_mysql_param , offset , 4 , ENC_LITTLE_INDIAN ) ){// this will be ENC_NA
                                  std::cerr<<"-- error hf_mysql_param--  part 2"<<std::endl;
                                  return offset ;
                          }
                          offset += 2 ;
                          //check more data is available or not
                          if ( buff::Buffer::get_remaining_length( offset ) ){
                                  if( !buff::Buffer::Read ( rawDataPacket ,fieldInfo , hf_mysql_payload, offset , 0 , ENC_NA ) ){
                                          std::cerr<<"-- error hf_mysql_payload -- "<<std::endl;
                                          return offset ;

                                  }
                                  offset +=buff::Buffer::get_string_length (rawDataPacket , offset ) ;
                          }
                                 field::prev_query.prev_query_state = REQUEST;
                                  break ;
                                  //tels the server to execute the statement , identified by statement ID : ( 4byte statement ID , 1 byte for flags , 4 byte iteration cound.


                 case COM_EXECUTE:
                                  if( !buff::Buffer::Read ( rawDataPacket , fieldInfo , hf_mysql_stmt_id , offset , 4 , ENC_LITTLE_INDIAN ) ){// this will be ENC_NA
                                          std::cerr<<"-- error hf_mysql_stmt_id--  part 2"<<std::endl;
                                          return offset ;

                                  }
                                  offset += 4 ;
                                  if ( !buff::Buffer::Read (rawDataPacket , fieldInfo , hf_mysql_exec_flags5 , offset , 1 , ENC_NA ) ){
                                          std::cerr<<" error at hf_mysql_exec_flags5--- "<<std::endl;
                                          return offset;
                                  }
                                  offset ++ ;
                                  if ( !buff::Buffer::Read( rawDataPacket ,fieldInfo , hf_mysql_exec_iter , offset , 4 , ENC_LITTLE_INDIAN ) ){
                                          std::cerr<<" error at hf_mysql_exec_iter "<<std::endl;
                                          return offset;
                                  }
                                  offset +=4 ;

                                  //check remaing length remaining or not
                                  if ( buff::Buffer::get_remaining_length ( offset ) ){
                                          if ( !buff::Buffer::Read(rawDataPacket , fieldInfo , hf_mysql_payload , offset , 0 , ENC_NA ) ){
                                                  std::cerr<<"error hf_mysql_payload---"<<std::endl;
                                                  return offset;
                                          }
                                          offset +=buff::Buffer::get_string_length (rawDataPacket , offset );

                                  }
                                 field::prev_query.prev_query_state = RESPONSE_TABULAR;
                                  //return offset ;
                                  break ;
                                  //4 byte int for the offset , 2 byte integer for the flag , 4 byte int for the slave server ID
                                  //a string for the long name
                                  //
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

bool CreatePacketMysql::dissectMysql ( actRawDataStruct *rawDataPacket , int totalPacketLength , int packetNo ){
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
     std::cout<<"hbh\n";
	//know the length of the packet
        int offset=0;
        while ( offset < totalPacketLength ){
          //  std::cout<<"totalPacketLength"<<std::endl;
            buff::Buffer::pass = false;
            //read the packet length
            std::cout<<"hf_mysql_packet_length"<<hf_mysql_packet_length<<std::endl;
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

