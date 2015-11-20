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
 *         Author:  Suman Roy  (email.suman.roy@gmail.com),
 *   Organization:  SELF
 *
 * =====================================================================================
 */
#include "../include/sniffing.hpp"
#include "../include/ipc.hpp"

bool flagCapture = false , flagStop = false;
struct sockaddr_in snif::stSource;
struct sockaddr_in snif::stDest;

STUB_INT snif::successCount = 0;

//globaly declaration
STUB_CHAR ** cDevs;
STUB_INT count=0;
    //Initialize static members of class RawPacketProcess.
    STUB_INT snif::iTcp = 0 ;
    STUB_INT snif::iUdp = 0;
    STUB_INT snif::iIcmp = 0 ;
    STUB_INT snif::iOthers = 0;
    STUB_INT snif::iIgmp = 0;
    STUB_INT snif::iTotal = 0;
    STUB_INT snif::i = 0;
    STUB_INT snif::j = 0;
    STUB_INT snif::simaphore = 1;
    pcap_t * snif::pHandle;
    pthread_t thread;
    std::fstream snif::fileHandler;


    /* 
     * ===  FUNCTION  ======================================================================
     *         Name:  signalCallbackHandler
     *  Description:  signal handling for stoping the process
     * =====================================================================================
     */

void snif::signalCallbackHandler(STUB_INT i_signum){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"] Signal received-"
		<<i_signum<<'\n';
	exit(i_signum);
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  printEthernetHeader
 *  Description:  print details of ethernet information 
 * =====================================================================================
 */

void snif::printEthernetHeader(const u_char *ucBuffer){

#ifdef DEBUG
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";


	struct ethhdr    *st_eth;

	st_eth = ( struct ethhdr * ) ucBuffer ;
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"
		<<"\t*******Ethernet Header*******\t\n "
		<<"\n[ Destination Addreaa]:"<<":"<<

		std::setw(2)<<std::hex<<(STUB_INT)st_eth->h_dest [ 0 ] <<":"<<
		std::setw( 2 )<<std::hex<<( STUB_INT )st_eth->h_dest [ 1 ] <<":"
		<<std::setw ( 2 ) <<std::hex<< ( STUB_INT )st_eth->h_dest [ 2 ] <<":"
		<<std::setw (  2 )<<std::hex<<( STUB_INT )st_eth->h_dest [ 3 ] <<":"
		<<std::setw( 2 )<<std::hex<<( STUB_INT )st_eth->h_dest [ 4 ] <<":"
		<<std::setw ( 2 )<<std::hex<<( STUB_INT )st_eth->h_dest [ 5 ]<<'\n'
		<<"\n[Source address ]:"<<":"<<
		std::setw( 2 )<<std::hex<<( STUB_INT)st_eth->h_source [ 0 ] <<":"
		<<std::setw( 2 ) <<std::hex<<( STUB_INT )st_eth->h_source [ 1 ] <<":"
		<<std::setw ( 2 )<<std::hex<<( STUB_INT )st_eth->h_source [ 2 ] <<":"
		<<std::setw ( 2 ) <<std::hex<<( STUB_INT ) st_eth ->h_source [ 3 ] <<":"
		<<std::setw( 2 ) <<std::hex<<( STUB_INT ) st_eth->h_source [ 4 ] <<":"
		<<std::setw( 2 )<<std::hex<<( STUB_INT ) st_eth->h_source [ 5 ] <<'\n'
		<<"\n[Protocol]"<< ( unsigned short )st_eth->h_proto<<std::endl;
#endif
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  writePacket
 *  Description:  write the captured packets into a file.
 * =====================================================================================
 */
//void snif::writePacket( u_char *ucArgs , const struct pcap_pkthdr* pHandler , 
//		const u_char *ucBuffer){
void snif::writePacket( const struct pcap_pkthdr *pHandler , const u_char *ucBuffer){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

#ifdef DEBUG
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"erite packet:"
		<<pHandler->len<<'\n';
	std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"length:"
		<<( STUB_INT )pHandler->len<<'\n';
#endif
	snif::fileHandler.write ( reinterpret_cast<const STUB_CHAR*> ( &pHandler->len) ,
		       	sizeof ( STUB_INT ) );
	snif::fileHandler.write( reinterpret_cast<const STUB_CHAR*> ( &ucBuffer) , 
			pHandler->len);
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  processPacket
 *  Description:  after capturing a packet from the network layer, this method take care
 *                further processes.
 * =====================================================================================
 */

void snif::processPacket(  u_char * uc_args ,const pcap_pkthdr *p_header ,
	       	const u_char * ucBuffer ){

	std::cout<<"File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	STUB_INT       iSize;
	struct iphdr   *stIpHeader;

	iSize = p_header->len;

	/*-----------------------------------------------------------------------------
	 *  get the ip header part of this incoming packet, excluding the ethernet
	 *  header
	 *-----------------------------------------------------------------------------*/
	stIpHeader= ( struct iphdr * ) ( ucBuffer + sizeof ( struct ethhdr ) );
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
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<
		"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"\nTCP\t:"<<iTcp<<"\t UDP\t: "
		<<iUdp<<"\tICMP\t:"<<iIcmp<<"\tGMP\t:"<<iIgmp<<"\tOthers\t:"
		<<iOthers<<"\tTotal\t:"<<iTotal<<'\n';
	return ;
	
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  printTcpPacket
 *  Description:  print tcp packets dield info
 * =====================================================================================
 */

void snif::printTcpPacket( const u_char *ucBuffer , STUB_INT iSize ){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	rawDataStruct                *rawData;
	captureDb::StoreRawPacket    pHandler;
	proto::_ports::iterator      it1 , it2;
	unsigned short               usIphdrlen;
	STUB_INT                     headerSize;
	struct iphdr                 *stIpHeader;

	stIpHeader = ( struct iphdr * ) 
		( ucBuffer + sizeof ( struct ethhdr ) );
	usIphdrlen = stIpHeader->ihl * 4 ;
	struct tcphdr *stTcpHeader = ( struct tcphdr * ) 
		( ucBuffer  + usIphdrlen +  sizeof ( struct ethhdr ) );
	headerSize= sizeof ( struct ethhdr ) + usIphdrlen + 
		( stTcpHeader->doff * 4 );
//	if ( ( ntohs ( stTcpHeader->source)  == 3306 ) | ( ntohs ( stTcpHeader->dest ) == 3306 )  | ( ntohs ( stTcpHeader->dest ) == 389 )| ( ntohs ( stTcpHeader->source ) == 389 ) ) {
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"PORTS\n";
	for ( it1 = proto::ports.begin() ; it1!= proto::ports.end(); ++it1 )
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
			"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
			<<"]"<<"["<<it1->first<<"]["<<it1->second<<'\n';
	
	if(  ( ( it1 = proto::ports.find( ntohs ( stTcpHeader->source ) ) ) 
				!= proto::ports.end() ) || 
			( ( it2 = proto::ports.find( ntohs ( stTcpHeader->dest ) ))
			  != proto::ports.end() )) {
		try{
			
		//create the instance of raw data
		try {
			rawData = new rawDataStruct();
		}
		catch ( std::bad_alloc &ba ){
			std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
				<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<
				__TIME__<<"]"<<"Function name[ Exception:"<<ba.what() <<'\n';
		}
		it1 == proto::ports.end() ? ( rawData->protocolName = it2->second ) :
		       	(rawData->protocolName = it1->second );
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
			"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<
			__TIME__<<"]"<<"PROTOCOL ADDED"<<rawData->protocolName<<'\n';

		

		rawData->sourcePort = ntohs( stTcpHeader->source );
		rawData->destinationPort = ntohs ( stTcpHeader->dest );
		rawData->sequenceNumber = ntohl ( stTcpHeader->seq ) ;
		rawData->acknowledgeNumber=ntohl ( stTcpHeader->ack_seq ) ;
		rawData->length =  (iSize - headerSize )  ;
		( ( unsigned STUB_INT )stTcpHeader->psh ) == 1 ? rawData->tcpFlag.PSH = true 
			:  rawData->tcpFlag.PSH = false ;
		( ( unsigned STUB_INT ) stTcpHeader->ack ) == 1 ? rawData->tcpFlag.ACK = true  
			: rawData->tcpFlag.ACK = false ;
		if( ( iSize - headerSize) > 0 ){
			rawData->data = new  u_char [ rawData->length];
			memcpy ( ( u_char* ) ( rawData->data + 0 ) , ( u_char * )
				       	( ucBuffer + headerSize ) , rawData->length );
			
			 
		}

		( ( unsigned STUB_INT )stTcpHeader->syn ) == 1 ? rawData->tcpFlag.SYN = 1 :
		       	rawData->tcpFlag.SYN = 0;
		(  ( unsigned STUB_INT ) stTcpHeader->fin ) ==  1 ? rawData->tcpFlag.FIN = 
			true : rawData->tcpFlag.FIN = false;
		/*
for ( STUB_INT i = 0 ; i < rawData->length ; ++i )
std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<rawData->data[i];
std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<'\n';
*/
#ifdef DEBUG
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
			"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
			<<"]"<<"[PSH flag]: = "<<rawData->tcpFlag.PSH<<'\n'
			<<"[source port]: "<<rawData->sourcePort<<'\n'
			<<"[destination port]: "<<rawData->destinationPort<<'\n'
			<<"[sequence number]:"<<(STUB_INT)rawData->sequenceNumber<<'\n'
			<<"[Acknowledge number]:"<<(STUB_INT)rawData->acknowledgeNumber<<'\n'
			<<"[Acknowledge flag]:"<<rawData->tcpFlag.ACK<<'\n'
			<<"[SYN flag]:"<<rawData->tcpFlag.SYN<<'\n'
			<<"[FIN flag]:"<<rawData->tcpFlag.FIN<<'\n'
			<<"[Size is]:"<<iSize - headerSize <<std::endl;
#endif
		//have to write a buffer handler.(object pl).
		pHandler.packetHandler( rawData );
	
			delete []rawData->data;
			delete rawData;
	}
		
		catch ( std::exception &ea ){
			std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] Exception:"<<ea.what()<<'\n';
			exit ( 1 );
		}
		return ;
		
	}
	
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  printIpHeader
 *  Description:  print IP header info
 * =====================================================================================
 */
void snif::printIpHeader ( const u_char *ucBuffer  ){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";
	STUB_CHAR       s[20];
	STUB_CHAR       s2[20];
	struct iphdr    *stIpHeader;

	snif::printEthernetHeader ( ucBuffer  );
	// unsigned short usIphdrlen ;
	stIpHeader = ( struct iphdr * ) ( ucBuffer + 
			sizeof ( struct ethhdr ) );
	// usIphdrlen =stIpHeader->ihl * 4 ;
	memset ( &stSource , 0 , sizeof ( stSource ) );
	stSource.sin_addr.s_addr = stIpHeader->saddr ;
	memset ( &stDest , 0 , sizeof ( stDest ) );
	stDest.sin_addr.s_addr = stIpHeader->daddr;
	inet_ntop(AF_INET, &(stSource.sin_addr), s, 100);
	inet_ntop(AF_INET, &(stDest.sin_addr), s2, 100);
#ifdef DEBUG
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		<<"]\n*****IP HEADER****** \n"
		<<"\n[IP Version]:"<<( unsigned STUB_INT ) stIpHeader->version
		<<"[IP Header Length]:"<<( unsigned STUB_INT ) stIpHeader->ihl
	       	<<"DWORDS or "<< ( ( unsigned STUB_INT ) ( stIpHeader->ihl ) ) * 4 
		<<"Bytes"
		<<"\n[Type of service]:"<<( unsigned STUB_INT ) stIpHeader->tos
		<<"\n[IP Total length]"<< ntohs ( stIpHeader->tot_len ) 
		<<"Bytes( size of packets ) "
		<<"\n[Identification]"<<ntohs ( stIpHeader->id ) 
		<<"\n[TTL]"<<( unsigned STUB_INT ) stIpHeader->ttl
		<<"\n[Protocol]"<< ( unsigned STUB_INT ) stIpHeader->protocol
		<<"\n[Checksum]"<<ntohs ( stIpHeader->check )
		<<"\n[ Source Ip]"<<s
		<<"\n[ Destination Ip]"<<s2<<std::endl;
#endif
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  printData
 *  Description:  print char by char
 * =====================================================================================
 */
void snif::printData ( const u_char *ucData , STUB_INT iSize ) {

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	for ( STUB_INT i=0 ; i < iSize ; ++ i ){
		if ( i!= 0 && i % 16 == 0 ){ //if one line of hex print os complete.....
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
				<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
				<<__TIME__<<"]"<<"        ";
			for ( STUB_INT j= i - 16 ; j < i ; ++ j ){
				if ( ucData [ j ] >=32 && ucData [ j ] <= 128 )
					std::cout<<" File Name ["<<__FILE__<<" ] Function [ "
						<<__FUNCTION__<<"] Line ["<<__LINE__<<"] Date\
						Time ["<<__DATE__<<"_"<<__TIME__<<"]"<<
						( unsigned STUB_CHAR ) ucData [ j ] ;//if it's a number or alphabet
				else
					std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<
						__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["
						<<__DATE__<<"_"<<__TIME__<<"]"<<".";// else print a dot
				
			}
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";
			
		}
		if ( i % 16 == 0 ) std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
			<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<
			std::hex<<( unsigned STUB_INT ) ucData [ i ] ;
		if ( i == iSize - 1 ){ //print the last space
			for ( STUB_INT j= 0 ; j < 15 - i % 16 ; ++ j )
				std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<
					__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<
					__DATE__<<"_"<<__TIME__<<"]"<<"   ";//extra space
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
				<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__
				<<"_"<<__TIME__<<"]"<<"       ";
			for ( STUB_INT j= i - i % 16 ; j <=i ; ++ j){
				if ( ucData [ j ] >= 32 && ucData [ j ] <=128 )
					std::cout<<" File Name ["<<__FILE__<<" ] Function [ "
						<<__FUNCTION__<<"] Line ["<<__LINE__<<"] Dat\
						eTime ["<<__DATE__<<"_"<<__TIME__<<"]"
						<<( unsigned STUB_CHAR ) ucData [ j ] ;
				else
					std::cout<<" File Name ["<<__FILE__<<" ] Function [ "
						<<__FUNCTION__<<"] Line ["<<__LINE__<<"] Date\
						Time ["<<__DATE__<<"_"<<__TIME__<<"]"<<".";
				
			}
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
				<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
				<<__TIME__<<"]\n";
			
		}
		
	}
	
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  giveInterface
 *  Description:  return all available interfaces
 * =====================================================================================
 */
STUB_CHAR ** snif::giveInterface( void ){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	STUB_CHAR    errorBuffer[ 100 ] ;
	pcap_if_t    *pAlldevsp , *pDevice ;
	STUB_INT     iCount;

	cDevs=new STUB_CHAR*[100];
	for (STUB_INT i=0; i<100; i++)
		{
			cDevs[ i ] = new STUB_CHAR[100];
			
		}

	iCount=1 ;
	if ( pcap_findalldevs ( &pAlldevsp , errorBuffer ) ){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
			<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
			<<"]Error finding devices \t "<<errorBuffer<<std::endl;
		exit (EXIT_FAILURE);
	}
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]---Searching Done \n";

	//PrSTUB_INT the available devices
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		<<"] Available devices are \n";
	for ( pDevice=pAlldevsp ; pDevice != NULL ; pDevice=pDevice->next ){
		if ( pDevice->name != NULL )
			strcpy( cDevs[ iCount ] , pDevice->name );
		iCount ++;
	}
	strcpy ( cDevs [iCount ] , "NULL" );
	return cDevs;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  startSniffing
 *  Description:  read network packets from the provided interface
 * =====================================================================================
 */

void snif::startSniffing( STUB_INT id){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	STUB_CHAR    *deviceName ;
	STUB_CHAR    errorBuffer[ 100 ] ;

	//snif::fileHandler.open("temp.bin", std::ios::in |std::ios::out | std::ios::app | std::ios::binary);
	flagCapture = true;
	flagStop = false;
//	STUB_INT * id = ( STUB_INT * ) value;
//	deviceName=cDevs [ *id ]; // take the device name to sniff
	deviceName = cDevs [ id ];
#ifdef DEBUG
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"]"<<"\nOpening device for sniffing \t"
		<<deviceName<<std::endl;
#endif

	if ( !( pHandle= pcap_open_live ( deviceName , 65536 , 1 , 0 , errorBuffer ) ) ){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"]"<<"Could't open device :\t"
			<<deviceName <<" : "<<errorBuffer <<'\n';
		exit (EXIT_FAILURE);
		
	}
	//put the device for sniffing loop
	signal(SIGINT, snif::signalCallbackHandler);

	/*
      create a child thread and give access to the following function
      */

    pcap_loop ( pHandle , -1 , snif::processPacket , NULL );
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  stopSniffing
 *  Description:  stop the capturing packet operation.
 * =====================================================================================
 */

void snif::stopSniffing ( ){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	flagCapture = false;
	while ( flagStop );
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"]\n";
	try {
		pcap_close( pHandle );
		flagStop = true;
	}
	catch ( std::exception &e ){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "
			<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["
			<<__DATE__<<"_"<<__TIME__<<"]"<<"Exception:"
			<<e.what()<<'\n';
	}
	// snif::fileHandler.close();
	//std::cout.flush();
	//snif::fileHandler.flush();
//	snif::fileHandler.close();
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  analysisFromFile
 *  Description:  dissect and learn from the already captured tcpdump file
 * =====================================================================================
 */

void snif::analysisFromFile ( std::string fileName ){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	pcap_t              *pcap;
	struct pcap_pkthdr  header;
	const STUB_UCHAR    *packet;
	STUB_CHAR           errbuf[PCAP_ERRBUF_SIZE];

//	STUB_CHAR *fileName = (STUB_CHAR*)value;
//
	pcap = pcap_open_offline( fileName.c_str() , errbuf);
	if (pcap == NULL){
        fprintf(stderr, "error reading pcap file: %s\n", errbuf);
		exit(1);
		}
	while ( ( packet = pcap_next(pcap, &header ) ) != NULL ){
		
		snif::processPacket( packet,  header.len );//caplen
	}

}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  processPacket
 *  Description:  process the packet.
 * =====================================================================================
 */

void snif::processPacket ( const STUB_UCHAR* ucBuffer , STUB_INT length ){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	struct iphdr    *stIph;

	stIph = ( struct iphdr * ) ( ucBuffer + 
			sizeof ( struct ethhdr ) );
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
    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
	    <<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"\nTCP\t:"
	    <<iTcp<<"\t UDP\t: "<<iUdp<<"\tICMP\t:"<<iIcmp<<"\tGMP\t:"<<iIgmp
	    <<"\tOthers\t:"<<iOthers<<"\tTotal\t:"<<iTotal<<'\n';
}
	
