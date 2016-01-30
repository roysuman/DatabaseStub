/*
 * =====================================================================================
 *
 *       Filename:  paresrmanager.cpp
 *
 *    Description:  mange all parser
 *
 *        Version:  1.0
 *        Created:  Saturday 30 January 2016 10:08:30  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  SIGCONT (suman roy), email.suman.roy@gmail.com
 *   Organization:  OPEN SOURCE
 *
 * =====================================================================================
 */

#include "parsermanager.h"
bool
ParserManager::parse_config( void ){
	if ( xml_parse->load_file() ){
		if ( xml_parse->parse_header() ){
			if ( xml_parse->start_parsing () ){
				XmlRingBufferParse parse_ring(ring_buffer_xml );
				if ( parse_ring.load_file() && parse_ring.parse_header() && parse_ring.start_parsing() ){
					return true;
				}

			}
		}
	}
	return false;
	
}

