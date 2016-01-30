/*
 * =====================================================================================
 *
 *       Filename:  parseringbuffer.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Saturday 30 January 2016 03:15:39  IST
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
#include "parseringbuffer.h"
bool
XmlRingBufferParse::load_file( void ){
	return ParseXml::load_file();
}
bool
XmlRingBufferParse::parse_header( void ){
	root=xmlBOM.documentElement();
	if ( root.tagName() !=RINGBUFFER ) return false;


}

bool
XmlRingBufferParse::start_parsing( void ){
	QDomDocument component = root.firstChild().toElement();
	while ( !component.isNull() ){
		if ( component.tagName() == "SETUP"){


			std::string component_name = component.attribute("NAME","").toText().data().toStdSting();
			int buffer_size = component.attribute("BUFFER_SIZE","").toText().data().toInt();
			int element_size = component.attribute("ELEMENT_SIZE","").toText().data().toInt();
			int buffer_id = component.attribute("RINGBUFFER_ID","").toText().data().toInt();
			if( !RingBufferManager::init_new_ringbuffer(component_name,buffer_size, element_size, buffer_id )) return false;

		}else{ 
			return false;
		}
		component = component.nextSibling().toElement();
	}
	return true;
}
