
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



#ifndef SNIFFING_H_
#define SNIFFING_H_
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
#include "buffer.h"
#include "../common/vserver_datatype.h"
//global instance for databaseHandler.
#define tflag -3
extern  VS_BOOL __flagCapture__, __flagStop__;
class Snif{
	public:
		explicit Snif( Buffer &buffer_handler__):buffer_handler(buffer_handler__){}
		static VS_VOID* analysis_from_file( VS_VOID *);
		VS_VOID set_filter( std::string const file_name_, std::string const ip_ , VS_UINT32 const port);
	private:
		VS_BOOL seq_init;
		VS_UINT32    delta;
		VS_INT32 success_count;
		VS_UINT64 count_tcp_packet,count_udp_packet,count_icmp_packet,count_other_packet,count_igmp_packet,count_total_packet;
		VS_BOOL process_packet( const VS_UINT8 * , struct pcap_pkthdr );
		VS_BOOL process_tcp_packet ( const VS_UINT8 * , struct pcap_pkthdr );
		VS_VOID dump_data ( const VS_UINT8 * , VS_UINT64 );
		VS_VOID signal_callback_handker( VS_INT32  );
		Buffer buffer_handler;
		static std::string dump_file_name;
		static std::string filter_ip;
		static VS_UINT32    filter_port;

};
#endif /* SNIFFING_HPP */
