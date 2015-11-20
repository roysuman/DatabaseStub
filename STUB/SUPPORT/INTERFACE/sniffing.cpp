/*
 * =====================================================================================
 *
 *       Filename:  sniffing.cpp
 *
 *    Description:  defination of header file sniffing.hpp
 *
 *        Version:  1.0
 *        Created:  Monday 23 September 2013 08:02:02  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy( 346163 )  (roy.suman@cognizant.com),
 *   Organization:  Cognizant Technological Solutions
 *
 * =====================================================================================
 */

#include "sniffing.hpp"
#include "ipc.hpp"
bool flagCapture = false , flagStop = false;
struct sockaddr_in snif::stSource;
struct sockaddr_in snif::stDest;

int snif::successCount = 0;

//globaly declaration
char ** cDevs;
int count=0;
    //Initialize static members of class RawPacketProcess.
    int snif::iTcp = 0 ;
    int snif::iUdp = 0;
    int snif::iIcmp = 0 ;
    int snif::iOthers = 0;
    int snif::iIgmp = 0;
    int snif::iTotal = 0;
    int snif::i = 0;
    int snif::j = 0;
    int snif::simaphore = 1;
    pcap_t * snif::pHandle;
    pthread_t thread;
    std::fstream snif::fileHandler;

//single handling for stoping the process

void snif::signalCallbackHandler(int i_signum){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<'\n';
	std::cout<<__FUNCTION__<<"Caught signal --"<<i_signum<<'\n';
	exit(i_signum);
}


void snif::printEthernetHeader(const u_char *ucBuffer){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<'\n';
	struct ethhdr *st_eth= ( struct ethhdr * ) ucBuffer ;
#ifdef DEBUG
	std::cout<<"\t*******Ethernet Header*******\t\n "
		<<"\n[ Destination Addreaa]:"<<":"<<std::setw(2)<<std::hex<<(int)st_eth->h_dest [ 0 ] <<":"<<std::setw( 2 )<<std::hex<<( int )st_eth->h_dest [ 1 ] <<":"<<std::setw ( 2 ) <<std::hex<< ( int )st_eth->h_dest [ 2 ] <<":"<<std::setw (  2 )<<std::hex<<( int )st_eth->h_dest [ 3 ] <<":"<<std::setw( 2 )<<std::hex<<( int )st_eth->h_dest [ 4 ] <<":"<<std::setw ( 2 )<<std::hex<<( int )st_eth->h_dest [ 5 ]<<'\n'
		<<"\n[Source address ]:"<<":"<<std::setw( 2 )<<std::hex<<( int)st_eth->h_source [ 0 ] <<":"<<std::setw( 2 ) <<std::hex<<( int )st_eth->h_source [ 1 ] <<":"<<std::setw ( 2 )<<std::hex<<( int )st_eth->h_source [ 2 ] <<":"<<std::setw ( 2 ) <<std::hex<<( int ) st_eth ->h_source [ 3 ] <<":"<<std::setw( 2 ) <<std::hex<<( int ) st_eth->h_source [ 4 ] <<":"<<std::setw( 2 )<<std::hex<<( int ) st_eth->h_source [ 5 ] <<'\n'
		<<"\n[Protocol]"<< ( unsigned short )st_eth->h_proto<<std::endl;
#endif
}

//functio that will write the capture packet into a file
void snif::writePacket( u_char *ucArgs , const struct pcap_pkthdr* pHandler , const u_char *ucBuffer){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
#ifdef DEBUG
	std::cout<<"erite packet:"<<pHandler->len<<'\n';
	std::cerr<<"length:"<<( int )pHandler->len<<'\n';
#endif
	snif::fileHandler.write ( reinterpret_cast<const char*> ( &pHandler->len) , sizeof ( int ) );
	snif::fileHandler.write( reinterpret_cast<const char*> ( &ucBuffer) , pHandler->len);
}


