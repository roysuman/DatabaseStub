/*
 * =====================================================================================
 *
 *       Filename:  parser.h
 *
 *    Description:  parse xml file
 *
 *        Version:  1.0
 *        Created:  Saturday 30 January 2016 02:18:24  IST
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

std::string ring_buffer_xml;
class ParseXml{
	public:
		explicit ParseXml( std::string& file_name_,size_t count_ = 0):file_name(file_name_),count(count_){}
		virtual ~ParseXml( void);
		bool parse_xml(void);
	private:
		std::string            file_name;
		size_t                 count;
		virtual bool           load_file( void);
		virtual bool           start_parsing(void);
		virtual bool           parse_header( void);
		std::string            type_name;
		//The QDomDocument class represents an XML document.
		QDomDocument            xmlBOM;
		QDomElement             root;
};

