/*
 * =====================================================================================
 *
 *       Filename:  buffer.cpp
 *
 *    Description:  dexcribes all functions declared at buffer.hpp
 *
 *        Version:  1.0
 *        Created:  Sunday 22 September 2013 10:36:03  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy (emainl.suman.roy@gmail.com), 
 *   Organization:  Code For Fun
 *
 * =====================================================================================
 */

//#include"buffer.hpp"
//defien empty constructor


    //all types of function required to read/write data from raw buffer

/*
//defien empty constructor
template < class T> buff::Buffer<T>::Buffer(){}
template < class T> buff::Buffer< T >::~Buffer(){}
template <class T> STUB_UINT buff::Buffer< T >::tvbLength = 3; // initialized by 3 because packet parameter length is 3
//make the pass false , 1st time buffer read will read the length of the packet and is pass is false then it will update it at the buffer length , because next time it will create some override error.
template < class T>bool buff::Buffer< T >::pass = false ;

//function defination of Read
//proto::field_info is a structur that contais all field protocols of corresponding protocols
//index determiones which index/field protocol data have to read.
//tvb contais the raw data in buffer
//offset is the current position of the data.
//length is no. of byte of the data have to be read.
//
template<class T> T  buff::Buffer< T >::Read( actRawDataStruct *rawDataPacket , proto::fieldInfo *fieldInfo , STUB_INT index , STUB_INT *offset , STUB_INT length , STUB_INT encryption ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	if ( rootRowPass ) rootRowPass = false;
	T data;
    QString dissectorName ( fieldInfo[ index ].name );
    switch ( fieldInfo [ index ].type ){
        case types::UINT16:
        case types::UINT24 :
        case types::UINT32:{

					      std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<"type is FT_UINT16 / FT_UINT24 / FT_UINT32\n";
					      STUB_UINT32 temp;
                          temp =types::getGuint8( (u_char *)rawDataPacket->data , rawDataPacket->length  , *offset ,length , encryption );
					      // pass is used to cut the lengtgh first time
                          if ( !buff::Buffer<T>::pass ){
                              buff::Buffer<T>::tvbLength = temp + *offset ;
                              buff::Buffer<T>::pass= true ;
						      
					      }
					      
					      data =  static_cast<std::ostringstream*>( &(std::ostringstream() << temp) )->str() ;
					      			      
				      }
				      break ;
        case types::UINT8:{
					     std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<"type is FT_UINT8\n";
					     STUB_UINT32 tempGuSTUB_INT32 = 0;
                         tempGuSTUB_INT32 =( STUB_UINT32 ) types::getGuint8 ( (u_char*)rawDataPacket->data , buff::Buffer<T>::tvbLength , *offset  ) ;
					     data =  static_cast<std::ostringstream*>( &(std::ostringstream() << tempGuSTUB_INT32) )->str() ;
					    }
				     break;
				     				      
        case types::STRING :{
					       
					      std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<"type is FT_STRING\n";
                          buff::Buffer<void>::printBufferFieldProto( fieldInfo [ index ] );
                          data =  types::getString ( (u_char*)rawDataPacket->data , buff::Buffer<T>::tvbLength , *offset , length );
				       }
                       break;
	}
    buff::Buffer<void>::printBufferFieldProto ( fieldInfo [ index ] );
	
	*offset += length;
	return data;
}

//print the protocol information

template < class T >bool buff::Buffer< T >::printBufferFieldProto ( proto::fieldInfo fi ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	proto::Proto::printRegistrationData( fi );
	return true;
}

//read 8bits and return it as 32bit STUB_INT
template < class T >STUB_UINT32 buff::Buffer< T >::getGuint8( actRawDataStruct *rawDataPacket , STUB_INT offset ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"FUNCTION:"<<__FUNCTION__<<std::endl;
    if ( buff::Buffer<T>::tvbLength == 1 )
		return 1;
    return ( types::getGuint8 ( (u_char*)rawDataPacket->data  , buff::Buffer<T>::tvbLength , offset ) );
}

//get the length of the string from the current offset
template <class T >STUB_UINT32 buff::Buffer< T >::getStringLength (  actRawDataStruct *rawDataPacket , STUB_INT offset ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"FUNCTION:"<<__FUNCTION__<<std::endl;
    std::string stringValue = types::getString ( (u_char *) rawDataPacket->data , buff::Buffer<T>::tvbLength , offset , 0 );
	return ( stringValue.length() + 1 );
}*/
//whether end of buffer reached??
/*
template < class T >bool buff::Buffer< T >::getRemainingLength ( STUB_INT offset ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"FUNCTION:"<<__FUNCTION__<<std::endl;
    if ( buff::Buffer::tvbLength ( offset + 1 ) )
		return true;
	return false;
}
*/
//return the remaining length from the current offset
/*
template < class T >STUB_INT buff::Buffer< T >::returnRemainingLength ( STUB_INT offset ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"FUNCTION:"<<__FUNCTION__<<std::endl;

    return ( buff::Buffer<T>::tvbLength - ( offset + 1 ) );
}

template < class T>STUB_UINT16 buff::Buffer< T >::getLetohs ( actRawDataStruct * rawDataPacket , STUB_INT offset ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"FUNCTION:"<<__FUNCTION__<<std::endl;
        const u_char *data = (u_char * )rawDataPacket->data ;
	return ( letohs16( data + offset ) );
	
}

template < class T>STUB_UINT32 buff::Buffer< T >::getLetohl ( actRawDataStruct * rawDataPacket , STUB_INT offset ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"FUNCTION:"<<__FUNCTION__<<std::endl;

        const u_char *data = (u_char * )rawDataPacket->data ;
	return ( letohl32( data + offset ) );
}

template < class T>STUB_UINT64 buff::Buffer< T >::getLetoh64 ( actRawDataStruct *rawDataPacket , STUB_INT offset ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"FUNCTION:"<<__FUNCTION__<<std::endl;
        const u_char *data = (u_char * )rawDataPacket->data ;
	return ( letoh64( data + offset ) );

}

*/