//modify
void snif:: processPacket(  u_char * uc_args ,const pcap_pkthdr *p_header , const u_char * ucBuffer ){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<'\n';
	int iSize=p_header->len;
	//Get IP header part of this packet , excluding the ethernet header
	struct iphdr *stIpHeader= ( struct iphdr * ) ( ucBuffer + sizeof ( struct ethhdr ) );
	++ iTotal ;
	switch ( stIpHeader->protocol ) // check the protocol and take action depending on protocol
	{
		case 1: //ICMP protocol
			++iIcmp;
			break;
			
		case 2: // IGMP protocol
			++iIgmp;
			break;
			
		case 6: //TCP protocol , this protocol we need to sniff for database port
			snif::successCount ++;
			++iTcp;
			snif::printTcpPacket ( ucBuffer , iSize ) ;
			break;
			
		case 17: // UDP protocol
			++ iUdp;
			break;
			
		default: // some other protocol like ARP etc..
			++iOthers;
			break;
			
	}//end of switch
	std::cout<<"\nTCP\t:"<<iTcp<<"\t UDP\t: "<<iUdp<<"\tICMP\t:"<<iIcmp<<"\tGMP\t:"<<iIgmp<<"\tOthers\t:"<<iOthers<<"\tTotal\t:"<<iTotal<<'\n';
	return ;
	
}

