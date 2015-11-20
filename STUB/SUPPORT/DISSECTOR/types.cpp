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
// defination of function is_contigious()
bool types::isContiguous ( int total_length , int offset , int byte_needed ){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	if ( total_length < 0 || offset < 0){
		std::cout<<__FUNCTION__<<"No length \n";
		return false;
		}
/*	std::cout<<"Total length = "<<total_length<<std::endl
		<<"offset   ="<<offset<<std::endl
		<<"byte_needed = "<<byte_needed<<std::endl;
		*/
	if ( ( offset + byte_needed ) <= total_length )
		return true;
	else return false;
}

//function defination of get_guint24
//this function will read length byte from given buffer.
guint32 types::getGuint ( const u_char * tvb , int total_length , int offset , int length ,  int encryption ){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	tvb = tvb + offset ;
	//check contiguous data available for 3 byte ?
    if ( !isContiguous(  total_length , offset , length ) ){
		std::cout<<__FUNCTION__<<"failed function is_contiguous \n";
		return 0;
	}
        guint32  tempInt = 0;
		//if contigous  then read data of length and convert to uint24 and return.
		switch ( length ){
			case 2: {
                    encryption == 1?  ( tempInt = letohs16 ( tvb ) ) : ( tempInt =ntohs16 ( tvb ) );
                    return tempInt;
				}
				break;
			case 3:{
                        (encryption == 1 ) ? ( tempInt = letoh24 ( tvb ) ) : ( tempInt = ntoh24 ( tvb ) );
                    return tempInt;
			       }
			       break;
			case 4:{
                       ( encryption == 1 ) ? ( tempInt = letohl32 ( tvb ) ) : ( tempInt = ntohl32 ( tvb ) ) ;
                       return tempInt;
				       
			       }
			       break;
			       
                   return tempInt ;

	}
	return 0;


}

//this function is needed to read 1byte data from  buffer and will
//retuirn guint8
guint32 types::getGuint8 ( const u_char * tvb, int totalLength , int offset ){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	tvb = tvb + offset ;
	guint32 temp=0;
//	std::cout<<"total -length "<<total_length <<std::endl;
//	std::cout<<"inside checking zone \n";
    if ( isContiguous(  totalLength , offset , 1 ) )memcpy(&temp, tvb , 1);
		return temp;

}

//defination of the function get_string()
std::string types::getString ( const u_char * tvb  , int totalLength , int offset  , int length ){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	if ( offset < 0 ) std::cerr<<__FUNCTION__<<"offset<0\n ";
    if ( offset > totalLength ) std::cerr<<__FUNCTION__<<"offset  >total length \n";
	tvb = tvb + offset ;
        std::cout<<__FUNCTION__<<"length="<<length<<"total length="<<totalLength<<std::endl;
	if ( length == 0 ){
        std::string temp1;

//        for( int ii= offset ; ii<=total_length; ++ ii){
//            std::cout<<tvb[ii];
//            if ( tvb[ii] == '\0')break;
//        }

        temp1 =reinterpret_cast<const char*>(tvb ) ;
std::cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";
       std::cout<<__FUNCTION__<<"temp="<<temp1<<"length="<<temp1.length()<<std::endl;
std::cout<<"!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n";

        return temp1;
	}
	else{
		//coppy into a string
		try {

			char *array = new ( std::nothrow ) char [ length + 1 ] ;
			memcpy ( array , tvb , length );
			array [ length  ] = '\0';
			std::string temp1( array );
                        //std::cout<<"data at temp = "<<temp1<<std::endl;
			delete []array;

			return temp1;
		}
		catch ( std::bad_alloc &ba ){
			std::cerr<<__FUNCTION__<<"exception cgt\t"<<ba.what() <<std::endl;
		}
	}
	return "NULL";
}
