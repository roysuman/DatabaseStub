/*
 * =====================================================================================
 *
 *       Filename:  ringbuffertest.cpp
 *
 *    Description:  test the ring buffer api
 *
 *        Version:  1.0
 *        Created:  Sunday 31 January 2016 12:35:12  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  SIGCONT (suman roy), email.suman.roy@gmail.com
 *   Organization:  OPEN SOURCE
 *
 * =====================================================================================
 */

#include "../core/api/ringbuffer.h"
#include "../core/api/ringbuffer.cpp"

#include <iostream>
int main(){
	std::string buffer_name = "test_ring_buffer";
	RingBufferManager::init_new_ring_buffer(  buffer_name, 1024 , 16);
	RingBufferManager ii;
	ii.print_info();
	return 0;
}
