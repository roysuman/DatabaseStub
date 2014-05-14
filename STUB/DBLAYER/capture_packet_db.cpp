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
 *   Organization:  Cognizant Technological solutions
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
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	captureQuery::CaptureDbSettingQuery capSetting;
	return ( capSetting.insertCaptureConfiguration (  ) );
}
//
//     CLASS------------------- RemoteServer -----------------------------
//
captureDb::RemoteServer::RemoteServer( ) {}
captureDb::RemoteServer::~RemoteServer() {}

bool captureDb::RemoteServer::addNewServerInfo( void ){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	captureQuery::RemoteServerQuery remoteServer;
	return ( remoteServer.addNewServerInfo() );
}

serverStruct * captureDb::RemoteServer::displayServerTable( void ){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	captureQuery::RemoteServerQuery remoteServer;
	return ( remoteServer.displayServerTable() );
}



//
//     CLASS STORERAWPACKET-----------------------------------
//     -----------------------------------------------------------------
int captureDb::currentConversationId = -1;
int captureDb::currentConversationPacketSequence = -1;
bool captureDb::synFin = false;
int captureDb::packetNumber = -1;
captureDb::StoreRawPacket::StoreRawPacket(){}

captureDb::StoreRawPacket::~StoreRawPacket(){}

/*for copying current credentials at prev packet
 *
 */
bool captureDb::StoreRawPacket::copyPacket ( bool appDb , conversation *currentConversation , rawDataStruct *rawData ){ //true if app
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	if ( currentConversationId < 0 ) return false;
	std::cout<<__FUNCTION__<<"app array\t"<<currentConversation->currentPositionAppArray<<
		"db arrau \t"<<currentConversation->currentPositionDbArray<<std::endl;
	try{
		if ( appDb ){
			std::cout<<__FUNCTION__<<"packe is a app packet"<<std::endl;
			currentConversation->allPreviousPacketApp [  (++ currentConversation->currentPositionAppArray ) ].prevSequenceNumber = rawData->sequenceNumber;
			currentConversation->allPreviousPacketApp [ currentConversation->currentPositionAppArray ].prevAcknowledgeNumber = rawData->acknowledgeNumber;
			currentConversation->allPreviousPacketApp [ currentConversation->currentPositionAppArray ].prevLength = rawData->length;
			currentConversation->allPreviousPacketApp [ currentConversation->currentPositionAppArray ].tcpFlag.ACK = rawData->tcpFlag.ACK;
			
		}
		else {
			std::cout<<__FUNCTION__<<"packe is a db packet\n";
			currentConversation->allPreviousPacketDb [ ( ++currentConversation->currentPositionDbArray  ) ].prevSequenceNumber = rawData->sequenceNumber;
			currentConversation->allPreviousPacketDb [ currentConversation->currentPositionDbArray ].prevAcknowledgeNumber = rawData->acknowledgeNumber;
			currentConversation->allPreviousPacketDb [ currentConversation->currentPositionDbArray ].prevLength = rawData->length;
			currentConversation->allPreviousPacketDb [ currentConversation->currentPositionAppArray ].tcpFlag.ACK = rawData->tcpFlag.ACK;
			
		}
	}
	catch ( std::exception &ea){
		std::cout<<__FUNCTION__<<"Exception:"<<ea.what();
		exit (0 );
		}

//std::cout<<"packe is a db packet"<<std::endl;
//std::cout<<"app array\t"<<currentConversation.currentPositionAppArray<<
//"db arrau \t"<<currentConversation.currentPositionDbArray<<std::endl;
    return true;
}


/*
 * search that this opacket is conti.. for this conversation or not
 * */
