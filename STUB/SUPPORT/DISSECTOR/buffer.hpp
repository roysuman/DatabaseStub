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
#include"../STRUCTURE/rawdata_structure.hpp"
#include "../../TCPSTUB/generatepacket.h"
#include "../../STRUCTURE/sumanGtkmm.hpp"
#include "field.hpp"
namespace buff{
template <class T>class Buffer{
		public:
			static bool rootRowPass;
			static guint tvbLength;
			static bool pass;
			Buffer( void );
			~Buffer( void );
			//read the data from tvb , buffer.
			static T Read ( actRawDataStruct * , proto::fieldInfo * , int  , int * , int , int );
			//print the information of the current protocol catched from buffer
			static bool printBufferFieldProto ( proto::fieldInfo );
			//get the ont byte value
			static guint32 getGuint8 ( actRawDataStruct * , int );
			//return the length of string
			static guint32 getStringLength ( actRawDataStruct * , int );
			//check whether buffer has remaining length or not
			static bool getRemainingLength ( int );
			//return remaining length
			static gint returnRemainingLength ( int );
            static bool addHeading ( );
			static guint16 getLetohs ( actRawDataStruct * , int );
			static guint32 getLetohl ( actRawDataStruct * , int );
			static guint64 getLetoh64 ( actRawDataStruct * , int );
			
			
	};

template < class T> buff::Buffer<T>::Buffer(){}
template < class T> buff::Buffer< T >::~Buffer(){}
template <class T> guint buff::Buffer< T >::tvbLength = 3; // initialized by 3 because packet parameter length is 3
//make the pass false , 1st time buffer read will read the length of the packet and is pass is false then it will update it at the buffer length , because next time it will create some override error.
template < class T>bool buff::Buffer< T >::pass = false ;
template < class T> bool buff::Buffer< T >::rootRowPass = true;
//function defination of Read
//proto::field_info is a structur that contais all field protocols of corresponding protocols
//index determiones which index/field protocol data have to read.
//tvb contais the raw data in buffer
//offset is the current position of the data.
//length is no. of byte of the data have to be read.
//
template<class T> T  buff::Buffer< T >::Read( actRawDataStruct *rawDataPacket , proto::fieldInfo *fieldInfoData , int index , int *offset , int length , int encryption ){
    T data;

    std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
    if ( buff::Buffer< T >::rootRowPass ) buff::Buffer< T >::rootRowPass = false;
    QString dissectorName ( fieldInfoData[ index ].name );
    switch ( fieldInfoData [ index ].type ){
        case types::UINT16:
        case types::UINT24 :
        case types::UINT32:{
                  data = types::getGuint( (u_char *)rawDataPacket->data , rawDataPacket->length  , *offset ,length , encryption ) ;
                   // pass is used to cut the lengtgh first time
                   if ( !buff::Buffer<T>::pass ){
                       buff::Buffer<T>::tvbLength =  boost::get< int > (data)  + *offset ;
                       buff::Buffer<T>::pass= true ;
                       }
                    *offset += length;
              // return data;
                   // static_cast<std::ostringstream*>( &(std::ostringstream() << temp) )->str() ;
                      break ;

               }
        case types::UINT8:{
                  data = ( guint32 ) types::getGuint8 ( (u_char*)rawDataPacket->data , buff::Buffer<T>::tvbLength , *offset  ) ;
                    *offset += length;
                  //    data =  static_cast<std::ostringstream*>( &(std::ostringstream() << tempGuint32) )->str() ;

             // return data;
              break;
              }

        case types::STRING :{
                    buff::Buffer<void>::printBufferFieldProto( fieldInfoData [ index ] );
                    data = types::getString ( (u_char*)rawDataPacket->data , buff::Buffer<T>::tvbLength , *offset , length ) ;
                    *offset += length;
                    //return data;
              break;

                }
    case types::BYTES :{
                  // T data;
                    *offset += length;
                  // return data;
                   break;
               }
//	case default :{
//		       break;
//		      }


    }
    buff::Buffer<void>::printBufferFieldProto ( fieldInfoData [ index ] );
    *offset += length;
    return data;
//	return data;

}

//print the protocol information

template < class T >bool buff::Buffer< T >::printBufferFieldProto ( proto::fieldInfo fi ){
    std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
    proto::Proto::printRegistrationData( fi );
    return true;
}

//read 8bits and return it as 32bit int
template < class T >guint32 buff::Buffer< T >::getGuint8( actRawDataStruct *rawDataPacket , int offset ){
    std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
    if ( buff::Buffer<T>::tvbLength == 1 )
        return 1;
    return ( types::getGuint8 ( (u_char*)rawDataPacket->data  , buff::Buffer<T>::tvbLength , offset ) );
}

//get the length of the string from the current offset
template <class T >guint32 buff::Buffer< T >::getStringLength (  actRawDataStruct *rawDataPacket , int offset ){
    std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
    std::string stringValue = types::getString ( (u_char *) rawDataPacket->data , buff::Buffer<T>::tvbLength , offset , 0 );
    return ( stringValue.length() + 1 );
}
//whether end of buffer reached??
/*
template < class T >bool buff::Buffer< T >::getRemainingLength ( int offset ){
    std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
    if ( buff::Buffer::tvbLength ( offset + 1 ) )
        return true;
    return false;
}
*/
//return the remaining length from the current offset
template < class T >int buff::Buffer< T >::returnRemainingLength ( gint offset ){
    std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;

    return ( buff::Buffer<T>::tvbLength - ( offset + 1 ) );
}

template < class T>guint16 buff::Buffer< T >::getLetohs ( actRawDataStruct * rawDataPacket , int offset ){
    std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
        const u_char *data = (u_char * )rawDataPacket->data ;
    return ( letohs16( data + offset ) );

}

template < class T>guint32 buff::Buffer< T >::getLetohl ( actRawDataStruct * rawDataPacket , int offset ){
    std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;

        const u_char *data = (u_char * )rawDataPacket->data ;
    return ( letohl32( data + offset ) );
}

template < class T>guint64 buff::Buffer< T >::getLetoh64 ( actRawDataStruct *rawDataPacket , int offset ){
    std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
        const u_char *data = (u_char * )rawDataPacket->data ;
    return ( letoh64( data + offset ) );

}


}
#endif /* BUFFER_HPP */
