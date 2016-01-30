/*
 * =====================================================================================
 *
 *       Filename:  captureoptions.h
 *
 *    Description:  capture options generaly set from GUI
 *
 *        Version:  1.0
 *        Created:  Wednesday 27 January 2016 08:51:24  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  SIGCONT (suman roy), email.suman.roy@gmail.com
 *   Organization:  OPEN SOURCE
 *
 * =====================================================================================
 */


/* 
 *This program is free software: you can redistribute it and/or modify
 *it under the terms of the GNU General Public License as published by
 *the Free Software Foundation, either version 3 of the License, or
 *(at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. */
#ifndef CAPTURE_OPTIONS
#define CAPTURE_OPTIONS
/* 
#ifdef __cplusplus
extern "C"{
#endif
*/
#include <sys/types.h>
#include <QList>

/* the following struct is setting--set by GUI */
typedef struct _capture_opts capture_opts;

struct _capture_opts{
	//TODO indices of interfaces to capture
//	char*                     device_name;//it must be an array to hold all user specified
	 				     //interfaces...from which they want to read data
	bool                      save_file;/* TRUE: SAVE packet in file */
	char*			  file_name; /* if need to save */
//	HRING*			  ring_buffer;/* write packet */
	void*			  ring_buffer;/* write packet */
	//TODO BELOW FUTURE USE
	bool			  stop_packet_set;/* TRUE: stop packet capture after certan packet captured */
	size_t                    stop_packet_count;/* no of packet need to capture before closing*/
	bool                      stop_byte_set; /* TRUE: stop sniffing after capturing a byte limit */
	size_t			  stop_byte_count;/* byte limit */
	bool			  stop_time_duration;/* TRUE: stop after a certain time duration */
	size_t                    time_duration;/* time duration */
	bool                      do_dissect; /* TRUE:dissect packet after capturing */
};
static capture_opts global_capture_opts;

extern bool
set_capture_options( capture_opts* cap_opts);
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  init_capture_options
 *  Description:  initialize capture options.
 * =====================================================================================
 */
extern void
init_capture_options( capture_opts* cap_opts);


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  log_capture_options
 *  Description:  print all options set.
 * =====================================================================================
 */
extern void
log_capture_options( capture_opts* cap_opts);


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  setup_interface_list
 *  Description:  setup all interface list.
 *  		 read available interface list from get_available_interface_list
 *
 * =====================================================================================
 */
extern bool
setup_interface_list( capture_opts* cap_opts);

extern bool
is_file_write_enable( capture_opts* cap_opts);
extern bool
is_dissect_enable( capture_opts* cap_opts);
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  atexit_interface_list
 *  Description:  free al resources
 * =====================================================================================
 */
extern void
atexit_interface_list( capture_opts* cap_opts);
/* 
#ifdef __cplusplus
}
#endif
*/
#endif