bool captureDb::StoreRawPacket::searchMother( bool appDb  , conversation  *currentConversation , rawDataStruct *rawData){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	if ( currentConversationId < 0 ) return false;
	if ( appDb ){
		for ( int i = currentConversation->currentPositionDbArray ; i>=0 ; i -- ){
			if ( ( rawData->acknowledgeNumber == currentConversation->allPreviousPacketDb [ i ].prevAcknowledgeNumber ) && ( rawData->sequenceNumber ==  ( currentConversation->allPreviousPacketDb [ i ].prevSequenceNumber + currentConversation->allPreviousPacketDb [ i ].prevLength ) ))
				return true;
			
		}
		return false;
		
	} else {
		for ( int i = currentConversation->currentPositionAppArray ; i>=0 ; i -- ){
			if ( ( rawData->acknowledgeNumber == currentConversation->allPreviousPacketApp [ i ].prevAcknowledgeNumber )&& ( rawData->sequenceNumber == currentConversation->allPreviousPacketApp [ i ].prevSequenceNumber +currentConversation->allPreviousPacketApp [ i ].prevLength  ) )
				return true;
			
		}
		return false;
		
	}
}

/*
 * functiopn to calculate valid ack
 * */
bool captureDb::StoreRawPacket::validPack ( bool appDb , conversation *currentConversation , rawDataStruct *rawData){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	if ( currentConversationId < 0 ) return false;
	std::cout<<__FUNCTION__<<"Current position app array\t"<<currentConversation->currentPositionAppArray
		<<"currnet db array\t"<<currentConversation->currentPositionDbArray<<std::endl;
	if ( appDb ){ // check ack with respect to previous app packets
		for ( int i = currentConversation->currentPositionAppArray ; i>= 0 ; -- i ){
			if ( ( rawData->acknowledgeNumber == ( currentConversation->allPreviousPacketApp [ i ].prevSequenceNumber + currentConversation->allPreviousPacketApp [ i ].prevLength ) ) && ( rawData->sequenceNumber == currentConversation->allPreviousPacketApp [ i ].prevAcknowledgeNumber ) )
				return true;
			
		}
		return false ;
		
	}  else {
		std::cout<<__FUNCTION__<<"inside false part of function valid packet\n";
		for ( int i = currentConversation->currentPositionDbArray ; i>=0 ; -- i ){
			if ( ( rawData->acknowledgeNumber == ( currentConversation->allPreviousPacketDb [ i ].prevSequenceNumber + currentConversation->allPreviousPacketDb[ i ].prevLength ) ) && ( rawData->sequenceNumber == currentConversation->allPreviousPacketDb[ i ].prevAcknowledgeNumber ) ){
				std::cout<<__FUNCTION__<<"return ning true \n";
				std::cout<<__FUNCTION__<<"previous seq no : "<<currentConversation->allPreviousPacketDb [ i ].prevSequenceNumber<<std::endl
					<<"previous length   :"<<currentConversation->allPreviousPacketDb [ i ].prevLength <<std::endl
					<<"previous acknowledgement no =  :"<<currentConversation->allPreviousPacketDb [ i ].prevAcknowledgeNumber<<std::endl;
				return true;
			}
		}
		std::cout<<__FUNCTION__<<"return ning false \n";
		return false ;
		
	}
}

