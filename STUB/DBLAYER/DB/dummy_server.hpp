/*
 * =====================================================================================
 *
 *       Filename:  dummy_server.hpp
 *
 *    Description:  for dummy server
 *
 *        Version:  1.0
 *        Created:  Friday 15 November 2013 11:29:40  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy (), 
 *   Organization:  Cognizant Technological solutions
 *
 * =====================================================================================
 */

#ifndef DUMMY_SERVER_HPP_
#define DUMMY_SERVER_HPP_
#include <iostream>
#include <sqlite3.h>
#include <sstream>

#include "function.hpp"
#include "../../STRUCTURE/database_structure.hpp"
#include "../../STRUCTURE/rawdata_structure.hpp"
#include "../../STRUCTURE/scenario_struct.hpp"

namespace serverQuery{
    class OpenProjectQuery{
        public:
        OpenProjectQuery();
        ~OpenProjectQuery();
        bool openProject( std::string );
        scenarioInformation ** showScenarios();
        //char **chowScenarioInformation ( std::string );
    };
    
    class DummyServerQuery{
        public:

		DummyServerQuery();
		~DummyServerQuery();
		bool readConversation ( int );
                int getLastConversationId( );
                actSeriesStruct * getChunckPackets( const char * , int , queryData *& );


        
        };
}
#endif

