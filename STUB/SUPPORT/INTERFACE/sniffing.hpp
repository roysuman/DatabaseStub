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
#include "../../STRUCTURE/rawdata_structure.hpp"
#include "../../DBLAYER/capture_packet_db.hpp"
#include "../../TCPSTUB/mainwindow.h"
#include "ipc.hpp"
#include "../DISSECTOR/proto_ldap.hpp"

#include "../../TCPSTUB/ui_mainwindow.h"
extern bool flagCapture, flagStop;
namespace snif{
	extern int successCount;
	extern std::fstream fileHandler;

	extern	std::fstream file1;
	//	static int i_line_no;
	//	 extern std::fstream file1;
	extern  struct sockaddr_in stSource;
	extern struct sockaddr_in stDest;
	extern  pcap_t * pHandle;
	extern pthread_t thread;  // to create thread
	//extern bool k_flag = true ;
	//extern int i_count_insert = 0;
    //extern void open( void );
	extern int iTcp,iUdp,iIcmp,iOthers,iIgmp,iTotal,i,j,simaphore;	
	extern void processPacket( u_char * , const pcap_pkthdr * , const u_char* );
	extern void processPacket( const u_char * , int );

	extern void writePacket( u_char * , const struct pcap_pkthdr * , const u_char * );
	//extern void processIpPacket ( u_char * , int );
	//extern void printIpPacket ( const u_char * , int );
	extern void printTcpPacket ( const u_char * , int );
	//extern void printUdpPacket ( const u_char *  , int );
	//extern void printIcmpPacket ( const u_char * , int );
	extern void printData ( const u_char * , int );
	extern void printEthernetHeader(const u_char *);
	extern void printIpHeader ( const u_char *, int );
	extern void signalCallbackHandler(int );
	extern char** giveInterface ( void );
	//start sniffing with the given interface id
        extern void * startSniffing( void *  );
        extern void  stopSniffing();
    extern void* analysisFromFile( void * );

	
	
}
#endif /* SNIFFING_HPP */
