/*
 * =====================================================================================
 *
 *       Filename:  sniffing.cpp
 *
 *    Description:  defination of header file sniffing.hpp
 *
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
#include "sniffing.hpp"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  process_tcp_packet
 *  Description:  print tcp packets dield info
 * =====================================================================================
 */

std::string Snif::dump_file_name;
std::string Snif::filter_ip;
std::string Snif::filter_port;
bool 
Snif::process_tcp_packet( const u_char *buffer , struct pcap_pkthdr packet_header   ){
	unsigned short               ip_header_len;
	size_t                       header_size;
	struct iphdr                 *str_ip_header;
	bool                         ret_value = true;
	__rawNetData                 *raw_data;
	size_t                       temp_size;
	struct tcphdr                *str_tcp_header 

	temp_size = packet_header.len;
	str_ip_header = ( struct iphdr * ) 
		( buffer + sizeof ( struct ethhdr ) );
	ip_header_len = str_ip_header->ihl * 4 ;
	str_tcp_header = ( struct tcphdr * ) 
		( buffer  + (str_ip_header->ihl * 4 ) +  sizeof ( struct ethhdr ) );
	header_size= sizeof ( struct ethhdr ) + ip_header_len + 
		( str_tcp_header->doff * 4 );
#ifdef DEBUG
	std::cout<<PRINT<<"Source Ip ADDRES ["<<
		inet_ntoa( *(struct in_addr *) &str_ip_header->saddr)
		<<"] And Destination Ip Address [ "<<
		inet_ntoa( *(struct in_addr *) &str_ip_header->daddr)
		<<" ] \n";
#endif
	try {
		raw_data = new __rawNetData();
	}
	catch ( const std::bad_alloc &ba){
		std::cerr<<PRINT<<" Exception:"<<ba.what() <<std::endl;
		ret_value = false;
	}
	if ( ret_value ){
		//get the dateTime from the packet header
		raw_data->dateTime = getTime(&packet_header.ts);
		raw_data->sourceIp = 
			std::string( inet_ntoa( *(struct in_addr *) &str_ip_header->saddr) );
		raw_data->destinationIp = 
			std::string ( inet_ntoa( *(struct in_addr *) &str_ip_header->daddr) );
		raw_data->sourcePort = ntohs( str_tcp_header->source );
		raw_data->destinationPort = ntohs ( str_tcp_header->dest) ;
		if ( !seq_init ){
			delta =  ntohl ( str_tcp_header->seq );
			seq_init = true;
		}
		raw_data->sequenceNumber =
			(uint32_t) ntohl( str_tcp_header->seq ) -delta;// /- 33278;// ( str_tcp_header->seq ) ;
		raw_data->acknowledgeNumber=
			ntohl( str_tcp_header->ack_seq ) - delta;
		raw_data->dataLength =  (temp_size - header_size );
		( ( unsigned int )str_tcp_header->psh ) == 1 ? 
			raw_data->networkTcpFlags.__PSH__ = true 
			:  raw_data->networkTcpFlags.__PSH__ = false ;
		( ( unsigned int ) str_tcp_header->ack ) == 1 ?
			raw_data->networkTcpFlags.__ACK__ = true
			: raw_data->networkTcpFlags.__ACK__ = false ;
		( unsigned int )str_tcp_header->syn  == 1 ? 
			raw_data->networkTcpFlags.__SYN__ = true :
			raw_data->networkTcpFlags.__SYN__ = 0;
		( unsigned int ) str_tcp_header->fin  ==  1 ? 
			raw_data->networkTcpFlags.__FIN__ = true : 
			raw_data->networkTcpFlags.__FIN__ = false;
		//TODO coppy the data also
		
#ifdef DEBUG
		std::cout<<PRINT<<" Packet Info\nSource port [ "<<raw_data->sourcePort<< " ]destination port [ "
			<<raw_data->destinationPort<<"] sequence number ["
			<<(int)raw_data->sequenceNumber<<" ] Acknowledge number["
			<<(int)raw_data->acknowledgeNumber<<"] Network Flags \n Acknowledge [ "
			<<raw_data->networkTcpFlags.__ACK__
			<<" ] PSH [ "<<raw_data->networkTcpFlags.__PSH__
			<<"] SYN ["<<raw_data->networkTcpFlags.__SYN__
			<<"] FIN ["<<raw_data->networkTcpFlags.__FIN__
			<<"] Packet Size["<<temp_size - header_size <<" ] \n";
		
#endif
		try{
			while (  buffer_handler.write_buffer ( raw_data )  == 0 && ret_value  ){
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			//	ret_value =  !buffer_handler->checkSignal() ;//check whether grouping thread raised and signal to terminate pcap?
				//close pcap
			}
			//delete []raw_data->data;
			delete raw_data;
		}
		catch ( std::exception &ea ){
			std::cerr<<PRINT<<" Exception:"<<ea.what()<<std::endl;
			ret_value = false;
		}
	}
	return ret_value;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  dump_data
 *  Description:  print char by char
 * =====================================================================================
 */
void 
Snif::dump_data ( const u_char *ucData , size_t temp_size ) {

	for ( size_t i=0 ; i < temp_size ; ++ i ){
		if ( i!= 0 && i % 16 == 0 ){ //if one line of hex print os complete.....

			std::cout<<"        ";
			for ( size_t j= i - 16 ; j < i ; ++ j ){
				if ( ucData [ j ] >=32 && ucData [ j ] <= 128 )
					std::cout<<( unsigned char ) ucData [ j ] ;//if it's a number or alphabet
				else
					std::cout<<".";// else print a dot
			}
		}
		if ( i % 16 == 0 ) 
			std::cout<<std::hex<<( unsigned int ) ucData [ i ] ;
		if ( i == temp_size - 1 ){ //print the last space
			for ( size_t j= 0 ; j < 15 - i % 16 ; ++ j )
				std::cout<<"]"<<"   ";//extra space
			std::cout<<"       ";
			for ( size_t j= i - i % 16 ; j <=i ; ++ j){
				if ( ucData [ j ] >= 32 && ucData [ j ] <=128 )
					std::cout<<( unsigned char ) ucData [ j ] ;
				else
					std::cout<<".";
			}
		}
	}
}

void
Snif::set_filter( std::string const file_name_, 
		  std::string const ip_,
		  uint32_t    const port_){
#ifdef DEBUG
	std::cout<<PORT<<"Set tcp dump file name[ "<<file_name_
		<<"\nFilter Ip Address [ "<<ip__
		<<"\n Filter Port [ "<<port_<<" ] \n";
#endif
	dump_file_name = file_name_;
	filter_ip = ip_;
	filter_port = port_;
	return;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  analysis_from_file
 *  Description:  dissect and learn from the already captured tcpdump file
 * =====================================================================================
 */

void* 
Snif::analysis_from_file ( void *temp ){
#ifdef DEBUG
	std::cout<<PRINT<<"Reading file:[ "<<fileName<<" ] "<<std::endl;
#endif

	pcap_t                *pcap;
	struct pcap_pkthdr    header;
	const u_char          *packet;
	struct iphdr          *str_ip_header;
	bool                  ret_value;
	char                  errbuf[PCAP_ERRBUF_SIZE];
	Snif                  *snf_ptr;

	snf_ptr = ( Snif*)temp;

	ret_value = true;
	
	pcap = pcap_open_offline( fileName.c_str() , errbuf);
	if (pcap == NULL){
		std::cerr<<PRINT<<"error reading pcap file: \n"<< errbuf<<std::endl;
		return nullptr;
	}
	if ( ret_value ){
		try{
			while ( ( packet = pcap_next(pcap, &header ) ) != NULL && ret_value  ){
				str_ip_header = ( struct iphdr * ) ( packet + sizeof ( struct ethhdr ) );
				if ( std::string(inet_ntoa ( *(struct in_addr * )&str_ip_header->saddr) )== Init::configuration.ip ||  std::string(inet_ntoa (*(struct in_addr * ) &str_ip_header->daddr) )== Init::configuration.ip ) {
					ret_value = snf_ptr->process_packet( packet,  header );//caplen
				}
			}

			__rawNetData    *newFileNextIndicator = new __rawNetData();
			newFileNextIndicator->sourcePort = 0;

			while (  buffer_handler.write_buffer ( newFileNextIndicator )  == 0 ){
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
			delete newFileNextIndicator;
			pcap_close( pcap );
		}
		catch ( std::exception &ea ){
			std::cerr<<PRINT<<" Exception:"<<ea.what()<<std::endl;
			return nullptr;
		}
	}
	return nullptr;
}
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  process_packet
 *  Description:  process the packet.
 * =====================================================================================
 */

bool 
Snif::process_packet ( const u_char* buffer , struct pcap_pkthdr packet_header ){
#ifdef DEBUG
	std::cout<<PRINT<<"\nProcessPacket\n";

	struct iphdr    *str_iph;
	bool            ret_value;

	ret_value = true;

	str_iph = ( struct iphdr * ) ( buffer +	sizeof ( struct ethhdr ) );
	++ count_total_packet ;
	switch ( str_iph->protocol ){ // check the protocol and take action depending on protocol
		case 1: //ICMP protocol
                ++count_icmp_packet;
                break;
				
            case 2: // IGMP protocol
                ++count_igmp_packet;
                break;
				
            case 6: //TCP protocol , this protocol we need to sniff for database port
                ++count_tcp_packet;
                 ret_value = snif::process_tcp_packet ( buffer , packet_header ) ;
                break;
				
            case 17: // UDP protocol
                ++ count_udp_packet;
                break;
				
            default: // some other protocol like ARP etc..
                ++count_other_packet;
                break;
				
        }//end of switch
#ifdef DEBUG
	std::cout<<PRINT<<"\n TCP [ "<<count_tcp_packet
		<<"]\n UDP[ "<<count_udp_packet
		<<" ]\nICMP["<<count_icmp_packet
		<<" ]\n GMP ["<<count_igmp_packet
		<<"]\n Others ["<<count_other_packet
		<<"]\n Total[ "<<count_total_packet<<"]\n";
#endif
	return ret_value; 
}
	
