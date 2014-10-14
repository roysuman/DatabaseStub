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
 *   Organization:  SELF
 *
 * =====================================================================================
 */

#ifndef DUMMY_SERVER_HPP_
#define DUMMY_SERVER_HPP_
#include <iostream>
#include <sqlite3.h>
#include <sstream>

#include "function.hpp"
#include "../STRUCTURE/include/database_structure.hpp"
#include "../STRUCTURE/include/rawdata_structure.hpp"
#include "../STRUCTURE/include/scenario_struct.hpp"
#include "../../SUPPORT/globalDatatypes.hpp"

/*-----------------------------------------------------------------------------
 *  a struct for returning conversation chunck packets with dynamic data flag ( if delta value part is <0then dynamic part is true
 *-----------------------------------------------------------------------------*/
typedef struct _dynamicValueWitnConversationChunck dynamicValueWitnConversationChunck;
struct _dynamicValueWitnConversationChunck{
	actSeriesStruct *conversationChunck;
	bool dynamicFlag;
};
namespace serverQuery{
    class OpenProjectQuery{
        public:
        OpenProjectQuery();
        ~OpenProjectQuery();
        bool openProject( std::string );
        scenarioInformation ** showScenarios();
        //STUB_CHAR **chowScenarioInformation ( std::string );
    };
    
    class DummyServerQuery{
        public:

		DummyServerQuery();
		~DummyServerQuery();
		bool readConversation ( STUB_INT );
                STUB_INT getLastConversationId( );
                actSeriesStruct * getChunckPackets( const STUB_CHAR * , STUB_INT , queryData *& , STUB_INT );
//		dynamicValueWitnConversationChunck *getChunckPackets ( const STUB_CHAR * , STUB_INT , queryData *& );


        
        };
}
#endif

