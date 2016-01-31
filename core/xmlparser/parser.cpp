/*
 * =====================================================================================
 *
 *       Filename:  parser.cpp
 *
 *       Description:  
 *
 *       Version:  1.0
 *       Created:  Saturday 30 January 2016 02:24:15  IST
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


#include"parser.h"
std::string ring_buffer_xml;

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  load_file
 *  Description:  load the xml file for parsing
 * =====================================================================================
 */
bool
ParseXml::load_file( void ){
  //  std::string path= "/home/suman/MY_PROJECT/git/DatabaseStub/config/vserver-util.xml";
   // this->file_name = path;
	// Load xml file as raw data
    QFile f(this->file_name.c_str());
	if (!f.open(QIODevice::ReadOnly )){
#ifdef UNIT_TEST
        std::cout<<"Not able to open file"<<std::endl;
#endif
		return false;
	}
#ifdef UNIT_TEST
    std::cout<<"File opened"<<std::endl;
#endif
	// Set data into the QDomDocument before processing
	xmlBOM.setContent(&f);
	f.close();
	return true;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  parse_header
 *  Description:  parse the header of loaded xml file and
 *  		  do some check.
 *  		  @return true on success else false.
 * =====================================================================================
 */
bool
ParseXml::parse_header( void ){
	// Extract the root markup
	root=xmlBOM.documentElement();
	// Get root names and attributes
	QString type=root.tagName();
#ifdef UNIT_TEST
    qDebug()<<type;
    qDebug()<<"SUMAN";
#endif
//	type_name=(root.attribute("TYPE","No name")).toStdString();
//	this.count=root.attribute("COUNT","0").toInt();
	return true;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  start_parsing
 *  Description:  init the parsing of config file.
 *                this method sequentially parse all node values for
 *                initializing the environment
 *                @return true on success else false.
 * =====================================================================================
 */
bool
ParseXml::start_parsing( void ){
	// Get the first child of the root (Markup COMPONENT is expected)
	QDomElement component=root.firstChild().toElement();

qDebug()<<"is null";
	// Loop while there is a child
	while(!component.isNull()){
#ifdef UNIT_TEST
        qDebug()<<"TAGNAME"<<component.tagName();
#endif
		// Check if the child tag name is COMPONENT
        if (component.tagName()=="SETUP_ENVIRONEMNT"){
            if ( !setup_environment( component )) return false;
			}
        else if( component.tagName()=="TEST"){
            std::cout<<"TEST-tag"<<std::endl;
        }

		// Next component
		component = component.nextSibling().toElement();
	}
	return true;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  aetup_environment
 *  Description:  store the config files which needed to parse to
 *  	          setup the application..Ex. Ringbuffer config file
 *  	          @QDomElement: current element head.
 *  	          @return true if it does not fetch any error else false.
 * =====================================================================================
 */
bool
ParseXml::setup_environment( QDomElement component){
	// Get the first child of the component
 //  QDomElement child   =component.nextSibling().toElement();
    QDomNode n = component.firstChild();
    while( !n.isNull() ){
         QDomElement child   =n.toElement();
         if ( !child.isNull()){
             if (child.tagName()=="RING_BUFFER"){
                 QString temp =child.attribute("PATH","");
                 ring_buffer_xml = temp.toStdString();
             }

         }
         // Next child
         n = n.nextSibling();
    }
	return true;
}

ParseXml::~ParseXml(){}
