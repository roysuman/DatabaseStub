/*
 * =====================================================================================
 *
 *       Filename:  ringbuffer.h
 *
 *       Description:  
 *
 *       Version:  1.0
 *       Created:  Friday 29 January 2016 12:14:29  IST
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

#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include <iostream>
#include<cstring>
#include<map>
class RingBuffer{
	public:
		explicit RingBuffer( std::string& name,size_t buffer_size_ = 1024, size_t element_size_ = 0, size_t read_head_ = 0, size_t write_head_ =0):buffer_size(buffer_size_), read_head(read_head_), write_head(write_head_), ring_buffer_name(name),element_size( element_size_),buffer(NULL){}
		virtual    ~RingBuffer( void );
		/* 
		 * print the buffer info
		 * */
		//TODO whu following method adding creating problem?

	//	void print_( void );
		/* 
		 * initialize a ring buffer 
		 * */
		bool       init_ring_buffer(  const size_t buffer_size_ = 0 , const size_t element_sizep= 0  ) ;
		/* 
		 * get reference of an empty slot from  ringbuffer's
		 * **ref: reference of write memory on success else  NULL
		 * returns true in *ref contains a valid address else false
		 * */
		bool       get_write_reference( char** ref);
		/* 
		 * get reference of an empty slot from RingBuffer
		 * if there is no empty slot in ring-buffer then this functio
		 * waits for an empty slot
		 * */
		bool       wait_and_get_write_reference( char** ref );
		void publish_data( char** ref , unsigned int mask);
		/* 
		 * get a reference from ring buffer.
		 * this method sequentially checks ring buffer for a slot with
		 * matching mask..returns false if ringbuffer is empty or no such
		 * data with desired mask is present else returns true 
		 * */
		bool       get_read_reference( char** ref, size_t* read_head_,unsigned int mask);
		bool       wait_and_get_read_reference( char** ref,size_t* read_head_, unsigned int mask);
		/* 
		 * update the mask value of given reference  
		 * */
		void       update_mask( char** ref, unsigned int mask );

		/* 
		 * returns true if ring buffer is empty else false
		 * */
		bool       is_ring_buffer_empty( void);

		/* 
		 * returns true if ring-buffer is full else true 
		 * */
		bool       is_ring_buffer_full( void );
		/* 
		 * return the name of the ring buffer
		 * */

		std::string get_name(){ return ring_buffer_name ;}

	private:
		/* 
		 * starting byte address of data array
		 * */
		char*          buffer;
		/* 
		 *position of read_head
		 * */
		size_t         read_head;
		/* 
		 * position of write_head 
		 * */
		size_t         write_head;
		/* 
		 * size of the buffer in byte
		 * */
		size_t         buffer_size;
		/* 
		 * buffer initiated ot not..true if is initialized else false
		 * */
		bool           has_buffer_init;
		/* 
		 *size of eaxh slot of ring-buffer
		 * */
		size_t         element_size;
		/* 
		 * name of the ring buffer 
		 * */
		std::string    ring_buffer_name;
		/* 
		 * unique id of this ring-buffer 
		 * */
		size_t         ring_buffer_id;
		/* 
		 *returns true if buffer already initialized else false
		 * */
		inline bool    is_buffer_init(void) const { return has_buffer_init;} 

};
/* 
 *typdef for mapping RingBuffer instant against ring-buffer name
 * */
typedef std::map<std::string,RingBuffer*> map_ring_buffer_type;
typedef map_ring_buffer_type::iterator map_ring_buffer_type_iterator;


#include "apihelper.h"
/* 
 * Ring buffer manager..to keep track of all existing ring buffers
 * */
class RingBufferManager: public ApiAbstract{
	public:
		RingBufferManager( ){}
		virtual ~RingBufferManager(){}

		/* 
		 * return a new instance of class RingBuffer.
		 * */
		//RingBuffer* get_empty_ringbuffer_instant( void );
		void* get_empty_instance( std::string& , size_t buffer_size_ = 0, size_t element_size_ = 0) override;

		/*
		 * search ringbuffer map container by ring-buffer name 
		 * returns ringbuffer instance..if ring buffer exist
		 * else returns NULL
		 */
		//RingBuffer* get_ring_buffer_by_name(const  std::string ring_buffer_name);
		void* get_instance_by_name(const  std::string& ring_buffer_name) override;

		/* 
		 * register new configured ring bufer into map container
		 * */
		//bool register_configured_ring_buffer( RingBuffer* instance);
		bool register_api_instance( void* instance) override;

		/* 
		 * destroy an existing ring buffer 
		 * */
		//bool destroy_ring_buffer( const std::string& ring_buffer_name);
		bool destroy_api_instance_by_name( const std::string& ring_buffer_name) override;

		/* 
		 * print ring buffer stat..print the read head and write head
		 * of each registered ringbuffer
		 * */
		//void print_stat( void );
		void print_api_stat( void ) override;
		/* 
		 * create a new instance of RingBuffer */


		static bool init_new_ring_buffer( std::string& buffer_name, size_t buffer_size, size_t element_size);
		static void destroy_container( void);
		void print_info( void ) override;
	private:
		/* how many ring buffer has been configured */
		static size_t max_ring_buffer_count;

		/* container map for RingBuffer instance against ring-buffer name */
		static map_ring_buffer_type map_ring_buffer_container;
};
#endif
