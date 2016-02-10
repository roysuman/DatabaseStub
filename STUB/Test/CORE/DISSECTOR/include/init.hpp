/*
 * =====================================================================================
 *
 *       Filename:  init.hpp
 *
 *    Description:  this file for initial initialization
 *
 *        Version:  1.0
 *        Created:  Sunday 29 September 2013 09:30:18  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy(  )  (email.suman.roy@gmail.com), 
 *   Organization:  SELF
 *
 * =====================================================================================
 */

#ifndef INIT_HPP
#define INIT_HPP 
#include <iostream>
#include "proto_mysql.hpp"
#include "../../../SUPPORT/globalDatatypes.hpp"
//initialize methods for register dissector and generator
class Init{
	public:
		static void  init  ( void );
};

void Init::init(void ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";
	Mysql::initialize (); // initialize mysql protocol
	//future use when new protocol will be added.

}
#endif /* INIT_HPP */