/*
 * =====================================================================================
 *
 *       Filename:  capturemanager.h
 *
 *       Description:  manage the capture interface
 *
 *       Version:  1.0
 *       Created:  Sunday 07 February 2016 06:37:31  IST
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
#ifndef CAPTIRE_MANAGER_H
#define CAPTIRE_MANAGER_H
#include "core/api/ringbuffer.h"
#include "capture/pcapinterface.h"
#include <iostream>
#include<pthread.h>

class CaptureManager{
	public:
		explicit CaptureManager( void){
			init_capture_inv();
		}
		virtual CaptureManager( void );
		
	protected:
		bool start_capture( capture_opts cap_options, char* error_msg );
		static void* thread_for_capture_net_packet( capture_opts , char* error_msg);
		stop_capture( void );
	private:
		void init_capture_inv( void );
		/* I am more reliable with pthread */
		pthread_t    pcap_thread;
		pthread_t    dissector_thread;

};
#endif
