/*
 * =====================================================================================
 *
 *       Filename:  function.hpp
 *
 *    Description:  function required to manupulating some sql
 *
 *        Version:  1.0
 *        Created:  Wednesday 06 November 2013 02:44:35  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy (), 
 *   Organization:  Cognizant Technological solutions
 *
 * =====================================================================================
 */

#ifndef FUNCTION_HPP_
#define FUNCTION_HPP_
#include <iostream>
#include <sqlite3.h>

namespace func{
	std::string quotesql ( const std::string & );
	bool executeStatus ( int , char * );
    int callback(void *, int , char **, char **);
}

#endif
