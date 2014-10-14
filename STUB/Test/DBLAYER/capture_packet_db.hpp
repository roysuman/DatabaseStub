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
 *   Organization:  SELF
 *
 * =====================================================================================
 */

#ifndef CAPTURE_PACKET_DB_HPP_
#define CAPTURE_PACKET_DB_HPP_
#include "../STRUCTURE/include/scenario_struct.hpp"
#include "../STRUCTURE/include/rawdata_structure.hpp"
#include "DB/capture_packet.hpp"
#include "../CORE/DISSECTOR/include/proto_mysql.hpp"
#include "../SUPPORT/globalDatatypes.hpp"

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
	extern STUB_INT lowerLimitConversationDiary;
	extern STUB_INT currentConversationId;
	extern STUB_INT currentConversationPacketSequence ;
	extern bool synFin;
	extern STUB_INT packetNumber;
	
       

	class StoreRawPacket{
		public:
			StoreRawPacket();
			~StoreRawPacket();
                        bool packetHandler( rawDataStruct * );
                        bool copyPacket ( bool , conversation * , rawDataStruct * );// coppy a packet into prev store array
                        bool searchMother (bool  , conversation* , rawDataStruct *);//search the packet belongs to this conversation or not
                        bool validPack ( bool , conversation * , rawDataStruct *);
			bool checkSimultaneouslyNewPacket ( bool , conversation * , rawDataStruct * );
                        bool checkDbGreeting ( conversation * , rawDataStruct *);
			bool updateQueryTypeQueryAtDatabase ( ); // this functio used for updating the query type and query at database after fininshing packet capture operation.


	};
}
#endif

