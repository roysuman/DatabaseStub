/*
   implementation of bar.hpp
   */
#include "ber.hpp"

//dissector for class BER
ber::Ber::~Ber(){}
//constructor for clas BER
ber::Ber::Ber(){}

/*
   Function getBerIdentifier will dissect the identifier byte */
int ber::Ber::getBerIdentifier( const u_char *buffer , int offset , gint8 * berClass , bool *primFlag , gint32 *tag ){
	std::cout<<"\nFUNCTION:"<<__FUNCTION__<<std::endl;
	*primFlag = false;
	*berClass = 0;
	*tag = 0 ;
	guint8 id = 0 ;
//	memcpy( &id , buffer + offset , 1 );// coppy first one byte
	id = buffer [ offset ];
	offset ++;
#ifdef DEBUG
	std::cout<<"BER ID:"<<id<<std::endl;
#endif
     *berClass = (id >> 6) & 0x03;
     *primFlag = (id >> 5) & 0x01;
     *tag  = id & 0x1F;
#ifdef DEBUG
     std::cout<<"[BerClass]:"<<(int)*berClass<<"[primFlag]:"<<(int)primFlag<<"[tag]:"<<(int)*tag<<std::endl;
     std::cout<<__FUNCTION__<<"[OFFSET:]"<<offset<<std::endl;
#endif
	return offset;

}

/*
   Function getBerLength to return the length of a ber data
   */
int ber::Ber::getBerLength( const u_char *buffer , int offset , int *length){
	*length = 0;
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	guint8 len = 0 , tempLen;
	guint32 totalLength = 0;
	len = buffer [ offset ];
	offset ++;
#ifdef DEBUG
	std::cout<<"First byte for length:"<<len<<std::endl;
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
	std::cout<<__FUNCTION__<<"decoded length:"<<*length<<std::endl;
	std::cout<<__FUNCTION__<<"offset:"<<offset<<std::endl;
#endif
	return offset;
}


bool ber::Ber::readBerInteger ( const u_char *buffer , int offset , int length , int *data ){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
#ifdef DEBUG
	std::cout<<"[offset]:"<<offset<<"[length]:"<<length<<"[data]:"<<*data<<std::endl;
#endif
	try{
		*data = 0;
		for ( int i = 0 ; i< length ; ++ i)
			*data = ( *data << 8 ) + buffer[ offset ++ ];
		return true;
	}
	catch ( std::exception &e ){
		std::cerr<<"exception cgt:"<<e.what()<<std::endl;
        exit ( -1);
	}
}

int ber::Ber::readBerBlock( const u_char *buffer , int offset , int totalLength, std::string fieldName ){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	gint8 berClass;
	bool primFlag;
	gint32 tag;
	int lengthData;
	offset = ber::Ber::getBerIdentifier( buffer , offset , &berClass , &primFlag , &tag );
	offset = ber::Ber::getBerLength ( buffer , offset , &lengthData );
	switch ( (int)tag ){
		case 1:
			std::cout<<__FUNCTION__<<"["<<fieldName<<"]:"<<( buffer [ offset ] == true ?"TRUE":"FALSE")<<std::endl;
			break;
		case 2:
		case 10:
			int data;
			ber::Ber::readBerInteger( buffer , offset , lengthData , &data );
			std::cout<<__FUNCTION__<<"["<<fieldName<<"]:"<<data<<std::endl;
			break;
		case 4:
            std::cout<<__FUNCTION__<<"["<<fieldName<<"]:"<<types::getString( buffer , totalLength , offset , lengthData )<<std::endl;
			break;
		default:

			std::cout<<__FUNCTION__<<"DEFAULT DATA\n";
	}
	return ( offset + lengthData );
}

