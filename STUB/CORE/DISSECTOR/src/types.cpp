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
#include "../include/shift_int.hpp"
#include "../include/types.hpp"
// defination of function is_contigious()
bool types::isContiguous ( STUB_INT total_length , STUB_INT offset , STUB_INT byte_needed ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";
	if ( total_length < 0 || offset < 0){
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
			"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
			"] No length \n";
		return false;
		}
/*	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"Total length = "<<total_length<<std::endl
		<<"offset   ="<<offset<<std::endl
		<<"byte_needed = "<<byte_needed<<std::endl;
		*/
	if ( ( offset + byte_needed ) <= total_length )
		return true;
	else{
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
			<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"
			<<"RETURN FALSE\n"; 
		return false;
	}
}

//function defination of get_STUB_UINT24
//this function will read length byte from given buffer.
STUB_UINT32 types::getGuint ( const u_char * tvb , STUB_INT total_length , STUB_INT offset ,
	       	STUB_INT length ,  STUB_INT encryption ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		<<"]\n";
	tvb = tvb + offset ;
	//check contiguous data available for 3 byte ?
    if ( !isContiguous(  total_length , offset , length ) ){
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
			"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
			"] failed function is_contiguous \n";
		return 0;
	}
        STUB_UINT32  tempInt = 0;
		//if contigous  then read data of length and convert to uSTUB_INT24 and return.
		switch ( length ){
			case 2: {
                    encryption == 1?  ( tempInt = letohs16 ( tvb ) ) : 
			    ( tempInt =ntohs16 ( tvb ) );
                    return tempInt;
				}
				break;
			case 3:{
                        (encryption == 1 ) ? ( tempInt = letoh24 ( tvb ) ) 
				: ( tempInt = ntoh24 ( tvb ) );
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
				"]"<<"READ DATA:"<<tempInt<<'\n';

                    return tempInt;
			       }
			       break;
			case 4:{
                       ( encryption == 1 ) ? ( tempInt = letohl32 ( tvb ) ) : 
			       ( tempInt = ntohl32 ( tvb ) ) ;
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"]"<<"READ DATA:"<<tempInt<<'\n';
                       return tempInt;
				       
			       }
			       break;
			       
                   return tempInt ;

	}
	return 0;


}

//this function is needed to read 1byte data from  buffer and will
//retuirn STUB_UINT8
STUB_UINT32 types::getGuint8 ( const u_char * tvb, STUB_INT totalLength , STUB_INT offset ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	STUB_UINT32    temp;
	
	temp= - 1;

#ifdef DEBUG
	  std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		  __LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"LENGTh"<<
		  totalLength<<"OFFSET:"<<offset<<'\n';
#endif 
//	tvb = tvb + offset ;
//	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"total -length "<<total_length <<std::endl;
//	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"inside checking zone \n";

    if ( isContiguous(  totalLength , offset , 1 ) ){
	    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		    __LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"INSIDE TRUE\n";
	    temp =( ( STUB_INT )tvb [ offset ] );
        //  memcpy(&temp, tvb , 1);
    }

    return temp ;

}

//defination of the function get_string()
std::string types::getString ( const u_char * tvb  , STUB_INT totalLength , STUB_INT offset  
		, STUB_INT length ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";
	if ( offset < 0 ) std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]offset<0\n ";
    if ( offset > totalLength ) std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<
	    __FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
		    "] offset  >total length \n";
	tvb = tvb + offset ;
        std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"] length="<<length<<
		"total length="<<totalLength<<std::endl;
	if ( length == 0 ){
        std::string temp1;

        temp1 =reinterpret_cast<const STUB_CHAR*>(tvb ) ;
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<
		"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\
		!!!!!!!!!!!!!!!!!!!!!!!!!\n";
       std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
	       __LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<
	       "temp="<<temp1<<"length="<<temp1.length()<<std::endl;
       std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
	       __LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<
	       "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\
	       !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";

        return temp1;
	}
	else{
		//coppy into a string
		try {

			STUB_CHAR *array = new ( std::nothrow ) STUB_CHAR [ length + 1 ] ;
			
			memcpy ( array , tvb , length );
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<
				__TIME__<<"]"<<"\n[";
			for ( STUB_INT ii = 0 ; ii<length ; ++ii)
				std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
					<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
					<<__TIME__<<"]"<<(STUB_CHAR)tvb[ii];
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<
				__TIME__<<"]"<<"]\n";
			array [ length  ] = '\0';
			std::string temp1( array );
                        std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"]"<<"data at temp = "<<temp1<<std::endl;
			delete []array;

			return temp1;
		}
		catch ( std::bad_alloc &ba ){
			std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
				"] exception cgt\t"<<ba.what() <<std::endl;
		}
	}
	return "NULL";
}

