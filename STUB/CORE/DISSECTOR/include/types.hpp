#ifndef TYPES_HPP
#define TYPES_HPP 
#include <sstream>
#include<string.h>
#include <math.h>
#include "boost/variant.hpp"
#include <boost/any.hpp>
//functions for exra information relates to protocol implementation
#include "../STRUCTURE/include/globalDatatypes.hpp"
#include "../../../SUPPORT/globalDatatypes.hpp"
//single precision
#define IEEE_SP_EXPONENT 0x7F800000
#define IEEE_SP_MANTISSA 0x007FFFFF
#define IEEE_SP_SIGN 0x80000000
#define IEEE_SP_MANTISSA_WIDTH 23
#define IEEE_SP_NUMBER_WIDTH 32
#define IEEE_SP_EXP_WIDTH 8
#define IEEE_SP_BIAS ((1 << (IEEE_SP_EXP_WIDTH - 1) ) - 1 )
#define IEEE_SP_INFINITE ((1 << IEEE_SP_EXP_WIDTH) - 1)
#define IEEE_SP_IMPLIED_BIT (1 << IEEE_SP_MANTISSA_WIDTH)
#define IEEE_SP_INFINITE ((1 << IEEE_SP_EXP_WIDTH) - 1)
//STUB_DOUBLE precision
#define IEEE_DP_NUMBER_WIDTH	64	/* bits in number */
#define IEEE_DP_EXP_WIDTH	11	/* bits in exponent */
#define IEEE_DP_MANTISSA_WIDTH	52	/* IEEE_DP_NUMBER_WIDTH - 1 - IEEE_DP_EXP_WIDTH */

#define IEEE_DP_SIGN_MASK	0x8000000000000000LL
#define IEEE_DP_EXPONENT_MASK	0x7FF0000000000000LL
#define IEEE_DP_MANTISSA_MASK	0x000FFFFFFFFFFFFFLL
#define IEEE_DP_INFINITY	IEEE_DP_EXPONENT_MASK

#define IEEE_DP_IMPLIED_BIT (1LL << IEEE_DP_MANTISSA_WIDTH)
#define IEEE_DP_INFINITE ((1 << IEEE_DP_EXP_WIDTH) - 1)
#define IEEE_DP_BIAS ((1 << (IEEE_DP_EXP_WIDTH - 1)) - 1)
typedef boost::variant< STUB_INT ,std::string , boost::any > returnType;
namespace types{
	 enum idisplay_format {
		 BASE_NONE,	// *< none */
		 BASE_DECIMAL,	// *< decimal */
		 BASE_HEX,	// *< hexadecimal */
		 BASE_OCT,	// *< octal */
		 BASE_DEC_HEX,	// *< decimal (hexadecimal) */
		 BASE_HEX_DEC,	// *< hexadecimal (decimal) */
		 BASE_CUSTOM,	// *< call custom routine (in ->strings) to format */

			 };
	 


        // field types 
	enum ftenum {
		NONE,	// used for text labels with no value 
//		PROTOCOL,
//		BOOLEAN,	// TRUE and FALSE come from <glib.h> 
		UINT8,
		UINT16,
		UINT24,	// really a UINT32, but displayed as 3 hex-digits if FD_HEX*/
		UINT32,
		UINT64,
		INT8,
		INT16,
		INT24,	/* same as for UINT24 */
		INT32,
//		INT64,
		FLOAT,
		DOUBLE,
//		ABSOLUTE_TIME,
//		RELATIVE_TIME,
		STRING,
//		STRINGZ,	/* for use with proto_tree_add_item() */
		UINT_STRING,	/* for use with proto_tree_add_item() */
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
    bool isContiguous (  STUB_INT , STUB_INT , STUB_INT );

	//this function read length - byte (  ) of data from
	//the buffer and send the corresponding uSTUB_INT data.
	//fisr parameter is the raw data buffer
	//second parameter is the total length of the raw data
	//next parameter is the current offset
	//last one is the no byte need to be read
    STUB_UINT32 getGuint ( const u_char  * , STUB_INT  , STUB_INT ,STUB_INT , STUB_INT  );
	//this function is needed to read 1byte data from  buffer and will
	//retuirn STUB_UINT8
    STUB_UINT32 getGuint8 ( const u_char * , STUB_INT , STUB_INT );

	//read the string value from the buffer
    std::string getString ( const u_char * , STUB_INT , STUB_INT , STUB_INT);
    //read the STUB_FLOAT value from buffer
    STUB_FLOAT getFloat( const u_char * , STUB_INT , STUB_INT , STUB_INT , STUB_INT );
    STUB_DOUBLE getDouble ( const u_char * , STUB_INT , STUB_INT , STUB_INT , STUB_INT );
    //read the STUB_INT value
    STUB_INT32 getInt( const u_char * , STUB_INT , STUB_INT  , STUB_INT , STUB_INT );

	
	}

#endif /* TYPES_HPP */
