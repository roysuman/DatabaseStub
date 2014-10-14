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
 *   Organization:  SELF
 *
 * =====================================================================================
 */

#ifndef NEWPACKETDB_HPP_
#define NEWPACKETDB_HPP_
#include <iostream>
#include <sqlite3.h>
#include <sstream>
#include "../STRUCTURE/include/scenario_struct.hpp"
#include "../STRUCTURE/include/rawdata_structure.hpp"
#include "DB/newpacket.hpp"
#include "../CORE/DISSECTOR/include/proto_mysql.hpp"
#include "DB/capture_packet.hpp"
#include "capture_packet_db.hpp"
#include "../SUPPORT/globalDatatypes.hpp"


namespace createPacketDb{
	class GenarateRawPacket{
		public:
			GenarateRawPacket ();
			~GenarateRawPacket ();
			actSeriesStruct * getChunkPackets ( STUB_INT );
			conPacketNo * getAssignedConPackNo( );
			bool insertGeneratedPacket ( actSeriesStruct *& , queryData*& );
            bool deleteWholeConversation ( STUB_INT );
	    bool deletePacketRegardingConversationId ( STUB_INT );
	    

	};
}

#endif

