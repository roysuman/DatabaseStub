/*
 * =====================================================================================
 *
 *       Filename:  proto.cpp
 *
 *    Description:  this mainly defien all the functions defines at header proto.hpp
 *    and some oher functions related to that
 *
 *        Version:  1.0
 *        Created:  Thursday 19 September 2013 12:53:18  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy (), 
 *   Organization:  SELF
 *
 * =====================================================================================
 */


#include "../include/proto.hpp"

//again define proto_map variable.

proto::_ports proto::ports;

//proto::_protoMap proto::protoMap;
proto::_protoMap proto::protoMap;


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  registerProto
 *  Description:  register the protocol informations at run time
 * =====================================================================================
 */

bool proto::Proto::registerProto( std::string protocolName , proto::fpStruct *funcStructure ,
	       	STUB_INT noDissectr ){

    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
	    __LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

    fieldInfo   *fieldInformation; 

    if (  proto::protoMap.find ( protocolName ) == proto::protoMap.end() ){
//    if ( protoMapIterator == proto::protoMap.end() ){ // this port is not registered yet
        try{
            fieldInformation = new ( std::nothrow ) fieldInfo [ noDissectr ] ;
            mapkey maped ( funcStructure , fieldInformation );
            if ( ( protoMap.insert( std::make_pair ( protocolName , maped ) ).second )  )
            return true;
        }
        catch( std::bad_alloc &ba ){
            std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		    __LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"] Exception :"
		    <<ba.what()<<'\n';
            exit ( -1 );
        }
    }
    return false;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  insertDissectorProto
 *  Description:  register all field informations of a new protocol
 * =====================================================================================
 */

bool proto::Proto::insertDissectorProto ( std::string protocolName , STUB_INT noDisectorProto ,
	       	packetInfo * pInfo ){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<
		"Registering ... [PORTOCOL]:"<<protocolName<<'\n';    //check that protocol/port is registered or not into the map

	mapkey                        mapedKey;
	fieldInfo                     *fieldInfoRef;
	proto::_protoMap::iterator    protoMapIterator;

	if ( ( protoMapIterator = proto::protoMap.find( protocolName ) ) ==
		       	proto::protoMap.end() ) {

		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
			"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
			"] [Protocol]--"<<protocolName<<"--has not been registerd\n";
		return false;
	}
	//port is registered
	else{

		/*-----------------------------------------------------------------------------
		 *  second element of the protoMap is an array of ieldInfo
		 *-----------------------------------------------------------------------------*/
		mapedKey =protoMapIterator->second;
		fieldInfoRef = mapedKey.second;
		for ( STUB_INT loop = 0 ; loop < noDisectorProto ; ++ loop ){
			* ( pInfo [ loop ].index ) = loop ;
			//now coppy the values from p_info->hf_info fields
			fieldInfoRef [ loop ] = pInfo [ loop ].hfInfo;
			proto::Proto::printRegistrationData ( pInfo [ loop ].hfInfo ) ;
		}
	}

/*                actRawDataStruct *packetSettingDataArray;// = new packetSettingDataArray();
            queryData * queryDataArray;// = new queryDataArray();

            boost::any_cast< bool ( * )( actRawDataStruct * , queryData *& )> ( boost::get < boost::any > (Proto::initDissect( 3306 , 1 ) ) )  ( packetSettingDataArray ,  queryDataArray );
*/
    return true;
	
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  printRegistrationData
 *  Description:  print the registered protocol field informations.
 * =====================================================================================
 */

void proto::Proto::printRegistrationData ( proto::fieldInfo fi ){

    //std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
//	    __LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
	    __LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<
	    "packet INFO:: Name:"<<fi.name<<'\n';

}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  initDissect
 *  Description:  find the dissector for a protocol--
 *               two kinds of dissector methods have been registered--
 *               this method will return appropriate dissector depending on the choice
 * =====================================================================================
 */

returnType proto::Proto::initDissect( std::string protocolName , STUB_INT choice ){

     std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
	     __LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

     std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
	     __LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"] return dissector for\
	     protocol[PROTOCOL]:"<<protocolName<<'\n';

     mapkey                        maped;
     proto::fpStruct               *func;
     proto::_protoMap::iterator    protomapIterator;

     //check this port is registered or not
     if (  ( protomapIterator = proto::protoMap.find ( protocolName ) ) == 
		     proto::protoMap.end() ){ 
	     std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		     "] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
		     "]"<<"Going to return false\n";
	     exit(0); 
	     return false;
     }
     else{
         mapkey maped = protomapIterator->second;
         func = maped.first;
		 
         if ( choice !=1  ){
             std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		     "] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
		     "]"<<"return:"<<"functionToInnitiateDissecton\n";
             return  func->functionToInnitiateDissecton;
         }
         else{

             std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<
		     "] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
		     "]"<<"functionToGetClientRequest\n";
             return func->functionToGetClientRequest ;
         }
		
        }
 }

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  logProtocols
 *  Description:  log all registered protocols info in a file
 * =====================================================================================
 */
bool proto::Proto::logProtocols(){

    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
	    __LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";
    mapkey          maped;
    Json::Value     protocols;
    Json::Value     dissectors;
//    fieldInfo       fieldInfoRef;
    std::fstream    protocolFile;
 //   fpStruct        *noOfDissector;

    //open a file to keep registered protocol's informations.
   //("registeredProtocol.log", std::ios::out);
    protocolFile.open("../../CONFIG/registeredProtocol.log", std::ios::out );
    if ( !protocolFile.is_open() ){
        std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
		"] --can't open registered prototcol log\n";
        return false;
        }
    // jSON file for keeping information of registered protocols
    Json::Value dissectorsArray(Json::arrayValue);
    //   proto::_proto_map::iterator protomap_iterator;
    for ( proto::_protoMap::iterator protoMapIterator =protoMap.begin(); 
		    protoMapIterator != protoMap.end() ; 
		    ++protoMapIterator ){ // if port/protocol is not registered
        //second element of the proto_map is a array of field_info
        //reffer this array pf field info in a field_info poSTUB_INTer;
//        mapkey maped=protoMapIterator->second;
        //get the no f dissector
      //  fpStruct *noOfDissector = maped.first;
      //  fieldInfo *fieldInfoRef = maped.second;
        //this fied is not working properly
        std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<
		__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<
		"] no of dissecto is"<<std::endl;
        // exit(0);
        //	std::size_t size =sizeof( reffer ) / sizeof( field_info );
        for ( STUB_INT i=0 ; i<132 ; ++ i ){ // no of dissector given hardcoded // 132 if no. of field for mysql
            dissectors["fieldName"]= i;
            dissectorsArray.append(dissectors);
        //	dissectors["abbreviated name"]=reffer[ i ].;
            dissectorsArray.append(dissectors);
        }
        //protocols ["ProtocolS"][ static_cast<std::ostringstream*>( &(std::ostringstream() << ( *protoMapIterator).first) )->str() ]["Dissector"]=dissectorsArray;
         protocols ["ProtocolS"][(( *protoMapIterator).first).c_str() ]["Dissector"]=dissectorsArray;
        protocolFile<<protocols<<std::endl;

    }
    //  protocolFile<<protocols<<std::endl;
    return true;
}


