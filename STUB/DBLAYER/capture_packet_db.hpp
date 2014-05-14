/*
 * =====================================================================================
 *
 *       Filename:  capture_packet_db.hpp
 *
 *    Description:  DB layer for 
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

#ifndef CAPTURE_PACKET_DB_HPP_
#define CAPTURE_PACKET_DB_HPP_
#include "../STRUCTURE/scenario_struct.hpp"
#include "DB/capture_packet.hpp"
#include "../SUPPORT/DISSECTOR/proto_mysql.hpp"

#include <iostream>

namespace captureDb{


	class CaptureDbSetting{
		public:
			CaptureDbSetting();
			~CaptureDbSetting();
			bool insertCaptureConfiguration (  );

			
	};

	class RemoteServer{
		public:
			RemoteServer();
			~RemoteServer();
			bool addNewServerInfo ( void );
			serverStruct * displayServerTable ( void );

	};

	//global variables for class StoreRawPacket
	extern int currentConversationId;
	extern int currentConversationPacketSequence ;
	extern bool synFin;
	extern int packetNumber;
	
       

	class StoreRawPacket{
		public:
			StoreRawPacket();
			~StoreRawPacket();
                        bool packetHandler( rawDataStruct * );
                        bool copyPacket ( bool , conversation * , rawDataStruct * );// coppy a packet into prev store array
                        bool searchMother (bool  , conversation* , rawDataStruct *);//search the packet belongs to this conversation or not
                        bool validPack ( bool , conversation * , rawDataStruct *);
                        bool checkDbGreeting ( conversation * , rawDataStruct *);
            bool updateQueryTypeQueryAtDatabase ( void ); // this functio used for updating the query type and query at database after fininshing packet capture operation.


	};
}
#endif

