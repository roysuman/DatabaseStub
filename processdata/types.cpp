/*
 * =====================================================================================
 *
 *       Filename:  types.cpp
 *
 *    Description:  this function describes all functions defined at types.hpp
 *
 *        Version:  1.0
 *        Created:  Sunday 22 September 2013 11:04:35  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy (email.suman.roy@gmail.com), 
 *   Organization:  Code For Fun
 *
 * =====================================================================================
 */
#include<iostream>
#include <stdlib.h>
#include "shift_int.hpp"
#include "types.hpp"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  is_contigious
 *  Description:  Check whether read byte request does not overflow the total length
 *               @@total_length: total length of data
 *               @@offset:current position
 *               @@byte_neede: byte need to read from current offset
 * =====================================================================================
 */

VS_BOOL 
Types::is_contigious ( VS_ULONG const total_length , 
		       VS_ULONG offset , 
		       VS_ULONG byte_needed ){

	VS_BOOL   return_val;

#ifdef DEBUG
	std::cout<<"Check is demanded read byte["<<byte_needed<<" ] does not overflow the total\
		length [ "<<total_length<<" ] from current read position [ "<<offset<<"]\n";
#endif

	if ( total_length <  ZERO  ||  offset <  ZERO  ){

#ifdef INFO

		std::cout<<"Either total length[ "<<total_length<<" ] < ZERO or offset["<<offset<<" ] < ZERO\n";
#endif

		return_val = false;
	}
	else if ( ( offset + byte_needed ) <= total_length ){
		return_val = true;
	}else{
		std::cerr<<"read byte needed [ "<<byte_neede<<" ] is less than total length "\
			<<total_length <<" + from current offset [ "<<offset<<"]\n";
		return_val = false;
	}
	return return_val;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  get_int
 *  Description:  read the integer value of size(depending upon the length)
 *                from the buffer ( tvb + offset )
 *                @@tvb: buffer
 *                @@total_length: buffer length
 *                @@offset: buffer ofset...reading index
 *                @@length: no of bytes to read
 *                @@ encryption: decison.. lthos | lthol
 *                @@Return: return the read data.. 0 on error
 *
 * =====================================================================================
 */

VS_BOOL
Types::get_int ( const VS_UINT8 *& tvb ,
	         VS_ULONG const total_length , 
		 VS_ULONG offset ,
		 VS_ULONG length ,  
		 VS_INT32 const encryption,
		 VS_INT32 &read_result_int){

	VS_BOOL   return_val;
        
	tvb = tvb + offset ;
	//check contiguous data available for 3 byte ?
    if ( !is_contigious(  total_length , offset , length ) ){
	    return_val = false;
	} else{
		/* if is contogious then read data and return of type uint32_t */
		switch ( length ){
			case 1:/* read one byte int */
				read_result_int = (uint32_t)tvb[offset];
				break;
			case 2:/* read two bytes int */
				encryption == 1?  ( read_result_int = letohs16 ( tvb ) ) : 
					( read_result_int =ntohs16 ( tvb ) );
				break;
			case 3:/* read 3bytes int */
				encryption == 1  ? ( read_result_int = letoh24 ( tvb ) ):
					( read_result_int = ntoh24 ( tvb ) );
				break;
			case 4:/* read 4bytes int */
				encryption == 1 ? ( read_result_int = letohl32 ( tvb ) ):
					( read_result_int = ntohl32 ( tvb ) ) ;
				break;
			default:
				std::cerr<<PRINT<<"Switch value of length is a wrong choice\n";
				return_val = false;
		}
	return return_val;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  get_int8
 *  Description:  read value of one byte and convert to int32
 *               @@tvb: buffer
 *               @@total_length: total buffer length
 *               @@offset: start index of data
 *               @@return: return the read data
 *               
 * =====================================================================================
 */
VS_BOOL
Types::get_int8 ( const VS_UINT8 *& tvb,
	          VS_ULONG const total_length ,
		  VS_ULONG offset,
	          VS_INT32 &read_int	){

	VS_BOOL   return_val;
#ifdef DEBUG
	  std::cout<<PRINT<<"Read one byte int from buffer of index [ "<<offset<<" ] Where buffer total length is [ "<<total_length<<" ] \n";
#endif 
	  /* check whether total buffer length allowes to read one byte */

	  if ( is_contigious(  total_length , offset , 1 ) ){
		  /* read one byte from buffer */
		  read_int =( ( int )tvb [ offset ] );
		  return_val = true;
	  }else{
		  return_val = false;
	  }
	  
	  return return_val;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  get_string
 *  Description:  read a string from the buffer..starting from offset
 *               @@tvb: buffer
 *               @@total_length: buffer total length
 *               @@offset: read index from
 *               @@length: length of the string
 * =====================================================================================
 */
VS_BOOL
Types::get_string ( const VS_UINT8 * tvb  , 
		    VS_ULONG const total_length , 
		    VS_ULONG offset,
		    VS_ULONG length,
	            std::string &temp_string_read){

	VS_BOOL    return_val;

	/* offset must be >=0 */
	if ( offset < 0 ){
		std::cerr<<" String Read Error Offset<0\n ";
		return_val = false;
goto: END_RETURN;
	}
	if ( offset > total_length ){
		std::cerr<<"String read error Offset  > Total Buffer Length \n";
		return_val = false;
goto: END_RETURN;
	}
	/* point to the starting index */
	tvb = tvb + offset ;
	/* if length to read passed as a 0, then read a null terminated string */
	if ( length == 0 ){
		temp_string_read = reinterpret_cast<const unsigned char* >(tvb ) ;
#ifdef DEBUG
		std::cout<<"Read null terminated string [ "<<temp_string_read<<" ] \n";
#endif
	}
	else{
		try {
			/* create a char array of length */
			unsigned char *array = new unsigned char [ length + 1 ] ; /* +1 to hold the '\0' */
			memcpy ( array , tvb , length );
			array[length + 1 ] = '\0';/* put a null value to indicate end */
			//FIXME which oe ? array [ length  ] = '\0';
			std::string temp_str( array );
			temp_string_read = temp_str;
#ifdef DEBUG
			std::cout<<PRINT<<"Read string["<<temp_string_read<<" ]  of length ["<<length <<" ]\n";
#endif
			/* free the char array */
			delete []array;
		}
		catch ( const std::bad_alloc &ba ){
			std::cout<<PRINT<<"Exception on creating unsigned char array "<<ba.what()<<std::endl;
			return_val = false;
		}
	}
END_RETURN:
	return return_val;
		
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  get_float
 *  Description:  read float number
 *                @@tvb: buffer
 *                @@total_length: total buffer length
 *                @@offset: read index
 *                @@length: dummy..always it will be 4 bytes..//FIXME future use
 *                @@encryption: is encryption?
 *
 * =====================================================================================
 */
VS_BOOL
Types::get_float ( const VS_UINT8 *& tvb  , 
		   VS_ULONG const total_length , 
		   VS_ULONG offset, 
		   VS_ULONG length ,
		   VS_INT32 const  encryption,
	           VS_FLOAT &float_data){
	
	VS_UINT32   data;
	VS_LONG     sign;
	VS_LONG     exponent;
	VS_LONG     mantissa;
	VS_BOOL     return_val;

	/* check whether buffer overflow happens on 4 bytes read */

	if ( length != 4 && ( ( offset + 4 ) > total_length  )){
		std::cerr<<PRINT<<"Error on reading a float...if length[ "<<length<<"] != 4 .then it's error...else buffer overflow \n";
		return_val = false;
	}
	else{
		encryption == 1 ? ( data = pletohl ( tvb ) )  : (data = pletohs ( tvb ) );
		sign = data & IEEE_SP_SIGN;
		exponent = data & IEEE_SP_EXPONENT;
		mantissa = data & IEEE_SP_MANTISSA;
		if ( ( sign & ~IEEE_SP_SIGN  ) == 0 ) float_data = 0.0;//FIXME ---- is it an error??
		else{
			exponent = ( ( exponent >> IEEE_SP_MANTISSA_WIDTH ) - IEEE_SP_BIAS ) - 	IEEE_SP_MANTISSA_WIDTH;
			mantissa |= IEEE_SP_IMPLIED_BIT;
			if (sign)
				float_data  = -mantissa * pow(2, exponent);
			else
				float_data = mantissa * pow(2, exponent);
			return_val = true;
		}
	}
	return return_val;
}


//read VS_DOUBLE
VS_BOOL
Types::get_double ( const VS_UINT8 *& tvb ,
	            VS_ULONG const total_length ,
		    VS_ULONG offset,
		    VS_ULONG length ,
		    VS_INT32 const encryption,
	            VS_DOUBLE &double_data	){

	VS_BOOL   return_val;

	if ( length != 8 && ( ( offset + 8 ) > total_length  )){
		std::cerr<<PRINT<<"Error on Reading Double from buffer\
			Either length [ "<<length<<" ] != 8 \
			Or offset ["<<offset <<" ] + 8 = [\
		       	"<<offset + 8 <<" ] > total buffer length\
		       	[ "<<total_length<<" ] \n";

		return_val = false;
	}else {
		VS_UINT64 data;
		encryption == 1 ? ( data = pletohll( tvb ) ) : 
			(data = pletohss ( tvb )  ) ;
		VS_INT64    sign;
		VS_INT64    exponent;
		VS_INT64    mantissa;

		sign = data & IEEE_DP_SIGN_MASK;
		exponent = data & IEEE_DP_EXPONENT_MASK;
		mantissa = data & IEEE_DP_MANTISSA_MASK;
		if ( ( sign & ~ IEEE_DP_SIGN_MASK ) == 0 ){
			double_data= 0.0;//FIXME ..is it error?
			return_val = false;
		}
		else{
			exponent = ((exponent >> IEEE_DP_MANTISSA_WIDTH) - IEEE_DP_BIAS) -
				IEEE_DP_MANTISSA_WIDTH;
			mantissa |= IEEE_DP_IMPLIED_BIT;
			if (sign){
				double_data = -mantissa * pow(2, exponent);
			}
			else{
				double_data = mantissa * pow(2, exponent);
			}
			return_val = true;
		}
	}
	return return_val;
}
/*
VS_INT32
Types::get_int ( const unsigned char * tvb , int total_length , int offset , 
		int length ,  int encryption ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<
		__TIME__<<"]\n";
	tvb = tvb + offset ;
	//check contiguous data available for 3 byte ?
    if ( !is_contigious(  total_length , offset , length ) ){
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
			"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
			<<"] failed function is_contiguous \n";
		return 0;
	}
        int32  read_result_int = 0;
		//if contigous  then read data of length and convert to uint24 and return.
		switch ( length ){
			case 1:
				read_result_int =(int8) get_int8( tvb , total_length , offset);
				break;
			case 2: 
				read_result_int=(int16) ( encryption == 1?  letohs16 ( tvb ) : 
						ntohs16 ( tvb ) );
				break;
			case 3:
				read_result_int =   (encryption == 1  ? letoh24 ( tvb )  : 
						ntoh24 ( tvb ) );
				if ( read_result_int & 0x80000000 )
					//sigen bit set
					read_result_int |=0xFF000000;
				break;
			case 4:
				read_result_int = ( encryption == 1  ? letohl32 ( tvb ) : 
						ntohl32 ( tvb ) ) ;
				std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<
					__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<
					__DATE__<<"_"<<__TIME__<<"]"<<"TEMP"<<read_result_int<<'\n';
				break;
			default:
				std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<
					__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<
					__DATE__<<"_"<<__TIME__<<"]"<<"ERROR ON READING INT\n";
				return 0;
		}
		return read_result_int ;
}
*/
