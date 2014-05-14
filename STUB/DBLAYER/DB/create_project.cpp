/*
 * =====================================================================================
 *
 *       Filename:  create_project.cpp
 *
 *    Description:  this is for creating the project.
 *    it will store required project information.
 *    this contains all information for creating project 1st time.
 *
 *        Version:  1.0
 *        Created:  11/04/2013 02:13:37 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  SUMAN ROY (), suman.roy@cognizant.com
 *   Organization:  COGNIZANT TECHNOLOGICAL SOLUTIONS
 *
 * =====================================================================================
 */

#include <iostream>
#include "create_project.hpp"
#include "function.hpp"
#include "../../STRUCTURE/database_structure.hpp"
//./----------------------------------------functions

int initProject::rc;
char *initProject::sql ;
char *initProject::zErrMsg ;
 //define constructor
 
 initProject::Project::Project(){}

 // destructor
 initProject::Project::~Project(){}

 //function create DB
 bool initProject::Project::createDb(  ){
     std::cout<<"create Db\n";
     std::string db_name =dbCredentials.databasePath +"/" + dbCredentials.databaseName + ".db";
     std::cout<<" check == DB name \t"<<db_name<<std::endl;

    int rc = sqlite3_open ( db_name.c_str() , &dbCredentials.db );
     if ( rc ){
         std::cerr<<" DEb cant create"<<std::endl;
         return false ;
         }
         else {
             std::cout<<"initProject::Project::createDb ->db created "<<std::endl;
             return true;

             }
 }

 bool initProject::Project::createTableScenario ( void ){
     std::cout<<"initProject::Project::createTableScenario -> creating table \n"<<std::endl;


    std::string sqlStatement="CREATE TABLE SCENARIO ( S_NAME TEXT PRIMARY KEY NOT NULL , CATAGORY TEXT NOT NULL , PROTOCOL TEXT NOT NULL ,"\
                  "SERVER_IP TEXT , PORT INTEGER  );";

     return ( func::executeStatus ( sqlite3_exec(dbCredentials.db, sqlStatement.c_str() , func::callback, 0, &zErrMsg )  , zErrMsg));
           

 }



bool initProject::Project::createTableServerInfo( void ){

     std::string sqlStatement="CREATE TABLE SERVER_INFO ( S_NAME TEXT PRIMARY KEY NOT NULL , CATAGORY TEXT NOT NULL ," \
                   "SERVER_IP TEXT , PORT INTEGER  );";
     return ( func::executeStatus ( sqlite3_exec(dbCredentials.db, sqlStatement.c_str() , func::callback, 0, &zErrMsg )  , zErrMsg));
}


