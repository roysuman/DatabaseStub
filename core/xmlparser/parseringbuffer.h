/*
 * =====================================================================================
 *
 *       Filename:  parseringbuffer.h
 *
 *    Description:  parse the ring buffer environmnet
 *
 *        Version:  1.0
 *        Created:  Saturday 30 January 2016 03:08:14  IST
 *       Revision:  none
 *       Compiler:  gcc
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
#pragma once
// Library needed for processing XML documents
#include <QtXml>
// // Library needed for processing files
#include <QFile>
#include<iostream>
#include<string>

#include "parser.h"
class XmlRingBufferParse: public ParseXml{
	public:
		explicit XmlRingBufferParse( std::string* file_name_= 0,size_t count_=0):file_name(file_name_),count_(count_){}
		virtual ~XmlRingBufferParse(void);
		bool parse_xml(void) override;
	private:
		bool        load_file( void ) override;
		bool        start_parsing(void) override;
		bool        parse_header( void) override;
};
