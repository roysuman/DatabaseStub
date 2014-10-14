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
 *         Author:  SUMAN ROY (), email.suman.roy@gmail.com
 *   Organization:  SELF
 *
 * =====================================================================================
 */

#include <iostream>
#include "create_project.hpp"
#include "function.hpp"
#include "../../STRUCTURE/include/database_structure.hpp"
//./----------------------------------------functions

STUB_INT initProject::rc;
STUB_CHAR *initProject::sql ;
STUB_CHAR *initProject::zErrMsg ;
 //define constructor
 
 initProject::Project::Project(){}

 // destructor
 initProject::Project::~Project(){}

 //function create DB
 bool initProject::Project::createDb(  ){
     std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
	     <<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__
	     <<"_"<<__TIME__<<"]"<<"create Db\n";
     std::string db_name =
	     dbCredentials.databasePath +"/" + 
	     dbCredentials.databaseName + ".db";
     std::cout<<" File Name ["<<__FILE__<<" ] Function [ "
	     <<__FUNCTION__<<"] Line ["<<__LINE__
	     <<"] DateTime ["<<__DATE__<<"_"
	     <<__TIME__<<"]"<<" check ==\
	     DB name \t"<<db_name<<std::endl;

    STUB_INT rc = 
	    sqlite3_open ( db_name.c_str() , &dbCredentials.db );
     if ( rc ){
	     std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "
		     <<__FUNCTION__<<"] Line ["<<__LINE__
		     <<"] DateTime ["<<__DATE__<<"_"
		     <<__TIME__<<"]"<<" DEb cant create\n";
	     return false ;
	     
     }else {
	     std::cout<<" File Name ["<<__FILE__<<" ] Function [ "
		     <<__FUNCTION__<<"] Line ["<<__LINE__<<"] Date\
		     Time ["<<__DATE__<<"_"<<__TIME__<<"]"
		     <<"initProject::Project::createDb ->\
		     db created \n";
	     return true;
	     
     }
     
 }

 bool initProject::Project::createTableScenario ( void ){
	 std::cout<<" File Name ["<<__FILE__<<" ] Function [ "
		 <<__FUNCTION__<<"] Line ["<<__LINE__<<"] Date\
		 Time ["<<__DATE__<<"_"<<__TIME__
		 <<"] initProject::Project::createTableScenario \
		 -> creating table \n";

	 std::string sqlStatement="CREATE TABLE SCENARIO ( S_NAME\
				   TEXT PRIMARY KEY NOT NULL ,\
				   CATAGORY TEXT NOT NULL ,\
				   PROTOCOL TEXT NOT NULL ,\
				   SERVER_IP TEXT , PORT INTEGER  );";
	 
	 return ( func::executeStatus ( sqlite3_exec(dbCredentials.db, 
					 sqlStatement.c_str() , 
					 func::callback, 0, &zErrMsg )  ,
				 zErrMsg));
           

 }



bool initProject::Project::createTableServerInfo( void ){
	std::string sqlStatement="CREATE TABLE SERVER_INFO (\
				  S_NAME TEXT PRIMARY KEY NOT NULL ,\
				  CATAGORY TEXT NOT NULL ,\
				  SERVER_IP TEXT , PORT INTEGER  );";

	return ( func::executeStatus ( sqlite3_exec(dbCredentials.db, 
					sqlStatement.c_str() , 
					func::callback, 0, 
					&zErrMsg )  , zErrMsg));
}


