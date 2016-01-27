/*
 * =====================================================================================
 *
 *       Filename:  pcapinterface.c
 *
 *    Description:  read heder file for definations
 *
 *        Version:  1.0
 *        Created:  Wednesday 27 January 2016 03:19:51  IST
 *       Revision:  none
 *       Compiler:  g++4.7
 *
 *         Author:  Suman Roy (), suman.roy@cognizant.com
 *   Organization:  Cognizant Technological Solutions
 *
 * =====================================================================================
 */
#include "pcapinterface.h"
#include "captureoptions.h"
#include <sys/time.h>

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
	interface_info *temp= new interface_info;
	temp->name = strdup ( interface_name);
	temp->description = strdup ( interface_description);
	temp->loopbak = is_loopback;
	return temp;

}

std::vector<interface_info*>
get_available_interface_list( int *error, char**error_description){
	std::vector<interface_info*> interface_list;
	interface_info* inf_info;
	char error_buffer[PCAP_ERRBUF_SIZE];
	 pcap_if_t *alldevsp , *device;
	 if ( pcap_findalldevs( &alldevsp , error_buffer ) == -1 ){
		 /* not able to read interface list from the system */
		 *error = ERROR_GET_INTERFACE_LIST;
		 if ( error_description != NULL ){
			 strncpy( *error_description,error_buffer,PCAP_ERRBUF_SIZE);
		 }
	 }else if ( alldevsp !=NULL){
		 /*success....got interface list
		 now put each interface into the interface_list
		 */
		 for ( device = alldevsp ; device!= NULL ; device= device->next ){
			 inf_info = get_new_interface( device->name , device->description, (device->flags & PCAP_IF_LOOPBACK)?true:false);
			 interface_list.push_back(inf_info);
			 
		 }
		 pcap_freealldevs( alldevsp);
	 }else{ /* no interface found */
		 *error_description = NULL;
		 *error = 0;
	 }
	 return interface_list;
}

static void
loop_write_ringbuffer ( unsigned char* cap_options , const struct pcap_pkthdr * pkhdr, const unsigned char*data){
}


static size_t
do_capture( pcap_options *cap_options){
	int inpcket;
	int packet_count_before;

	packet_count_before = global_ld.packet_count;
	while( global_ld.is_alive){
		inpcket = pcap_dispatch( cap_options->pcap_h , -1 , loop_write_ringbuffer,(unsigned char*)cap_options);
		if ( inpcket < 0 ){
			if ( inpcket == -1 ){
				cap_options->error = true;
			}
			global_ld.is_alive = false;
		}

	}
	return global_ld.packet_count - packet_count_before;
}
bool
start_capture_loop( capture_opts* cap_options,struct pcap_stat* status , bool *status_know){
	

	struct timeval  up_time, curr_time;
	int err_close;
	char error_msg[MAX_MSG_LENGTH + 1];
	pcap_options *pcap_opt;


	pcap_opt = new pcap_options ;
	pcap_opt->pcap_h = pcap_open_live ( cap_options->device_name , 65536 , 1 , 0 , error_msg );
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
