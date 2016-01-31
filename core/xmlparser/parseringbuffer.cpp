/*
 * =====================================================================================
 *
 *       Filename:  parseringbuffer.cpp
 *
 *       Description:  
 *
 *       Version:  1.0
 *       Created:  Saturday 30 January 2016 03:15:39  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *       Author:  SIGCONT (suman roy), email.suman.roy@gmail.com
 *       Organization:  OPEN SOURCE
 *       LICENSE: GNU GPL
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * =====================================================================================
 */


#include "parseringbuffer.h"

#include "../../core/api/ringbuffer.h"
#include "../../core/api/ringbuffer.cpp"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ~XmlRingBufferParse
 *  Description:  the destructor...TODO check anything need to free?
 * =====================================================================================
 */
XmlRingBufferParse::~XmlRingBufferParse(){}
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  load_file
 *  Description:  load the xml file for parsing...it's an override method
 *  		  which simply calls Baseclass(ParseXml) method.
 *  		  @return true on success else false.
 * =====================================================================================
 */
bool
XmlRingBufferParse::load_file( void ){
	return ParseXml::load_file();
}



/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  parse_header
 *  Description:  parse the header of loaded xml file and
 *  		  do some check. It's a override method of class ParseXml
 *  		  @return true on success else false.
 * =====================================================================================
 */
bool
XmlRingBufferParse::parse_header( void ){
	root=xmlBOM.documentElement();
#ifdef UNIT_TEST
	qDebug()<<root.tagName();
#endif
	if ( root.tagName() !="RINGBUFFER" ) return false;
	qDebug()<<"return true";
	return true;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  start_parsing
 *  Description:  init the parsing of config file.
 *                this method sequentially parse all node values for
 *                initializing ring-buffer. It's an override method
 *                of class ParseXml.
 *                @return true on success else false.
 * =====================================================================================
 */
bool
XmlRingBufferParse::start_parsing( void ){
	QDomElement component = root.firstChild().toElement();
	while ( !component.isNull() ){
#ifdef UNIT_TEST
        qDebug()<<"TAGNAME"<<component.tagName();
#endif
		if ( component.tagName() == "SETUP"){
			/* read ring buffer config */
			parse_ring_buffer(component);
		}else{
			qDebug()<<"ERROR....tagName invalid";
			return false;
		}
		component = component.nextSibling().toElement();
	}
	return true;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  parse_ring_buffer
 *  Description:  parse config for needed to create a RingBuffer.
 *  		  this method create an RingBUffer instance on successful
 *  		  parsing of config and register that ring-buffer.
 *  		  @return: true on success else false.
 * =====================================================================================
 */
bool
XmlRingBufferParse::parse_ring_buffer( QDomElement child){
		if ( !child.isNull()){
			if ( child.tagName()=="SETUP" ){
				QString name_ = child.attribute("NAME","");
				QString size_ = child.attribute("BUFFER_SIZE","");
				QString element_size_ = child.attribute("ELEMENT_SIZE_","");
				QString ring_buffer_id_ = child.attribute("RINGBUFFER_ID","");
				/* register this ringbuffer */
				std::string buffer_name = name_.toStdString();// "test_ring_buffer";
				size_t element_size = element_size_.toUInt();
				size_t ring_buffer_id = ring_buffer_id_.toUInt();
				size_t size = size_.toUInt();
				RingBufferManager::init_new_ring_buffer( buffer_name, size , element_size);
				qDebug()<<" Name "<<name_
					<<" Size " <<size_
					<<"Element size "<<element_size_
					<<" Buffer Id "<<ring_buffer_id_;
				
			}else return false;
		}else return false;
	return true;
}
/* 
bool
XmlRingBufferParse::parse_xml(){
	ParseXml::parse_xml();
}*/
