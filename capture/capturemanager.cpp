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
void
InitWorker::perform_init_worker(  void ){
	//TODO Future--handle progress bar
	CaptureManager::get_instance()->init_pcap_process(  cap_options , error_msg );
	emit finished();
}
*/
/* 
 * destructor 
 * */
CaptureManager::~CaptureManager( void ){
	delete interface_instance;

}

void
CaptureManager::init_pcap_process( void ){
	/* TODO init ring buffer handle...
	 * FUTURE ADD: add file-handle if data need to store into file */


	std::string ring_buffer_name = "collectorRingBuffer";
	RingBufferManager ring_manager;

	RingBuffer* ins = (RingBuffer*)ring_manager.get_instance_by_name(ring_buffer_name);
	if ( ins == nullptr ){
		qDebug()<<"Error...no ring-buffer named collectorRingBuffer"
			<<"registered in the system";
		//TODO set error MSG
		return;
	}
        std::cout<<ins->get_name()<<std::endl;
	cap_options->ring_buffer_handle = (void*)ins; 
	/*create thread for pcap capture TODO set attribute */
	if ( interface_instance!= nullptr){
		interface_instance->start_capture_loop( cap_options, error_msg);
	}
}


void
CaptureManager::stop_capture( void ){
	//TODO call method of InterfaceHandler class to stop capture.
	if ( interface_instance!= nullptr){
		interface_instance->stop_capture();
	}
	return;
}


