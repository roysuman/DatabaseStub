/*
 * =====================================================================================
 *
 *       Filename:  database_manager.h
 *
 *    Description:  database manager
 *
 *        Version:  1.0
 *        Created:  Sunday 11 October 2015 04:48:48  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  ROY (), email.suman.roy@gmail.com
 *   Organization:  NA
 *
 * =====================================================================================
 */
#ifndef DATABASE_MANAGER_H
#ifdef DATABASE_MANAGER_H

#include <sqlite3.h>
#include<iostream>

#include "database_basic_setup.h"

class DatabaseManager:public DatabaseSetup{
	public:
		explicit DatabaseManager( std::string const db_path_name){
			db_setup = new DatabaseSetup(  db_path_name );
		}
		virtual ~DatabaseManager(){
			delete db_setup;
		}
	protected:
		/* depending upon the flag create or open db */
		bool init_db( std::string const db_name, int const flag);
		inline void close_db( void){ (void)db_setup->close_db( );}
	private:
		DatabaseSetup    *db_setup;
};
#endif
