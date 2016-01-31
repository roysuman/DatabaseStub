/*
 * =====================================================================================
 *
 *       Filename:  pcapinterface.cpp
 *
 *       Description:  
 *
 *       Version:  1.0
 *       Created:  Wednesday 27 January 2016 03:19:51  IST
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


#include "pcapinterface.h"
#include "captureoptions.h"
#include <sys/time.h>

loop_data global_ld;
unsigned long start_time = 0;
void
init_global_interface_list( std::vector<interface_info>& int_info ){
	std::vector<interface_info>::iterator it;
	for ( it = global_available_interfaces.begin() ; it != global_available_interfaces.end() ; ++it ){
		if ( it->name != NULL)
			free(it->name);
		if ( it->description != NULL)
			free( it->description);
	}
	global_available_interfaces.erase( global_available_interfaces.begin(), global_available_interfaces.end());
	global_available_interfaces.resize(int_info.size());

	int loop = 0;

	for ( it = int_info.begin(); it!= int_info.end(); ++it ){
		global_available_interfaces[loop].name = strdup( it->name);
		global_available_interfaces[loop].description = strdup( it->description);
		global_available_interfaces[ loop ].loopback = it->loopback;
		global_available_interfaces[ loop].promiscious_mode = false;
		global_available_interfaces[loop].active_snaplen = true;
		global_available_interfaces[loop].snaplen = 65536;
		global_available_interfaces[ loop ].timeout =READ_TIMEOUT;

	}
	return;

}



/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  get_new_interface
 *  Description:  assing the values into a variable of type interface_info
 *  		and return it.
 *  		@interface_name: name of the interface
 *  		@interface_description:description of the interface
 *  		@is the interface is loopback device?
 *
 *  		@return a struct pointer of type interface_info .
  * =====================================================================================
 */
static interface_info*
get_new_interface( const char* interface_name , const char* interface_description,
		bool is_loopback ){
	interface_info *temp= new (std::nothrow) interface_info;
	if ( temp == NULL ) return NULL;
	if ( interface_name != NULL){
		temp->name = strdup ( interface_name);
	}else{
		temp->name = NULL;
	}
	if ( interface_description != NULL){
		temp->description = strdup ( interface_description);
	}else{
		temp->description = NULL;
	}
	temp->loopback = is_loopback;
	/* 
	qDebug()<<" Interface "<<temp->name
		<<"descripton "<<temp->description
		<<"iSLoopback?"<<(bool)temp->loopback;
		*/
	return temp;

}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  get_available_interface_list
 *  Description:  get all available interface list of the system under current users
 *  		  permission
 *  		  @*error: reference of error number..which got assigned to a value
 *  		  greater that 0 (> 0), on occurrence of any error.
 *  		  @*error_description: char reference to stpre the error string
 *
 *  		  @return: returns a vector of interface_info*, of all available interface
 *  		  info
 * =====================================================================================
 */
