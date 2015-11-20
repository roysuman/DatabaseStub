/*
 * =====================================================================================
 *
 *       Filename:  database_basic_setup.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Sunday 11 October 2015 03:52:19  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  ROY (), email.suman.roy@gmail.com
 *   Organization:  NA
 *
 * =====================================================================================
 */
#include "database_basic_setup.h"

const bool
DatabaseSetup::create_data_base( const std::string database_path_along_name, int const flag ){
	int ret;
	bool    return_val;
	if ( db != NULL ){
		close(db);
	}
	switch( flag ){
		case 1:/* create db with read and write operation */
			ret = sqlite3_open_v2(database_path_along_name, &db, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE |  SQLITE_OPEN_NOMUTEX , NULL );
			break;
		case 2:/* open db with only read operation */
			ret = sqlite3_open_v2(database_path_along_name, &db, SQLITE_OPEN_READONLY |SQLITE_OPEN_FULLMUTEX , NULL );
			break;
		default:
			std::cout<<PRINT<<"Wrong flag for crating | open DB\n";
			return false;
	}
	if ( ret == SQLITE_OK ){
		std::cout<<PRINT<<"Db created successfully \n";
		return_val=  true;
	}
	else{
		std::cout<<PRINT<<"Create | Open databse error "<<sqlite3_errstr(ret)<<std::endl;
		return_val =  false;
	}
	return return_val;
}
void
DatabaseSetup::close_db( void){
	int    ret;

	ret = sqlite3_close( db );
	if ( ret != SQLITE_OK ){
		std::cout<<PRINT<<"Error on closing Sqlit3 databse...Error"<<sqlite3_errstr( ret)<<std::endl;
	}
	return;
}


bool
DatabaseSetup::create_table( void ){
#ifdef DEBUG
	sttd::cout<<PRINT<<" Create tables\n";
#endif
	std::string sql_statement_1="CREATE TABLE PACKET_SETTING"
	      	+" ( CONVERSATION_ID INTEGER PRIMARY KEY NOT NULL , PACKET_NO INTEGER\
	       	NOT NULL , SEQ_NO INTEGER NOT NULL , ACK_NO INTEGER NOT NULL ,\
		 RAW_DATA BLOB , STATUS INTEGER , QUERY_TYPE TEXT , QUERY TEXT,\
		 PROTOCOL TEXT NOT NULL , DELTA_VALUE INTEGER , DELTA_VALUE2 INTEGER );";
	std::string sql_statement_2 = "CREATE TABLE PACKET" +
		" ( CONVERSATION_ID INTEGER  NOT NULL ,PACKET_NO  INTEGER NOT NULL ,\
	       	DATA BLOB , APPDB INTEGER NOT NULL,SEQ_NO INTEGER NOT NULL , ACK_NO\
	       	INTEGER NOT NULL , LENGTH INTEGER );";
	return ( execute_statement(sql_statement_1) && execute_statement(sql_statement_2) );
}


