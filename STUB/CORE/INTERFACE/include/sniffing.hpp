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
#include <boost/thread.hpp>
#include <fcntl.h>
#include "../../../STRUCTURE/include/rawdata_structure.hpp"
#include "../../../DBLAYER/capture_packet_db.hpp"
#include "../../../TCPSTUB/mainwindow.h"
#include "../../../SUPPORT/globalDatatypes.hpp"
//#include "ipc.hpp"

#include "../../DISSECTOR/include/proto.hpp"
#include "../../../TCPSTUB/ui_mainwindow.h"
extern bool flagCapture, flagStop;
namespace snif{
	extern STUB_INT successCount;
	extern std::fstream fileHandler;

	extern	std::fstream file1;
	//	static STUB_INT i_line_no;
	//	 extern std::fstream file1;
	extern  struct sockaddr_in stSource;
	extern struct sockaddr_in stDest;
	extern  pcap_t * pHandle;
	extern pthread_t thread;  // to create thread
	//extern bool k_flag = true ;
	//extern STUB_INT i_count_insert = 0;
    //extern void open( void );
	extern STUB_INT iTcp,iUdp,iIcmp,iOthers,iIgmp,iTotal,i,j,simaphore;	
	extern void processPacket( u_char * , const pcap_pkthdr * , const u_char* );
	extern void processPacket( const u_char * , STUB_INT );

	extern void writePacket(  const struct pcap_pkthdr * , const u_char * );
	//extern void processIpPacket ( u_char * , STUB_INT );
	//extern void printIpPacket ( const u_char * , STUB_INT );
	extern void printTcpPacket ( const u_char * , STUB_INT );
	//extern void printUdpPacket ( const u_char *  , STUB_INT );
	//extern void printIcmpPacket ( const u_char * , STUB_INT );
	extern void printData ( const u_char * , STUB_INT );
	extern void printEthernetHeader(const u_char *);
	extern void printIpHeader ( const u_char *);
	extern void signalCallbackHandler(STUB_INT );
	extern STUB_CHAR** giveInterface ( void );
	//start sniffing with the given STUB_INTerface id
        //extern void * startSniffing( void *  );
	extern void startSniffing( STUB_INT );

        extern void  stopSniffing( );
	extern void analysisFromFile( std::string );

	
	
}
#endif /* SNIFFING_HPP */
