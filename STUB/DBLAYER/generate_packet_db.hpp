
/*
 * =====================================================================================
 *
 *       Filename:  generate_packet_db.hpp
 *
 *    Description:  all  busines layer function for inserting created packets.
 *
 *        Version:  1.0
 *        Created:  Wednesday 06 November 2013 02:34:43  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy (), 
 *   Organization:  Cognizant Technological solutions
 *
 * =====================================================================================
 */
#ifndef GENERATE_PACKET_DB_HPP_
#define GENERATE_PACKET_DB_HPP_
#include "../STRUCTURE/rawdata_structure.hpp"
#include "iostream"

 typedef struct _conPacketNo{
    int packetNo;
    int conversationNo;
};
typedef struct _conPacketNo conPacketNo;

namespace newPacket{

    class GeneratPacketInsert{
        public:
        conPacketNo * getAssignedConPackNo( ); 
        bool insertGeneratedPacket ( actSeriesStruct *& );
        
        };
}

#endif
