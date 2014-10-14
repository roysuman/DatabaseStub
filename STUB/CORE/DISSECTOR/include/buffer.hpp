#ifndef BUFFER_HPP
#define BUFFER_HPP 
#include "boost/variant.hpp"
#include<iostream>
#include <sstream>
#include<fstream>
#include<stdlib.h>
#include <QTreeWidgetItem>
#include "proto.hpp"
#include"types.hpp"
#include "shift_int.hpp"
#include"../STRUCTURE/include/rawdata_structure.hpp"
#include "../../../TCPSTUB/generatepacket.h"
#include "../STRUCTURE/include/globalDatatypes.hpp"
#include "field.hpp"
#include "../../../SUPPORT/globalDatatypes.hpp"
namespace buff{
template <class T>class Buffer{
		public:
			static bool rootRowPass;
			static STUB_UINT tvbLength;
			static bool pass;
			Buffer( void );
			~Buffer( void );
			//read the data from tvb , buffer.
			static T Read ( actRawDataStruct * , proto::fieldInfo * , 
					STUB_INT  , STUB_INT * , STUB_INT , STUB_INT );
			//print the information of the current protocol catched from buffer
			static bool printBufferFieldProto ( proto::fieldInfo );
			//get the ont byte value
			static STUB_UINT32 getGuint8 ( actRawDataStruct * , STUB_INT );
			//return the length of string
			static STUB_UINT32 getStringLength ( actRawDataStruct * , STUB_INT );
			//check whether buffer has remaining length or not
			static bool getRemainingLength ( STUB_INT );
			//return remaining length
			static STUB_INT returnRemainingLength ( STUB_INT );
			static bool addHeading ( );
			static STUB_UINT16 getLetohs ( actRawDataStruct * , STUB_INT );
			static STUB_UINT32 getLetohl ( actRawDataStruct * , STUB_INT );
			static STUB_UINT64 getLetoh64 ( actRawDataStruct * , STUB_INT );
			static STUB_UINT32 getLetoh24 ( actRawDataStruct * , STUB_INT );
			
			
	};

template < class T> buff::Buffer<T>::Buffer(){}
template < class T> buff::Buffer< T >::~Buffer(){}

/*-----------------------------------------------------------------------------
 *  init by 3 because packet parameter length is 3
 *-----------------------------------------------------------------------------*/
template <class T> STUB_UINT buff::Buffer< T >::tvbLength = 3; 

/*-----------------------------------------------------------------------------
 *  1st time bufferread will read the length of the packetand is pass is false
 *  then it will update it at the buffer length, because next time it will 
 *  create some overide error.
 *-----------------------------------------------------------------------------*/

template < class T>bool buff::Buffer< T >::pass = false ;
template < class T> bool buff::Buffer< T >::rootRowPass = true;


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  Read
 *  Description:  
 *  read data from buffer--
 * proto::field_info is a structur that contais all field protocols of corresponding protocols
 * index determiones which index/field protocol data have to read. 
 * tvb contais the raw data in buffer 
 * offset is the current position of the data. 
 * length is no. of byte of the data have to be read.
 * =====================================================================================
 */

template<class T> T  buff::Buffer< T >::Read( actRawDataStruct *rawDataPacket , 
		proto::fieldInfo *fieldInfoData , STUB_INT index , 
		STUB_INT *offset , STUB_INT length , STUB_INT encryption ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"]\n";

	T    data;

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"]"<<"OFFSET"<<*offset<<'\n';
	if ( buff::Buffer< T >::rootRowPass ) buff::Buffer< T >::rootRowPass = false;
	QString dissectorName ( fieldInfoData[ index ].name );
	switch ( fieldInfoData [ index ].type ){
        case types::UINT16:
        case types::UINT24 :
        case types::UINT32:{
				   std::cout<<" File Name ["<<__FILE__<<" ] Function [ "
					   <<__FUNCTION__<<"] Line ["<<__LINE__
					   <<"] DateTime ["<<__DATE__<<"_"
					   <<__TIME__<<"]"<<"UINT\n";
                  data = types::getGuint( (u_char *)rawDataPacket->data , 
				  rawDataPacket->length  , *offset ,length , 
				  encryption ) ;
                   // pass is used to cut the lengtgh first time
                   if ( !buff::Buffer< bool >::pass ){
                       buff::Buffer< STUB_INT >::tvbLength =  
			       boost::get< STUB_INT > (data)  + *offset ;
		       std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			       <<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			       <<__TIME__<<"] Initialized totall length:"
			       <<buff::Buffer< STUB_INT >::tvbLength<<'\n';
                       buff::Buffer< bool >::pass= true ;
                       }
                      break ;

               }
        case types::UINT8:
			   data = ( STUB_UINT32 ) types::getGuint8 ( (u_char*)rawDataPacket->data , 
					   buff::Buffer< STUB_INT >::tvbLength , *offset  ) ;
			   break;
	case types::INT8:
	case types::INT16:
	case types::INT24:
	case types::INT32: { 
			   data = types::getInt( (u_char *)rawDataPacket->data , rawDataPacket->length  ,
					   *offset , length , encryption ) ;
			   
			   break;}
			   
	case types::STRING :{
                    buff::Buffer<void>::printBufferFieldProto( fieldInfoData [ index ] );
                    data = types::getString ( (u_char*)rawDataPacket->data , 
				    buff::Buffer< STUB_INT >::tvbLength , *offset , length ) ;
		    //length = data.length() + 1;

                    *offset += (boost::get< std::string >(data)).length();
                    return data;
              break;

                }
    case types::BYTES :{
                  // T data;
                  //  *offset += length;
                  // return data;
                   break;
               }
    case types::FLOAT: 
		       data = types::getFloat( (u_char *)rawDataPacket->data , rawDataPacket->length  ,
				       *offset , length , encryption ) ;
		       break;
    case types::DOUBLE:
		       data = types::getDouble ( ( u_char *) rawDataPacket->data , rawDataPacket->length , 
				       *offset , length ,encryption);
		       break;
    case types::UINT_STRING:
		       data = types::getGuint( (u_char *)rawDataPacket->data , rawDataPacket->length  , 
				       *offset ,length , encryption ) ;
		       break;
    case types::NONE:
		       //nothing to do
		       break;
    case types::UINT64:
		       break;



    }
    buff::Buffer<void>::printBufferFieldProto ( fieldInfoData [ index ] );
    *offset += length;
    return data;

}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  printBufferFieldProto
 *  Description:  print the protocol information
 * =====================================================================================
 */
template < class T >bool buff::Buffer< T >::printBufferFieldProto ( 
		proto::fieldInfo fi ){
    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
	    <<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

    proto::Proto::printRegistrationData( fi );
    return true;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  getGuint8
 *  Description:  read 8bits and return it as 32bit INT
 * =====================================================================================
 */

template < class T >STUB_UINT32 buff::Buffer< T >::getGuint8( 
		actRawDataStruct *rawDataPacket , STUB_INT offset ){

    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
	    <<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
	    <<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"
	    <<"[BUFFER LENGTH]:"<<buff::Buffer< STUB_INT >::tvbLength<<'\n';

    if ( buff::Buffer< STUB_INT >::tvbLength == 1 )
        return 1;
    return ( types::getGuint8 ( (u_char*)rawDataPacket->data  , 
			    buff::Buffer< STUB_INT >::tvbLength , offset ) );
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  getStringLength
 *  Description:  get the length of the string from the current offset
 * =====================================================================================
 */

template <class T >STUB_UINT32 buff::Buffer< T >::getStringLength (  
		actRawDataStruct *rawDataPacket , STUB_INT offset ){

    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
	    <<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";
    std::string   stringValue;

    stringValue = types::getString ( (u_char *) rawDataPacket->data , 
		    buff::Buffer< STUB_INT >::tvbLength , offset , 0 );

    return ( stringValue.length() + 1 );
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  returnRemainingLength
 *  Description:  return the remaing length from the current offset
 * =====================================================================================
 */

template < class T >STUB_INT buff::Buffer< T >::returnRemainingLength ( 
		STUB_INT offset ){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"]\n";

	return ( buff::Buffer< STUB_INT >::tvbLength - ( offset + 1 ) );
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  getLethos
 *  Description:  define---
 * =====================================================================================
 */
template < class T>STUB_UINT16 buff::Buffer< T >::getLetohs ( actRawDataStruct * rawDataPacket ,
	       	STUB_INT offset ){
	
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	const u_char   *data;


	if ( types::isContiguous(  buff::Buffer<STUB_INT>::tvbLength , offset , 4 ) ){
		data = (u_char * )rawDataPacket->data ;
		return ( letohs16( data + offset ) );
		
	}
	return -1;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  getLetohl
 *  Description:  define--
 * =====================================================================================
 */

template < class T>STUB_UINT32 buff::Buffer< T >::getLetohl ( 
		actRawDataStruct * rawDataPacket , STUB_INT offset ){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	const u_char    *data;
	
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"] TVB LENGTH:"
		<<buff::Buffer<STUB_INT>::tvbLength<<"offset"<<offset<<'\n';

	if ( types::isContiguous(  buff::Buffer<STUB_INT>::tvbLength , offset , 4 ) ){
		data = (u_char * )rawDataPacket->data ;
		return ( letohl32( data + offset ) );
	}
	exit ( 0);
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  getLetoh64
 *  Description:  define--
 * =====================================================================================
 */

template < class T>STUB_UINT64 buff::Buffer< T >::getLetoh64 ( 
		actRawDataStruct *rawDataPacket , STUB_INT offset ){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	const u_char   *data;

	if ( types::isContiguous(  buff::Buffer<STUB_INT>::tvbLength , offset , 8 ) ){
		data = (u_char * )rawDataPacket->data ;
		return ( letoh64( data + offset ) );
	}
	exit(0);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  getLetoh24
 *  Description:  define---
 * =====================================================================================
 */

template < class T> STUB_UINT32 buff::Buffer < T >::getLetoh24( 
		actRawDataStruct *rawDataPacket , STUB_INT offset ){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"]\n";
	const u_char   *data; 

	if ( types::isContiguous(  buff::Buffer<STUB_INT>::tvbLength , offset , 3 ) ){
		*data = ( u_char *)rawDataPacket->data;
		return( letoh24( data + offset ) ) ;
	}
	exit(0);
}

}
#endif /* BUFFER_HPP */
