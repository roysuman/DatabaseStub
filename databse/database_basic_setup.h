/*
 * =====================================================================================
 *
 *       Filename:  database_basic_setup.h
 *
 *    Description:  open and setup the db environment
 *
 *        Version:  1.0
 *        Created:  Sunday 11 October 2015 03:42:40  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  ROY (), email.suman.roy@gmail.com
 *   Organization:  NA
 *
 * =====================================================================================
 */
#ifndef DATABASE_BASIC_SETUP_H
#define DATABASE_BASIC_SETUP_H
#include "database_basic_operations.h"

class DatabaseSetup: pubic DatabaseBaiscOps{
	public:
		explicit DatabaseSetup(std::string databse_path_along_name_):databse_path_along_name(databse_path_along_name_){
			db= NULL;
			is_open = false;

		}
	private:
		static sqlite3   *db;
		static std::string    databse_path_along_name;
		static is_open;
		const bool create_table( void );

	protected:
		const bool create_data_base( const std::string database_path_along_name="NULL");
		void close_db(void);

		
}

#endif
