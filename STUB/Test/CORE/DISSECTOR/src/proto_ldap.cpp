/*
for defination of ldap.cpp
created on thesame date of ldap.hpp
*/

#include "../include/proto_ldap.hpp"
#include<stdio.h>
#include "jsoncpp/json.h" // for json
#include "jsoncpp/writer.h" // for json
#include <fstream>


std::unordered_map< STUB_INT , std::string > Ldap::resultCode={
		 {   0, "SUCCESS" },
		 {   1, "operationsError" },
		 {   2, "protocolError" },
		 {   3, "timeLimitExceeded" },
		 {   4, "sizeLimitExceeded" },
		 {   5, "compareFalse" },
		 {   6, "compareTrue" },
		 {   7, "authMethodNotSupported" },
		 {   8, "strongAuthRequired" },
		 {  10, "referral" },
		 {  11, "adminLimitExceeded" },
		 {  12, "unavailableCriticalExtension" },
		 {  13, "confidentialityRequired" },
		 {  14, "saslBindInProgress" },
		 {  16, "noSuchAttribute" },
		 {  17, "undefinedAttributeType" },
		 {  18, "inappropriateMatching" },
		 {  19, "constraSTUB_INTViolation" },
		 {  20, "attributeOrValueExists" },
		 {  21, "invalidAttributeSyntax" },
		 {  32, "noSuchObject" },
		 {  33, "aliasProblem" },
		 {  34, "invalidDNSyntax" },
		 {  36, "aliasDereferencingProblem" },
		 {  48, "inappropriateAuthentication" },
		 {  49, "invalidCredentials" },
		 {  50, "insufficientAccessRights" },
		 {  51, "busy" },
		 {  52, "unavailable" },
		 {  53, "unwillingToPerform" },
		 {  54, "loopDetect" },
		 {  64, "namingViolation" },
		 {  65, "objectClassViolation" },
		 {  66, "notAllowedOnNonLeaf" },
		 {  67, "notAllowedOnRDN" },
		 {  68, "entryAlreadyExists" },
		 {  69, "objectClassModsProhibited" },
		 {  71, "affectsMultipleDSAs" },
		 {  80, "other" },
		 { 118, "canceled" },
		 { 119, "noSuchOperation" },
		 { 120, "tooLate" },
		 { 121, "cannotCancel" },
	 };
//constructor
Ldap::Ldap(){}
//destructor
Ldap::~Ldap(){}
//initialize all ldap protocols
 bool Ldap::initialize( void ){
	 std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		 __LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";
	 proto::fpStruct *functionStructureLdap = new proto::fpStruct();
	 functionStructureLdap->functionToInnitiateDissecton = &Ldap::dissectLdap;
//	 functionStructureLdap.functionToGetClientRequest= NULL ;
    if (! proto::Proto::registerProto ( "LDAP" , functionStructureLdap , 0 )  ){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
			"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
			"]cn't register LDAP protocol\n" ;
		return false;
	}
	return true; 
}

STUB_INT Ldap::dissectAttributeDescAndLdapValue( const u_char *buffer , 
		STUB_INT offset , STUB_INT totalLength ){
	//attributeDesc
	offset = ber::Ber::readBerBlock( buffer , offset , totalLength , 
			"ATTRIBUTE-DESC" );
	//ldapValue
	offset = ber::Ber::readBerBlock( buffer , offset , totalLength , 
			"LDAP-VALUE-STRING" );
	return offset;
}

//DISSECT LDAP FILTER SUBSTRING_ITEMS
STUB_INT Ldap::dissectLdapSubStringFilterItems( const u_char *buffer , STUB_INT offset , STUB_INT totalLength ){
	bool primFlag;
	STUB_INT8 berClass;
	STUB_INT32 tag;
	STUB_INT lengthData;
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";
	offset = ber::Ber::getBerIdentifier( buffer , offset , &berClass ,
		       	&primFlag , &tag );
	offset = ber::Ber::getBerLength ( buffer , offset , &lengthData );
	switch ( ( STUB_INT ) tag ){
		case 0:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
				"] [FirstItem]:"<<types::getString ( buffer , totalLength , 
						offset , lengthData )<<std::endl;
			break;
		case 1:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] [Middle]:"<<types::getString ( buffer , totalLength , 
						offset , lengthData )<<std::endl;
			break;
		case 2:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
				"] [LastItem]:"<<types::getString ( buffer , totalLength , 
						offset , lengthData )<<std::endl;
			break;
	}
	offset += lengthData;
	return offset;
}

