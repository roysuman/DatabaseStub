/*
 * =====================================================================================
 *
 *       Filename:  newpacket.hpp
 *
 *    Description:  same as DB/newpacket.hpp
 *
 *        Version:  1.0
 *        Created:  Monday 09 December 2013 12:55:29  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy (), 
 *   Organization:  Cognizant Technological solutions
 *
 * =====================================================================================
 */

#ifndef NEWPACKETDB_HPP_
#define NEWPACKETDB_HPP_
#include <iostream>
#include <sqlite3.h>
#include <sstream>
#include "../STRUCTURE/scenario_struct.hpp"
#include "../STRUCTURE/rawdata_structure.hpp"
#include "DB/newpacket.hpp"
#include "../SUPPORT/DISSECTOR/proto_mysql.hpp"
#include "DB/capture_packet.hpp"
#include "capture_packet_db.hpp"


namespace createPacketDb{
	class GenarateRawPacket{
		public:
			GenarateRawPacket ();
			~GenarateRawPacket ();
			actSeriesStruct * getChunkPackets ( int );
            conPacketNo * getAssignedConPackNo( );
            bool insertGeneratedPacket ( actSeriesStruct *& );
            bool deleteWholeConversation ( int );
	    bool deletePacketRegardingConversationId ( int );
	    

	};
}

#endif