//read STUB_FLOAT no
STUB_FLOAT types::getFloat ( const u_char * tvb  , STUB_INT totalLength , STUB_INT offset  , 
		STUB_INT length , STUB_INT encryption ){

	if ( length != 4 && ( ( offset + 4 ) <= totalLength  )){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<
			__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__
			<<"_"<<__TIME__<<"]"<<"Function name[ Either Length not 4 or ( offset + 4 )\
		       	> totalLength , hence error for reading STUB_FLOAT from STUB_CHAR buffer\n";
		exit ( 0 );
	}
    STUB_UINT data;
	encryption == 1 ? ( data = pletohl ( tvb ) )  : (data = pletohs ( tvb ) )  ;
	long sign;
	long exponent;
	long mantissa;
	sign = data & IEEE_SP_SIGN ;
	exponent = data & IEEE_SP_EXPONENT;
	mantissa = data & IEEE_SP_MANTISSA;
	if ( ( sign & ~IEEE_SP_SIGN  ) == 0 ) return 0.0;
		exponent = ( ( exponent >> IEEE_SP_MANTISSA_WIDTH ) - IEEE_SP_BIAS ) 
			- 	IEEE_SP_MANTISSA_WIDTH;
		mantissa |= IEEE_SP_IMPLIED_BIT;
		if (sign)
			return -mantissa * pow(2, exponent);
		else
			return mantissa * pow(2, exponent);
}


//read STUB_DOUBLE
STUB_DOUBLE types::getDouble ( const u_char * tvb  , STUB_INT totalLength , STUB_INT offset  , 
		STUB_INT length , STUB_INT encryption ){
	if ( length != 8 && ( ( offset + 8 ) <= totalLength  )){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<
			__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<
			__DATE__<<"_"<<__TIME__<<"]"<<"Function name[ Either Length not \
			8 or ( offset + 8 ) > totalLength , hence error for reading \
			STUB_FLOAT from STUB_CHAR buffer\n";
		exit ( 0 );
	}
	STUB_UINT64 data;
	encryption == 1 ? ( data = pletohll( tvb ) ) : 
		(data = pletohss ( tvb )  ) ;
	STUB_INT64 sign;
	STUB_INT64 exponent;
	STUB_INT64 mantissa;
	sign = data & IEEE_DP_SIGN_MASK;
	exponent = data & IEEE_DP_EXPONENT_MASK;
	mantissa = data & IEEE_DP_MANTISSA_MASK;
	if ( ( sign & ~ IEEE_DP_SIGN_MASK ) == 0 ) return 0.0;
	exponent = ((exponent >> IEEE_DP_MANTISSA_WIDTH) - IEEE_DP_BIAS) -
		IEEE_DP_MANTISSA_WIDTH;
	mantissa |= IEEE_DP_IMPLIED_BIT;
	if (sign) return -mantissa * pow(2, exponent);
	else return mantissa * pow(2, exponent);
}
//read STUB_INT
STUB_INT32 types::getInt ( const u_char * tvb , STUB_INT totalLength , STUB_INT offset , 
		STUB_INT length ,  STUB_INT encryption ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<
		__TIME__<<"]\n";
	tvb = tvb + offset ;
	//check contiguous data available for 3 byte ?
    if ( !isContiguous(  totalLength , offset , length ) ){
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
			"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
			<<"] failed function is_contiguous \n";
		return 0;
	}
        STUB_INT32  tempInt = 0;
		//if contigous  then read data of length and convert to uSTUB_INT24 and return.
		switch ( length ){
			case 1:
				tempInt =(STUB_INT8) getGuint8( tvb , totalLength , offset);
				break;
			case 2: 
				tempInt=(STUB_INT16) ( encryption == 1?  letohs16 ( tvb ) : 
						ntohs16 ( tvb ) );
				break;
			case 3:
				tempInt =   (encryption == 1  ? letoh24 ( tvb )  : 
						ntoh24 ( tvb ) );
				if ( tempInt & 0x80000000 )
					//sigen bit set
					tempInt |=0xFF000000;
				break;
			case 4:
				tempInt = ( encryption == 1  ? letohl32 ( tvb ) : 
						ntohl32 ( tvb ) ) ;
				std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<
					__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<
					__DATE__<<"_"<<__TIME__<<"]"<<"TEMP"<<tempInt<<'\n';
				break;
			default:
				std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<
					__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<
					__DATE__<<"_"<<__TIME__<<"]"<<"ERROR ON READING INT\n";
				return 0;
		}
		return tempInt ;
}

