/*
 * =====================================================================================
 *
 *       Filename:  capture_packet_db.cpp
 *
 *    Description:  implementation of capture_packet.hpp
 *
 *        Version:  1.0
 *        Created:  Wednesday 06 November 2013 02:39:13  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy (),
 *   Organization:  SELF
 *
 * =====================================================================================
 */

#include "capture_packet_db.hpp"
//
// 	CLASS ------ CaptureDbSetting-----------
//
captureDb::CaptureDbSetting::CaptureDbSetting() {} //constructor
captureDb::CaptureDbSetting::~CaptureDbSetting(){} // destructor
bool captureDb::CaptureDbSetting::insertCaptureConfiguration ( ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	captureQuery::CaptureDbSettingQuery capSetting;
	return ( capSetting.insertCaptureConfiguration (  ) );
}
//
//     CLASS------------------- RemoteServer -----------------------------
//
captureDb::RemoteServer::RemoteServer( ) {}
captureDb::RemoteServer::~RemoteServer() {}

bool captureDb::RemoteServer::addNewServerInfo( void ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	captureQuery::RemoteServerQuery remoteServer;
	return ( remoteServer.addNewServerInfo() );
}

serverStruct * captureDb::RemoteServer::displayServerTable( void ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	captureQuery::RemoteServerQuery remoteServer;
	return ( remoteServer.displayServerTable() );
}



//
//     CLASS STORERAWPACKET-----------------------------------
//     -----------------------------------------------------------------
STUB_INT captureDb::currentConversationId = -1;
STUB_INT captureDb::currentConversationPacketSequence = -1;
bool captureDb::synFin = false;
STUB_INT captureDb::packetNumber = -1;
captureDb::StoreRawPacket::StoreRawPacket(){}

captureDb::StoreRawPacket::~StoreRawPacket(){}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  copyPacket
 *  Description:  store current packet's information like seq no , ack no in client| server array
 * =====================================================================================
 */
