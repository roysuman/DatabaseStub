/*
 * =====================================================================================
 *
 *       Filename:  group_packet.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Friday 01 May 2015 02:44:11  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  ROY (), email.suman.roy@gmail.com
 *   Organization:  NA
 *
 * =====================================================================================
 */
#include "group_packet.h"

VS_INT64 k=0;
//static datatype
VS_BOOL                GroupPacket::is_init = false;
VS_INT32               GroupPacket::packet_number =-1;
VS_BOOL                GroupPacket::is_syn_fin = false;
conversation_struct    GroupPacket::conversation_diary[ 1000];
VS_INT32               GroupPacket::active_conversation_id = -1;
VS_BOOL                GroupPacket::last_db = false;
VS_INT32               GroupPacket::file_count = 1;
VS_INT32               GroupPacket::relative_active_conversation = 0;
VS_INT32               GroupPacket::relative_packet_number = 0;
//TODO a db instance and buffer instance have to pass
GroupPacket::GroupPacket( Buffer &bo):read_buffer_obj(bo){
//	read_buffer_obj = bo;
	try{
	/*	db_instance = new DbManager();
		if ( db_instance->isOpen() ){
			db_instance->create_table();
		}*/
		for ( VS_INT32 i = 0 ; i < 1000 ; ++i ){
			conversation_diary [ i ].current_index_source_array = -1;
			conversation_diary [ i].current_index_destination_array = -1;
			conversation_diary [ i ] .source_previous_packets =new prev_net_packet_struct [ 10 ];
			conversation_diary [ i ] .destination_previous_packets = new prev_net_packet_struct [ 10 ];
			packet_number = -1;
		}
		is_init = true;
	}
	catch ( const std::bad_alloc &ba){
		std::cerr<<PRINT<<"Exception:"<<ba.what()<<std::endl;
		is_init = false;
	}
}
VS_BOOL GroupPacket::group_init(){
	VS_BOOL    return_value;
	return_value = true;
	try{
		for ( VS_INT32 i = 0 ; i < 1000 ; ++i ){
			delete conversation_diary[ i ].destination_previous_packets;
			delete conversation_diary [ i ].source_previous_packets;
			conversation_diary [ i ].current_index_source_array = -1;
			conversation_diary [ i].current_index_destination_array = -1;
			conversation_diary [ i ] .source_previous_packets =new prev_net_packet_struct [ 10 ];
			conversation_diary [ i ] .destination_previous_packets = new prev_net_packet_struct [ 10 ];
		}
		relative_active_conversation ++;
		relative_packet_number ++;
		relative_active_conversation += active_conversation_id;
		relative_packet_number += packet_number;
		file_count++;
		packet_number= -1;
		active_conversation_id = -1;
	}
	catch ( const std::exception &e ){
		std::cerr<<"Not able to set the environmane to parse read buffer packet\n";
		return_value = false;
		std::cerr<<PRINT<<"Exception:"<<e.what()<<std::endl;
	}
	return return_value;

}
GroupPacket::~GroupPacket(){
	try{
//		delete db_instance;
		for ( VS_INT32 i = 0 ; i < 1000 ; ++i ){
			delete conversation_diary[ i ].destination_previous_packets;
			delete conversation_diary [ i ].source_previous_packets;
		}
	}
	catch ( const std::exception &e ){
		std::cerr<<PRINT<<"Exception:"<<e.what()<<std::endl;
	}
}

