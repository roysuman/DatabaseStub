/*
 * =====================================================================================
 *
 *       Filename:  shift_char.cpp
 *
 *    Description:  for coppying different datatype into STUB_CHAR *
 *
 *        Version:  1.0
 *        Created:  Thursday 19 December 2013 12:55:02  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy (), email.suman.roy@gmail.com
 *   Organization:  SELF
 *
 * =====================================================================================
 */
#include "../include/shift_char.hpp"

bool nths16 ( STUB_CHAR *&tvb , STUB_INT offset , STUB_INT data ) {

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	bool    returnValue;

	returnValue = false;

	try{
		tvb +=offset;
                tvb [ offset  ] = data & 0xff;
		tvb [ ++offset ] = ( data >> 8 ) & 0xff ;
                //tvb [ ++offset ] = ( data >>16 ) & 0xff ;
		returnValue = true;
	}catch ( std::exception &e ){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
			<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
			"] exception "<<e.what()<<std::endl;
		exit ( -1 );
		returnValue = false;
	}
		return returnValue;
		
}

bool nth24 ( STUB_CHAR *&tvb , STUB_INT offset , STUB_INT data ) {

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	bool    returnValue;

	returnValue = false;

	try{
                //tvb +=offset;
		tvb [ offset ] = data & 0xff;
		tvb [ ++offset ] = ( data >> 8 ) & 0xff ;
		tvb [ ++offset ] = ( data >>16 ) & 0xff ;
                //tvb [ ++offset ] = ( data >>32 ) & 0xff ;
		returnValue = true;
	}catch ( std::exception &e ){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
			<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
			"] exception "<<e.what()<<std::endl;
		returnValue= false;
	}
		return returnValue;
		
}

bool nth32( STUB_CHAR *tvb , STUB_INT offset , STUB_INT data ){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__
		<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	bool   returnValue;

	returnValue = false;

	try{
		tvb [ offset ] = data & 0xff;
		tvb [ ++offset ] = ( data >> 8 ) & 0xff ;
		tvb [ ++offset ] = ( data >>16 ) & 0xff ;
		tvb [ ++offset ] = ( data >>32 ) & 0xff ;
		returnValue = true;
	}
	catch ( std::exception &ea ){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
			__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
			"] Exception:"<<ea.what()<<'\n';
		returnValue = false;
	}
	return returnValue;
}

bool lths16( STUB_CHAR *tvb , STUB_INT offset , STUB_INT value ){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<
		"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	bool    returnValue;

	returnValue = false;


	try{
		tvb [ offset ] = value & 0xff;
		tvb [ ++offset ] =( value >> 8 ) & 0xff;
		returnValue = true;
	}
	catch ( std::exception &ea ){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
			<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
			"]Exception:"<<ea.what()<<'\n';
		returnValue = false;
		exit(0);
	}
	return returnValue;
}

