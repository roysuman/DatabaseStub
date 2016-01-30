/*
 * =====================================================================================
 *
 *       Filename:  ringbuffer.cpp
 *
 *    Description: see the header file for all defination 
 *
 *        Version:  1.0
 *        Created:  Friday 29 January 2016 03:49:24  IST
 *       Revision:  none
 *       Compiler:  g++4.7
 *
 *         Author:  SIGCONT (suman roy), email.suman.roy@gmail.com
 *   Organization:  OPEN SOURCE
 *
 * =====================================================================================
 */
/* 
 *This program is free software: you can redistribute it and/or modify
 *it under the terms of the GNU General Public License as published by
 *the Free Software Foundation, either version 3 of the License, or
 *(at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. */
#include "ringbuffer.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  init_ring_buffer
 *  Description:  initialize the ring buffer.
 *  		  create the memory for buffer.
 * =====================================================================================
 */
bool
RingBuffer::init_ring_buffer( const size_t buffer_size_, const size_t element_size_ ){
	size_t bytes;
	if ( buffer_size == 0 ){
		buffer_size = buffer_size_;
		element_size = element_size_;
		bytes = buffer_size * element_size;
	}
	else {
		bytes = buffer_size_ * element_size_;
	}
	buffer = (char*)::operator new[]( bytes);
	has_buffer_init = true;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ~RingBuffer
 *  Description:  destructor for the class RingBuffer
 *  		  free the created memory.
 * =====================================================================================
 */

RingBuffer::~RingBuffer( void ){
	if ( buffer != NULL )
		::operator delete(buffer);
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  get_write_reference
 *  Description:  return an empth slot from buffer...to write data
 *  		  into ring buffer
 * =====================================================================================
 */

bool
RingBuffer::get_write_reference( char** ref ){
	bool    return_val = true;
	if ( has_buffer_init && ( buffer_size > ( write_head - read_head ) ) ){
		size_t offset = write_head % buffer_size;
		offset *= element_size;

		*ref = (char*)(buffer + offset);
	}else{
		*ref = NULL;
		return_val =  false;
		std::cerr<<"ERROR....not able to get an empty slot from"
			"Ring buffer...exiting"<<std::endl;
	}
	return return_val;

}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  wait_and_get_write_reference
 *  Description:  get an empty slot from buffer..to write data into ring-buffer
 *  		 this method should wait till it does not get an empty slot.
 * =====================================================================================
 */
bool
RingBuffer::wait_and_get_write_reference( char** ref ){
	bool    return_val = false;
	int count = 0;
	if ( !has_buffer_init );
	else{
		while (  !return_val){
			if ( buffer_size > ( write_head - read_head) ) {
				size_t offset = write_head % buffer_size;
				offset *= element_size;
				*ref = (char*)(buffer + offset);
				return true;
			}
			count++;
			if ( count == MAX_TRY)break;
			else void(0);
		}
	}
	return return_val;
}

bool
RingBuffer::get_read_reference( char** ref,size_t *read_head_, unsigned int mask){
	bool    return_val = false;
	size_t    offset;
	if ( has_buffer_init ){
		offset = *read_head_ % buffer_size;
		offset *= element_size;
		while ( !return_val && ( *read_head_ < write_head  ) ){
			if ( (*(unsigned int*)(buffer + offset ) == 0 )|| ( *(unsigned int*)(buffer + offset ) > mask )) *read_head_ ++;
			else if ( *(unsigned int*)(buffer + offset ) == mask ){
				*ref = buffer  + offset + sizeof ( unsigned int );
				return_val = true;
				*read_head_ ++;
			}else return false;
			offset += element_size;
		}
	}else{
		std::cerr<<"Not able to get the reference from"
			<<"Ring Buffer,,.. buffer not initialized"
			<<std::endl;
	}
	return return_val;
}

bool
RingBuffer::wait_and_get_read_reference( char** ref,size_t *read_head_, unsigned int mask){
	bool    return_val = false;
	size_t    offset;
	if ( has_buffer_init ){
		offset = *read_head_ % buffer_size;
		offset *= element_size;
		while ( !return_val && ( *read_head_ < write_head  ) ){
			if ( (*(unsigned int*)(buffer + offset ) == 0 )|| ( *(unsigned int*)(buffer + offset ) > mask )) *read_head_ ++;
			else if ( *(unsigned int*)(buffer + offset ) == mask ){
				*ref = buffer  + offset + sizeof ( unsigned int );
				return_val = true;
				*read_head_ ++;
			}else{
				continue ;//TODO SLEEP}
			}
		}
	offset += element_size;
	}else{
		std::cerr<<"Not able to get the reference from"
			<<"Ring Buffer,,.. buffer not initialized"
			<<std::endl;
	}
	return return_val;
}

void
RingBuffer::publish_data( char** ref , unsigned int mask ){
	*(unsigned int *)(*ref) = ( 0 || mask );
	write_head ++;

}
void
RingBuffer::update_mask( char** ref, unsigned int mask ){
	*(unsigned int* )(ref) =  mask ;
	return;
}

bool
RingBuffer::is_ring_buffer_empty( void ){
	return ( read_head == write_head ? true: false);
}
bool 
RingBuffer::is_ring_buffer_full( void ){
	return ( (read_head + buffer_size) == write_head ? true: false );
}
/* 
void
RingBuffer::print_( void ){
	std::cout<<"RingBufferName : "<<ring_buffer_name
		<<"\n ring_buffer_id : "<<ring_buffer_id
		<<"\nReadHead : "<< read_head
	       <<"\nWriteHead : "<<write_head
	       <<"\nBufferInitialized? "<<is_buffer_init()
	       <<"\nBufferCapacity : "<<buffer_size
	       <<"\nElement Size : "<<element_size
	       <<std::endl;
	return;

}
*/
/*-----------------------------------------------------------------------------
 * class RingBufferManager
 *-----------------------------------------------------------------------------*/

size_t RingBufferManager::max_ring_buffer_count = 0;
map_ring_buffer_type  RingBufferManager::map_ring_buffer_container;
void*
RingBufferManager::get_empty_instance( std::string& name , size_t buffer_size_, size_t element_size_) {
	//RingBuffer* temp = new ( std::nothrow) RingBuffer;
	//return ( void*)temp;
	RingBuffer *temp = new ( std::nothrow) RingBuffer(name);
	return ( void*)temp;
}

bool
RingBufferManager::register_api_instance( void* instance_ ){
	bool   return_val = false;
	RingBuffer* instance = ( RingBuffer*) instance_;
	if ( instance != NULL ){
//		map_ring_buffer_container.insert ( std::make_pair(instance->get_name() , instance) );
		if (RingBufferManager::map_ring_buffer_container.insert ( std::make_pair(instance->get_name() , instance) ).second == false ) return_val = false;
		else{
			RingBufferManager::max_ring_buffer_count --;
			return_val = true;
		}
	}else{
		std::cerr<<"ERROR...on inserting element in"
			<<" Ring-Buffer container...as instance is a"
			<<" NULL pointer"<<std::endl;
	}
	return return_val;
}
bool
RingBufferManager::init_new_ring_buffer( std::string& buffer_name_, size_t buffer_size_ , size_t element_size_){
	bool    return_val = true;
	RingBufferManager ring_manager;
	RingBuffer *temp_ring= (RingBuffer*)ring_manager.get_empty_instance( buffer_name_);
	if ( temp_ring == NULL ) return_val = false;
	else{
		temp_ring->init_ring_buffer(  buffer_size_, element_size_);/* 
		temp_ring->ring_buffer_name = buffer_name_;
		temp_ring->buffer_size = buffer_size_ ;
		temp_ring->element_size= element_size_;
		temp_ring->init_ring_buffer();*/
		ring_manager.register_api_instance( (void*)temp_ring);
	}
	return return_val;
}

void*
RingBufferManager::get_instance_by_name( const std::string& name ){
	map_ring_buffer_type_iterator it;
	it = RingBufferManager::map_ring_buffer_container.find( name );
	if ( it == RingBufferManager::map_ring_buffer_container.end() ){
		return NULL;
	}
	return (void*)(it->second);
}

bool
RingBufferManager::destroy_api_instance_by_name( const std::string& name ){
	bool   return_val = true;
	map_ring_buffer_type_iterator it;
	it = RingBufferManager::map_ring_buffer_container.find( name );
	if ( it == RingBufferManager::map_ring_buffer_container.end() ){
		return_val = false;
	}else {
		RingBufferManager::map_ring_buffer_container.erase( it );
		RingBufferManager::max_ring_buffer_count --;
	}
	return return_val;
}

void
RingBufferManager::destroy_container( void ){
	RingBufferManager::map_ring_buffer_container.erase( RingBufferManager::map_ring_buffer_container.begin(),
			RingBufferManager::map_ring_buffer_container.end());
}
void
RingBufferManager::print_api_stat( void ){
	//TODO implementation
}

void
RingBufferManager::print_info( void ){
	map_ring_buffer_type_iterator it;
	for ( it = RingBufferManager::map_ring_buffer_container.begin();
			it!= RingBufferManager::map_ring_buffer_container.end();
			++it){
		std::cout<<it->second->get_name();
//		it->second->print_info();

	}

}