//dissect ldapfilters f search request
STUB_INT Ldap::dissectLdapFilter( const u_char *buffer , STUB_INT offset , STUB_INT totalLength ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";
	STUB_INT8 berClass;
	bool primFlag;
	STUB_INT32 tag;
	STUB_INT lengthData;
	STUB_INT endPoSTUB_INT;
	offset = ber::Ber::getBerIdentifier( buffer , offset , &berClass , &primFlag , &tag );

	offset = ber::Ber::getBerLength ( buffer , offset , &lengthData );
	switch ( ( STUB_INT )tag ){
		case 0:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__\
				<<"]IT'S and FLAG\n";
			return ( dissectLdapFilter( buffer , offset , totalLength ) );
			break;
		case 1:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] IT'S or FLAG\n";
			return ( dissectLdapFilter( buffer , offset , totalLength ) );
			break;
		case 2:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] IT'S not FLAG\n";
			return ( dissectLdapFilter( buffer , offset , totalLength ) );
			break;
		case 3:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] IT'S equalityMatch FLAG\n";
			offset = dissectAttributeDescAndLdapValue( buffer , offset, totalLength );
			if ( offset < totalLength ) 
				return (Ldap::dissectLdapFilter( buffer , offset , totalLength ) ); 
			break;
		case 4:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
				"] IT'S substring FLAG\n";
			offset = ber::Ber::readBerBlock( buffer , offset , totalLength , "TYPES" );
			offset = ber::Ber::getBerIdentifier( buffer , offset , &berClass , 
					&primFlag , &tag );
			offset = ber::Ber::getBerLength ( buffer , offset , &lengthData );
			endPoSTUB_INT = offset + lengthData;
			while ( offset < endPoSTUB_INT )
			offset =dissectLdapSubStringFilterItems( buffer , offset , 
					offset + lengthData );
			if ( offset < totalLength ) 
				return (Ldap::dissectLdapFilter( buffer , offset , totalLength ) ); 
			break;
		case 5:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] IT'S greater-or-Equal FLAG\n";
			offset = dissectAttributeDescAndLdapValue( buffer , offset,
				       	totalLength );
			if ( offset < totalLength ) 
				return (Ldap::dissectLdapFilter( buffer , offset ,
						       	totalLength ) ); 
			break;
		case 6:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
				"] IT'S less-or-Equal FLAG\n";
			offset = dissectAttributeDescAndLdapValue( buffer , offset, totalLength );
			if ( offset < totalLength ) 
				return (Ldap::dissectLdapFilter( buffer , offset , totalLength ) ); 
			break;
		case 7:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
				"] IT'S present FLAG\n";
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
				"]"<<"[TYPES]:"<<types::getString ( buffer , totalLength ,
					       	offset , lengthData );
			offset += lengthData;
			if ( offset < totalLength ) 
				return (Ldap::dissectLdapFilter( buffer , offset , totalLength ) ); 

			break;
		case 8:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
				"] IT'S approaxMatch FLAG\n";
			offset = dissectAttributeDescAndLdapValue( buffer , offset, totalLength );
			if ( offset < totalLength ) 
				return (Ldap::dissectLdapFilter( buffer , offset , totalLength ) ); 
			break;
		case 9:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] IT'S extensibleMatch FLAG\n";
			break;
		default:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] NULL\n";
	}
	return offset;
}


//DISSECT LDAP SEARCH REQUEST

STUB_INT Ldap::dissectLdapSearchRequest( const u_char *buffer , STUB_INT offset , STUB_INT totalLength ){
	//base object
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";
	STUB_INT8 berClass;
	bool primFlag;
	STUB_INT32 tag;
	STUB_INT  lengthData;
	offset = ber::Ber::readBerBlock( buffer , offset , totalLength , "BASE_OBJECT" );
	offset = ber::Ber::readBerBlock( buffer , offset , totalLength , "SCOPE" );
	//derefAliases
	offset = ber::Ber::readBerBlock( buffer , offset , totalLength , "ALIASES" );
	//sizelimit
	offset = ber::Ber::readBerBlock( buffer , offset , totalLength , "SIZE-LIMIT" );
	//timelimit
	offset = ber::Ber::readBerBlock( buffer , offset , totalLength , "TIME-LIMIT" );

	//types only

	offset = ber::Ber::readBerBlock( buffer , offset , totalLength , "TYPES-ONLY" );
	//filter -- complex one
	ber::Ber::getBerLength ( buffer , offset + 1 , &lengthData );
#ifdef DEBUG
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"####LENGTH###\
		[OFFSET]:"<<offset<<"[LENGTH]:"<<lengthData<<std::endl;
#endif
	offset = dissectLdapFilter( buffer , offset , offset + lengthData );
	//attributes
	offset = ber::Ber::getBerIdentifier( buffer , offset , &berClass , &primFlag , &tag );
	offset = ber::Ber::getBerLength ( buffer , offset , &lengthData );
	return ber::Ber::readBerBlock( buffer , offset , totalLength , "ATTRIBUTES" );
	
}
//dissect the ldap bind request packet
 //method to dissect ldap bindrequest packet protocols.

 //ldap bindrequest
 //ldap-version-
 //ldap-name
 //ldap-authentication

