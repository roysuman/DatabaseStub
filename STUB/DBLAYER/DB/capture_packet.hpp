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
 *   Organization:  Cognizant Technological solutions
 *
 * =====================================================================================
 */

#ifndef CAPTURE_PACKET_HPP_
#define CAPTURE_PACKET_HPP_

#include <sstream> 
#include <iostream>
#include <sqlite3.h>
#include <assert.h>
#include "../../STRUCTURE/scenario_struct.hpp"
#include "../../STRUCTURE/database_structure.hpp"
#include "../../STRUCTURE/rawdata_structure.hpp"
#include "function.hpp"
namespace captureQuery{
	extern int firstfourPacket ;
//	extern sqlite3 *db;
	extern int rc;
	extern int packetId ;
	extern char *sql;
	extern char *zErrMsg;
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
			int packetId ;
			StoreRawPacketQuery();
			~StoreRawPacketQuery();
                        int selectPacketSetting( bool , rawDataStruct *);
                        int insertPacketSetting  ( bool , int, int , rawDataStruct * );
                        bool updatePacketSettingApp( bool , int , int , rawDataStruct * );
			bool updatePacketSettingApp ( queryData *& , int  );
                        bool insertPacket( bool , int , int , rawDataStruct * );
                        bool insertDbGreeting ( int , int , rawDataStruct * );
			actRawDataStruct * selectPacketSetting ( );
	};


}

#endif

