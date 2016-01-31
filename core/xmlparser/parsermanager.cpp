/*
 * =====================================================================================
 *
 *       Filename:  parsermanager.cpp
 *
 *       Description:  
 *
 *       Version:  1.0
 *       Created:  Saturday 30 January 2016 10:08:30  IST
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


#include "parsermanager.h"
bool
ParserManager::parse_config( void ){
	if ( xml_parse->load_file() ){
		if ( xml_parse->parse_header() ){
			if ( xml_parse->start_parsing () ){
                XmlRingBufferParse  parse_ring(ring_buffer_xml );
				if ( parse_ring.load_file() && parse_ring.parse_header() && parse_ring.start_parsing() ){
					return true;
				}

			}
		}
	}
	return false;
	
}