// to print tcp pack info
void snif::printTcpPacket( const u_char *ucBuffer , int iSize ){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<'\n';
	unsigned short usIphdrlen;
	const u_char *data;
	struct iphdr *stIpHeader= ( struct iphdr * ) ( ucBuffer + sizeof ( struct ethhdr ) );
	usIphdrlen = stIpHeader->ihl * 4 ;
	struct tcphdr *stTcpHeader = ( struct tcphdr * ) ( ucBuffer  + usIphdrlen +  sizeof ( struct ethhdr ) );
	//data
	data = (const u_char *)((unsigned char *)stTcpHeader + (stTcpHeader->doff * 4));
	int headerSize= sizeof ( struct ethhdr ) + usIphdrlen + ( stTcpHeader->doff * 4 );
	if ( ( ntohs ( stTcpHeader->source)  == 3306 ) | ( ntohs ( stTcpHeader->dest ) == 3306 )  | ( ntohs ( stTcpHeader->dest ) == 389 )| ( ntohs ( stTcpHeader->source ) == 389 ) ) {
		try{
		//create the instance of raw data
		rawDataStruct *rawData;
		try {
			rawData = new rawDataStruct();
		}
		catch ( std::bad_alloc &ba ){
			std::cerr<<__FUNCTION__<<"Exception:"<<ba.what() <<'\n';
		}
		rawData->sourcePort = ntohs( stTcpHeader->source );
		rawData->destinationPort = ntohs ( stTcpHeader->dest );
		rawData->sequenceNumber = ntohl ( stTcpHeader->seq ) ;
		rawData->acknowledgeNumber=ntohl ( stTcpHeader->ack_seq ) ;
		rawData->length = iSize - headerSize ;
		( ( unsigned int )stTcpHeader->psh ) == 1 ? rawData->tcpFlag.PSH = true :  rawData->tcpFlag.PSH = false ;
		( ( unsigned int ) stTcpHeader->ack ) == 1 ? rawData->tcpFlag.ACK = true  : rawData->tcpFlag.ACK = false ;
		if( ( iSize - headerSize) > 0 )
		      	rawData->data = ucBuffer + headerSize;
		( ( unsigned int )stTcpHeader->syn ) == 1 ? rawData->tcpFlag.SYN = 1 : rawData->tcpFlag.SYN = 0;
		(  ( unsigned int ) stTcpHeader->fin ) ==  1 ? rawData->tcpFlag.FIN = true : rawData->tcpFlag.FIN = false;
#ifdef DEBUG
		std::cout<<"[PSH flag]: = "<<rawData->tcpFlag.PSH<<'\n'
			<<"[source port]: "<<rawData->sourcePort<<'\n'
			<<"[destination port]: "<<rawData->destinationPort<<'\n'
			<<"[sequence number]:"<<rawData->sequenceNumber<<'\n'
			<<"[Acknowledge number]:"<<rawData->acknowledgeNumber<<'\n'
			<<"[Acknowledge flag]:"<<rawData->tcpFlag.ACK<<'\n'
			<<"[SYN flag]:"<<rawData->tcpFlag.SYN<<'\n'
			<<"[FIN flag]:"<<rawData->tcpFlag.FIN<<'\n'
			<<"[Size is]:"<<iSize - headerSize <<std::endl;
#endif
		//have to write a buffer handler.(object pl).
		captureDb::StoreRawPacket pHandler;
		pHandler.packetHandler( rawData );
	
//			delete []rawData->data;
			delete rawData;
	}
		
		catch ( std::exception &ea ){
			std::cerr<<__FUNCTION__<<"Exception:"<<ea.what()<<'\n';
			exit ( 1 );
		}
		return ;
		
	}
	
}
//print ip header information
void snif::printIpHeader ( const u_char *ucBuffer , int iSize ){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<'\n';
	snif::printEthernetHeader ( ucBuffer  );
	// unsigned short usIphdrlen ;
	struct iphdr  * stIpHeader = ( struct iphdr * ) ( ucBuffer + sizeof ( struct ethhdr ) );
	// usIphdrlen =stIpHeader->ihl * 4 ;
	memset ( &stSource , 0 , sizeof ( stSource ) );
	stSource.sin_addr.s_addr = stIpHeader->saddr ;
	memset ( &stDest , 0 , sizeof ( stDest ) );
	stDest.sin_addr.s_addr = stIpHeader->daddr;
	char s[20];
	char s2[20];
	inet_ntop(AF_INET, &(stSource.sin_addr), s, 100);
	inet_ntop(AF_INET, &(stDest.sin_addr), s2, 100);
#ifdef DEBUG
	std::cout<<"\n*****IP HEADER****** \n"
		<<"\n[IP Version]:"<<( unsigned int ) stIpHeader->version
		<<"[IP Header Length]:"<<( unsigned int ) stIpHeader->ihl <<"DWORDS or "<< ( ( unsigned int ) ( stIpHeader->ihl ) ) * 4 <<"Bytes"
		<<"\n[Type of service]:"<<( unsigned int ) stIpHeader->tos
		<<"\n[IP Total length]"<< ntohs ( stIpHeader->tot_len ) <<"Bytes( size of packets ) "
		<<"\n[Identification]"<<ntohs ( stIpHeader->id ) 
		<<"\n[TTL]"<<( unsigned int ) stIpHeader->ttl
		<<"\n[Protocol]"<< ( unsigned int ) stIpHeader->protocol
		<<"\n[Checksum]"<<ntohs ( stIpHeader->check )
		<<"\n[ Source Ip]"<<s
		<<"\n[ Destination Ip]"<<s2<<std::endl;
#endif
}
void snif::printData ( const u_char *ucData , int iSize ) {
	std::cout<<"FUNCTION:"<<__FUNCTION__<<'\n';
	for ( int i=0 ; i < iSize ; ++ i ){
		if ( i!= 0 && i % 16 == 0 ){ //if one line of hex print os complete.....
			std::cout<<"        ";
			for ( int j= i - 16 ; j < i ; ++ j ){
				if ( ucData [ j ] >=32 && ucData [ j ] <= 128 )
					std::cout<<( unsigned char ) ucData [ j ] ;//if it's a number or alphabet
				else
					std::cout<<".";// else print a dot
				
			}
			std::cout<<std::endl;
			
		}
		if ( i % 16 == 0 ) std::cout<<"  \n";
		std::cout<<std::hex<<( unsigned int ) ucData [ i ] ;
		if ( i == iSize - 1 ){ //print the last space
			for ( int j= 0 ; j < 15 - i % 16 ; ++ j )
				std::cout<<"   ";//extra space
			std::cout<<"       ";
			for ( int j= i - i % 16 ; j <=i ; ++ j){
				if ( ucData [ j ] >= 32 && ucData [ j ] <=128 )
					std::cout<<( unsigned char ) ucData [ j ] ;
				else
					std::cout<<".";
				
			}
			std::cout<<std::endl;
			
		}
		
	}
	
}
char ** snif::giveInterface( void ){
    char errorBuffer[ 100 ] ;
        
  //  snif::open();
    pcap_if_t *p_alldevsp , *p_device ;
    cDevs=new char*[100];
    for (int i=0; i<100; i++)
        {
            cDevs[ i ] = new char[100];
			
        }


    int i_count=1 ;
    //Get available devices
    if ( pcap_findalldevs ( &p_alldevsp , errorBuffer ) ){
        std::cerr<<"Error finding devices \t "<<errorBuffer<<std::endl;
        exit (EXIT_FAILURE);
    }
    std::cout<<"\nSearching Done \n";
    //Print the available devices
    std::cout<<"Available devices are \n";
    for ( p_device=p_alldevsp ; p_device != NULL ; p_device=p_device->next ){
        if ( p_device->name != NULL )
            strcpy( cDevs[ i_count ] , p_device->name );
        i_count ++;
        }
    strcpy ( cDevs [i_count ] , "NULL" );

    return cDevs;
}