bool captureDb::StoreRawPacket::checkDbGreeting ( conversation *currentConversation , rawDataStruct *rawData ){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	if ( currentConversationId == -1 ) return true;
	else {
		std::cout<<__FUNCTION__<<"checkDBGreeting "<<currentConversationId<<std::endl;
		return false ;
		
	}

	// THIS CODE BELOW HAVE TO BE MODIFY
	for ( int i = currentConversation->currentPositionAppArray ; i>= 0 ; -- i ){
		if ( ( currentConversation->allPreviousPacketApp [ i ].prevLength == 0 ) && ( currentConversation->allPreviousPacketApp [ i ].tcpFlag.ACK ) && ( rawData->acknowledgeNumber == currentConversation->allPreviousPacketApp [ i ].prevSequenceNumber + currentConversation->allPreviousPacketApp [ i ].prevLength ) && ( rawData->sequenceNumber == currentConversation->allPreviousPacketApp [ i ].prevAcknowledgeNumber ) )
			return true;
		
	}
	return false;
}

 
bool captureDb::StoreRawPacket::packetHandler ( rawDataStruct *rawData ){
	
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	std::cout<<"to insert datat into db\n";
//	std::cout<<"DISSECT\n";
//	Mysql::dissect_mysql( rawData->data , rawData->length );
//	return true;


    //check if the packet is a three way handshaking or connection terminatioon or not
    //if it is of that type then no need to save the packet
    //because client server will autometic send those packets.
    if ( rawData->tcpFlag.SYN || rawData->tcpFlag.FIN  ){
        synFin = true;
        std::cout<<__FUNCTION__<<"packet with syn or fin \n";
        return true;
    }

    captureQuery::StoreRawPacketQuery queryHandlerInstance;

    //if the synFin flag is true that means next packet of acknowledgement also no need to save.
	
    //now consider the packet wheather coming from APP or DB
    //if the source port is  not 3306 then it's a packet coming from app
    if ( rawData->sourcePort != 3306 ){
        std::cout<<__FUNCTION__<<"APP PACKET \n";
        //check wheather th epacket is acknowledgement packet or not
        //for a acknowledgement packet length of the packet will be 0 and ACK flag
        //will be set
        if ( ( rawData->length == 0 )  && rawData->tcpFlag.ACK ){
            if ( synFin ){// if previous packet was connection setup or terminated packet
                std::cout<<__FUNCTION__<<"prev packet was connection termineted packet\n";
                synFin = false;
                return true;

            }
		 

            //now search valid ACK packet by searching all previous packet of this conversation came
            //from DB and make that packet rcvack field true.
            //if valid ack found then store it
            std::cout<<__FUNCTION__<<"conversation id \t"<<currentConversationId<<std::endl;
		
            if ( validPack ( false , &conversationDiary [ currentConversationId ] , rawData ) ){
                std::cout<<__FUNCTION__<<"it's a valid acknowledgement packet of this conversation\n";
                //store tis packet into packet with respect to current conversationId
                queryHandlerInstance.insertPacket( true , currentConversationId , ++packetNumber , rawData);
                copyPacket ( true ,&conversationDiary [ currentConversationId ] , rawData );
                return true;

		

            }
        }

        //check wheather the packet is a new packet or noti
	std::cout<<"control .. \n:";

        if ( (validPack ( false , &conversationDiary [ currentConversationId ] , rawData )) ){// !
            copyPacket ( true , &conversationDiary [ ++currentConversationId ] , rawData );

		
            std::cout<<__FUNCTION__<<"it is a new packet\n";
            if ( queryHandlerInstance.insertPacketSetting ( true , currentConversationId , ++packetNumber , rawData ) ){
                std::cout<<__FUNCTION__<<" inserted new packet info into PACKET_SETTING\n";
                if ( queryHandlerInstance.insertPacket ( true , currentConversationId , packetNumber , rawData) )
                    return true ;
                else return false;
				
            }
            return false ;
			
        }
        //else for sure it is a Middle pack
        if ( searchMother ( false ,&conversationDiary [ currentConversationId ] , rawData ) ){
            copyPacket ( true , &conversationDiary [ currentConversationId ] , rawData);
		
            std::cout<<__FUNCTION__<<"Middle packet \n";
            if ( queryHandlerInstance.insertPacket ( true , currentConversationId , ++packetNumber , rawData) ){
                std::cout<<__FUNCTION__<<"middle packet inserted\n";
                return true ;
            }
            else return false;
        }

        //updated on 7-12 for the error --- when a single select query coming without any DB greetings the first packet from app was not capturing,
        //but if db handshaking occurs 1st then it's being captured
        else {
         copyPacket ( true , &conversationDiary [ ++currentConversationId ] , rawData );
        if ( queryHandlerInstance.insertPacketSetting ( true , currentConversationId , ++packetNumber ,rawData) ){
            std::cout<<__FUNCTION__<<"now insert packet\n";
            queryHandlerInstance.insertPacket ( true , currentConversationId ,  packetNumber , rawData );
                    return true;
                }
        }

		
    }
		
    else {
        std::cout<<__FUNCTION__<<"it is a db packet\n";
    //	std::cout<<"Current position app array\t"<<conversationDiary [ currentConversationId ].currentPositionAppArray
    //	<<"currnet db array\t"<<conversationDiary [ currentConversationId ].currentPositionDbArray<<std::endl;
        if ( ( rawData->length == 0 )  && rawData->tcpFlag.ACK ){
            if ( synFin ){// if previous packet was connection setup or terminated packet
                std::cout<<__FUNCTION__<<"prev packet wa connection termineted packet or ack\n";
                return true;
            }

            if ( validPack ( true , &conversationDiary [ currentConversationId ] , rawData) ){
                copyPacket ( false , &conversationDiary [ currentConversationId ] , rawData );
		
                std::cout<<__FUNCTION__<<"it's a valid acknowledgement packet of this conversation\n";
                //store tis packet into packet with respect to current conversationId
                if (queryHandlerInstance.insertPacket ( false , currentConversationId , ++packetNumber , rawData ) ){
                    std::cout<<__FUNCTION__<<"ACK packet inserted \n";
                    return true;
                }

            }
        }

        //check wheather the packet is a new packet or not
        if ( validPack ( true , &conversationDiary [ currentConversationId ] , rawData) ){ // !
            if ( checkDbGreeting ( &conversationDiary [ currentConversationId ] , rawData ) ){
                std::cout<<__FUNCTION__<<"This is a greetings packet from db\n";
                 if ( queryHandlerInstance.insertDbGreeting  ( ++currentConversationId , ++packetNumber , rawData) ){
                     queryHandlerInstance.insertPacket  ( false , currentConversationId , packetNumber , rawData);
                     copyPacket ( false , &conversationDiary [ currentConversationId ] , rawData );
		
                     std::cout<<__FUNCTION__<<"inserted into greeting sd \n";

                     return true;
                 }
//                 else {
//                     std::cout<<"cant insert into greeting DB\n";
//                     return false;
//                 }

                    }

            std::cout<<__FUNCTION__<<"it is a reply data\n"<<std::endl;
            if ( queryHandlerInstance.insertPacket ( false , currentConversationId , ++ packetNumber , rawData) ){
                copyPacket ( false , &conversationDiary [ currentConversationId ] , rawData );
		
                std::cout<<__FUNCTION__<<"Reply packet inserted \n";
                return true;
            }
            return false;

            }
        //else for sure it is a Middle pack
        if ( searchMother ( false , &conversationDiary [ currentConversationId ] , rawData ) ){
            copyPacket ( true , &conversationDiary [ currentConversationId ] , rawData );
            std::cout<<__FUNCTION__<<"Middle packet \n";
            if ( queryHandlerInstance.insertPacket ( false , currentConversationId , ++ packetNumber , rawData ) ){
                std::cout<<__FUNCTION__<<"Reply packet inserted \n";
                return true;
					
                }
                return false;
				
        }
            else {
                std::cout<<__FUNCTION__<<"It's a db greetings \n";
                 if ( queryHandlerInstance.insertDbGreeting  ( ++currentConversationId , ++packetNumber , rawData) ){
                     std::cout<<__FUNCTION__<<"conversation id ="<<currentConversationId<<std::endl;

                    std::cout<<"line 294\n";
                    std::cout<<conversationDiary [ 0].conversationId<<"check"<<std::endl;
                    std::cout<<conversationDiary->currentPositionDbArray<<std::endl;
                    std::cout<<__FUNCTION__<<"conversationDiary->currentPositionDbArray"<<conversationDiary->currentPositionDbArray<<std::endl;
                    conversationDiary->allPreviousPacketDb [  ( conversationDiary->currentPositionDbArray ) ].prevSequenceNumber = rawData->sequenceNumber;
                    //currentConversation->allPreviousPacketDb [++ ( currentConversation->currentPositionDbArray  ) ].prevSequenceNumber = rawData.sequenceNumber;
                    captureDb::StoreRawPacket::copyPacket ( false , &conversationDiary [ currentConversationId ] , rawData );
                    std::cout<<__FUNCTION__<<"app array\t"<<conversationDiary [currentConversationId].currentPositionAppArray<<
			    "db arrau**************** \t"<<conversationDiary [currentConversationId].currentPositionDbArray<<
			    "conversation Id\t"<<currentConversationId<<std::endl;
		    if ( queryHandlerInstance.insertPacketSetting ( false , currentConversationId , packetNumber ,rawData) ){
                        std::cout<<__FUNCTION__<<"now insert packet\n";
                        queryHandlerInstance.insertPacket ( false , currentConversationId ,  packetNumber , rawData );
			return true;
                    }
					
//                    if ( queryHandlerInstance.insertPacket ( false , currentConversationId ,  packetNumber ) ){
//                        std::cout<<"Reply packet inserted \n";
//                        return true;
//
//                        }
                    else{
                            std::cout<<__FUNCTION__<<"Cant insert packet\n";
                            return false;
                        }
                     return true;
                 }
                 else {
                     std::cout<<__FUNCTION__<<"cant insert into greeting DB\n";
                     return false;
                 }
				
				
            }
			
    }
return false;
}

