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
#include "sniffing.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  process_tcp_packet
 *  Description:  prVS_INT32 tcp packets dield info
 * =====================================================================================
 */

VS_BOOL __flagCapture__ = false, __flagStop__ = false;
std::string Snif::dump_file_name;
std::string Snif::filter_ip;
VS_UINT32 Snif::filter_port;
VS_BOOL 
Snif::process_tcp_packet( const VS_UINT8 *buffer , struct pcap_pkthdr packet_header   ){
	unsigned short               ip_header_len;
	VS_UINT64                       header_size;
	struct iphdr                 *str_ip_header;
	VS_BOOL                         ret_value = true;
	raw_net_data_struct                 *raw_data;
	VS_UINT64                       temp_size;
	struct tcphdr                *str_tcp_header ;

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
		raw_data = new raw_net_data_struct();
	}
	catch ( const std::bad_alloc &ba){
		std::cerr<<PRINT<<" Exception:"<<ba.what() <<std::endl;
		ret_value = false;
	}
	if ( ret_value ){
		raw_data->source_ip = 
			std::string( inet_ntoa( *(struct in_addr *) &str_ip_header->saddr) );
		raw_data->destination_ip = 
			std::string ( inet_ntoa( *(struct in_addr *) &str_ip_header->daddr) );
		raw_data->source_port = ntohs( str_tcp_header->source );
		raw_data->destination_port = ntohs ( str_tcp_header->dest) ;
		if ( !seq_init ){
			delta =  ntohl ( str_tcp_header->seq );
			seq_init = true;
		}
		raw_data->sequence_number =
			(VS_UINT32) ntohl( str_tcp_header->seq ) -delta;// /- 33278;// ( str_tcp_header->seq ) ;
		raw_data->acknowledge_number=
			ntohl( str_tcp_header->ack_seq ) - delta;
		raw_data->data_length =  (temp_size - header_size );
		( ( unsigned VS_INT32 )str_tcp_header->psh ) == 1 ? 
			raw_data->tcp_flags.PSH = true 
			:  raw_data->tcp_flags.PSH = false ;
		( ( unsigned VS_INT32 ) str_tcp_header->ack ) == 1 ?
			raw_data->tcp_flags.ACK = true
			: raw_data->tcp_flags.ACK = false ;
		( unsigned VS_INT32 )str_tcp_header->syn  == 1 ? 
			raw_data->tcp_flags.SYN = true :
			raw_data->tcp_flags.SYN = 0;
		( unsigned VS_INT32 ) str_tcp_header->fin  ==  1 ? 
			raw_data->tcp_flags.FIN = true : 
			raw_data->tcp_flags.FIN = false;
		//TODO coppy the data also
		
#ifdef DEBUG
		std::cout<<PRINT<<" Packet Info\nSource port [ "<<raw_data->source_port<< " ]destination port [ "
			<<raw_data->destination_port<<"] sequence number ["
			<<(VS_INT32)raw_data->sequence_number<<" ] Acknowledge number["
			<<(VS_INT32)raw_data->acknowledge_number<<"] Network Flags \n Acknowledge [ "
			<<raw_data->tcp_flags.__ACK__
			<<" ] PSH [ "<<raw_data->tcp_flags.__PSH__
			<<"] SYN ["<<raw_data->tcp_flags.__SYN__
			<<"] FIN ["<<raw_data->tcp_flags.__FIN__
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
 *  Description:  prVS_INT32 VS_INT8 by VS_INT8
 * =====================================================================================
 */
VS_VOID 
Snif::dump_data ( const VS_UINT8 *ucData , VS_UINT64 temp_size ) {

	for ( VS_UINT64 i=0 ; i < temp_size ; ++ i ){
		if ( i!= 0 && i % 16 == 0 ){ //if one line of hex prVS_INT32 os complete.....

			std::cout<<"        ";
			for ( VS_UINT64 j= i - 16 ; j < i ; ++ j ){
				if ( ucData [ j ] >=32 && ucData [ j ] <= 128 )
					std::cout<<( unsigned VS_INT8 ) ucData [ j ] ;//if it's a number or alphabet
				else
					std::cout<<".";// else prVS_INT32 a dot
			}
		}
		if ( i % 16 == 0 ); 
		//	std::cout<<std::hex( (unsigned VS_INT32 ) ucData [ i ]) ;
		if ( i == temp_size - 1 ){ //prVS_INT32 the last space
			for ( VS_UINT64 j= 0 ; j < 15 - i % 16 ; ++ j )
				std::cout<<"]"<<"   ";//extra space
			std::cout<<"       ";
			for ( VS_UINT64 j= i - i % 16 ; j <=i ; ++ j){
				if ( ucData [ j ] >= 32 && ucData [ j ] <=128 )
					std::cout<<( unsigned VS_INT8 ) ucData [ j ] ;
				else
					std::cout<<".";
			}
		}
	}
}

VS_VOID
Snif::set_filter( std::string const file_name_, 
		  std::string const ip_,
		  VS_UINT32    const port_){
#ifdef DEBUG
	std::cout<<PRINT<<"Set tcp dump file name[ "<<file_name_
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

VS_VOID* 
Snif::analysis_from_file ( VS_VOID *temp ){
#ifdef DEBUG
	std::cout<<PRINT<<"Reading file:[ "<<dump_file_name<<" ] "<<std::endl;
#endif

	pcap_t                *pcap;
	struct pcap_pkthdr    header;
	const VS_UINT8          *packet;
	struct iphdr          *str_ip_header;
	VS_BOOL                  ret_value;
	char                  errbuf[PCAP_ERRBUF_SIZE];
	Snif                  *snf_ptr;

	snf_ptr = ( Snif*)temp;

	ret_value = true;
	
	pcap = pcap_open_offline( dump_file_name.c_str() , errbuf);
	if (pcap == NULL){
		std::cerr<<PRINT<<"error reading pcap file: \n"<< errbuf<<std::endl;
		return nullptr;
	}
	if ( ret_value ){
		try{
			while ( ( packet = pcap_next(pcap, &header ) ) != NULL && ret_value  ){
				str_ip_header = ( struct iphdr * ) ( packet + sizeof ( struct ethhdr ) );
				if ( std::string(inet_ntoa ( *(struct in_addr * )&str_ip_header->saddr) )== "127.0.0.1" ||  std::string(inet_ntoa (*(struct in_addr * ) &str_ip_header->daddr) )== "127.0.0.1" ) {
					ret_value = snf_ptr->process_packet( packet,  header );//caplen
				}
			}

			raw_net_data_struct    *new_file_next_indicator = new raw_net_data_struct();
			new_file_next_indicator->source_port = 0;

			while (  snf_ptr->buffer_handler.write_buffer ( new_file_next_indicator )  == 0 ){
				std::this_thread::sleep_for(std::chrono::milliseconds(100));
			}
			delete new_file_next_indicator;
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

VS_BOOL 
Snif::process_packet ( const VS_UINT8* buffer , struct pcap_pkthdr packet_header ){
#ifdef DEBUG
	std::cout<<PRINT<<"\nProcessPacket\n";
#endif

	struct iphdr    *str_iph;
	VS_BOOL            ret_value;

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
                 ret_value = process_tcp_packet ( buffer , packet_header ) ;
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
	
