#ifndef BUFFER_HPP
#define BUFFER_HPP 
#include "boost/variant.hpp"
#include<iostream>
#include <sstream>
#include<fstream>
#include<stdlib.h>

#include "proto.h"
#include"types.h"
#include "shift_int.h"
namespace buff{
template <class T>
	class Buffer{
		public:
			explicit Buffer( void ):root_row_pass(true),tvb_length(0),pass(false){}
			virtual ~Buffer(){}
		protected:
			/* set length */
			inline void set_length( VS_ULONG &len){ tvb_length = len ;}
			/* set pass variable */
			inline void set_pass_veriable( VS_BOOL pass_){ pass = pass_;}
			/* read data from input buffer */
			VS_BOOL read_buffer ( actRawDataStruct * , field_info *,
				       VS_ULONG  , VS_ULONG * , VS_ULONG , VS_INT32 , T &data );
			/* read one byte unsigned integer */
			VS_BOOL get_uint_8 ( actRawDataStruct * , VS_ULONG , VS_UINT32 );

			/* get the length of a null terminated string starting from offset */

			VS_BOOL get_string_length ( actRawDataStruct * , VS_ULONG , VS_ULONG&  );

			/* return the remaing length of the buffer data from current offset */
			inline VS_ULONG  return_remaining_length ( VS_ULONG offset ){
				return ( tvb_length - offset ) + 1;
			}

			/* read bigIndian and littleIndian */

			VS_BOOL getLetohs ( actRawDataStruct * , VS_ULONG ,VS_UINT16);
			VS_BOOL get_letohl ( actRawDataStruct * , VS_ULONG , VS_UINT32);
			VS_BOOL get_letoh_64 ( actRawDataStruct * , VS_ULONG, VS_UINT64 );
			VS_BOOL get_letoh_24 ( actRawDataStruct * , VS_ULONG , VS_UINT32);

