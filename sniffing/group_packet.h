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
#define zero 0
extern long k;

class GroupPacket: public DbManager {
	private:
		static bool                is_init;
		static bool                lastDb;
		static int                 fileCount;
		static bool                isSynFin;
		static __conversation__    conversationDiary[1000];
		static int                 packetNumber;
		static int                 activeConversationId;
		DbManager                  *dbInstance;
		static int                 relativeActiveConversation;
		static int                 relativePacketNumber;


	public:
		GroupPacket();
		~GroupPacket();
		bool gInit();
		void* start_grouping( void);
		bool packet_handler( __rawNetData__ * );
		bool copy_packet( bool , __conversation__ * , __rawNetData__ * );
		bool search_mother( bool , __conversation__ * , __rawNetData__ * );
		bool valid_pack( bool , __conversation__ * , __rawNetData__  *);
		bool insert_db( __rawNetData__ * , bool, bool );
		//bool checkSimultaniousNewPacket( bool , __conversation__ * , __rawNetData__ *);
		//bool checkGreeting( 	__conversation__ *, __rawNetData__ * );


};
/*
class ParsePacket{
	public:
		bool sendData
};
*/	       	


#endif
