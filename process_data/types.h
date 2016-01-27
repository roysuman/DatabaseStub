#ifndef TYPES_H
#define TYPES_H 
#include <sstream>
#include <string.h>
#include <math.h>
#include "boost/variant.hpp"
#include <boost/any.hpp>
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
typedef boost::variant< VS_INT32 ,std::string , boost::any > return_type;
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
	PROTOCOL,
	BOOLEAN,	// TRUE and FALSE come from <glib.h> 
	UINT8,
	UINT16,
	UINT24,	// really a uint32_t, but displayed as 3 hex-digits if FD_HEX*/
	UINT32,
	UINT64,
	INT8,
	INT16,
	INT24,	/* same as for UINT24 */
	INT32,
	INT64,
	FLOAT,
	DOUBLE,
	ABSOLUTE_TIME,
	RELATIVE_TIME,
	STRING,
	BYTES,
};
class Types{
		 protected:
		 /* TODO: other functions to read others datatypes. */
		 VS_BOOL get_int ( VS_UINT8 const *& , VS_ULONG  , VS_ULONG , VS_ULONG , VS_INT32 , VS_INT32& );
		 VS_BOOL get_int8 ( const VS_UINT8  *& , VS_ULONG const , VS_ULONG , VS_INT32& );
		 VS_BOOL get_string ( const VS_UINT8 *& , VS_ULONG const ,VS_ULONG , VS_ULONG , std::string &);
		 VS_BOOL get_float( const VS_UINT8 *& , VS_ULONG const , VS_ULONG , VS_ULONG , VS_INT32 , VS_FLOAT& );
		 VS_BOOL get_double ( const VS_UINT8 *& , VS_ULONG const ,VS_ULONG , VS_ULONG , VS_INT32 , VS_DOUBLE& );
		 private:
		 /* only protected methods can check whether contigious or not */
		 VS_BOOL is_contiguous ( VS_ULONG const , VS_ULONG , VS_ULONG );

};

#endif /* TYPES_HPP */
