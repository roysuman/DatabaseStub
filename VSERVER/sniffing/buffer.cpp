/*
 * =====================================================================================
 *
 *       Filename:  buffer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Friday 01 May 2015 10:44:10  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  ROY (), email.suman.roy@gmail.com
 *   Organization:  NA
 *
 * =====================================================================================
 */
#include"buffer.h"
VS_UINT64            Buffer::buff_obj_count = 0;
std::mutex        Buffer::buffer_mutex_lock;
VS_INT32               Buffer::read_head = -1;
VS_INT32               Buffer::write_head = -1;
VS_BOOL              Buffer::signal = false;
raw_net_data_struct    *Buffer::buffer = nullptr;
VS_BOOL              Buffer::buffer_init = false;
VS_UINT64            Buffer::buffer_read_count = 0;
VS_UINT64            Buffer::buffer_write_count= 0;
 pthread_mutex_t lock;
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Buffer
 *  Description:  constructor for the buffer class. It's innitiate the buffer shared 
 *                memory. Mutex lock protected.
 * =====================================================================================
 */
Buffer::Buffer(){

#ifdef DEBUG
	std::cout<<PRINT<<"Creating BUffer obj\n";
#endif
	pthread_mutex_lock(&lock);
//	std::lock_guard<std::mutex> guard(buffer_mutex_lock);
	if ( !buffer_init ){
		try{
			buffer = new raw_net_data_struct[ BUFFER_SIZE];
			buffer_init = true;

//		buff_obj_count = 0;
		}
		catch ( const std::bad_alloc &ba ){
			std::cerr<<PRINT<<"Exception:"<<ba.what()<<std::endl;
			buffer_init = false;
		}
	}
	buff_obj_count ++;
	 pthread_mutex_unlock(&lock);
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  init_buffer
 *  Description:  method that getting called by the constructor. Which actually allocates
 *                the buffer memory.
 * =====================================================================================
 */
VS_BOOL Buffer::init_buffer(){
	VS_BOOL    returnValue;

	pthread_mutex_lock(&lock);
//	std::lock_guard<std::mutex> guard(buffer_mutex_lock);
	returnValue = true;
	try{
		buffer = new raw_net_data_struct[ BUFFER_SIZE];
	}
	catch ( const std::bad_alloc &ba ){
		std::cerr<<PRINT<<"Exception:"<<ba.what()<<std::endl;
		returnValue = false;
	}
	buffer_init = returnValue;
	pthread_mutex_unlock(&lock);
	return returnValue;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ~Buffer
 *  Description:  destructor for the buffer class. That frees the buffer memory( condition
 *                object reference must be 0 ).
 * =====================================================================================
 */
Buffer::~Buffer(){
	pthread_mutex_lock(&lock);
//	std::lock_guard<std::mutex> guard(buffer_mutex_lock);
	buff_obj_count--;
	if ( buff_obj_count == 0 ){
		try{
			std::cout<<PRINT<<"Deleting Buffer obj\n";
//			delete []buffer;
		}
		catch ( const std::exception &e ){
			std::cerr<<PRINT<<"Exception:"<<e.what()<<std::endl;
		}
	} else std::cout<<PRINT<<"Buffer Obj Count: [ "<<buff_obj_count<<" ] \n";
	 pthread_mutex_unlock(&lock);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  write_buffer
 *  Description:  write __rawData__ structure's object VS_INT32o the buffer.
 *                lock Protected. It's a circular buffer
 * =====================================================================================
 */
VS_INT32 Buffer::write_buffer( raw_net_data_struct *&packet ){
	std::cout<<PRINT<<"write data in Buffer\n";
	VS_INT32    returnValue;
	pthread_mutex_lock(&lock);

//	std::lock_guard<std::mutex> guard(buffer_mutex_lock);
	returnValue = 1;
#ifdef DEBUG
	std::cout<<PRINT<<"Buffer Read head Position :[ "<<read_head<<std::endl;
	std::cout<<PRINT<<"Buffer Write Head Position:[ "<<write_head<<std::endl;
#endif
	if ( buffer_init ){
		if ( write_head == -1 ){
			++write_head;
			++read_head;
		}else{ 
			if ( write_head == BUFFER_SIZE -1 ){
				if ( read_head == 0 ) returnValue = 0;
				else write_head = 0;
				
			}else ++write_head;
		}
		if ( returnValue == 1 ){
#ifdef DEBUG
			buffer [ write_head ].source_port = packet->source_port;
			buffer [ write_head ].destination_port = packet->destination_port;
			buffer [ write_head ].sequence_number = packet->sequence_number;
			buffer [ write_head].acknowledge_number = packet->acknowledge_number;
			buffer [ write_head ].data_length = packet->data_length;
			buffer [ write_head ].source_ip= packet->source_ip.c_str();
			buffer [ write_head ].destination_ip = packet->destination_ip.c_str();

			buffer [ write_head ].date_time = packet->date_time.c_str();
			buffer[ write_head ].tcp_flags.ACK = packet->tcp_flags.ACK ;
			buffer[ write_head ].tcp_flags.SYN = packet->tcp_flags.SYN ;
			buffer[ write_head ].tcp_flags.FIN = packet->tcp_flags.FIN ;

			buffer[ write_head ].tcp_flags.PSH = packet->tcp_flags.PSH ;

			buffer[ write_head ].tcp_flags.RST = packet->tcp_flags.RST ;

			buffer[ write_head ].tcp_flags.URG = packet->tcp_flags.URG ;
#endif

//			memcpy ( (void*)(buffer + write_head  ) ,(void*)packet , sizeof ( raw_net_data_struct ) );
#ifdef ERROR
			raw_net_data_struct *pp =  new raw_net_data_struct;
			memcpy( pp , buffer + write_head , sizeof ( raw_net_data_struct ) );
			std::cout<<"\nip;"<<pp->source_ip<<std::endl;
			delete pp;

#endif
			buffer_write_count++;
		}
	}else returnValue = -1;
	pthread_mutex_unlock(&lock);
	return returnValue;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  read_buffer
 *  Description:  read a raw_net_data_struct element from the buffer VS_INT32o the reference variable
 *                 Lock protected, and circular.
 * =====================================================================================
 */
VS_INT32 Buffer::read_buffer( VS_UINT64 noOfPackets , raw_net_data_struct *& packet ){
	VS_INT32    returnValue;
	pthread_mutex_lock(&lock);
//	std::lock_guard<std::mutex> guard(buffer_mutex_lock);
	noOfPackets = 1;

#ifdef DEBUG
	std::cout<<PRINT<<"Buffer write Count :[ "<<read_head<<std::endl;
	std::cout<<PRINT<<"Buffer Read Count:[ "<<write_head<<std::endl;
#endif

	returnValue = 1;
	if ( buffer_init ){
		if ( read_head == -1 ) returnValue = 0;
		else {
			packet->source_port = buffer [ write_head ].source_port ;
		        packet->destination_port=buffer [ write_head ].destination_port ;
			packet->sequence_number =buffer [ write_head ].sequence_number ;
			packet->acknowledge_number= buffer [ write_head].acknowledge_number; 
			packet->data_length = buffer [ write_head ].data_length ;
			packet->source_ip = buffer [ write_head ].source_ip.c_str();
			packet->destination_ip = buffer [ write_head ].destination_ip.c_str();

			packet->date_time = buffer [ write_head ].date_time .c_str();
		        packet->tcp_flags.ACK =buffer[ write_head ].tcp_flags.ACK ;
		        packet->tcp_flags.SYN = buffer[ write_head ].tcp_flags.SYN ;
			packet->tcp_flags.FIN  = buffer[ write_head ].tcp_flags.FIN ;

			packet->tcp_flags.PSH  = buffer[ write_head ].tcp_flags.PSH ;

			 packet->tcp_flags.RST= buffer[ write_head ].tcp_flags.RST ;

			packet->tcp_flags.URG= buffer[ write_head ].tcp_flags.URG ;

		//	memcpy ((void*) packet ,(void*)( buffer+ read_head )  , sizeof ( raw_net_data_struct  )   );
#ifdef ERROR
			raw_net_data_struct *pp =  new raw_net_data_struct;
			memcpy( pp , buffer + read_head , sizeof ( raw_net_data_struct ) );
			std::cout<<"\nip;"<<pp->source_ip<<std::endl;
			exit(0);
#endif			
			buffer_read_count++;
			if ( read_head == write_head ){
				read_head = -1;
				write_head = -1;
			}else if ( read_head == BUFFER_SIZE -1 )
				read_head = 0;
			else ++read_head;
		}
	}else returnValue = -1;
	 pthread_mutex_unlock(&lock);
	return returnValue;
}
VS_BOOL Buffer::give_signal(){
	VS_BOOL    returnValue;
	pthread_mutex_lock(&lock);

	returnValue = true;

//	std::lock_guard<std::mutex> guard(buffer_mutex_lock);
	signal = true;
	 pthread_mutex_unlock(&lock);
	return returnValue;
}

VS_BOOL Buffer::check_signal( ){
	VS_BOOL    returnValue;
	pthread_mutex_lock(&lock);
	std::lock_guard<std::mutex> guard(buffer_mutex_lock);
	returnValue = signal;
	 pthread_mutex_unlock(&lock);
	return ( returnValue );
}

