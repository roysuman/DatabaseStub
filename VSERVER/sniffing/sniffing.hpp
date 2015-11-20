
/*
 * =====================================================================================
 *
 *       Filename:  sniffing.hpp
 *
 *    Description:  alalyse tcpdump file
 *        Version:  1.0
 *        Created:  ThursDay 30 April 2015 08:02:02  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy  (email.suman.roy@gmail.com),
 *   Organization:  Cognizant Technological SOlutions
 *
 * =====================================================================================
 */



#ifndef SNIFFING_HPP_
#define SNIFFING_HPP_
#include<pcap.h>
#include<iostream>
#include<stdlib.h>
#include<stdint.h>
#include <stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<net/ethernet.h>
#include<netinet/ip_icmp.h>
#include<netinet/udp.h>   //Provides declarations for udp header
#include<netinet/tcp.h>   //Provides declarations for tcp header
#include<netinet/ip.h>    //Provides declarations for ip header
#include<fstream>
#include<signal.h>
#include<iomanip>
#include <pthread.h>
#include<iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sstream>
#include<thread>
#include "packetDataStructure.hpp"
#include "buffer.hpp"
#include "init.hpp"
//global instance for databaseHandler.
#define tflag -3
 bool __flagCapture__, __flagStop__;
class Snif{
	public:
		explicit Snif( Buffer &buffer_handler__):buffer_handler(buffer_handler__);
		static void* analysis_from_file( void *);
		void set_filter( std::string const file_name_, std::string const ip_ , uint32_t const port);
	private:
		bool seq_init;
		uint32_t    delta;
		int success_count;
		size_t count_tcp_packet,count_udp_packet,count_icmp_packet,count_other_packet,count_igmp_packet,count_total_packet;
		bool process_packet( const u_char * , struct pcap_pkthdr );
		bool process_tcp_packet ( const u_char * , struct pcap_pkthdr );
		void dump_data ( const u_char * , size_t );
		void signal_callback_handker( int  );
		const BUffer buffer_handler;
		static std::string dump_file_name;
		static std::string filter_ip;
		static uint32_t    filter_port;

};
#endif /* SNIFFING_HPP */
