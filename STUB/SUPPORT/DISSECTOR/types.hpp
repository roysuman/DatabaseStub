#ifndef TYPES_HPP
#define TYPES_HPP 
#include <sstream>
#include<string.h>
#include "boost/variant.hpp"
#include <boost/any.hpp>
//functions for exra information relates to protocol implementation
#include "../../STRUCTURE/sumanGtkmm.hpp"
typedef boost::variant< int ,std::string , boost::any > returnType;
namespace types{
	 enum idisplay_format {
		 BASE_NONE,	// *< none */
		 BASE_DECIMAL,	// *< decimal */
		 BASE_HEX,	// *< hexadecimal */
		 BASE_OCT,	// *< octal */
		 BASE_DEC_HEX,	// *< decimal (hexadecimal) */
		 BASE_HEX_DEC,	// *< hexadecimal (decimal) */
		 BASE_CUSTOM	// *< call custom routine (in ->strings) to format */
			 };
	 


        // field types 
	enum ftenum {
//		NONE,	// used for text labels with no value 
//		PROTOCOL,
//		BOOLEAN,	// TRUE and FALSE come from <glib.h> 
		UINT8,
		UINT16,
		UINT24,	// really a UINT32, but displayed as 3 hex-digits if FD_HEX*/
		UINT32,
//		UINT64,
//		INT8,
//		INT16,
//		INT24,	/* same as for UINT24 */
//		INT32,
//		INT64,
//		FLOAT,
//		DOUBLE,
//		ABSOLUTE_TIME,
//		RELATIVE_TIME,
		STRING,
//		STRINGZ,	/* for use with proto_tree_add_item() */
//		UINT_STRING,	/* for use with proto_tree_add_item() */
		/*UCS2_LE, */    /* Unicode, 2 byte, Little Endian     */
//		ETHER,
		BYTES,
//		UINT_BYTES,
//		IPv4,
//		IPv6,
//		IPXNET,
//		FRAMENUM,	/* a UINT32, but if selected lets you go to frame with that number */
//		PCRE,	/* a compiled Perl-Compatible Regular Expression object */
//		GUID,	/* GUID, UUID */
//		OID,		/* OBJECT IDENTIFIER */
//		EUI64,
//		AX25,
//		NUM_TYPES /* last item number plus one */
			
	};
	//check contiguios or not regarding to the length
	//
	//1st parameter is the total length of the rawdata
	//second is current offset
	//3rd one is the no. of byte have to read
    bool isContiguous (  int , int , int );

	//this function read length - byte (  ) of data from
	//the buffer and send the corresponding uint data.
	//fisr parameter is the raw data buffer
	//second parameter is the total length of the raw data
	//next parameter is the current offset
	//last one is the no byte need to be read
    guint32 getGuint ( const u_char  * , int  , int ,int , int  );
	//this function is needed to read 1byte data from  buffer and will
	//retuirn guint8
    guint32 getGuint8 ( const u_char * , int , int );

	//read the string value from the buffer
    std::string getString ( const u_char * , int , int , int);
	
	}

#endif /* TYPES_HPP */
