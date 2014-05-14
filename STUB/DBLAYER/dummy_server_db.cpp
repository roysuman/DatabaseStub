/*
 * =====================================================================================
 *
 *       Filename:  dummy_server_db.cpp
 *
 *    Description:  to call function of DB/dummy_server.hpp
 *
 *        Version:  1.0
 *        Created:  11/15/2013 05:14:54 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  SUMAN ROY (), suman.roy@cognizant.com
 *   Organization:  COGNIZANT TECHNOLOGICAL SOLUTIONS
 *
 * =====================================================================================
 */

#include "dummy_server_db.hpp"

serverDb::DummyServer::DummyServer(){}
serverDb::DummyServer::~DummyServer(){}
int serverDb::DummyServer::getLastConversationId(){
    serverQuery::DummyServerQuery serverQueryInstance;
    return (  serverQueryInstance.getLastConversationId() );
}

bool serverDb::DummyServer::readConversation ( int conversationId ){
    serverQuery::DummyServerQuery serverQueryInstance ;
    return ( serverQueryInstance.readConversation( conversationId ) );

}

//read the chunck packets corresponding to recent conversatioon.
actSeriesStruct * serverDb::DummyServer::getChunckPackets( const char * buffer , int length  , queryData *& queryDataArray ){
    serverQuery::DummyServerQuery *serverQueryInstance = new serverQuery::DummyServerQuery();
    return ( serverQueryInstance->getChunckPackets( buffer , length  , queryDataArray ) );

}


/*
 * all the functions of class OPEN PROJECT
 * */

serverDb::OpenProject::OpenProject(){};
serverDb::OpenProject::~OpenProject(){}

/*
 *the function openProject is used to load the db .
 * */
bool serverDb::OpenProject::openProject( std::string databasePath ){
    //create an instance of OpenProjectQuery in DB dummy_serevr.hp[p
    serverQuery::OpenProjectQuery openProjectQueryInstance;
    return ( openProjectQueryInstance.openProject (  databasePath ) );
}

/*
 *this function to fetch scenario information of this project
 * */
scenarioInformation ** serverDb::OpenProject::showScenarios ( void ){
    /* cretae ani nstance for OpenProjectQuery::showScenarios();
     * */
    serverQuery::OpenProjectQuery openProjectQueryInstance;
    return ( openProjectQueryInstance. showScenarios( ) );
}