VS_BOOL GroupPacket::copy_packet( VS_BOOL client_server_flag , conversation_struct *active_converation , raw_net_data_struct *packet_data ){
	VS_BOOL    return_value;
#ifdef DEBUG
	std::cout<<PRINT<<"Data going to insert\n"
		<<"Sequence Number :[ "<<packet_data->sequence_number<<" ]\n"
		<<"Acknowledge Number:["<<packet_data->acknowledge_number<<" ] \n"
		<<"Data Length:["<<packet_data->data_length<<"] \n"
		<<"Acknowledge Flag:[ "<<packet_data->tcp_flags.g<<"]"<<std::endl;
#endif

	return_value = true;
	try {
		++packet_number;

		if ( client_server_flag ){ // this a client packet
			active_converation->source_previous_packets[ (++active_converation->current_index_source_array) ].
				sequence_number = packet_data->sequence_number ;
			active_converation->source_previous_packets[ ( active_converation->current_index_source_array)].
				acknowledge_number = packet_data->acknowledge_number;

			active_converation->source_previous_packets[ ( active_converation->current_index_source_array)].
				data_length = packet_data->data_length ;

			active_converation->source_previous_packets[ ( active_converation->current_index_source_array)].
				tcp_flags.ACK  = packet_data->tcp_flags.ACK;
#ifdef DEBUG
			std::cout<<PRINT<<"It's copying at client array Index:["
				<<active_converation->current_index_source_array <<" \n"<<std::endl;
#endif
		}
		else{
			active_converation->destination_previous_packets[ (++active_converation->current_index_destination_array) ].
				sequence_number = packet_data->sequence_number;
			active_converation->destination_previous_packets[ (active_converation->current_index_destination_array) ].
				acknowledge_number = packet_data->acknowledge_number;

			active_converation->destination_previous_packets[ (active_converation->current_index_destination_array) ].
				data_length = packet_data->data_length;
			active_converation->destination_previous_packets[ (active_converation->current_index_destination_array) ].
				tcp_flags.ACK  = packet_data->tcp_flags.ACK;
#ifdef DEBUG
			std::cout<<PRINT<<"It's copying at server array Index:["
				<<active_converation->current_index_destination_array <<" ]"<<std::endl;
#endif
		}
	}
	catch ( const std::exception &e ){
		std::cerr<<PRINT<<"Exception:"<<e.what()<<std::endl;
		return_value = false;
	}
	return return_value;
}


VS_BOOL GroupPacket::search_mother( VS_BOOL client_server_flag , conversation_struct *active_converation , raw_net_data_struct *packet_data ){
	VS_INT32    index;
	VS_BOOL      return_value;
	return_value = true;
	if ( active_conversation_id < zero ){ // conversationId must be >0
		std::cout<<PRINT<<"RETURNONG FALSE\n";
		return_value = false;
	}
	try {
		if( client_server_flag && return_value ){
			for ( index = active_converation->current_index_destination_array ; index>= zero ; index -- ){
				if ( ( packet_data->acknowledge_number == active_converation->destination_previous_packets[ index ].
							acknowledge_number ) && 
						( packet_data->sequence_number == active_converation->destination_previous_packets[ index ]
						  .sequence_number + active_converation->destination_previous_packets[ index ].data_length ) );// return_value = true;
				else return_value = false;
			}
		}
		else if ( return_value ){
			for ( index = active_converation->current_index_source_array ; index>= zero ; index -- ){
				if ( ( packet_data->acknowledge_number == active_converation->source_previous_packets[ index ].
							acknowledge_number ) && ( packet_data->sequence_number == 
								active_converation->source_previous_packets[ index ].sequence_number +
							       	active_converation->source_previous_packets[ index ].data_length ) );// return_value = true;
				else return_value = false;
			}
		}
	}
	catch ( const std::exception &e ){
		std::cerr<<PRINT<<"Exception:"<<e.what()<<std::endl;
		return_value = false;
	}
	return return_value;
}


VS_BOOL GroupPacket::valid_pack(VS_BOOL client_server_flag ,  conversation_struct *active_converation , raw_net_data_struct *packet_data ){
	VS_INT32    index;
	VS_BOOL      return_value;

	return_value = true;

	if ( active_conversation_id < zero ) return_value = false;
		std::cout<<PRINT<<"RETURNONG FALSE\n";
	try {
		if ( client_server_flag  && return_value ){
			for ( index = active_converation->current_index_source_array; index >=zero ; --index ){
				if ( ( packet_data->acknowledge_number == active_converation->source_previous_packets[ index ].
							sequence_number + active_converation->source_previous_packets[ index ].
							data_length ) && ( packet_data->sequence_number == 
								active_converation->source_previous_packets[ index ].
								acknowledge_number ) ) ;//return_value = true;
				else return_value = false;
			}
		}
		else if ( return_value ){
			for ( index = active_converation->current_index_destination_array; index >=zero ; --index ){
				if ( ( packet_data->acknowledge_number == active_converation->destination_previous_packets[ index ].
							sequence_number + active_converation->destination_previous_packets[ index ].
							data_length ) && ( packet_data->sequence_number == 
								active_converation->destination_previous_packets[ index ].
								acknowledge_number ) );// return_value = true;
				else return_value = false;
			}
		}
	}
	catch ( const std::exception &e ){
		std::cerr<<PRINT<<"Exception"<<e.what()<<std::endl;
		return_value = false;
	}
	return return_value;
}

