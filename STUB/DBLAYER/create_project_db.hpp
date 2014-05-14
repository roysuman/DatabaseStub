/*
 * =====================================================================================
 *
 *       Filename:  create+project_db.hpp
 *
 *    Description:  db interface for create_project.hpp
 *
 *        Version:  1.0
 *        Created:  Wednesday 06 November 2013 11:31:32  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy (), 
 *   Organization:  Cognizant Technological solutions
 *
 * =====================================================================================
 */

#ifndef CREATE_PROJECT_DB_HPP_
#define CREATE_PROJECT_DB_HPP_
#include <iostream>
#include "DB/create_project.hpp"
namespace dbCreateProject{
	class CreateProject{
		public:

			bool createInitDb (  );
			
	};
}

#endif

