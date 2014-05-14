/*
 * =====================================================================================
 *
 *       Filename:  database_structure.hpp
 *
 *    Description:  structures to maintain database information, at a particular time only one database will be active
 		  so only one instance of database variable is needed.
 *
 *        Version:  1.0
 *        Created:  Wednesday 06 November 2013 03:06:10  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy (), 
 *   Organization:  Cognizant Technological solutions
 *
 * =====================================================================================
 */

#ifndef DATABASE_STRUCTURE_HPP_
#define DATABASE_STRUCTURE_HPP_
#include <sqlite3.h>
#include <iostream>
//Structure for dtoring database information , like db pointer, database name and path(location) of the database in local machine.
typedef struct _database databaseStruct;
struct _database{
	sqlite3 *db;
	std::string databaseName;
	std::string databasePath;
	
};
//varibale for stroting information of open sqlite3 database.
extern databaseStruct dbCredentials;
//during capture mode of this tool, we are going to filter network packets regarding to the server IP/Port. 
//suppose we are going to capture mysql packets coming from mysql server x.x.x.x and port 3306. This server struct holds the informations of 
//client/source of server that is our source of packets.

typedef struct _serverStructure serverStruct;
struct _serverStructure{
	std::string serverName;
	std::string serverType;
	std::string serverIp;
	std::string serverPort;
};

//one variable, that will hold the server information.
extern serverStruct serverCredentials;

#endif