STUB_INT Ldap::dissectLdapBindRequest( const u_char *buffer , STUB_INT totalLength , STUB_INT offset ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";
	return ( ber::Ber::readBerBlock( buffer , offset , totalLength , 
				"LDAP_VERSION" ) );

}

//dissect ldap partialattributs
STUB_INT Ldap::dissectLdapPartialAttributes( const u_char *buffer , STUB_INT offset , STUB_INT totalLength ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";
	//get the value for bar-identifier
	STUB_INT8 berClass;
	bool primFlag;
	STUB_INT32 tag;
	STUB_INT lengthData;
	//dissect attribute description//
	//get the ber identifier dissected data
	offset = ber::Ber::getBerIdentifier( buffer , offset , &berClass , 
			&primFlag , &tag );
	//get the length for data
	offset = ber::Ber::getBerLength ( buffer , offset , &lengthData	);
	offset = ber::Ber::readBerBlock( buffer , offset , totalLength ,
		       	"ATTRIBUTE-DESCRIPTION" );
	//get the ber identifier dissected data
	offset = ber::Ber::getBerIdentifier( buffer , offset , &berClass , 
			&primFlag , &tag );
	//get the length for data
	offset = ber::Ber::getBerLength ( buffer , offset , &lengthData );
	STUB_INT uppBoundPosition = offset + lengthData;
	STUB_INT count = 0;
	while ( offset < uppBoundPosition ){
		offset = ber::Ber::readBerBlock( buffer , offset , totalLength ,
			       	"VALUE-" + static_cast < std::ostringstream *> ( & ( 
						std::ostringstream () << ++count ) )->str() );

	}
		return offset;
}

//dissect ldap result entry
STUB_INT Ldap::dissectLdapSearchResultEntry( const u_char* buffer , STUB_INT offset , STUB_INT totalLength ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<
		"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";
	//get the value for bar-identifier
	STUB_INT8 berClass;
	bool primFlag;
	STUB_INT32 tag;
	offset = ber::Ber::readBerBlock( buffer , offset , totalLength , "OBJECT-NAME" );
	//get the ber identifier dissected data
	offset = ber::Ber::getBerIdentifier( buffer , offset , &berClass , &primFlag , &tag );
	//get the length for data
	STUB_INT protocolLength;
	offset = ber::Ber::getBerLength ( buffer , offset , &protocolLength );
	STUB_INT upperBound = offset + protocolLength ;
	while ( offset < upperBound )
	offset = Ldap::dissectLdapPartialAttributes( buffer , offset , offset + protocolLength );
	return offset;
}

