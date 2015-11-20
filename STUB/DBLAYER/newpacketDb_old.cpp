/*
 * =====================================================================================
 *
 *       Filename:  newpacket.cpp
 *
 *    Description:  defined at .hpp
 *
 *        Version:  1.0
 *        Created:  Monday 09 December 2013 12:59:56  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy (), 
 *   Organization:  SELF
 *
 * =====================================================================================
 */

#include "newpacketDb.hpp"


createPacketDb::GenarateRawPacket::GenarateRawPacket (){}

createPacketDb::GenarateRawPacket :: ~GenarateRawPacket (){}

actSeriesStruct *  createPacketDb::GenarateRawPacket::getChunkPackets ( STUB_INT conversationId ){
    createPacketQuery::GenarateRawPacketQuery createRawpacket;

        return ( createRawpacket.getChunkPackets ( conversationId ) );

}

bool createPacketDb::GenarateRawPacket::insertGeneratedPacket( actSeriesStruct *& conversationPacket ){
    createPacketQuery::GenarateRawPacketQuery *instance = new createPacketQuery::GenarateRawPacketQuery();
    return ( instance->insertGeneratedPacket( conversationPacket ) );

}


