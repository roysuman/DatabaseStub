/*
 * =====================================================================================
 *
 *       Filename:  rawdata_structure.cpp
 *
 *    Description:  implementation of rawdata_structure.hpp
 *
 *        Version:  1.0
 *        Created:  Friday 08 November 2013 12:05:35  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy (),
 *   Organization:  Cognizant Technological solutions
 *
 * =====================================================================================
 */

#include "rawdata_structure.hpp"
#include "fstream"
#define size 1000
//rawDataStruct rawData;

conversation  conversationDiary[1000];// = new conversationDiary [ 10 ];

prevPacket pastData;

bool initDataStructure (){
	std::cout<<"FUNCTION"<<__FUNCTION__<<'\n';
	for ( int i = 0 ; i<1000 ; i++ ){//maximun 1000 conversation can be gen and each conv can contain max 10 APP and DB packets.
		conversationDiary [ i ] .currentPositionAppArray = -1;
		conversationDiary [ i ].currentPositionDbArray = -1;
		conversationDiary [ i ].allPreviousPacketApp = new prevPacket [ 10 ];
		conversationDiary [ i ].allPreviousPacketDb = new prevPacket [ 10 ];
}
    return true;
}



void printData ( int communicationId ){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<'\n';
	std::cout<<__FUNCTION__<<"[App array current position]:"<<conversationDiary [ communicationId ] .currentPositionAppArray<<'\n';
	std::cout<<__FUNCTION__<<"[DB array index current position]:"<<conversationDiary [ communicationId ] .currentPositionDbArray<<'\n';
	std::cout<<__FUNCTION__<<"[previous APP packets]---> \n";
	for ( int i = 0 ; i<=conversationDiary[ communicationId ].currentPositionAppArray ; ++i ){
		std::cout<<__FUNCTION__<<"-----App packet----\n";
		std::cout<<__FUNCTION__<<"[Packet No]:"<<i<<'\n';
		std::cout<<__FUNCTION__<<"[sequence no]:"<< conversationDiary [ communicationId ].allPreviousPacketApp [ i ].prevSequenceNumber<<'\n';
		std::cout<<__FUNCTION__<<"[Acknowledge no]"<<conversationDiary [ communicationId ].allPreviousPacketApp [ i ].prevAcknowledgeNumber<<'\n';
		std::cout<<__FUNCTION__<<"[Length ]"<<conversationDiary [ communicationId ] .allPreviousPacketApp [ i ].prevLength<<'\n';
		
	}
	std::cout<<__FUNCTION__<<": previous DB packets \n";
	for ( int i = 0 ; i<=conversationDiary[ communicationId ].currentPositionDbArray ; ++i ){
		std::cout<<__FUNCTION__<<"-------DB packet=---------n";
		std::cout<<__FUNCTION__<<"[Packet No]"<<i<<'\n';
		std::cout<<__FUNCTION__<<"[Sequence no]"<< conversationDiary [ communicationId ].allPreviousPacketDb [ i ].prevSequenceNumber<<'\n';
		std::cout<<__FUNCTION__<<"[Acknowledge no]"<<conversationDiary [ communicationId ].allPreviousPacketDb [ i ].prevAcknowledgeNumber<<'\n';
		std::cout<<__FUNCTION__<<"[Length]"<<conversationDiary [ communicationId ] .allPreviousPacketDb [ i ].prevLength<<'\n';
		
	}
}

//for dummy server

actSeriesStruct actConversationDiary [  1000 ] ; //maximum act conversation diary is 1000.

//function implementation for acopConversationUntill a packet
//this function will copy a conversation until topacket is reached and will copy the data part of toPacket until offset.

actSeriesStruct *newConversationPack;
bool copyConversationPartially ( actSeriesStruct *&newConversation ,  actSeriesStruct *fullConversationChunk , int fromPacket , int toPacket , int offsetOfToPacket , int lengthOfNewData ) {
	std::cout<<"FUNCTION:"<<__FUNCTION__<<'\n';
	//fetch the new possible conversation id for this conversation
	int newConversationId = 0 ;// wrie a function for db to know the letest conversation ID
	int newSequenceNo = 0; // get the latest seq no from db and increaent by 1.
	if ( fromPacket == 0 ){ // first time for thos conversation to create a new conversation
		try{
			newConversation = new actSeriesStruct();
			(newConversation)->actRawData = new actRawDataStruct [ fullConversationChunk->noOfPacket + 5 ];
		}
		catch ( std::bad_alloc &ba ){
			std::cerr<<__FUNCTION__<<"cought exception at STRUCTURE/rawdata_structure.cpp copyConversationPertially "<<ba.what()<<std::endl;
			exit ( -1 );
			return NULL;
		}
		newConversation->converationId = newConversationId + 1 ;
		newConversation->seqNumber =newSequenceNo + 1;//  fullConversationChunk->seqNumber;
		newConversation->noOfPacket = 2 ;
		//have to delete
		newConversation->actRawData [ 0 ].data = new char[ 5000 ];
		newConversation->actRawData [ 1 ].data = new char[ 5000 ];
		
	}
	//now coppy the data pasrt untill the to packet offset position.
	for ( int i = fromPacket ; i<=toPacket ;  i++ ){
		newConversation->actRawData[ i ].appServer =  fullConversationChunk->actRawData [ i ].appServer;
		newConversation->actRawData[ i ].packetNumber =  fullConversationChunk->actRawData [ i ].packetNumber;
		if ( i != toPacket ){
			try {
				// newConversation->actRawData [ i ].data = new char[ fullConversationChunk->actRawData[i].length ];
				newConversation->actRawData [ i ].length = fullConversationChunk->actRawData[ i ].length ;
			}
			catch ( std::bad_alloc &ba ){
				std::cerr<<__FUNCTION__<<"cought exception"<<ba.what()<<std::endl;
				exit( -1 );
			}
			memcpy ( newConversation->actRawData [ i ].data , fullConversationChunk->actRawData [ i ].data , fullConversationChunk->actRawData [ i ].length );
		}
		else {
			try { 
				// lengthOfNewData+=1024;
			//	newConversation->actRawData [ i ].data = new char[ lengthOfNewData];
				newConversation->actRawData [ i ].length = lengthOfNewData ;
			}   
			catch ( std::bad_alloc &ba ){
				std::cerr<<__FUNCTION__<<"cought exception"<<ba.what()<<std::endl;
				exit ( -1 );
			}
			memcpy ( newConversation->actRawData [ i ].data + 0, fullConversationChunk->actRawData[ i ].data + 0, offsetOfToPacket  );//offsetOfToPacket
			//  file5<<"\nnewConversation->actRawData->length: "<<newConversation->actRawData[i].length<<"\n";
			//  file5<<"New conv header + null data: ";
			//  for(int j=0;j<newConversation->actRawData[i].length;j++)
			//      file5<<newConversation->actRawData [ i ].data[j];
			//  file5<<"\n";
		}
	}
	//file5.close();
	return true;
}

queryPacketJson QueryPacket ;
insertRowValues colByColDataTogether;

bool deleteActSeriesStruct( actSeriesStruct *& packet ){
	if ( packet == NULL ) return true;
	try{
		for ( int sequenceNo = 0 ; sequenceNo < packet->noOfPacket ; ++ sequenceNo ){
			delete [] packet->actRawData[sequenceNo ].data;
			//delete packet->actRawData;
		}
		delete packet;
	}
	catch ( std::exception &e ){
		std::cerr<<"Exception:"<<e.what()<<'\n';
		return false;
	}
	return true;
}

