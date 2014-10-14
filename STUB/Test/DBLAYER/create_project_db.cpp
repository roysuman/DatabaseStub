/*
 * =====================================================================================
 *
 *       Filename:  create+project_db.cpp
 *
 *    Description:  DB STUB_INTerface for create_project.cpp
 *
 *        Version:  1.0
 *        Created:  Wednesday 06 November 2013 11:31:01  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy (),
 *   Organization:  SELF
 *
 * =====================================================================================
 */
#include "create_project_db.hpp"

bool dbCreateProject::CreateProject::createInitDb(  ){

    initProject::Project initializeDb;
    if ( initializeDb.createDb ( ) ){
        return ( initializeDb.createTableScenario () & initializeDb.createTableServerInfo() );
    }
    return false;

}
