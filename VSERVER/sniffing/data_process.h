/*
 * =====================================================================================
 *
 *       Filename:  data_process.h
 *
 *    Description:  pocess the tcp_dump file
 *
 *        Version:  1.0
 *        Created:  Saturday 10 October 2015 07:28:22  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  ROY (), email.suman.roy@gmail.com
 *   Organization:  NA
 *
 * =====================================================================================
 */
#ifndef DATA_PROCESS_H
#define DATA_PROCESS_H
#include "buffer.h"
#include "group_packets.h"
#include "sniffing.h"
#define NEW_BUFFER                  0x01
#define NEW_GROUP_PACKET            0x02
#define NEW_SNIF                    0x03

class ProcessData{
	public:
		explicit ProcessData( std::string const ip_address_="127.0.0.1", uint32_t port_ = 0):ip_address_filter(ip_address_),port_filter(port_){
			try{
				if ( (buff = new Buffer())!= NULL ){
					flag |= NEW_BUFFER;
				}
				if  ( (grp_pack = new GrupPacket( *buff ))!= NULL ){
					flag |= NEW_GROUP_PACKET;
				}
				if ( (snif = new Snif(*buff)) != NULL ){
					flag |= NEW_SNIF;
				}
			}
			catch ( const std::bad_alloc &ba){
				std::cerr<<PRINT<<"Exception on initializing process data eenvironment"<<ba.what()<<std::endl;
				is_init = false;
				return;
			}
			is_init = true;
			return;
		}
		virtual ~ProcessData(){
			if ( flag && NEW_BUFFER) delete buff;
			if ( flag && NEW_GROUP_PACKET ) delete grp_pack;
			if ( flag && NEW_SNIF ) delete snif;
			return;
		}
	protected:
		const int  start_processing_dump_file( std::string const file_name,std::string const ip_address = "127.0.0.1",const uint32_t port =0);
	private:
		Buffer               *buff;
		GrupPacket           *grp_pack;
		Snif                 *snif;
		unsigned int         flag;
		bool                 is_init;
		pthread_t            file_process_thread;
		pthread_t            group_packet_thread;
};

#endif
