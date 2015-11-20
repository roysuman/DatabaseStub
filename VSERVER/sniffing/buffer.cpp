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
#include"buffer.hpp"
size_t            Buffer::buff_obj_count = 0;
std::mutex        Buffer::buffer_mutex_lock;
int               Buffer::read_head = -1;
int               Buffer::write_head = -1;
bool              Buffer::signal = false;
__rawNetData__    *Buffer::buffer = NULL;
bool              Buffer::buffer_init = false;
size_t            Buffer::buffer_read_count = 0;
size_t            Buffer::buffer_write_count= 0;
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
			buffer = new __rawNetData__[ BUFFER_SIZE];
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
bool Buffer::init_buffer(){
	bool    returnValue;

	pthread_mutex_lock(&lock);
//	std::lock_guard<std::mutex> guard(buffer_mutex_lock);
	returnValue = true;
	try{
		buffer = new __rawNetData__[ BUFFER_SIZE];
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
 *  Description:  write __rawData__ structure's object into the buffer.
 *                lock Protected. It's a circular buffer
 * =====================================================================================
 */
int Buffer::write_buffer( __rawNetData__ *&packet ){
	std::cout<<PRINT<<"write data in Buffer\n";
	int    returnValue;
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
			buffer [ write_head ].sourcePort = packet->sourcePort;
			buffer [ write_head ].destinationPort = packet->destinationPort;
			buffer [ write_head ].sequenceNumber = packet->sequenceNumber;
			buffer [ write_head].acknowledgeNumber = packet->acknowledgeNumber;
			buffer [ write_head ].dataLength = packet->dataLength;
			buffer [ write_head ].sourceIp= packet->sourceIp.c_str();
			buffer [ write_head ].destinationIp = packet->destinationIp.c_str();

			buffer [ write_head ].dateTime = packet->dateTime.c_str();
			buffer[ write_head ].networkTcpFlags.__ACK__ = packet->networkTcpFlags.__ACK__ ;
			buffer[ write_head ].networkTcpFlags.__SYN__ = packet->networkTcpFlags.__SYN__ ;
			buffer[ write_head ].networkTcpFlags.__FIN__ = packet->networkTcpFlags.__FIN__ ;

			buffer[ write_head ].networkTcpFlags.__PSH__ = packet->networkTcpFlags.__PSH__ ;

			buffer[ write_head ].networkTcpFlags.__RST__ = packet->networkTcpFlags.__RST__ ;

			buffer[ write_head ].networkTcpFlags.__URG__ = packet->networkTcpFlags.__URG__ ;
#endif

//			memcpy ( (void*)(buffer + write_head  ) ,(void*)packet , sizeof ( __rawNetData__ ) );
#ifdef ERROR
			__rawNetData__ *pp =  new __rawNetData__;
			memcpy( pp , buffer + write_head , sizeof ( __rawNetData__ ) );
			std::cout<<"\nip;"<<pp->sourceIp<<std::endl;
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
 *  Description:  read a __rawNetData__ element from the buffer into the reference variable
 *                 Lock protected, and circular.
 * =====================================================================================
 */
int Buffer::read_buffer( size_t noOfPackets , __rawNetData__ *& packet ){
	int    returnValue;
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
			packet->sourcePort = buffer [ write_head ].sourcePort ;
		        packet->destinationPort=buffer [ write_head ].destinationPort ;
			packet->sequenceNumber =buffer [ write_head ].sequenceNumber ;
			packet->acknowledgeNumber= buffer [ write_head].acknowledgeNumber; 
			packet->dataLength = buffer [ write_head ].dataLength ;
			packet->sourceIp = buffer [ write_head ].sourceIp.c_str();
			packet->destinationIp = buffer [ write_head ].destinationIp.c_str();

			packet->dateTime = buffer [ write_head ].dateTime .c_str();
		        packet->networkTcpFlags.__ACK__ =buffer[ write_head ].networkTcpFlags.__ACK__ ;
		        packet->networkTcpFlags.__SYN__ = buffer[ write_head ].networkTcpFlags.__SYN__ ;
			packet->networkTcpFlags.__FIN__  = buffer[ write_head ].networkTcpFlags.__FIN__ ;

			packet->networkTcpFlags.__PSH__  = buffer[ write_head ].networkTcpFlags.__PSH__ ;

			 packet->networkTcpFlags.__RST__= buffer[ write_head ].networkTcpFlags.__RST__ ;

			packet->networkTcpFlags.__URG__= buffer[ write_head ].networkTcpFlags.__URG__ ;

		//	memcpy ((void*) packet ,(void*)( buffer+ read_head )  , sizeof ( __rawNetData__  )   );
#ifdef ERROR
			__rawNetData__ *pp =  new __rawNetData__;
			memcpy( pp , buffer + read_head , sizeof ( __rawNetData__ ) );
			std::cout<<"\nip;"<<pp->sourceIp<<std::endl;
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
bool Buffer::give_signal(){
	bool    returnValue;
	pthread_mutex_lock(&lock);

	returnValue = true;

//	std::lock_guard<std::mutex> guard(buffer_mutex_lock);
	signal = true;
	 pthread_mutex_unlock(&lock);
	return returnValue;
}

bool Buffer::checkSignal( ){
	bool    returnValue;
	pthread_mutex_lock(&lock);
	std::lock_guard<std::mutex> guard(buffer_mutex_lock);
	returnValue = signal;
	 pthread_mutex_unlock(&lock);
	return ( returnValue );
}

