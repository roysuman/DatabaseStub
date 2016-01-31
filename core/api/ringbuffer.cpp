/*
 * =====================================================================================
 *
 *       Filename:  ringbuffer.cpp
 *
 *       Description:  
 *
 *       Version:  1.0
 *       Created:  Friday 29 January 2016 03:49:24  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *       Author:  SIGCONT (suman roy), email.suman.roy@gmail.com
 *       Organization:  OPEN SOURCE
 *       LICENSE: GNU GPL
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * =====================================================================================
 */


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

		*ref = (char*)(buffer + offset );
	}else{
		*ref = NULL;
		return_val =  false;
		std::cerr<<"ERROR....not able to get an empty slot from"
			"Ring buffer...exiting"<<std::endl;
	}
	return return_val;

}

/* 
 ===  FUNCTION  ======================================================================
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

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  get_read_reference
 *  Description:  once ring-buffer has some valuable data..consumers reads
 *  		  data from ring-buffer by ths method. This method provides
 *  		  the memory reference of the desired index of ring-buffer.
 *  		  The searching mechanism returns a reference of data
 *  		  whose mash field is same as variable mask.
 *  		  @**reaf: reference pointer, which holds valid index of
 *  		  ring buffer on suzzessf.
 *  		  @read_head_: consumers already processes data till
 *  		   read_head_ -1. Now trying to get matched from index>= 
 *  		   read_head_;
 *  		  @mask: mask used to search desired data.
 *  		  @return true on success else false.
 * =====================================================================================
 */
