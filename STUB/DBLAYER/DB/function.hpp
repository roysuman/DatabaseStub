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
 *   Organization:  SELF
 *
 * =====================================================================================
 */

#ifndef FUNCTION_HPP_
#define FUNCTION_HPP_
#include <iostream>
#include <sqlite3.h>
#include "../../SUPPORT/globalDatatypes.hpp"

namespace func{
	std::string quotesql ( const std::string & );
	bool executeStatus ( STUB_INT , STUB_CHAR * );
	STUB_INT callback(void * , STUB_INT,  STUB_CHAR **, STUB_CHAR **);
}

#endif
