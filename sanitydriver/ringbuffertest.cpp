/*
 * =====================================================================================
 *
 *       Filename:  ringbuffertest.cpp
 *
 *       Description:  
 *
 *       Version:  1.0
 *       Created:  Sunday 31 January 2016 12:35:12  IST
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



#include "../core/api/ringbuffer.h"
#include "../core/api/ringbuffer.cpp"

#include <iostream>
typedef struct _data data;
struct _data{
	int value;
	void print(){
		std::cout<<value;
	}
};
int main(){
	std::string buffer_name = "test_ring_buffer";
	RingBufferManager::init_new_ring_buffer(  buffer_name, 1024 , sizeof( data) + sizeof( unsigned int));
	RingBufferManager ii;
	ii.print_info();
	RingBuffer* ins = (RingBuffer*)ii.get_instance_by_name(buffer_name);
	std::cout<<ins->get_name()<<std::endl;
	data sample{100};
	size_t read_head = 0;
	char *d;//= new char [100];
	for( size_t loop=0;loop<10;++loop){
		sample.value = loop;
		ins->get_write_reference(&d );
		memcpy((d + sizeof(unsigned int)),&sample, sizeof(data));
		ins->publish_data( &d,2);
		std::cout<<"AMSK"<<*(unsigned int*)&d<<std::endl;
		//std::cout<<"data"<<*(int*)&(d+sizeof(unsigned int))<<std::endl;
	}
	for ( size_t loop=0;loop<1;++loop){
		if (ins->get_read_reference(&d,&read_head,2) ){
			std::cout<<"Got read reference for readhead "<<read_head<<std::endl;
			data* temp=(data*)d;
			temp->print();
			
		}
	}
	return 0;
}
