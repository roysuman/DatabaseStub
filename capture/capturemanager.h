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
#include "core/singleton.h"
#include "capture/pcapinterface.h"
#include <iostream>
#include<pthread.h>
#include<QObject>
class InterfaceHandler;
class CaptureManager: public QObject{
	Q_OBJECT
	public:
		CaptureManager( void){
			interface_instance = new (std::nothrow) InterfaceHandler( false);
		}
		virtual ~CaptureManager( void );
		void inline set_value( capture_opts* cap_opts_ , char* error_){
			cap_options = cap_opts_;
			error_msg = error_;
		}
		capture_opts* cap_options;
		char* error_msg;
	private:
		InterfaceHandler*    interface_instance;
        signals:
	 
	        /*emit signal when processing got finished*/	
        	void finished( void);
		
		/*update the received packet count
		  *emit this signal after a time interval*/
		void update_packet_count( size_t packet_count);
	public slots:
		/*start capture*/
		void init_pcap_process( void );
	        /* stop capture*/
	        void stop_capture( void );
};

#endif