//the function to update the PACKET_SETTING_ table after capturing all packets and storing the packets at database. it will store the query type any query string
bool captureDb::StoreRawPacket::updateQueryTypeQueryAtDatabase ( ){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<'\n';
	// frist create an instance of StoreRawPacketQuery
	captureQuery::StoreRawPacketQuery *instance ;
	try {
		instance = new captureQuery::StoreRawPacketQuery ();
		    
        }
        catch ( std::bad_alloc &ba ){
		std::cerr<<__FUNCTION__<<"exception cought "<<ba.what()<<std::endl;
		exit ( -1 );
	}
        actRawDataStruct *packetSettingDataArray = instance->selectPacketSetting ();
        // now we have all packets of table PACKET_SETTING_ for the particular scenario.
        //now for each raw packet dissect and update.
        int currentPacket = -1;
        while ( packetSettingDataArray [ ++currentPacket ].length != -999 ){
            //now for each packet update the database. after dissecting the packet
            //diisect each packet.

        }
	std::cout<<"[COUNT]:"<<currentPacket<<'\n';
        //currentPacket contains the all packet numbers upto this point.
        //now create queryData array
        std::cout<<__FUNCTION__<<"current packet ="<<currentPacket<<'\n';
        queryData *queryDataArray ;
        try{
            queryDataArray = new queryData [ currentPacket + 1 ];
            
            }
        catch ( std::bad_alloc &ba ){
            std::cerr<<__FUNCTION__<<"exception caught "<<ba.what()<<std::endl;
	    exit ( -1 );
        }
        //nowdissect all packets.
        std::cout<<__FUNCTION__<<"NOW DISSECT QUERY \n";

	try{
//		boost::any_cast< bool ( * )( actRawDataStruct * , queryData *& )> ( boost::get < boost::any > (proto::Proto::initDissect( 3306 , 1 ) ) )  ( packetSettingDataArray ,  queryDataArray );
	}
	catch ( std::exception &e ){
		std::cerr<<"EXCEPTION:"<<e.what()<<'\n';
		exit ( 0 );
	}
//	 Mysql::getQueryOnly ( packetSettingDataArray , queryDataArray );

  //      instance->updatePacketSettingApp( queryDataArray , currentPacket  );
        return true;
}
