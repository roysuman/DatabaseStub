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

/* 
#ifdef __cplusplus
extern "C"{
#endif
*/
#include <pcap.h>
#include <iostream>
#include<vector>
#include<QDebug>
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



/* keep book-keeping info of all available 
 * interfaces of current system */
typedef struct _interface_info interface_info;
struct _interface_info{
	char* name;
	char* description;
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
	size_t    packet_received;
	size_t    packet_dropped;
	size_t    packet_flushed;
	pcap_t*  pcap_h;
	bool     error;
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
extern loop_data global_ld;

extern unsigned long start_time;
static std::vector<interface_info> global_available_interfaces;

extern void
init_global_interface_list( std::vector<interface_info>& int_info);
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  get_available_interface_list
 *  Description:  returns all available interface list...
 * =====================================================================================
 */
extern std::vector<interface_info*>
get_available_interface_list( int *error, char *error_description);


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  start_capture_loop
 *  Description:  start the capturing...is visible to outer world
 * =====================================================================================
 */
extern bool
start_capture_loop( struct pcap_stat* status);
/* 
#ifdef __cplusplus
}
#endif
*/
#endif