bool
RingBuffer::get_read_reference( char** ref,size_t *read_head_, unsigned int mask){
	bool    return_val = false;
	size_t    offset;
	if ( has_buffer_init ){
		offset = *read_head_ % buffer_size;
		offset *= element_size;
		std::cout<<"\nInititalized ofset "<<offset<<std::endl;
		while ( !return_val && ( *read_head_ < write_head  ) ){
			std::cout<<*(unsigned int*)(buffer)<<std::endl;
			std::cout<<"Inside while\n"<<std::endl;
			if ( (*(unsigned int*)(buffer + offset ) == 0 )|| ( *(unsigned int*)(buffer + offset ) > mask )){std::cout<<"First check"<<std::endl; *read_head_ ++;}
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

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  wait_and_get_read_reference
 *  Description:  once ring-buffer has some valuable data..consumers reads
 *  		  data from ring-buffer by ths method. This method provides
 *  		  the memory reference of the desired index of ring-buffer.
 *  		  The searching mechanism returns a reference of data
 *  		  whose mash field is same as variable mask. If there is no
 *  		  available data in ring-buffer, wait and try again(fixed
 *  		  no of times) to get a valid slot.
 *  		  @**reaf: reference pointer, which holds valid index of
 *  		  ring buffer on suzzessf.
 *  		  @read_head_: consumers already processes data till
 *  		   read_head_ -1. Now trying to get matched from index>= 
 *  		   read_head_;
 *  		  @mask: mask used to search desired data.
 *  		  @return true on success else false.
 * =====================================================================================
 */
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

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  publish_data
 *  Description:  once publisher writes data at reference pointer. It's 
 *  		  publisher's responsibility to notify consumers about
 *  		  the availability of data. Publisher simply update the mask
 *  		  field.
 *  		  @ref: reference of data
 *  		  @mask: mask to set
 * =====================================================================================
 */
void
RingBuffer::publish_data( char** ref , unsigned int mask ){
	*(unsigned int *)&(*ref) = mask;
//	std::cout<<*((unsigned int*)(buffer));
	write_head ++;

}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  update_mask
 *  Description:  update the mask field of reference
 *  		  @ref: data reference in ring buffer.
 *  		  @mask: new mask value
 * =====================================================================================
 */
void
RingBuffer::update_mask( char** ref, unsigned int mask ){
	*(unsigned int* )&(*ref) =  mask ;
	return;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  is_ring_buffer_empty
 *  Description:  return true if ring-buffer has no data else false.
 * =====================================================================================
 */
bool
RingBuffer::is_ring_buffer_empty( void ){
	return ( read_head == write_head ? true: false);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  is_ring_buffer_full
 *  Description:  returns true if ring-buffer full else false.
 * =====================================================================================
 */
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
/* initialize of static members. */
size_t RingBufferManager::max_ring_buffer_count = 0;
map_ring_buffer_type  RingBufferManager::map_ring_buffer_container;


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  get_empty_instance
 *  Description:  return an empty instance of RingBuffer class.
 *                this method calls RingBuffer constructor to create
 *                a new instance.
 *                @name: name of the ring buffer.
 *                @buffer_size_: size of the buffer. number of elements.
 *                @element_size_: size of each element in ring buffer
 *                @return: returns a void* of created RingBuffer else NULL.
 * =====================================================================================
 */
void*
RingBufferManager::get_empty_instance( std::string& name , size_t buffer_size_, size_t element_size_) {
	//RingBuffer* temp = new ( std::nothrow) RingBuffer;
	//return ( void*)temp;
	RingBuffer *temp = new ( std::nothrow) RingBuffer(name);
	return ( void*)temp;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  register_api_instance
 *  Description:  register RingBuffer instance itno the static mapper.
 *  		  the ogic is to map the RingBuffer instance againest
 *  		  their name into a sat map of static type.
 *  		  @instance: pointer of RingBuffer instance.
 *  		  @return true if successfully inserted into mao else false
 * =====================================================================================
 */
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

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  init_new_ring_buffer
 *  Description:  helper method to initialized a new RingBuffer instance.
 *  		  it's static method, whose responsibility is to create
 *  		  new instance of RingBuffer and allocate memory for
 *  		  buffer then register into map.
 *  		  @buffer_name_:name of the new buffer.
 *  		  @buffer_size_: number of index.
 *  		  @element_size_: size of each element.
 *  		  @return true on success else false.
 * =====================================================================================
 */
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


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  get_instance_by_name
 *  Description:  search the map container for a registered RingBuffer 
 *                instance by buffer name. If RingBuffer is available 
 *                then return the RingBuffer instance else return false.
 *                @name: name of the ringbuffer, this is used to search
 *                map.
 *                @return RingBuffer instance on success else NULL.
 * =====================================================================================
 */
void*
RingBufferManager::get_instance_by_name( const std::string& name ){
	map_ring_buffer_type_iterator it;
	it = RingBufferManager::map_ring_buffer_container.find( name );
	if ( it == RingBufferManager::map_ring_buffer_container.end() ){
		return NULL;
	}
	return (void*)(it->second);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  destroy_api_instance_by_name
 *  Description:  remove instance of RingBuffer from map container.
 *                @name: used to search the map container. If desired
 *                RingBuffer is available then remove it.
 *                @return true on suzzess else false.
 * =====================================================================================
 */
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

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  destroy_container
 *  Description:  make empty of map container.
 * =====================================================================================
 */
void
RingBufferManager::destroy_container( void ){
	RingBufferManager::map_ring_buffer_container.erase( RingBufferManager::map_ring_buffer_container.begin(),
			RingBufferManager::map_ring_buffer_container.end());
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  print_api_stat
 *  Description:  print the information of all RingBuffer.
 *  		  like read_count, write_cout so on.
 * =====================================================================================
 */
void
RingBufferManager::print_api_stat( void ){
	//TODO implementation
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  print_info
 *  Description:  it helps during debuging. print information of all
 *                registered ring-buffer
 * =====================================================================================
 */
void
RingBufferManager::print_info( void ){
	map_ring_buffer_type_iterator it;
	for ( it = RingBufferManager::map_ring_buffer_container.begin();
			it!= RingBufferManager::map_ring_buffer_container.end();
			++it){
		std::cout<<it->second->get_name()<<std::endl;
//		it->second->print_info();

	}

}
