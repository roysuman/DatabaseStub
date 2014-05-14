/*
 * =====================================================================================
 *
 *       Filename:  shift_char.cpp
 *
 *    Description:  for coppying different datatype into char *
 *
 *        Version:  1.0
 *        Created:  Thursday 19 December 2013 12:55:02  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy (), 
 *   Organization:  Cognizant Technological solutions
 *
 * =====================================================================================
 */
#include "shift_char.hpp"
bool nths16 ( char *&tvb , int offset , int data ) {
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	try{
		tvb +=offset;
                tvb [ offset  ] = data & 0xff;
		tvb [ ++offset ] = ( data >> 8 ) & 0xff ;
                //tvb [ ++offset ] = ( data >>16 ) & 0xff ;
	}catch ( std::exception &e ){
		std::cerr<<__FUNCTION__<<"exception "<<e.what()<<std::endl;
		exit ( -1 );
		return false;
	}
		return true;
		
}

bool nth24 ( char *&tvb , int offset , int data ) {
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	try{
                //tvb +=offset;
		tvb [ offset ] = data & 0xff;
		tvb [ ++offset ] = ( data >> 8 ) & 0xff ;
		tvb [ ++offset ] = ( data >>16 ) & 0xff ;
                //tvb [ ++offset ] = ( data >>32 ) & 0xff ;
	}catch ( std::exception &e ){
		std::cerr<<__FUNCTION__<<":exception "<<e.what()<<std::endl;
		return false;
	}
		return true;
		
}

