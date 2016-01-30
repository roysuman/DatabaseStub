/*
 * =====================================================================================
 *
 *       Filename: apihelper.h
 *
 *    Description: helper for datastruct 
 *
 *        Version:  1.0
 *        Created:  Friday 29 January 2016 03:34:52  IST
 *       Revision:  none
 *       Compiler:  g++4.7
 *
 *         Author:  SIGCONT (suman roy), email.suman.roy@gmail.com
 *   Organization:  OPEN SOURCE
 *
 * =====================================================================================
 */
/* 
 *This program is free software: you can redistribute it and/or modify
 *it under the terms of the GNU General Public License as published by
 *the Free Software Foundation, either version 3 of the License, or
 *(at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>. */
#ifndef APIHELPER_H
#define APIHELPER_H
#define MAX_TRY 5
#include<iostream>
class ApiAbstract{
	public:
		ApiAbstract(){}
		virtual ~ApiAbstract(){}
		virtual void* get_empty_instance( std::string& , size_t capacity=0, size_t element_size = 0 ) {}
		virtual void* get_instance_by_name( const std::string&){}
		virtual bool register_api_instance( void* instance){}
		virtual bool destroy_api_instance_by_name( const std::string&){}
		virtual void print_api_stat( void) {}
		virtual void  print_info( void ){}
};
#endif
