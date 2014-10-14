/*
   implementation of bar.hpp
   */
#include "../include/ber.hpp"

//dissector for class BER
ber::Ber::~Ber(){}
//constructor for clas BER
ber::Ber::Ber(){}

/*
   Function getBerIdentifier will dissect the identifier byte */
STUB_INT ber::Ber::getBerIdentifier( const u_char *buffer , STUB_INT offset , STUB_INT8 * berClass , 
		bool *primFlag , STUB_INT32 *tag ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";
	*primFlag = false;
	*berClass = 0;
	*tag = 0 ;
	STUB_UINT8 id = 0 ;
//	memcpy( &id , buffer + offset , 1 );// coppy first one byte
	id = buffer [ offset ];
	offset ++;
#ifdef DEBUG
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"BER ID:"
		<<id<<std::endl;
#endif
     *berClass = (id >> 6) & 0x03;
     *primFlag = (id >> 5) & 0x01;
     *tag  = id & 0x1F;
#ifdef DEBUG
     std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
	     __LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"[BerClass]:"<<
	     (STUB_INT)*berClass<<"[primFlag]:"<<(STUB_INT)primFlag<<"[tag]:"<<(STUB_INT)*tag<<std::endl;
     std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
	     __LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"] [OFFSET:]"<<
	     offset<<std::endl;
#endif
	return offset;

}

/*
   Function getBerLength to return the length of a ber data
   */
STUB_INT ber::Ber::getBerLength( const u_char *buffer , STUB_INT offset , STUB_INT *length){
	*length = 0;
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";
	STUB_UINT8 len = 0 , tempLen;
	STUB_UINT32 totalLength = 0;
	len = buffer [ offset ];
	offset ++;
#ifdef DEBUG
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<\
		"First byte for length:"<<len<<std::endl;
#endif
	if ( ! ( len & 0x80 )  ) totalLength = len;
	else{
		len = len & 0x7F ;
		//offset += len;
		if ( len ){
			while ( len -- ){
				tempLen = buffer [ offset++ ];
				totalLength = (totalLength << 8 ) + tempLen ;
			}
		}
		
	}
	*length = totalLength;
#ifdef DEBUG
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
		"] decoded length:"<<*length<<std::endl;
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"] offset:"<<
		offset<<std::endl;
#endif
	return offset;
}


bool ber::Ber::readBerInteger ( const u_char *buffer , STUB_INT offset , STUB_INT length , 
		STUB_INT *data ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";
#ifdef DEBUG
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"[offset]:"<<
		offset<<"[length]:"<<length<<"[data]:"<<*data<<std::endl;
#endif
	try{
		*data = 0;
		for ( STUB_INT i = 0 ; i< length ; ++ i)
			*data = ( *data << 8 ) + buffer[ offset ++ ];
		return true;
	}
	catch ( std::exception &e ){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
			"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
			<<"]"<<"exception cgt:"<<e.what()<<std::endl;
        exit ( -1);
	}
}

STUB_INT ber::Ber::readBerBlock( const u_char *buffer , STUB_INT offset , STUB_INT totalLength, 
		std::string fieldName ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";
	STUB_INT8 berClass;
	bool primFlag;
	STUB_INT32 tag;
	STUB_INT lengthData;
	offset = ber::Ber::getBerIdentifier( buffer , offset , &berClass ,
		       	&primFlag , &tag );
	offset = ber::Ber::getBerLength ( buffer , offset , &lengthData );
	switch ( (STUB_INT)tag ){
		case 1:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<
				__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<
				__DATE__<<"_"<<__TIME__<<"] ["<<fieldName<<"]:"<<
				( buffer [ offset ] == true ?"TRUE":"FALSE")<<std::endl;
			break;
		case 2:
		case 10:
			STUB_INT data;
			ber::Ber::readBerInteger( buffer , offset , lengthData , &data );
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
				<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<
				__TIME__<<"] ["<<fieldName<<"]:"<<data<<std::endl;
			break;
		case 4:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<
				__TIME__<<"] ["<<fieldName<<"]:"<<
				types::getString( buffer , totalLength , offset , lengthData )
				<<std::endl;
			break;
		default:

			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<
				__TIME__<<"]"<<__FUNCTION__<<"DEFAULT DATA\n";
	}
	return ( offset + lengthData );
}