STUB_INT Ldap::dissectLdapSearchResultDone( const u_char *buffer , STUB_INT offset , STUB_INT totalLength ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";
#ifdef DEBUGMAP
	for ( auto ii= resultCode.begin() ; ii!=resultCode.end() ; ++ii)
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
			"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
			"]"<<ii->first<<"::"<<ii->second<<std::endl;
#endif

	//get the value for bar-identifier
	STUB_INT8 berClass;
	bool primFlag;
	STUB_INT32 tag;
	STUB_INT lengthData;
	//get the ber identifier dissected data
	offset = ber::Ber::getBerIdentifier( buffer , offset , &berClass , &primFlag , &tag );
	//get the length for data
	offset = ber::Ber::getBerLength ( buffer , offset , &lengthData );
	std::unordered_map< STUB_INT , std::string >::const_iterator got = 
		resultCode.find( ( STUB_INT ) buffer [ offset ++ ]);
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"] [RESULT CODE]:"<<
		got->first<<"[MEENING]:"<<got->second<<std::endl;
	//dissect ldapdn
	//get the ber identifier dissected data
	offset = ber::Ber::readBerBlock( buffer , offset , totalLength , "LDAP_DN" );
	offset = ber::Ber::readBerBlock( buffer , offset , totalLength , "ERROR-MESSAGE" );

	offset = ber::Ber::readBerBlock( buffer , offset , totalLength , "REFERRAL" );
	return offset;
}
STUB_INT Ldap::dissectLdapProtocol( actRawDataStruct *rawData , STUB_INT offset , STUB_INT totalLength ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";
	//That’s all fine. 0×30 is the start of a SEQUENCE in BER
	if ( !(rawData->length >=14  && rawData->data[ 0 ] == 0x30 ) ) {
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
			"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
			"]"<<"Error packet\n";
		return -1;
	}
	//get the value for bar-identifier
	STUB_INT8 berClass;
	bool primFlag;
	STUB_INT32 tag;
	//get the ber identifier dissected data
	offset = ber::Ber::getBerIdentifier( (const u_char*)rawData->data , offset ,
		       	&berClass , &primFlag , &tag );
	//get the length for data
	STUB_INT protocolLength;
	offset = ber::Ber::getBerLength (( const u_char *) rawData->data , 
			offset , &protocolLength );
	//read the protocol op 
	switch ( (STUB_INT)tag ){

		
		case 0:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
				"]LDAP BIND REQUEST \n";
			return ( ber::Ber::readBerBlock( ( const u_char *)rawData->data , offset 
						, totalLength , "LDAP_VERSION" ) );
			break;
		
		case 1:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
				"] LDAP RESPONSE -- NO NEED TO DISSECT\n";
			//bind response
			break;
		case 2:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] LDAP UNBIND REQUEST -- NO NEED TODISSECT\n";
			//unbinedrequest
			break;
		case 3://    {   3, "searchRequest" },
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"] LDAP SEARCH REQUEST-- NEED TO DISSECT\n";
			return ( Ldap::dissectLdapSearchRequest( ( const u_char *)rawData->data 
						, offset , protocolLength ) );
			
			break;
		case 4:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"]  LDAP SEARCH RESULT ENTRY-- need to dissect\n";
			return ( Ldap::dissectLdapSearchResultEntry( ( const u_char *)rawData->data
					       	, offset , protocolLength + offset ) );
			break;
		case 5:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
				"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
				<<"]  LDAP SEARCH RESULT DONE\n";
			return ( Ldap::dissectLdapSearchResultDone( ( const u_char *)rawData->data 
						,offset , protocolLength + offset ) );

			break;
			/*
		case 6:
			//      {  19, "searchResRef" },
			break;
		case 7:
			//     {   6, "modifyRequest" },
			break;
		case 8:
			// {   7, "modifyResponse" },
			break;

		case 9:
			//  {   9, "addResponse" },
			break;
		case 10:
			//       {  10, "delRequest" },
			break;
		case 11:
			// {  11, "delResponse" },
			break;
		case 12:
			//   {  12, "modDNRequest" },
			break;
		case 13:
			//   {  13, "modDNResponse" },
			break;
		case 14:
			//    {  14, "compareRequest" },
			break;
		case 15:
			// {  15, "compareResponse" },
			break;
		case 16:
			//  {  16, "abandonRequest" },
			break;
		case 23:
			//     {  23, "extendedReq" },
			break;
		case 24:
			//     {  24, "extendedResp" },
			break;
		case 25:
			//  25, "STUB_INTermediateResponse" },
			break;
			*/
	default:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
				__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
				"] NO NEED FURTHER DISSECTION\n";
			break;
           }
	return -999;

}

bool Ldap::dissectLdap( actRawDataStruct *rawDataPacket , STUB_INT totalPacketLength ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";
    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<
	    "] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"Toatal packet length:"
	    <<totalPacketLength<<std::endl;
	//get the value for bar-identifier
	STUB_INT8 berClass;
	bool primFlag;
	STUB_INT32 tag;
	STUB_INT offset = 0;
	//get the ber identifier dissected data
	offset = ber::Ber::getBerIdentifier( ( const u_char *)rawDataPacket->data , 
			offset , &berClass , &primFlag , &tag );
	//get the length for data
	STUB_INT totalLength;
	offset = ber::Ber::getBerLength ( ( const u_char * )rawDataPacket->data , 
			offset , &totalLength );
	//now check the datatype for ldap packeti
	//dissect message id
	offset = ber::Ber::readBerBlock( ( const u_char * )rawDataPacket->data , 
			offset , totalLength , "MESSAGE-ID" );
	//offset = Ldap::dissectLdapMessageId(( const u_char *) rawDataPacket->data , offset , totalLength );
	offset = Ldap::dissectLdapProtocol( *&rawDataPacket, offset, totalLength );
	return true;
}
