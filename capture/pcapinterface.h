/*
 * =====================================================================================
 *
 *       Filename:  pcapinterface.h
 *
 *       Description:  
 *
 *       Version:  1.0
 *       Created:  Wednesday 27 January 2016 03:14:18  IST
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

#ifndef PCAP_INTERFACE_H
#define PCAP_INTERFACE_H

#include <pcap.h>
#include <iostream>
#include<vector>
#include<QDebug>
#include <sys/types.h>

#include "core/api/ringbuffer.h"
#define ERROR_GET_INTERFACE_LIST 1
#define MAX_MSG_LENGTH 65535
#define READ_TIMEOUT 250
#define ERRBUFF_SIZE 512
/* there might by situation when we want to read packet
 * from all interfaces. */

/* before starting capturing...make ready the environment
 * write a method init_interface()..which will take cap_opts
 * and create an array of pcap_options ..after opening interfaces
 *
 * Then at start_capture_loop...with a loop you start reading each interface
 * prediocally...by giving a fixed packet read count and time limit
 *
 * create pointer of pcap_opts array..global..then fetch ine by one ..
 * but for now I am considering only one interface*/


/* the following struct is setting--set by GUI */
typedef struct _capture_opts capture_opts;

struct _capture_opts{
	//TODO indices of interfaces to capture
	std::string                     device_name;//it must be an array to hold all user specified
	 				     //interfaces...from which they want to read data
	bool                      save_file;/* TRUE: SAVE packet in file */
	char*			  file_name; /* if need to save */
	void*			  ring_buffer_handle;/* write packet */
	//TODO BELOW FUTURE USE
	bool			  stop_packet_set;/* TRUE: stop packet capture after certan packet captured */
	size_t                    stop_packet_count;/* no of packet need to capture before closing*/
	bool                      stop_byte_set; /* TRUE: stop sniffing after capturing a byte limit */
	size_t			  stop_byte_count;/* byte limit */
	bool			  stop_time_duration;/* TRUE: stop after a certain time duration */
	size_t                    time_duration;/* time duration */
	bool                      do_dissect; /* TRUE:dissect packet after capturing */
};


/* keep book-keeping info of all available 
 * interfaces of current system */
typedef struct _interface_info interface_info;
struct _interface_info{
	std::string name;
	std::string description;
	bool loopback;
	bool promiscious_mode;
	bool active_snaplen;
	int  snaplen;
	int timeout;
};


/* the following struct keep book-keeping info for each
 * individual interface */
typedef struct _pcap_options pcap_options;
struct _pcap_options{
	size_t          packet_received;
	size_t          packet_dropped;
	size_t          packet_flushed;
	pcap_t*         pcap_h;
	bool            error;
	capture_opts*   cap_opts;
//	int      interface_id;
};

/* the following struct keep book-keeping info for all interfaces */
typedef struct _loop_data loop_data;
struct _loop_data{
	bool      is_alive;/* if true continue capturing */
	int       err;/* if 0 no error..else error number */
	size_t    packet_count;/* number packet received till now. */
	size_t    packet_max;/* maximum packet allowed..if o then unlimited */
	size_t    byte_writen;

};


static std::vector<interface_info*> global_available_interfaces;

class InterfaceHandler{
	public:
		InterfaceHandler( bool choice=false );
        virtual ~InterfaceHandler( void ){}
	private:

		unsigned long start_time;

		pcap_t* open_capture_device( interface_info * inter_info,
				char(*errbuff)[ERRBUFF_SIZE]);
		size_t do_capture( pcap_options *cap_options);
		void setup_interface_list( void );
		interface_info* get_interface_info( std::string name);

	public:
		static int error;
		static char* error_description;
		static loop_data global_ld;
		static bool avail_interface_list;
		static std::vector<interface_info*> interface_list;
		static void  loop_write_ringbuffer( unsigned char* cap_options,
				const struct pcap_pkthdr* pkhdr,
				const unsigned char* data);
		static std::vector<interface_info*>
			get_available_interface_list( int *error_ , char* error_description_);


		static interface_info*
			get_new_interface( const char* interface_name,
					const char* interface_description,
					bool is_loopback=false);
		bool start_capture_loop( capture_opts* cap_options,
				char* error_msg_);
		void stop_capture( void );
				 
};

#endif
