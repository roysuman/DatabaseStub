#ifndef DUMMY_SERVER_DB_HPP_
#define DUMMY_SERVER_DB_HPP_
#include<iostream>
#include"DB/dummy_server.hpp"
#include "../STRUCTURE/scenario_struct.hpp"


namespace  serverDb{
    class DummyServer{
        public:
        DummyServer();
        ~DummyServer();
        bool readConversation ( int );
        int getLastConversationId () ;
         actSeriesStruct * getChunckPackets( const char * , int ,  queryData *& );





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
