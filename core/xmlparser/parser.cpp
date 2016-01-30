/*
 * =====================================================================================
 *
 *       Filename:  parser.cpp
 *
 *    Description:  parse the config
 *
 *        Version:  1.0
 *        Created:  Saturday 30 January 2016 02:24:15  IST
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
bool
ParseXml::load_file( void ){
	// Load xml file as raw data
	QFile f(this.file_name.c_str());
	if (!f.open(QIODevice::ReadOnly )){
		return false;
	}
	// Set data into the QDomDocument before processing
	xmlBOM.setContent(&f);
	f.close();
	return true;
}
bool
ParseXml::parse_header( void ){
	// Extract the root markup
	root=xmlBOM.documentElement();
	// Get root names and attributes
	QString type=root.tagName();
//	type_name=(root.attribute("TYPE","No name")).toStdString();
//	this.count=root.attribute("COUNT","0").toInt();
	return true;
}

bool
ParseXml::start_parsing( void ){
	// Get the first child of the root (Markup COMPONENT is expected)
	QDomElement component=root.firstChild().toElement();

	// Loop while there is a child
	while(!component.isNull()){
		// Check if the child tag name is COMPONENT
		if (component.tagName()=="COMPONENT"){
			// Read and display the component ID
			QString component_name=component.attribute("NAME","No NAME");
			switch( string_to_int(component_name)){
				case string_to_int("SETUP_ENVIRONMENT"):
					setup_environment( component );
					break;
					/* 
				case string_to_int( "RING_BUFFER"):
					if (child.tagName()=="VALUE") config_file=child.firstChild().toText().data().toStdString();
					setup_ring_buffer( config_file);

*/					break;
			}
		}else{
			return false;
			//some wrong tag
		}
		// Next component
		component = component.nextSibling().toElement();
	}
	return true;
}

bool
ParseXml::setup_environment( QDomElement component){
	// Get the first child of the component
	QDomElement child=component.firstChild().toElement();
	std::string tag_name;
	std::string config_file;
	
	
        // Read each child of the component node
        while (!child.isNull()){

            // Read Name and value
            if (child.tagName()=="NAME") tag_name=child.firstChild().toText().data().toStdString();
            if (child.tagName()=="PATH") config_file=child.firstChild().toText().data().toStdString();
	    switch( string_to_int( tag_name) ){
		    case string_to_int( "RING_BUFFER"):
			    ring_buffer_xml = config_file;

			    setup_ring_buffer( config_file);
			    break;
	    }
	    // Next child
            child = child.nextSibling().toElement();
        }
	return true;
}
