/*
 * =====================================================================================
 *
 *       Filename:  capture_packet.hpp
 *
 *    Description:  contains all capture packet related queries
 *
 *        Version:  1.0
 *        Created:  Wednesday 06 November 2013 01:50:03  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy (), 
 *   Organization:  SELF
 *
 * =====================================================================================
 */

#ifndef CAPTURE_PACKET_HPP_
#define CAPTURE_PACKET_HPP_

#include <sstream> 
#include <iostream>
#include <sqlite3.h>
#include <assert.h>
#include "../../STRUCTURE/include/scenario_struct.hpp"
#include "../../STRUCTURE/include/database_structure.hpp"
#include "../../STRUCTURE/include/rawdata_structure.hpp"
#include "function.hpp"
#include "../../SUPPORT/globalDatatypes.hpp"
namespace captureQuery{
	extern STUB_INT firstfourPacket ;
//	extern sqlite3 *db;
	extern STUB_INT rc;
	extern STUB_INT packetId ;
	extern STUB_CHAR *sql;
	extern STUB_CHAR *zErrMsg;
	class CaptureDbSettingQuery{
		public:
			CaptureDbSettingQuery( );
			~CaptureDbSettingQuery();
			bool insertCaptureConfiguration ( );
			bool createCaptureTable ( ); // create tables for storing captured Raw data
			

	};

	class RemoteServerQuery{
		public:
			RemoteServerQuery();
			~RemoteServerQuery();
			//function to add new sever
			bool addNewServerInfo ( void );
			serverStruct * displayServerTable ( void );
	};

	class StoreRawPacketQuery{
		public:
			STUB_INT packetId ;
			StoreRawPacketQuery();
			~StoreRawPacketQuery();
                        STUB_INT selectPacketSetting( bool , rawDataStruct *);
                        STUB_INT insertPacketSetting  ( bool , STUB_INT, STUB_INT , rawDataStruct * );
                        bool updatePacketSettingApp( bool , STUB_INT , STUB_INT , rawDataStruct * );
			bool updatePacketSettingApp ( queryData *& , STUB_INT  );
                        bool insertPacket( bool , STUB_INT , STUB_INT , rawDataStruct * );
                        bool insertDbGreeting ( STUB_INT , STUB_INT , rawDataStruct * );
			actRawDataStruct * selectPacketSetting ( );
			STUB_INT getCountPacketSetting();
			actRawDataStruct * getPacket( STUB_INT , bool );

	};


}

#endif