bool captureDb::StoreRawPacket::copyPacket ( bool cliServer , conversation *currentConversation , rawDataStruct *rawData ){ //true if app
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	if ( currentConversationId < 0 ) return false;
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<"[CLIENT array index]>"<<currentConversation->currentPositionClientArray<<
		"[SERVER array index]>"<<currentConversation->currentPositionServerArray<<'\n';
	try{
		if ( cliServer ){ // this is a client packet
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<"client packet\n";
			currentConversation->allPreviousPacketClient [  (++ currentConversation->currentPositionClientArray ) ].prevSequenceNumber = rawData->sequenceNumber;
			currentConversation->allPreviousPacketClient [ currentConversation->currentPositionClientArray ].prevAcknowledgeNumber = rawData->acknowledgeNumber;
			currentConversation->allPreviousPacketClient [ currentConversation->currentPositionClientArray ].prevLength = rawData->length;
			currentConversation->allPreviousPacketClient [ currentConversation->currentPositionClientArray ].tcpFlag.ACK = rawData->tcpFlag.ACK;
			
		}
		else {
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<"server packet\n";
			currentConversation->allPreviousPacketServer [ ( ++currentConversation->currentPositionServerArray  ) ].prevSequenceNumber = rawData->sequenceNumber;
			currentConversation->allPreviousPacketServer [ currentConversation->currentPositionServerArray ].prevAcknowledgeNumber = rawData->acknowledgeNumber;
			currentConversation->allPreviousPacketServer [ currentConversation->currentPositionServerArray ].prevLength = rawData->length;
			currentConversation->allPreviousPacketServer [ currentConversation->currentPositionClientArray ].tcpFlag.ACK = rawData->tcpFlag.ACK;
			
		}
	}
	catch ( std::exception &ea){
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<"Exception:"<<ea.what();
		exit (0 );
		}
    return true;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  searchMother
 *  Description:  check current packet belongs ro current conversaion or not
 * =====================================================================================
 */
bool captureDb::StoreRawPacket::searchMother( bool cliServer  , conversation  *currentConversation , rawDataStruct *rawData){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"FUNCTION:"<<__FUNCTION__<<'\n';;
	if ( currentConversationId < 0 ) return false;
	if ( cliServer ){
		for ( STUB_INT i = currentConversation->currentPositionServerArray ; i>=0 ; i -- ){
			if ( ( rawData->acknowledgeNumber == currentConversation->allPreviousPacketServer [ i ].prevAcknowledgeNumber ) && ( rawData->sequenceNumber ==  ( currentConversation->allPreviousPacketServer [ i ].prevSequenceNumber + currentConversation->allPreviousPacketServer [ i ].prevLength ) ))
				return true;
		}
		return false;
	} else {
		for ( STUB_INT i = currentConversation->currentPositionClientArray ; i>=0 ; i -- ){
			if ( ( rawData->acknowledgeNumber == currentConversation->allPreviousPacketClient [ i ].prevAcknowledgeNumber )&& ( rawData->sequenceNumber == currentConversation->allPreviousPacketClient [ i ].prevSequenceNumber +currentConversation->allPreviousPacketClient [ i ].prevLength  ) )
				return true;
			
		}
		return false;
	}
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  checkSimultaneouslyNewPacket
 *  Description:  method for checking two simultaneous new packet
 * =====================================================================================
 */
bool captureDb::StoreRawPacket::checkSimultaneouslyNewPacket ( bool cliServer , conversation *currentConversation , rawDataStruct *rawData ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"FUNCTION:"<<__FUNCTION__<<'\n';
	if ( currentConversationId < 0 ) return false;
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<"Current position CLIENT  array\t"<<currentConversation->currentPositionClientArray
		<<"currnet position SERVER array\t"<<currentConversation->currentPositionServerArray<<'\n';

	/*-----------------------------------------------------------------------------
	 *  check whether the packet is client packet or server packet
	 *  if the packet is client packet then check previous client packet, if both ack no are same and current packet's seq no = old seq + length then it's avalid new packet
	 *-----------------------------------------------------------------------------*/
	if ( cliServer ){ //client packet
		for ( STUB_INT i = currentConversation->currentPositionClientArray ; i>= 0 ; -- i ){
			if ( ( rawData->sequenceNumber == ( currentConversation->allPreviousPacketClient [ i ].prevSequenceNumber + currentConversation->allPreviousPacketClient [ i ].prevLength ) ) && ( rawData->acknowledgeNumber == currentConversation->allPreviousPacketClient [ i ].prevAcknowledgeNumber ) )
				return true;
		}
		return false;
	}
	else {
		//server packet 
		for ( STUB_INT i = currentConversation->currentPositionServerArray ; i>=0 ; -- i ){
			if ( ( rawData->sequenceNumber == ( currentConversation->allPreviousPacketServer [ i ].prevSequenceNumber + currentConversation->allPreviousPacketServer[ i ].prevLength ) ) && ( rawData->acknowledgeNumber == currentConversation->allPreviousPacketServer[ i ].prevAcknowledgeNumber ) ){
				std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<"previous seq no : "<<currentConversation->allPreviousPacketServer [ i ].prevSequenceNumber<<'\n'
					<<"previous length   :"<<currentConversation->allPreviousPacketServer [ i ].prevLength <<'\n'
					<<"previous acknowledgement no =  :"<<currentConversation->allPreviousPacketServer [ i ].prevAcknowledgeNumber<<'\n';
				return true;
			} 
		}
		return false ;
	}
	return false;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  validPack
 *  Description:  check current packet is a valid acknowledgement packet ornot ( RESPONSE )
 * =====================================================================================
 */
bool captureDb::StoreRawPacket::validPack ( bool cliServer , conversation *currentConversation , rawDataStruct *rawData){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"FUNCTION:"<<__FUNCTION__<<'\n';
	if ( currentConversationId < 0 ) return false;
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<"[CLIENT  array index]:"<<currentConversation->currentPositionClientArray
		<<"[SERVER array index]"<<currentConversation->currentPositionServerArray<<'\n';

	/*-----------------------------------------------------------------------------
	 *  check whether the packet is client packet or server packet
	 *-----------------------------------------------------------------------------*/
	if ( cliServer ){ 
		//if the packet is server packet
		for ( STUB_INT i = currentConversation->currentPositionClientArray ; i>= 0 ; -- i ){
			if ( ( rawData->acknowledgeNumber == ( currentConversation->allPreviousPacketClient [ i ].prevSequenceNumber + currentConversation->allPreviousPacketClient [ i ].prevLength ) ) && ( rawData->sequenceNumber == currentConversation->allPreviousPacketClient [ i ].prevAcknowledgeNumber ) )
				return true;
			
		}
		return false ;
		
	}  else {
		//if the packet is client packet
		for ( STUB_INT i = currentConversation->currentPositionServerArray ; i>=0 ; -- i ){
			if ( ( rawData->acknowledgeNumber == ( currentConversation->allPreviousPacketServer [ i ].prevSequenceNumber + currentConversation->allPreviousPacketServer[ i ].prevLength ) ) && ( rawData->sequenceNumber == currentConversation->allPreviousPacketServer[ i ].prevAcknowledgeNumber ) ){
				std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<"previous seq no : "<<currentConversation->allPreviousPacketServer [ i ].prevSequenceNumber<<std::endl
					<<"previous length   :"<<currentConversation->allPreviousPacketServer [ i ].prevLength <<std::endl
					<<"previous acknowledgement no =  :"<<currentConversation->allPreviousPacketServer [ i ].prevAcknowledgeNumber<<'\n';
				return true;
			}
		}
		return false ;
		
	}
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  checkDbGreeting
 *  Description:  check the packet is a db greeting packet or not---- need to update
 * =====================================================================================
 */
bool captureDb::StoreRawPacket::checkDbGreeting ( conversation *currentConversation , rawDataStruct *rawData ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	if ( currentConversationId == -1 ) return true;
	else {
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<"checkDBGreeting "<<currentConversationId<<std::endl;
		return false ;
		
	}

	// THIS CODE BELOW HAVE TO BE MODIFY
	for ( STUB_INT i = currentConversation->currentPositionClientArray ; i>= 0 ; -- i ){
		if ( ( currentConversation->allPreviousPacketClient [ i ].prevLength == 0 ) && ( currentConversation->allPreviousPacketClient [ i ].tcpFlag.ACK ) && ( rawData->acknowledgeNumber == currentConversation->allPreviousPacketClient [ i ].prevSequenceNumber + currentConversation->allPreviousPacketClient [ i ].prevLength ) && ( rawData->sequenceNumber == currentConversation->allPreviousPacketClient [ i ].prevAcknowledgeNumber ) )
			return true;
		
	}
	return false;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  packetHandler
 *  Description:  group network packets under an unique conversation ID and store the 
 *  packets into database.
 * =====================================================================================
 */
 
bool captureDb::StoreRawPacket::packetHandler ( rawDataStruct *rawData ){
	
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	/*-----------------------------------------------------------------------------
	 *  check if packet is a threeway handshaking or connection termination or not
	 *  if it's of that type then no need to save the packet , because client server will 
	 *  autometic takecare of those
	 *-----------------------------------------------------------------------------*/
    if ( rawData->tcpFlag.SYN || rawData->tcpFlag.FIN  ){
        synFin = true;
        std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<"packet with syn or fin \n";
        return true;
    }

    captureQuery::StoreRawPacketQuery queryHandlerInstance;

    /*-----------------------------------------------------------------------------
     *  if synflag is true that means next packet of acknowledgement also no need to save
     *  now consider whether packet coming for CLIENT(APP) or SERVER ( DB )
     *-----------------------------------------------------------------------------*/
    if ( rawData->sourcePort != 3306 ){
        std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<"PACKET COMING FROM CLIENT(APPLICATION)\n";

	/*-----------------------------------------------------------------------------
	 *  check whether the packet is acknowledgement packet or not
	 *  for acknowledgement packet length pf the packet is 0 and ACK flag is set
	 *-----------------------------------------------------------------------------*/
        if ( ( rawData->length == 0 )  && rawData->tcpFlag.ACK ){
            if ( synFin ){// if previous packet was connection setup or terminated packet
                std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<"prev packet was connection termineted packet\n";
                synFin = false;
                return true;

            }
		 
	    /*-----------------------------------------------------------------------------
	     *  now search valid ACK packet for the previous packets( source: SERVER ) of 
	     *  current conversation.
	     *  set rcvack field
	     *  if valid ACK found then store the packet
	     *-----------------------------------------------------------------------------*/
            std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<"conversation id \t"<<currentConversationId<<'\n';
		
            if ( validPack ( false , &conversationDiary [ currentConversationId ] , rawData ) ){
                std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<"it's a valid acknowledgement packet of this conversation\n";
                //store tis packet into packet with respect to current conversationId
                queryHandlerInstance.insertPacket( true , currentConversationId , ++packetNumber , rawData);
                copyPacket ( true ,&conversationDiary [ currentConversationId ] , rawData );
                return true;
            }
        }
	/*-----------------------------------------------------------------------------
	 *  for new client packet--  
	 *-----------------------------------------------------------------------------*/
        if ( (validPack ( false , &conversationDiary [ currentConversationId ] , rawData )) || checkSimultaneouslyNewPacket( true , &conversationDiary [ currentConversationId] , rawData ) ){// !

		/*-----------------------------------------------------------------------------
		 *  coppy the current packet into conversation diary
		 *-----------------------------------------------------------------------------*/
		copyPacket ( true , &conversationDiary [ ++currentConversationId ] , rawData );
		
		/*-----------------------------------------------------------------------------
		 *  insert the new packet into PACKET_SETTING_scenarioName and PACKET_scenarioName table
		 *
		 *-----------------------------------------------------------------------------*/
		if ( queryHandlerInstance.insertPacketSetting ( true , currentConversationId , ++packetNumber , rawData ) ){
		    if ( queryHandlerInstance.insertPacket ( true , currentConversationId , packetNumber , rawData) )
			    return true ;
		    else return false;
		    
	    }
	    return false ;
			
        }
        //else for sure it is a Middle pack
        if ( searchMother ( false ,&conversationDiary [ currentConversationId ] , rawData ) ){
		copyPacket ( true , &conversationDiary [ currentConversationId ] , rawData);
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<"Middle packet \n";
		if ( queryHandlerInstance.insertPacket ( true , currentConversationId , ++packetNumber , rawData) ){
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<"middle packet inserted\n";
			return true ;
			
		}
		else return false;
		
	}

        //updated on 7-12 for the error --- when a single select query coming without any DB greetings the first packet from app was not capturing,
        //but if db handshaking occurs 1st then it's being captured
        else {
         copyPacket ( true , &conversationDiary [ ++currentConversationId ] , rawData );
        if ( queryHandlerInstance.insertPacketSetting ( true , currentConversationId , ++packetNumber ,rawData) ){
            std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<"now insert packet\n";
            queryHandlerInstance.insertPacket ( true , currentConversationId ,  packetNumber , rawData );
                    return true;
                }
        }

		
    }
		
    /*-----------------------------------------------------------------------------
     *  else packet is a SERVER packet
     *-----------------------------------------------------------------------------*/
    else {
	    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<"it is a SERVER packet\n";
	    if ( ( rawData->length == 0 )  && rawData->tcpFlag.ACK ){
		    if ( synFin ){// if previous packet was connection setup or terminated packet
			    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<"previous packet was connection termineted packet or ack\n";
			    return true;
			    
		    }

		    /*-----------------------------------------------------------------------------
		     *  check whether the packet is a valid response packet from server or not
		     *  if yes then insert it into PACKET_scenarioName table
		     *-----------------------------------------------------------------------------*/
		    if ( validPack ( true , &conversationDiary [ currentConversationId ] , rawData) ){
			    copyPacket ( false , &conversationDiary [ currentConversationId ] , rawData );
			    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<"it's a valid acknowledgement packet of this conversation\n";
			    //store tis packet into packet with respect to current conversationId
			    if (queryHandlerInstance.insertPacket ( false , currentConversationId , ++packetNumber , rawData ) ){
				    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<"ACK packet inserted \n";
				    return true;
				    
			    }
		    }
	    }
	    
	    /*-----------------------------------------------------------------------------
	     *  check whether the packet is a freash new paket ?
	     *-----------------------------------------------------------------------------*/
	    if ( validPack ( true , &conversationDiary [ currentConversationId ] , rawData) ){ // !
		    if ( checkDbGreeting ( &conversationDiary [ currentConversationId ] , rawData ) ){
			    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<"This is a greetings packet from db\n";
			    if ( queryHandlerInstance.insertDbGreeting  ( ++currentConversationId , ++packetNumber , rawData) ){
				    queryHandlerInstance.insertPacket  ( false , currentConversationId , packetNumber , rawData);
				    copyPacket ( false , &conversationDiary [ currentConversationId ] , rawData );
				    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<"inserted into greeting sd \n";
				    return true;
				    
			    }
			    
		    }
		    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<"it is a reply data\n";
		    if ( queryHandlerInstance.insertPacket ( false , currentConversationId , ++ packetNumber , rawData) ){
			    copyPacket ( false , &conversationDiary [ currentConversationId ] , rawData );
			    return true;
			    
		    }
		    return false;
		    
	    }
	    //else for sure it is a Middle pack
	    if ( searchMother ( false , &conversationDiary [ currentConversationId ] , rawData ) ){
		    copyPacket ( true , &conversationDiary [ currentConversationId ] , rawData );
		    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<"Middle packet \n";
		    if ( queryHandlerInstance.insertPacket ( false , currentConversationId , ++ packetNumber , rawData ) ){
			    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<"Reply packet inserted \n";
			    return true;
		    }
		    return false;
	    }else {
		    /*-----------------------------------------------------------------------------
		     *  packet is a greeting packet from server--
		     *  when a new server greeting is coming have to errase previous packets from both array
		     *  for removing conflicttion.
		     *-----------------------------------------------------------------------------*/
		    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<"GREETING packet from SERVER \n";
		    /*-----------------------------------------------------------------------------
		     *  if server greeting appears more that one time under a scenario 
		     *-----------------------------------------------------------------------------*/
		    if( currentConversationId >= 0 ){
			    deleteConversationDiary();
			    initDataStructure();
		    }
		    if ( queryHandlerInstance.insertDbGreeting  ( ++currentConversationId , ++packetNumber , rawData) ){
			    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<"conversation id ="<<currentConversationId<<std::endl;
			    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<conversationDiary [ 0].conversationId<<"check"<<std::endl;
			    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<conversationDiary->currentPositionServerArray<<std::endl;
			    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<"conversationDiary->currentPositionServerArray"<<conversationDiary->currentPositionServerArray<<std::endl;
			    conversationDiary->allPreviousPacketServer [  ( conversationDiary->currentPositionServerArray ) ].prevSequenceNumber = rawData->sequenceNumber;
			    //currentConversation->allPreviousPacketServer [++ ( currentConversation->currentPositionServerArray  ) ].prevSequenceNumber = rawData.sequenceNumber;
			    captureDb::StoreRawPacket::copyPacket ( false , &conversationDiary [ currentConversationId ] , rawData );
			    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<"app array\t"<<conversationDiary [currentConversationId].currentPositionClientArray
				    <<"db arraarrau**************** \t"<<conversationDiary [currentConversationId].currentPositionServerArray
				    <<"conversation Id\t"<<currentConversationId<<std::endl;
			    if ( queryHandlerInstance.insertPacketSetting ( false , currentConversationId , packetNumber ,rawData) ){
				    queryHandlerInstance.insertPacket ( false , currentConversationId ,  packetNumber , rawData );
				    return true;
			    }else{
				    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<"Cant insert packet\n";
				    return false;
			    }
			    return true;
		    }else {
			    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<"cant insert into greeting DB\n";
			    return false;
		    }
	    }
    }
    return false;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  updateQueryTypeQueryAtDatabase
 *  Description:  update the PACKET_SETTING_scenarioName table after capturig and storing
 *  all the packets into PACKET_SETTING_* and PACKET_* tables.
 *  will update query string and type for all 1st packet coming from client
 * =====================================================================================
 */
bool captureDb::StoreRawPacket::updateQueryTypeQueryAtDatabase ( ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"FUNCTION:"<<__FUNCTION__<<'\n';
	// frist create an instance of StoreRawPacketQuery
	captureQuery::StoreRawPacketQuery *instance ;
	try {
		instance = new captureQuery::StoreRawPacketQuery ();
		    
        }
        catch ( std::bad_alloc &ba ){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"Function name["<<__FUNCTION__<<"] Line ["<<__LINE__<<"]"<<"exception cought "<<ba.what()<<std::endl;
		exit ( -1 );
	}
        actRawDataStruct *packetSettingDataArray= instance->selectPacketSetting ();
        // now we have all packets of table PACKET_SETTING_ for the particular scenario.
        //now for each raw packet dissect and update.
        STUB_INT totalPacket = instance->getCountPacketSetting();
	STUB_INT currentPacket = -1;
        queryData *queryDataArray ;
        try{
            queryDataArray = new queryData [ totalPacket + 1 ];
            
            }
        catch ( std::bad_alloc &ba ){
            std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"Function name["<<__FUNCTION__<<"] Line ["<<__LINE__<<"]"<<"exception caught "<<ba.what()<<std::endl;
	    exit ( -1 );
        }
	for ( STUB_INT i = 0 ; i < totalPacket ;++i ){
		try{
			boost::any_cast< bool ( * )( actRawDataStruct * , queryData *& , STUB_INT )> ( boost::get < boost::any > ( proto::Proto::initDissect( packetSettingDataArray [ i].protocolName , 1 ) ) )  ( packetSettingDataArray ,  queryDataArray , i );
		}
		catch ( std::exception &e ){
			std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"EXCEPTION:"<<e.what()<<'\n';
			exit ( 0 );
			
		}
	}
	for ( STUB_INT i = 0 ; i<totalPacket ; ++i){
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<queryDataArray[i].query<<std::endl;
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<'\n'<<queryDataArray[i].queryType<<std::endl;

	}

        instance->updatePacketSettingApp( queryDataArray , totalPacket  );
	//now delete the elements created by new.
	try{
		delete []queryDataArray;
		delete instance;
		delete []packetSettingDataArray;
	}
	catch ( std::exception &e ){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"EXCEPTION:"<<e.what()<<'\n';
		return false;
	}
exit(0);
        return true;
}
