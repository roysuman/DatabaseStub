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
 *   Organization:  Cognizant Technological solutions
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
#include "../../STRUCTURE/database_structure.hpp"
#include "../../STRUCTURE/rawdata_structure.hpp"
#include "../../STRUCTURE/scenario_struct.hpp"
#include "create_project.hpp"

typedef struct _conPacketNo conPacketNo;
struct _conPacketNo{
   int packetNo;
   int conversationNo;
};

namespace createPacketQuery{
	class GenarateRawPacketQuery{
		public:

			GenarateRawPacketQuery();
			~GenarateRawPacketQuery();
            actSeriesStruct * getChunkPackets( int );
            conPacketNo * getAssignedConPackNo();
            bool insertGeneratedPacket ( actSeriesStruct *& );
            bool deleteWholeConversation ( int );
	    bool deletePacketRegardingConversationId(int);

			
	};
}
#endif

