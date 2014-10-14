#include "structure.hpp"

//configStruct.hpp
configTcpStub configTcpFile;

//database structure
databaseStruct dbCredentials;

serverStruct serverCredentials;

//rawdatastruct.hpp
#define size 1000
//rawDataStruct rawData;

conversation  conversationDiary[1000];// = new conversationDiary [ 10 ];

prevPacket pastData;

bool initDataStructure (){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__
		<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";
	for ( STUB_INT i = 0 ; i<1000 ; i++ ){//maximun 1000 conversation can be gen and each conv can contain max 10 APP and DB packets.
		conversationDiary [ i ] .currentPositionAppArray = -1;
		conversationDiary [ i ].currentPositionDbArray = -1;
		conversationDiary [ i ].allPreviousPacketApp =
		       	new prevPacket [ 10 ];
		conversationDiary [ i ].allPreviousPacketDb =
		       	new prevPacket [ 10 ];
}
    return true;
}



void printData ( STUB_INT communicationId ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		<<"][App array current position]:"
		<<conversationDiary [ communicationId ] .currentPositionAppArray<<'\n';
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		<<"][DB array index current position]:"
		<<conversationDiary [ communicationId ] .currentPositionDbArray<<'\n';
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		<<"][previous APP packets]---> \n";
	for ( STUB_INT i = 0 ; i<=conversationDiary[ communicationId ].currentPositionAppArray ;
		       	++i ){
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"]-----App packet----\n";
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"][Packet No]:"<<i<<'\n';
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"][sequence no]:"
			<< conversationDiary [ communicationId ].allPreviousPacketApp [ i ].prevSequenceNumber<<'\n';
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"][Acknowledge no]"
			<<conversationDiary [ communicationId ].allPreviousPacketApp [ i ].prevAcknowledgeNumber<<'\n';
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"][Length ]"
			<<conversationDiary [ communicationId ] .allPreviousPacketApp [ i ].prevLength<<'\n';
		
	}
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__
		<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]: previous DB packets \n";
	for ( STUB_INT i = 0 ; i<=conversationDiary[ communicationId ].currentPositionDbArray ;
		       	++i ){
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"]-------DB packet=---------n";
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"][Packet No]"<<i<<'\n';
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"][Sequence no]"
			<< conversationDiary [ communicationId ].allPreviousPacketDb [ i ].prevSequenceNumber<<'\n';
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"][Acknowledge no]"
			<<conversationDiary [ communicationId ].allPreviousPacketDb [ i ].prevAcknowledgeNumber<<'\n';
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"][Length]"
			<<conversationDiary [ communicationId ] .allPreviousPacketDb [ i ].prevLength<<'\n';
		
	}
}

//for dummy server

actSeriesStruct actConversationDiary [  1000 ] ; //maximum act conversation diary is 1000.

//function implementation for acopConversationUntill a packet
//this function will copy a conversation until topacket is reached and will copy the data part of toPacket until offset.

actSeriesStruct *newConversationPack;
bool copyConversationPartially ( actSeriesStruct *&newConversation ,  
		actSeriesStruct *fullConversationChunk , STUB_INT fromPacket ,
	       	STUB_INT toPacket , STUB_INT offsetOfToPacket , STUB_INT lengthOfNewData ) {
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"]\n";
	//fetch the new possible conversation id for this conversation
	STUB_INT newConversationId = 0 ;// wrie a function for db to know the letest conversation ID
	STUB_INT newSequenceNo = 0; // get the latest seq no from db and increaent by 1.
	if ( fromPacket == 0 ){ // first time for thos conversation to create a new conversation
		try{
			newConversation = new actSeriesStruct();
			(newConversation)->actRawData = 
				new actRawDataStruct [ fullConversationChunk->noOfPacket + 5 ];
		}
		catch ( std::bad_alloc &ba ){
			std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
				<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__
				<<"_"<<__TIME__<<"] Exception "<<ba.what()<<std::endl;
			exit ( -1 );
			return NULL;
		}
		newConversation->converationId = newConversationId + 1 ;
		newConversation->seqNumber =newSequenceNo + 1;//  fullConversationChunk->seqNumber;
		newConversation->noOfPacket = 2 ;
		//have to delete
		newConversation->actRawData [ 0 ].data = new STUB_CHAR[ 5000 ];
		newConversation->actRawData [ 1 ].data = new STUB_CHAR[ 5000 ];
		
	}
	//now coppy the data pasrt untill the to packet offset position.
	for ( STUB_INT i = fromPacket ; i<=toPacket ;  i++ ){
		newConversation->actRawData[ i ].appServer = 
		       	fullConversationChunk->actRawData [ i ].appServer;
		newConversation->actRawData[ i ].packetNumber = 
		       	fullConversationChunk->actRawData [ i ].packetNumber;
		if ( i != toPacket ){
			try {
				// newConversation->actRawData [ i ].data = new STUB_CHAR[ fullConversationChunk->actRawData[i].length ];
				newConversation->actRawData [ i ].length = 
					fullConversationChunk->actRawData[ i ].length ;
			}
			catch ( std::bad_alloc &ba ){
				std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "
					<<__FUNCTION__<<"] Line ["<<__LINE__<<"] Dat\
					eTime ["<<__DATE__<<"_"<<__TIME__
					<<"] Exception"<<ba.what()<<std::endl;
				exit( -1 );
			}
			memcpy ( newConversation->actRawData [ i ].data , 
					fullConversationChunk->actRawData [ i ].data ,
				       	fullConversationChunk->actRawData [ i ].length );
		}
		else {
			try { 
				// lengthOfNewData+=1024;
			//	newConversation->actRawData [ i ].data = new STUB_CHAR[ lengthOfNewData];
				newConversation->actRawData [ i ].length = lengthOfNewData ;
			}   
			catch ( std::bad_alloc &ba ){
				std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "
					<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateT\
					ime ["<<__DATE__<<"_"<<__TIME__
					<<"] Exception"<<ba.what()<<std::endl;
				exit ( -1 );
			}
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


//scenariostruct.hpp
scenarioInformation scenInfo;
