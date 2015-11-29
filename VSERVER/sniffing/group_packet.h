/*
 * =====================================================================================
 *
 *       Filename:  grupPackets.hpp
 *
 *    Description:  grup the packet
 *
 *        Version:  1.0
 *        Created:  Friday 01 May 2015 02:37:42  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  ROY (), email.suman.roy@gmail.com
 *   Organization:  NA
 *
 * =====================================================================================
 */
#ifndef GROUP_PACKET_H_
#define GROUP_PACKET_H_
#include<iostream>
#include<stdlib.h>
#include "buffer.h"
#include "../common/vserver_datatype.h"
#define zero 0
extern VS_INT64 k;

class GroupPacket{//: public DbManager {
	private:
		static VS_BOOL                is_init;
		static VS_BOOL                last_db;
		static VS_INT32                 file_count;
		static VS_BOOL                is_syn_fin;
		static conversation_struct    conversation_diary[1000];
		static VS_INT32                 packet_number;
		static VS_INT32                 active_conversation_id;
//FIXME temp		DbManager                  *db_instance;
		static VS_INT32                 relative_active_conversation;
		static VS_INT32                 relative_packet_number;


	public:
		GroupPacket( Buffer &);
		~GroupPacket();
		VS_BOOL group_init();
		Buffer                  read_buffer_obj;
		static VS_VOID* start_grouping( VS_VOID*);
		VS_BOOL packet_handler( raw_net_data_struct * );
		VS_BOOL copy_packet( VS_BOOL , conversation_struct * , raw_net_data_struct * );
		VS_BOOL search_mother( VS_BOOL , conversation_struct * , raw_net_data_struct * );
		VS_BOOL valid_pack( VS_BOOL , conversation_struct * , raw_net_data_struct  *);
		VS_BOOL insert_db( raw_net_data_struct * , VS_BOOL, VS_BOOL );
		//VS_BOOL checkSimultaniousNewPacket( VS_BOOL , conversation_struct * , raw_net_data_struct *);
		//VS_BOOL checkGreeting( 	conversation_struct *, raw_net_data_struct * );


};


#endif
