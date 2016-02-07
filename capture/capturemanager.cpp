/*
 * =====================================================================================
 *
 *       Filename:  capturemanager.cpp
 *
 *       Description:  mangae lpacap
 *
 *       Version:  1.0
 *       Created:  Sunday 07 February 2016 10:58:33  IST
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
#include "capturemanager.h"
#include "core/api/ringbuffer.h" 
#include "capture/pcapinterface.h"
/* 
 * destructor 
 * */
CaptureManager::~CaptureManager( void ){}

bool
CaptureManager::start_capture( capture_opts* cap_options,char* error_msg){
	/* TODO init ring buffer handle...
	 * FUTURE ADD: add file-handle if data need to store into file */

	std::string ring_buffer_name = "collectorRingBuffer";
	RingBuffer* ins = (RingBuffer*)ii.get_instance_by_name(ring_buffer_name);
        std::cout<<ins->get_name()<<std::endl;
	cap_options->ring_buffer_handle = (void*)ins; 
	/*create thread for pcap capture TODO set attribute */
	if ( pthread_create( &pcap_thread , nullptr,&CaptureManager::thread_for_capture_net_packet,(void*)cap_options) != 0 )return false;

	/* TODO dissector handle with pthread */

	pthread_join( pcap_thread , NULL );


}

void*
CaptureManager::thread_for_capture_net_packet( void* cap_opt ){
	InterfaceHandler* interface_instance = new ( std::nothrows) InterfaceHandler( true );
	if ( interface_instancec!= nullptr){
		interface_instance->start_capture_loop( cap_opt, (void*)interface_instance);

	}
	
	return nullptr;
}


