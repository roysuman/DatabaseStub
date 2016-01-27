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
	interface_info *temp= malloc ( sizeof ( interface_info ) );
	temp->name = strdup ( interface_name);
	temp->description = strdup ( interface_description);
	temp->loopbak = is_loopback;
	return temp;

}

QList<interface_info*>*
get_available_interface_list( int *error, char**error_description){
	QList<interface_list*> interface_list;
	interface_info* inf_info;
	char error_buffer[PCAP_ERRBUF_SIZE];
	 pcap_if_t *alldevsp , *device;
	 if ( pcap_findalldevs( &alldevsp , error_buffer ) == -1 ){
		 /* not able to read interface list from the system */
		 *error = ERROR_GET_INTERFACE_LIST;
		 if ( error_description != NULL ){
			 strcpy( *error_description,error_buffer,PCAP_ERRBUF_SIZE);
		 }
		 return NULL;
	 }else if ( alldevsp !=NULL){
		 /*success....got interface list
		 now put each interface into the interface_list
		 */
		 for ( device = alldevsp ; device!= NULL ; device= device->next ){
			 inf_info = get_new_interface( device->name , device->description, (dev->flags & PCAP_IF_LOOPBACK)?TRUE:FALSE);
			 interface_list.append( inf_info );
		 }
		 pcap_freealldevs( alldevsp);
	 }else{ /* no interface found */
		 *error_description = NULL;
		 *error = 0;
		 return NULL;
	 }
	 return interface_list;
}

bool
start_capture_loop( capture_opts* cap_opts,struct pcap_stat* status , bool *status_know){
	

	struct timeval  up_time, curr_time;
	int err_close;
	char error_msg[MAX_MSG_LENGTH + 1];
	pcap_options *pcap_opts;

	pcap_options *pcap_opts;
	pcap_opts = malloc ( sizeof( pcap_options ) );
	pcap_opts->pcap_h = pcap_open_live ( deviceName , 65536 , 1 , 0 , error_msg );
	if ( pcap_opts->pcap_h == NULL ){
		/* error on opeing device for sniffing */
		return false;
	}
	pcap_opts->packet_received = 0;
	pcap_opts->packet_dropped = 0;
	pcap_opts->packet_flushed = 0;
	pcap_opts->error = false;


	/* setup global loop options */
	global_ld.is_alive = TRUE;
	global_ld.packet_count = 0;
	global_ld.packet_max = ( cap_opts->stop_packet_set? cap_opts->stop_packet_count: 0 );
	*status_know = false;
	
//	init_capture_stop_conditions();

	gettimrofday(&up_time,NULL);
	start_time = create_timestamp();
	do_capture( pcap_opts); 
	/*calculate capture time*/
	return true;


}

static size_t
do_capture( pcap_options *pcap_options){
	int inpcket;
	int packet_count_before;

	packet_count_before = global_ld->packet_count;
	while( global_ld.is_alive){
		inpcket = pcap_dispatch( cap_opts->pcap_h , -1 , loop_write_ringbuffer,(unsigned char*)cap_opts);
		if ( inpcket < 0 ){
			if ( inpcket == -1 ){
				cap_opts->error = TRUE;
			}
			global_ld.is_alive = FALSE;
		}

	}
	return global_ld->packet_count - packet_count_before;
}
static void
loop_write_ringbuffer ( unsigned char* pcap_opts , const struct pcap_pkthdr * pkhdr, unsigned char*data){
}

