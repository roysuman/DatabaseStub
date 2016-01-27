/*
 * =====================================================================================
 *
 *       Filename:  captureoptions.c
 *
 *    Description:  set up all capture options.
 *
 *        Version:  1.0
 *        Created:  Wednesday 27 January 2016 09:31:36  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  SIGCONT (suman roy), email.suman.roy@gmail.com
 *   Organization:  OPEN SOURCE
 *
 * =====================================================================================
 */

bool
init_capture_options( capture_opts* cap_opts){
	if ( cap_opts == NULL ) return false;
	if ( cap_opts->device_name != NULL){
		global_capture_opts->device_name = cap_opts->device_name;
	}else{
		global_capture_opts.device_name = NULL;
	}
	if ( *cap_opts != NULL ){
		global_capture_opts.file_name = cap_opts->file_name;
	}else{
		global_capture_opts.file_name = NULL;
	}
	if ( cap_opts->ring_buffer != NULL){
		global_capture_opts.ring_buffer = cap_opts->ring_buffer;
	}else {
		global_capture_opts.ring_buffer = NULL;
	}
	global_capture_opts.stop_packet_set = cap_opts->stop_packet_set;
	global_capture_opts.stop_packet_count = cap_opts->stop_packet_count;
	global_capture_opts.stop_byte_set = cap_opts->stop_byte_set;
	global_capture_opts.stop_byte_count = cap_opts->stop_byte_count;
	global_capture_opts.stop_time_duration = cap_opts->stop_time_duration;
	global_capture_opts.time_duration = cap_opts->time_duration;
	global_capture_opts.do_dissect = cap_opts->do_dissect;
	return;

}

void
init_capture_options( capture_opts* cap_opts){
	cap_opts->device_name = NULL;
	cap_opts->save_file = false;
	cap_opts->file_name = NULL;
	cap_opts->ring_buffer = NULL;
	cap_opts->stop_packet_set = false;
	cap_opts->stop_byte_set = false;
	cap_opts->stop_time_duration = false;
	cap_opts->do_dissect = false;
	return;
}

void
log_capture_options( cap_opts *cap_opts){
	//TODO
	return;
}

bool
setup_interface_list( capture_opts* cap_opts){
	//TODO
	return true;
}