void * snif::startSniffing ( void * value ){
	//snif::fileHandler.open("temp.bin", std::ios::in |std::ios::out | std::ios::app | std::ios::binary);
	flagCapture = true;
	flagStop = false;
	int * id = ( int * ) value;
	char *deviceName ;
	char errorBuffer[ 100 ] ;
	deviceName=cDevs [ *id ]; // take the device name to sniff
#ifdef DEBUG
	std::cout<<"\nOpening device for sniffing \t"<<deviceName<<std::endl;
#endif

	if ( !( pHandle= pcap_open_live ( deviceName , 65536 , 1 , 0 , errorBuffer ) ) ){
		std::cerr<<"Could't open device :\t"<<deviceName <<" : "<<errorBuffer <<'\n';
		exit (EXIT_FAILURE);
		
	}
	//put the device for sniffing loop
	signal(SIGINT, snif::signalCallbackHandler);
	/*
      create a child thread and give access to the following function
      */

    pcap_loop ( pHandle , -1 , snif::processPacket , NULL );
}

void snif::stopSniffing(){
	flagCapture = false;
	while ( flagStop );
	std::cout<<"FUNCTION"<<__FUNCTION__<<'\n';
	try {
		pcap_close( pHandle );
		flagStop = true;
	}
	catch ( std::exception &e ){
		std::cerr<<"Exception:"<<e.what()<<'\n';
	}
	// snif::fileHandler.close();
	//std::cout.flush();
	//snif::fileHandler.flush();
//	snif::fileHandler.close();
}

void * snif::analysisFromFile ( void *value ){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	pcap_t *pcap;
	const unsigned char *packet;
	char errbuf[PCAP_ERRBUF_SIZE];
	struct pcap_pkthdr header;
	char *fileName = (char*)value;
	pcap = pcap_open_offline( fileName , errbuf);
	if (pcap == NULL){
		fprintf(stderr, "error reading pcap file: %s\n", errbuf);
		exit(1);
		}
	while ( ( packet = pcap_next(pcap, &header ) ) != NULL ){
		
		snif::processPacket( packet,  header.len );//caplen
	}

}

void snif::processPacket ( const unsigned char* ucBuffer , int length ){
	struct iphdr *stIph= ( struct iphdr * ) ( ucBuffer + sizeof ( struct ethhdr ) );
	++ iTotal ;
	switch ( stIph->protocol ){ // check the protocol and take action depending on protocol
		case 1: //ICMP protocol
                ++iIcmp;
                break;
				
            case 2: // IGMP protocol
                ++iIgmp;
                break;
				
            case 6: //TCP protocol , this protocol we need to sniff for database port
                ++iTcp;
                snif::printTcpPacket ( ucBuffer , length ) ;
                break;
				
            case 17: // UDP protocol
                ++ iUdp;
                break;
				
            default: // some other protocol like ARP etc..
                ++iOthers;
                break;
				
        }//end of switch
    std::cout<<"\nTCP\t:"<<iTcp<<"\t UDP\t: "<<iUdp<<"\tICMP\t:"<<iIcmp<<"\tGMP\t:"<<iIgmp<<"\tOthers\t:"<<iOthers<<"\tTotal\t:"<<iTotal<<'\n';
}
	