VS_BOOL GroupPacket::insert_db( raw_net_data_struct *packet_data , VS_BOOL flag , VS_BOOL updateFlag= false ){
	VS_BOOL    return_value;

	return_value = false;
#ifdef DEBUG
	std::cout<<__FUNCTION__<<" Source Ip Address:[ " <<packet_data->source_ip 
		<<"] Destination Ip Address:[ "<< packet_data->destination_ip
		<<" ] COnversation: [ "<<active_conversation_id<<"] Packet: [ "
		<<packet_number<<" ] SourcePOrt : [ "
		<<packet_data->source_port<<" ]  Destination POrt:["
		<<packet_data->destination_port 
		<<" ] Time:["<<<<"]"<<std::endl;
#endif
	if ( updateFlag ){
/*		return_value = 
			db_instance->updtate_packet_index( active_conversation_id + relative_active_conversation );*/;
	}
	
	
  
	if ( flag ){
		/* return_value =  
			 db_instance->insert_packet_index( active_conversation_id + relative_active_conversation  , packet_data->source_ip  , packet_data->destination_ip , file_count );*/;
		if ( return_value ){
		/*	return_value = 
				insert_packet_info(  packet_number + relative_packet_number, active_conversation_id + relative_active_conversation  , packet_data->source_ip , packet_data->destination_ip ,  packet_data->source_port , packet_data->destination_port ,"test.com" , file_count, packet_data->data_length );*/;
			
		}

	}else{
		/*	return_value = 
				insert_packet_info(  packet_number + relative_packet_number, active_conversation_id + relative_active_conversation  , packet_data->source_ip , packet_data->destination_ip , packet_data->source_port , packet_data->destination_port ,"test.com" , file_count , packet_data->data_length);*/;

	}if ( !return_value )
			std::cerr<<PRINT<<"not able to insert data \n";

	return return_value ;


}

