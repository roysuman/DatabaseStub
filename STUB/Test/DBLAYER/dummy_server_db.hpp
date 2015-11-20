#ifndef DUMMY_SERVER_DB_HPP_
#define DUMMY_SERVER_DB_HPP_
#include<iostream>
#include"DB/dummy_server.hpp"
#include "../STRUCTURE/include/scenario_struct.hpp"
#include "../SUPPORT/globalDatatypes.hpp"


namespace  serverDb{
    class DummyServer{
        public:
        DummyServer();
        ~DummyServer();
        bool readConversation ( STUB_INT );
        STUB_INT getLastConversationId () ;
         actSeriesStruct * getChunckPackets( const STUB_CHAR * , STUB_INT ,  queryData *& , STUB_INT );





    };

    class OpenProject{
        public :
        OpenProject();
        ~OpenProject();
        bool openProject ( std::string );
        scenarioInformation** showScenarios ( );

    };
    
}

#endif
