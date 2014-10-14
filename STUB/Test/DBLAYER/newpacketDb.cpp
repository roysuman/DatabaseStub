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

actSeriesStruct *  createPacketDb::GenarateRawPacket::getChunkPackets (
	       	STUB_INT conversationId ){
    createPacketQuery::GenarateRawPacketQuery createRawpacket;

        return ( createRawpacket.getChunkPackets ( conversationId ) );

}

bool createPacketDb::GenarateRawPacket::insertGeneratedPacket ( 
		actSeriesStruct *& conversationPacket , queryData*& queryDataArray ){
    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
	    <<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";
    createPacketQuery::GenarateRawPacketQuery *clasInstance;
    try{
        clasInstance = new createPacketQuery::GenarateRawPacketQuery ();
		
	}
	catch ( std::bad_alloc &ba ){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
			<<"]"<<"exception ="<<ba.what()<<std::endl;
                exit(0);
	}
	//initialize the conversation No and packet no
        conPacketNo * conversationPacketNo =
	       	clasInstance->getAssignedConPackNo();
        conversationPacket->actRawData [ 0 ].packetNumber = 
		conversationPacketNo->packetNo + 1 ;
        conversationPacket->converationId = 
		conversationPacketNo->conversationNo + 1;
	clasInstance->insertGeneratedPacket ( conversationPacket , queryDataArray );
	delete clasInstance;
	return true;
/*
	//now update the query string,  added on 3_6_2014
	// frist create an instance of StoreRawPacketQuery
	captureQuery::StoreRawPacketQuery *instance ;
	try {
		instance = new captureQuery::StoreRawPacketQuery ();
		
	}
	catch ( std::bad_alloc &ba ){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"exception cought "<<ba.what()<<'\n';
		
	}
	// actRawDataStruct *packetSettingDataArray = instance->selectPacketSetting ();
                    // now we have all packets of table PACKET_SETTING_ for the particular scenario.
                    //now for each raw packet dissect and update.
	STUB_INT currentPacket = -1;
//                    while ( packetSettingDataArray [ ++currentPacket ].length != -999 ){
//                        //now for each packet update the database. after dissecting the packet
//                        //diisect each packet.
//
//                    }
                    //currentPacket contains the all packet numbers upto this poSTUB_INT.
                    //now create queryData array
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"current packet ="<<currentPacket<<std::endl;
	queryData *queryDataArray ;
	try{
		queryDataArray = new queryData [ 2 ];
		
	}
	catch ( std::bad_alloc &ba ){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"exception caught "<<ba.what()<<std::endl;
		
	}
	//nowdissect all packets.
	//  Mysql::getQueryOnly ( packetSettingDataArray , queryDataArray );
	actRawDataStruct *newRawDataArray = new actRawDataStruct  [ 1 ];
	newRawDataArray[0].length = conversationPacket->actRawData[0].length;
	newRawDataArray[0].appServer = conversationPacket->actRawData[0].appServer;
	newRawDataArray[0].data = new STUB_CHAR[ newRawDataArray[0].length ];
	memcpy( newRawDataArray[0].data , conversationPacket->actRawData[0].data , newRawDataArray[0].length);
	//   newRawDataArray[1].length = -999;
	Mysql::getQueryOnly( newRawDataArray , queryDataArray , 0 );
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"#### NOW UPDATE THE QUERY FLD\n";
	queryDataArray[0].packetNo =  conversationPacket->actRawData [ 0 ].packetNumber;
	instance->updatePacketSettingApp( queryDataArray , 1 );
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"QUERY FLD UPDATED\n";
	return true;
	//#adding ends

*/
	}

bool createPacketDb::GenarateRawPacket::deletePacketRegardingConversationId(
	       	STUB_INT conversatinId ){
        createPacketQuery::GenarateRawPacketQuery *instance;
         bool returnValue;
         std::ofstream FILEH ("checkAndDelete.log");
	try{
                instance = new createPacketQuery::GenarateRawPacketQuery();
                returnValue =
			instance->deletePacketRegardingConversationId(
				       	conversatinId) ; //instance.deletePacketRegardingConversationId ( conversationId );
                std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "
			<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["
			<<__DATE__<<"_"<<__TIME__<<"]"<<"return value="
			<<returnValue<<std::endl;
		delete instance;

	}
	catch ( std::bad_alloc &ba ){
                FILEH<<"cgt exception at createPacketDb::GenarateRawPacket::\
			deletePacketRegardingConversationId = "<<ba.what()
			<<std::endl;
		exit(0);
	}
        //std::fstream FILEH ("checkAndDelete.log");
        FILEH<<returnValue;
	return returnValue;

}
