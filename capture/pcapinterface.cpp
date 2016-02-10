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
#include <sys/time.h>

/* declearation of static members variable */
int      InterfaceHandler::error = 0;
char*    InterfaceHandler::error_description = NULL;
bool     InterfaceHandler::avail_interface_list = false;
std::vector<interface_info*> InterfaceHandler::interface_list;

loop_data InterfaceHandler::global_ld;
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  InterfaceHandler
 *  Description:  constructor of interface handler class.
 *  		  get and inti all interface list during 
 *  		  startup. If choice is true then init
 *  		  system interface list. If a user wants to process 
 *  		  already captured file then no need of 
 *  		  interface list.
 *  		  @return: does constructor returns anything?
 * =====================================================================================
 */

InterfaceHandler::InterfaceHandler( bool choice ){
	InterfaceHandler::error = 0;
//	*InterfaceHandler::error_description = NULL;
	choice?(void)setup_interface_list():void(0);
	return;
}



/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  setup_interface_list
 *  Description:  get all interface list of the system
 *                depending on the user's permission.
 * =====================================================================================
 */
void
InterfaceHandler::setup_interface_list( void ){
	interface_info* inf_info;
	char error_buffer[PCAP_ERRBUF_SIZE];
	 pcap_if_t *alldevsp , *device;
	 if ( pcap_findalldevs( &alldevsp , error_buffer ) == -1 ){
		 qDebug()<<"Not able to fetch interface list";
		 /* not able to read interface list from the system */
		 InterfaceHandler::error = ERROR_GET_INTERFACE_LIST;
		 if ( error_description != NULL ){
			 /* not able to read interface list from the system */
			 InterfaceHandler::error = ERROR_GET_INTERFACE_LIST;
			 strncpy( InterfaceHandler::error_description,error_buffer,PCAP_ERRBUF_SIZE);
		 }
		 avail_interface_list = false;
		 return;
	 }else if ( alldevsp !=NULL){
		 qDebug()<<" read interface list";
		 /*success....got interface info of the system wunder credentials 
		 now put each interface into the interface_list
		 */
		 for ( device = alldevsp ; device!= NULL ; device= device->next ){
			 inf_info = InterfaceHandler::get_new_interface( device->name , 
					 device->description, 
					 (device->flags & PCAP_IF_LOOPBACK)?true:false);

			 InterfaceHandler::interface_list.push_back(inf_info);
			 
		 }
		 pcap_freealldevs( alldevsp);
	 }else{ /* no interface found */
		 *InterfaceHandler::error_description = NULL;
		 InterfaceHandler::error = 0;
	 }
	 avail_interface_list = true; 
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
interface_info*
InterfaceHandler::get_new_interface( const char* interface_name , const char* interface_description,bool is_loopback ){
	interface_info *temp= new (std::nothrow) interface_info;
	if ( temp == NULL ) return NULL;
	if ( interface_name != NULL){
		temp->name = std::string ( interface_name);
	}
	if ( interface_description != NULL){
		temp->description = std::string ( interface_description);
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
InterfaceHandler::get_available_interface_list( int *error_, char*error_description_){
//	std::vector<interface_info*> interface_list;

	if (  InterfaceHandler::avail_interface_list ){
		//interface_list = InterfaceHandler::interface_list_private;
		*error_ = InterfaceHandler::error;
		strncpy( error_description_ , InterfaceHandler::error_description,PCAP_ERRBUF_SIZE);
		return interface_list; 

	}
	interface_info* inf_info;
	char error_buffer[PCAP_ERRBUF_SIZE];


	 pcap_if_t *alldevsp , *device;
	 if ( pcap_findalldevs( &alldevsp , error_buffer ) == -1 ){
		 qDebug()<<"Not able to fetch interface list";
		 /* not able to read interface list from the system */
		 *error_ = ERROR_GET_INTERFACE_LIST;
		 if ( error_description != NULL ){
			 strncpy( error_description_,error_buffer,PCAP_ERRBUF_SIZE);
		 }
	 }else if ( alldevsp !=NULL){
		 qDebug()<<" read interface list";
		 /*success....got interface info of the system wunder credentials 
		 now put each interface into the interface_list
		 */
		 for ( device = alldevsp ; device!= NULL ; device= device->next ){
			 inf_info = InterfaceHandler::get_new_interface( device->name , 
					 device->description, 
					 (device->flags & PCAP_IF_LOOPBACK)?true:false);

			 InterfaceHandler::interface_list.push_back(inf_info);
			 
		 }
		 pcap_freealldevs( alldevsp);
	 }else{ /* no interface found */
		 *error_description_ = NULL;
		 *error_ = 0;
	 }
	 avail_interface_list = true;
	 return InterfaceHandler::interface_list;
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
void
InterfaceHandler::loop_write_ringbuffer ( unsigned char* cap_options , const struct pcap_pkthdr * pkhdr, 
		const unsigned char*data){
	qDebug()<<"Write to ringbuffer";
	return;
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
size_t
InterfaceHandler::do_capture( pcap_options *cap_options){
	int inpcket;
	int packet_count_before;

	packet_count_before = InterfaceHandler::global_ld.packet_count;
	while( InterfaceHandler::global_ld.is_alive){
		qDebug()<<"Calling pcap_dispatch";
		inpcket = pcap_dispatch( cap_options->pcap_h , -1 , 
				InterfaceHandler::loop_write_ringbuffer,(unsigned char*)cap_options);
		if ( inpcket < 0 ){
			if ( inpcket == -1 ){
				cap_options->error = true;
			}
			InterfaceHandler::global_ld.is_alive = false;
		}

	}
	return InterfaceHandler::global_ld.packet_count - packet_count_before;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  open_capture_device
 *  Description:  open the device for capture
 * =====================================================================================
 */

pcap_t*
InterfaceHandler::open_capture_device( interface_info* inter_info, char (*errbuff)[ERRBUFF_SIZE]){
	pcap_t *pcap_header;

	qDebug()<< "Going to call pcap_open_live using following parametrs value"
        <<" Interface Name "<<inter_info->name.c_str()
		<<" SnapLen "<<inter_info->snaplen
		<<" Promiscious Mode "<<inter_info->promiscious_mode
		<<"Time-Out "<<inter_info->timeout;

    pcap_header = pcap_open_live ( (inter_info->name).c_str() , inter_info->snaplen , inter_info->promiscious_mode , inter_info->timeout, *errbuff );
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

//bool
//InterfaceHandler::start_capture_loop( capture_opts* cap_options,struct pcap_stat* status , bool *status_know, void* temp){
	
bool
InterfaceHandler::start_capture_loop( capture_opts* cap_options , char* error_msg_){
	struct timeval  up_time, curr_time;
	int err_close;
	char error_msg[ ERRBUFF_SIZE];


	pcap_options *pcap_opt;
	//TODO loop for each interface
    interface_info *int_info = get_interface_info( cap_options->device_name ); 
    if ( int_info == nullptr ) return false;
	pcap_opt = new pcap_options ;
    pcap_opt->pcap_h = this->open_capture_device( int_info , &error_msg);
	if ( pcap_opt->pcap_h == NULL ){
		/* error on opeing device for sniffing */
		return false;
	}
	pcap_opt->packet_received = 0;
	pcap_opt->packet_dropped = 0;
	pcap_opt->packet_flushed = 0;
	pcap_opt->error = false;
	pcap_opt->cap_opts = cap_options;


	/* setup global loop options */
	InterfaceHandler::global_ld.is_alive = true;
	InterfaceHandler::global_ld.packet_count = 0;
	InterfaceHandler::global_ld.packet_max = ( cap_options->stop_packet_set? cap_options->stop_packet_count: 0 );
//	*status_know = false;
	
//	init_capture_stop_conditions();

	gettimeofday(&up_time,NULL);
	//TODO start_time = create_timestamp();
	do_capture( pcap_opt); 
	/*calculate capture time*/
	return true;
}

interface_info*
InterfaceHandler::get_interface_info( std::string name ){
	interface_info*    int_inf = nullptr;

	std::vector<interface_info*>::iterator it;
	qDebug()<<"Get the interface info..."
		<<"Search interface by Name "
		<<name.c_str();

	for ( it = InterfaceHandler::interface_list.begin();
			it != InterfaceHandler::interface_list.end();
			++it){
		if  ( (*it)->name == name ){
			int_inf= *it;
			break;
		}
	}
	return int_inf;
}

void
InterfaceHandler::stop_capture( void ){
	InterfaceHandler::global_ld.is_alive = false;
}