		private:
			VS_BOOL     root_row_pass;//FIXME why me?
			VS_ULONG    tvb_length;   /* buffer total length  */
			VS_BOOL     pass;         //FIXME why me?
	};


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  read_buffer
 *  Description:  Read buffer date 
 *                @@actRawDataStruct : raw data packet //FIXME You told you will modify me
 *                @@field_info_str_data_ptr: array of all field info //FIXME just send the current one
 *                @@index: the active index of field_info.//FIXME only send the current struct 
 *                @@length: no of nyte to read //FIXME: work on this... why should I send length? use sizeof.
 *                @@encryption: little or big indian
 *                @@data : reference to hold the read data.
 *                @@return true on success read else return false.
 * =====================================================================================
 */
template<class T> VS_BOOL
       buff::Buffer< T >::read_buffer ( actRawDataStruct *rawDataPacket , 
		                        field_info_map_str *field_info_str_data_ptr ,
				        VS_ULONG  index , 
					VS_ULONG *offset ,
				        VS_ULONG length , //TODO remove length
				        VS_INT32  encryption,
		                        T &data ){

	       VS_BOOL   return_val;

	       /* read data depending on the field data type 
		* FIXME: to read uint and int of diierent size, get_int method of types.h has been
		* used. The reference variable to store the read data is getting passed to the function.
		* but how to convert the read data into signed and unsigned bit? */
	       switch ( field_info_str_data_ptr [ index ].type ){
		       case types::UINT16:
		       case types::UINT24 :
		       case types::UINT32:
			       /* read data from types.h */
			       return_val = get_int ( rawDataPacket->data , rawDataPacket->length, 
					       *offset ,length , encryption, data ) ;
			       break;

		       case types::UINT8:
			       return_val = types::get_int8 ( rawDataPacket->data , 
					   buff::Buffer< STUB_INT >::tvb_length , *offset, data  ) ;
			       break;
		       case types::INT8:
		       case types::INT16:
		       case types::INT24:
		       case types::INT32:
			       return_val = types::get_int( rawDataPacket->data , rawDataPacket->length  ,
					   *offset , length , encryption, data ) ;
			       break;

			       
		       case types::STRING:/* read string */
			       return_val = types::get_string ( rawDataPacket->data , 
					       buff::Buffer< STUB_INT >::tvb_length , *offset , length, data ) ;
			       *offset += (boost::get< std::string >(data)).length();/* increase the buffer pointer */
			       break;
			       
		       case types::BYTES:
			       //TODO implement
			       
			       break;

			       
		       case types::FLOAT: /* read float */
			       return_val = get_float( rawDataPacket->data , rawDataPacket->length,
					       *offset , length , encryption, data ) ;
			       break;
			       
		       case types::DOUBLE:/* read double */
			       return_val = get_double ( rawDataPacket->data , rawDataPacket->length,
					      *offset , length ,encryption, data);
			       break;
			       
		       case types::UINT_STRING:/* read unsigned string */
			       return_val = get_uint( rawDataPacket->data , rawDataPacket->length,
					       *offset ,length , encryption, data ) ;
			       break;
			       
		       case types::NONE:
			       /* this condition should not appear */
			       return_val = false;
			       break;
			       
		       case types::UINT64:
			       /* FIXME Implement */
			       break;
	       }
	       *offset += length;
	       return return_val;i
       }
     

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  get_string_length
 *  Description:  get the length of the string from the current offset
 *               @@rawDataPacket: struct variable fo packet
 *               @@offset: read index of string
 *               @@str_len: reference to hold the string length
 *               @@return true on success else flse.
 * =====================================================================================
 */

template <class T >VS_ULONG 
	buff::Buffer< T >::get_string_length (actRawDataStruct *rawDataPacket , 
			                      VS_ULONG  offset, VS_ULONG &str_len ){

		std::string    str;
		VS_BOOL        return_val;
	
		if ( get_string ( (u_char *) rawDataPacket->data , 
				tvb_length , offset , 0, &str ) ){
			str_len = str.length() + 1;/* reading a string from char array..so +1 for '\0' */
			return_val = true;
		}
		else{
			str_len =0;
			return_val = false;
		}
		return return_val;
	}



/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  get_letohs
 *  Description:  TODO
 * =====================================================================================
 */
template < class T>VS_UINT16 
	buff::Buffer< T >::get_letohs ( actRawDataStruct * rawDataPacket ,
			                VS_ULONG offset,
		                        VS_UINT16 &leth	){
		VS_UINT8    *data;

		if ( is_contiguous(  buff::Buffer<STUB_INT>::tvb_length , offset , 4 ) ){
			data = (u_char * )rawDataPacket->data ;
			leth = letohs16( data + offset );
			return_val = true;
		}else{
			return_val = false;
		}
		return return_val;
	}



/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  get_letohl
 *         Description:  TODO
 * =====================================================================================
 */

template < class T>VS_BOOL 
	buff::Buffer< T >::get_letohl ( actRawDataStruct * rawDataPacket , 
			STUB_INT offset,
		        VS_UIN32 &leto	){

		VS_UINT8   *data;
		VS_BOOL    return_val;

		if ( is_contiguous(  tvb_length , offset , 4 ) ){
			data = rawDataPacket->data ;
			leto =  letohl32( data + offset );
			return_val == true;
		}
		else{
			return_val = false;
		}
		return return_val;
	}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  get_letoh_64
 *  Description:  TODO
 * =====================================================================================
 */

template < class T>VS_BOOL
       	buff::Buffer< T >::get_letoh_64 (actRawDataStruct *rawDataPacket , 
			                 VS_ULONG offset,
		                         VS_UINT64 &leto){
		VS_UINT8    *data;
		VS_BOOL     return_val;
		if ( is_contiguous(tvb_length , offset , 8 ) ){
			data = rawDataPacket->data ;
			leto =  letoh64( data + offset );
			return_val = true;
		}else{
			return_val = false;
		}
	}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  get_letoh_24
 *  Description:  TODO
 * =====================================================================================
 */

template < class T> VS_BOOL
       	buff::Buffer < T >::get_letoh_24( actRawDataStruct *rawDataPacket ,
		                          VS_ULONG  offset,
		                          VS_UINT32 &leto){
		VS_UINT8    *data; 
		VS_BOOL     return_val;

		if ( is_contiguous( tvb_length , offset , 3 ) ){
			data = rawDataPacket->data;
			leto = letoh24( data + offset );
			return_val = true;
		}else{
			return_val = false;
		}
		return return_val;
	}

#endif /* BUFFER_H */