std::vector<interface_info*>
get_available_interface_list( int *error, char*error_description){
	std::vector<interface_info*> interface_list;
	interface_info* inf_info;
	char error_buffer[PCAP_ERRBUF_SIZE];
	 pcap_if_t *alldevsp , *device;
	 if ( pcap_findalldevs( &alldevsp , error_buffer ) == -1 ){
		 qDebug()<<"Not able to fetch interface list";
		 /* not able to read interface list from the system */
		 *error = ERROR_GET_INTERFACE_LIST;
		 if ( error_description != NULL ){
			 strncpy( error_description,error_buffer,PCAP_ERRBUF_SIZE);
		 }
	 }else if ( alldevsp !=NULL){
		 qDebug()<<" read interface list";
		 /*success....got interface info of the system wunder credentials 
		 now put each interface into the interface_list
		 */
		 for ( device = alldevsp ; device!= NULL ; device= device->next ){
			 inf_info = get_new_interface( device->name , 
					 device->description, 
					 (device->flags & PCAP_IF_LOOPBACK)?true:false);

			 interface_list.push_back(inf_info);
			 
		 }
		 pcap_freealldevs( alldevsp);
	 }else{ /* no interface found */
		 *error_description = NULL;
		 *error = 0;
	 }
	 return interface_list;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  loop_write_ringbuffer
 *  Description:  write the captured data into a RingBuffer...
 *  		  @cap_options: pcap_options reference for the current interface.
 *  		  @pkhdr: captured network packet header.
 *  		  @data: captured data.
 *
 * =====================================================================================
 */
static void
loop_write_ringbuffer ( unsigned char* cap_options , const struct pcap_pkthdr * pkhdr, 
		const unsigned char*data){
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  do_capture
 *  Description:  call pcap_dispatch with appropriate call back method..STOP receiving 
 *  		  packets on occurence of any error.
 *  		  @cap_options*:  pcap_options reference for holding information regardin
 *  		  to current interface.
 *  		  @Return: returns the number of captured packets.
 * =====================================================================================
 */
static size_t
do_capture( pcap_options *cap_options){
	int inpcket;
	int packet_count_before;

	packet_count_before = global_ld.packet_count;
	while( global_ld.is_alive){
		inpcket = pcap_dispatch( cap_options->pcap_h , -1 , 
				loop_write_ringbuffer,(unsigned char*)cap_options);
		if ( inpcket < 0 ){
			if ( inpcket == -1 ){
				cap_options->error = true;
			}
			global_ld.is_alive = false;
		}

	}
	return global_ld.packet_count - packet_count_before;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  open_capture_device
 *  Description:  open the device for capture
 * =====================================================================================
 */

static pcap_t*
open_capture_device( interface_info* inter_info, char (*errbuff)[ERRBUFF_SIZE]){
	pcap_t *pcap_header;

	qDebug()<< "Going to call pcap_open_live using following parametrs value"
		<<" Interface Name "<<inter_info->name
		<<" SnapLen "<<inter_info->snaplen
		<<" Promiscious Mode "<<inter_info->promiscious_mode
		<<"Time-Out "<<inter_info->timeout;

	pcap_header = pcap_open_live ( inter_info->name , inter_info->snaplen , inter_info->promiscious_mode , inter_info->timeout, *errbuff );
	return pcap_header;
}
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  start_capture_loop
 *  Description:  init the environment before goiong to capture mode. Open the interface
 *  		  interface handle for which live capture is going to happen.
 *  		  @cap_options: available capture options set by GUI
 *  		  @status: store the status of capture .
 *  		  @status_know: is status set
 *
 *  		  @return: true on success else false
 * =====================================================================================
 */

bool
start_capture_loop( capture_opts* cap_options,struct pcap_stat* status , bool *status_know){
	
	struct timeval  up_time, curr_time;
	int err_close;
	char error_msg[ ERRBUFF_SIZE];
	pcap_options *pcap_opt;
	//TODO loop for each interface
	interface_info int_info;//TODO = get_interface_info( position );
	pcap_opt = new pcap_options ;
	pcap_opt->pcap_h = open_capture_device( &int_info , &error_msg);
	if ( pcap_opt->pcap_h == NULL ){
		/* error on opeing device for sniffing */
		return false;
	}
	pcap_opt->packet_received = 0;
	pcap_opt->packet_dropped = 0;
	pcap_opt->packet_flushed = 0;
	pcap_opt->error = false;


	/* setup global loop options */
	global_ld.is_alive = true;
	global_ld.packet_count = 0;
	global_ld.packet_max = ( cap_options->stop_packet_set? cap_options->stop_packet_count: 0 );
	*status_know = false;
	
//	init_capture_stop_conditions();

	gettimeofday(&up_time,NULL);
	//TODO start_time = create_timestamp();
	do_capture( pcap_opt); 
	/*calculate capture time*/
	return true;
}
