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
 *   Organization:  SELF
 *
 * =====================================================================================
 */

#include "../include/rawdata_structure.hpp"
#include "fstream"
#define size 1000
//rawDataStruct rawData;

conversation  conversationDiary[1000];// = new conversationDiary [ 10 ];

prevPacket pastData;

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  initDataStructure
 *  Description:  initialize structure 
 * =====================================================================================
 */

bool initDataStructure (){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	for ( STUB_INT i = 0 ; i<1000 ; i++ ){//maximun 1000 conversation can be gen and each conv can contain max 10 APP and DB packets.
		conversationDiary [ i ] .currentPositionClientArray = -1;
		conversationDiary [ i ].currentPositionServerArray = -1;
		conversationDiary [ i ].allPreviousPacketClient = 
			new prevPacket [ 10 ];
		conversationDiary [ i ].allPreviousPacketServer = 
			new prevPacket [ 10 ];
}
    return true;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  deleteConversationDiary
 *  Description:  delete the conversation Diary
 * =====================================================================================
 */
bool deleteConversationDiar(){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	for ( STUB_INT i = 0 ;i < 1000 ; ++i ){
		try{
			delete []conversationDiary[ i ].allPreviousPacketClient;
			delete []conversationDiary[i ].allPreviousPacketServer;
		}
		catch ( std::exception &ea ){
			std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "
				<<__FUNCTION__<<"] Line ["<<__LINE__<<"] Date\
				Time ["<<__DATE__<<"_"<<__TIME__<<"]"
				<<"Function name["<<__FUNCTION__
				<<"] Line ["<<__LINE__
				<<"]EXCEPTION:["<<ea.what()<<"]\n";
			exit ( 0 );
			return false;
		}
		
	}
	 return true ;

	
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  printData
 *  Description:  print strcu init data
 * =====================================================================================
 */
void printData ( STUB_INT communicationId ){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		<<"][App array current position]:"
		<<conversationDiary [ communicationId ] .currentPositionClientArray<<'\n';
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		<<"][DB array index current position]:"
		<<conversationDiary [ communicationId ] .currentPositionServerArray<<'\n';
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		<<"][previous APP packets]---> \n";
	for ( STUB_INT i = 0 ; i<=conversationDiary[ communicationId ].currentPositionClientArray
		       	; ++i ){
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"]-----App packet----\n";
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"][Packet No]:"<<i<<'\n';
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"][sequence no]:"
			<< conversationDiary [ communicationId ].allPreviousPacketClient [ i ].prevSequenceNumber<<'\n';
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"][Acknowledge no]"
			<<conversationDiary [ communicationId ].allPreviousPacketClient [ i ].prevAcknowledgeNumber<<'\n';
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"][Length ]"
			<<conversationDiary [ communicationId ] .allPreviousPacketClient [ i ].prevLength<<'\n';
		
	}
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		<<"]: previous DB packets \n";
	for ( STUB_INT i = 0 ; i<=conversationDiary[ communicationId ].currentPositionServerArray ;
		       	++i ){
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"]-------DB packet=---------n";
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"][Packet No]"<<i<<'\n';
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"]"<<__FUNCTION__<<"[Sequence no]"
			<< conversationDiary [ communicationId ].allPreviousPacketServer [ i ].prevSequenceNumber<<'\n';
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"][Acknowledge no]"
			<<conversationDiary [ communicationId ].allPreviousPacketServer [ i ].prevAcknowledgeNumber<<'\n';
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"][Length]"
			<<conversationDiary [ communicationId ] .allPreviousPacketServer [ i ].prevLength<<'\n';
		
	}
}

//for dummy server

actSeriesStruct actConversationDiary [  1000 ] ; //maximum act conversation diary is 1000.

//function implementation for acopConversationUntill a packet
//this function will copy a conversation until topacket is reached and will copy the data part of toPacket until offset.

actSeriesStruct *newConversationPack;

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  copyConversationPartially
 *  Description:  create new data for ( update , insert query )
 * =====================================================================================
 */
bool copyConversationPartially ( actSeriesStruct *&newConversation ,  
		actSeriesStruct *fullConversationChunk , STUB_INT fromPacket ,
	       	STUB_INT toPacket , STUB_INT offsetOfToPacket , STUB_INT lengthOfNewData ) {

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	STUB_INT    newSequenceNo;
	STUB_INT    newConversationId;
	//fetch the new possible conversation id for this conversation
	newConversationId = 0 ;// wrie a function for db to know the letest conversation ID
	newSequenceNo = 0; // get the latest seq no from db and increaent by 1.
	if ( fromPacket == 0 ){ // first time for thos conversation to create a new conversation
		try{
			newConversation = new actSeriesStruct();
			(newConversation)->actRawData = 
				new actRawDataStruct [ fullConversationChunk->noOfPacket  ];
		}
		catch ( std::bad_alloc &ba ){
			std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
				<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
				<<__TIME__<<"]E xception "<<ba.what()<<std::endl;
			exit ( -1 );
			return NULL;
		}
		newConversation->converationId = newConversationId + 10 ;
		newConversation->seqNumber =newSequenceNo + 10;//  fullConversationChunk->seqNumber;
		newConversation->noOfPacket = 2 ;
		//have to delete
		/*newConversation->actRawData [ 0 ].data = new STUB_CHAR[ 5000 ];
		newConversation->actRawData [ 1 ].data = new STUB_CHAR[ 5000 ];
		newConversation->actRawData [2 ].data = new STUB_CHAR [5000 ];
		*/

		
	}
	//now coppy the data pasrt untill the to packet offset position.
	for ( STUB_INT i = fromPacket ; i<=toPacket ;  i++ ){
		newConversation->actRawData[ i ].appServer =
		      	fullConversationChunk->actRawData [ i ].appServer;
		newConversation->actRawData[ i ].packetNumber =  
			fullConversationChunk->actRawData [ i ].packetNumber;
		if ( i != toPacket ){
			try {
				newConversation->actRawData [ i ].data = 
					new STUB_CHAR[ fullConversationChunk->actRawData[i].length ];
				newConversation->actRawData [ i ].length = 
					fullConversationChunk->actRawData[ i ].length ;
			}
			catch ( std::bad_alloc &ba ){
				std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "
					<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["
					<<__DATE__<<"_"<<__TIME__<<"]Exception"<<ba.what()<<std::endl;
				exit( -1 );
			}
			memcpy ( newConversation->actRawData [ i ].data , 
					fullConversationChunk->actRawData [ i ].data ,
				       	fullConversationChunk->actRawData [ i ].length );
		}
		else {
			try { 
				// lengthOfNewData+=1024;
				newConversation->actRawData [ i ].data = 
					new STUB_CHAR[ lengthOfNewData];
				newConversation->actRawData [ i ].length = 
					lengthOfNewData ;
			}   
			catch ( std::bad_alloc &ba ){
				std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "
					<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["
					<<__DATE__<<"_"<<__TIME__<<"] Exception"<<ba.what()
					<<std::endl;
				exit ( -1 );
			}
#ifdef DEBUG
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
				<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
				<<__TIME__<<"]"<<"Before memcpy:\n"<<"LENGTH:"
				<<newConversation->actRawData [ i ].length<<'\n';
#endif
			memcpy ( newConversation->actRawData [ i ].data + 0, 
					fullConversationChunk->actRawData[ i ].data + 0,
				       	offsetOfToPacket  );//offsetOfToPacket
			//  file5<<"\nnewConversation->actRawData->length: "<<newConversation->actRawData[i].length<<"\n";
			//  file5<<"New conv header + null data: ";
			//  for(STUB_INT j=0;j<newConversation->actRawData[i].length;j++)
			//      file5<<newConversation->actRawData [ i ].data[j];
			//  file5<<"\n";
		}
	}
	//file5.close();
	return true;
}

queryPacketJson QueryPacket ;
insertRowValues colByColDataTogether;

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  deleteActSeriesStruct
 *  Description:  delete the struct
 * =====================================================================================
 */
bool deleteActSeriesStruct( actSeriesStruct *& packet ){
	
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	if ( packet == NULL ) return true;
	try{
		for ( STUB_INT sequenceNo = 0 ; sequenceNo < packet->noOfPacket ; ++ sequenceNo ){
			delete [] packet->actRawData[sequenceNo ].data;
			//delete packet->actRawData;
		}
		delete packet;
	}
	catch ( std::exception &e ){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"]"<<"Exception:"<<e.what()<<'\n';
		return false;
	}
	return true;
}