VS_BOOL GroupPacket::packet_handler ( raw_net_data_struct * packet_data ){
#ifdef DEBUG
	        std::cout<<PRINT<<" Source Ip ["<<packet_data->source_ip<<" ] Destination Ip [ "<<packet_data->destination_ip
			<<"  ]\nSourcePOrt [ "<<packet_data->source_port<<" ] \nDestinationPOrt ["
		<<packet_data->destination_port<<" ] \nSequence Number [ "<<packet_data->sequence_number
		<<"] \n AcknowledgeNumber: [ "<<packet_data->acknowledge_number<<"]\n Flags\n ACK [ "
		<<packet_data->tcp_flags.g<<" ] \n SYN[ "<<packet_data->tcp_flags.SYN
		<<" ] \n FIN"<<packet_data->tcp_flags.FIN<<" ] Data Length:[ "
		<<packet_data->data_length<<std::endl;
#endif

	VS_BOOL    return_value;

	return_value = true;
	if ( packet_data->tcp_flags.SYN || packet_data->tcp_flags.FIN ){
		is_syn_fin = true;
		return true;

	}
	if ( packet_data->destination_port == 3306 ){// 3306  ){ 
		//check whether the packet is acknowledgement packet or not
		//for acknwledgement packet length of the packet is [0] and ACK flag [ set]
		std::cout<<PRINT<<"Outgoing Packet -- going to DB"<<std::endl;
		if ( packet_data->data_length ==0 && packet_data->tcp_flags.ACK  ){
			if ( is_syn_fin  ){   return true; }
			std::cout<<PRINT<<" ACK FLAG ON-- OUTGOING \n";
			if ( valid_pack ( false , &conversation_diary [ active_conversation_id ] , packet_data ) ){
				std::cout<<PRINT<<"VALID ACK -- OUTGOING PACKET \n";
				//insertData VS_INT32o database ( true , active_conversation_id , ++packet_number , packet_data );
				return_value = copy_packet ( true , &conversation_diary [ active_conversation_id ] , packet_data );
				
				return_value == true ?return_value = insert_db( packet_data , false , true ): return_value = false;
				
				
			}else{
				std::cout<<PRINT<<" ACK PACKET NOT VALID--- OUTGOING\n";
				return_value = false;

			}
			
		}else if ( search_mother ( false , &conversation_diary [ active_conversation_id ] , packet_data ) && !last_db ){
			std::cout<<PRINT<<" CONSICUTIEVE PACKETS-- OUTGOING \n";
			return_value = copy_packet( true , &conversation_diary[ active_conversation_id ], packet_data );
			if ( packet_data->tcp_flags.ACK )
			return_value == true ?return_value = insert_db( packet_data , false , true ):return_value = false ;
			return_value == true ?return_value = insert_db( packet_data , false ):return_value = false ;
			//insert the packet
		}
	       //it's a new packet--start conversation
	       else  { 
		       std::cout<<"It's a fresh Outgoing Packet"<<std::endl;
		       last_db = false;
		  //     packet_number = 0;
		        
		       return_value = copy_packet( true , &conversation_diary [ ++active_conversation_id ] , packet_data );
		       //TODO it's first packet..insert VS_INT32o database after disecting

		       return_value == true ?return_value = insert_db( packet_data , true ):return_value = false ;
		       	//insertpacketSetting( true , ++packet);
	       }
	}else if ( packet_data->source_port ==  3306  ){// 3306 ){ //GOING TO CLIENT
		std::cout<<PRINT<<" IN COMING PACKET \n";
		if (   packet_data ->data_length == 0 && packet_data->tcp_flags.ACK  ) {
			if ( is_syn_fin ){  return true;}
			std::cout<<PRINT<<"IT;S ACK PACKET -- IN COMING \n";
			if (  valid_pack ( true , &conversation_diary [ active_conversation_id] , packet_data ) ){
			std::cout<<"VALID ACK RESPONSE PACKET -- IN COMING"<<std::endl;
			return_value = copy_packet( false , &conversation_diary [ active_conversation_id ] , packet_data );
			return_value == true ?return_value = insert_db( packet_data , false , true ):return_value = false ;
			}else{
				std::cerr<<PRINT<<" ACK PACKET NOT VALID-- IN COMING\n";
				return_value = false;
			}

		}else if ( search_mother ( true , &conversation_diary [active_conversation_id ] , packet_data ) ){
			std::cout<<PRINT<<"CONTIMNIOUS PACKET--- IN COMING"<<std::endl;
			return_value = copy_packet( false , &conversation_diary [ active_conversation_id ], packet_data );
			if ( packet_data->tcp_flags.ACK )
			return_value == true ?return_value = insert_db( packet_data , false , true ):return_value = false ;
			else

			return_value == true ?return_value = insert_db( packet_data , false ):return_value = false ;
		} // after sending a request client may get a request response without ACK
	       	else {// freash packet
			std::cout<<"FRESH PACKET -- INCOMING"<<std::endl;
		//	packet_number = 0;
		        if( is_syn_fin ) last_db = true;

			//it's a db greeting

			return_value = copy_packet ( false , &conversation_diary[ ++active_conversation_id ] , packet_data );
			//TODO insert VS_INT32o db
			return_value == true ?return_value = insert_db( packet_data , true):return_value = false ;
		}
	}
	is_syn_fin = false;
	return return_value;
}
VS_VOID* 
GroupPacket::start_grouping( VS_VOID* temp_ptr ){
	
#ifdef DEBUG
	std::cout<<PRINT<<"Reading and processing packet from shared Buffer\n";
#endif
	VS_INT32    readCount;
	GroupPacket *grp_packet_obj;
	Buffer      *read_buffer_obj;

	grp_packet_obj = ( GroupPacket*) temp_ptr;

	readCount = 0;

	raw_net_data_struct    *packet;
	VS_BOOL              flag;

	flag = false;
	try{
	//	read_buffer_obj = new Buffer();
		packet = new raw_net_data_struct();
	}
	catch ( const std::bad_alloc &ba ){
		std::cerr<<PRINT<<"Exception:"<<ba.what()<<std::endl;
	}
	VS_INT32 readReturn;
	while ( !flag ){
		readReturn = grp_packet_obj->read_buffer_obj.read_buffer( 1 , packet ) ;
		std::cout<<PRINT<<"read Return:[ "<<readReturn<<" ] \n";
		switch ( readReturn ){
			case 1:
#ifdef ERROR
				std::cout<<PRINT<<"Read PacketSource POOrt:[ "<<packet->source_port
					<<" ]:: Destination Port:[ "<<packet->destination_port<<" ]"<<std::endl;
#endif
				readCount++;
				switch ( packet->source_port ){
					case 0: 

						flag = !grp_packet_obj->group_init();

						break;
					default:
						if (! grp_packet_obj->packet_handler ( packet ) ){
							std::cerr<<PRINT<<"Error on packet grouping\n";
							flag = true;
						}
				}
				//	read_buffer_obj->giveSignal();

				//	flag = true;
				
				break;
			case -1:
				std::cerr<<PRINT<<"Error on read packet from buffer";
				exit(1);
				break;
			case 0:
				flag = grp_packet_obj->read_buffer_obj.check_signal();
				std::this_thread::sleep_for ( std::chrono::milliseconds( 100 ) );
				break;
			default:
				break;
				//std::cout<<PRINT<<"Unhandled return Value from read Buffer \n";
		}
	}
	std::cout<<PRINT<<"Total packet read from buffer: [ "<<readCount<< " ] \n";
}
