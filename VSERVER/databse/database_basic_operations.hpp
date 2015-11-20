/*
 * =====================================================================================
 *
 *       Filename:  database_basic_operations.h
 *
 *    Description:  database basic operations
 *
 *        Version:  1.0
 *        Created:  Sunday 11 October 2015 03:23:00  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  ROY (), email.suman.roy@gmail.com
 *   Organization:  NA
 *
 * =====================================================================================
 */
#ifndef DATABASE_BASIC_OPERATIONS_H
#define DATABASE_BASIC_OPERATIONS_H
#include<iostream>
#include<sqlite3.h>
static const std::string 
quotesql( const std::string& s ) {
	return std::string("\"") + s + std::string("\"");
}
const bool 
execute_status ( int status , char * error_msg ){

	bool    return_val;
	if ( status != SQLITE_OK ){
		std::cerr<<PRINT<<"Sqlite3 execute_status -> error"<<std::endl;
		sqlite3_free ( error_msg );
		return_val = false;
	}
	else {
#ifdef DEBUG
		 std::cout<<PRINT<<"Sqlite3 executeStatus- > ok\n";
#endif
		 sqlite3_free ( error_msg );
		 return_val = true;
	}
	return return_val;
}

static const int callback(void *temp,  int argc, char **argv, char **azColName){
	int    i;
	for(i=0; i<argc; i++){
		std::cout<< azColName[i]<<( argv[i] ? argv[i] : "NULL")<<std::endl;
	}
	return 0;
}
class DatabaseBaiscOps{
	private:
		sqlite3   *db;
	protected:
		inline bool execute_statement( std::string const querry){
			char *zerr_msg;
			return execute_status( sqlite3_exec(db,querry.c_str(),callback,0,zerr_msg),zerr_msg);
		}
		inline void init_dd_name( const sqlite3 * db_ ){
			ds = db_;
			return;
		}
};
#endif
