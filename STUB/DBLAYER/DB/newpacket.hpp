/*
 * =====================================================================================
 *
 *       Filename:  newpacket.hpp
 *
 *    Description:  all th ecodes for creating new packet raw data
 *
 *        Version:  1.0
 *        Created:  Monday 09 December 2013 12:20:51  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy (), 
 *   Organization:  SELF
 *
 * =====================================================================================
 */

#ifndef NEWPACKET_HPP_
#define NEWPACKET_HPP_

#include <iostream>
#include <sqlite3.h>
#include <sstream>
#include <assert.h>

#include "function.hpp"
#include "../STRUCTURE/include/database_structure.hpp"
#include "../STRUCTURE/include/rawdata_structure.hpp"
#include "../STRUCTURE/include/scenario_struct.hpp"
#include "create_project.hpp"
#include "../../SUPPORT/globalDatatypes.hpp"

typedef struct _conPacketNo conPacketNo;
struct _conPacketNo{
   STUB_INT packetNo;
   STUB_INT conversationNo;
};

namespace createPacketQuery{
	class GenarateRawPacketQuery{
		public:

			GenarateRawPacketQuery();
			~GenarateRawPacketQuery();
            actSeriesStruct * getChunkPackets( STUB_INT );
            conPacketNo * getAssignedConPackNo();
            bool insertGeneratedPacket ( actSeriesStruct *& , queryData *&);
            bool deleteWholeConversation ( STUB_INT );
	    bool deletePacketRegardingConversationId(STUB_INT);

			
	};
}
#endif

