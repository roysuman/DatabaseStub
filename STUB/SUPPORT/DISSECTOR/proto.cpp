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
 *   Organization:  Cognizant Technological solutions
 *
 * =====================================================================================
 */


#include "proto.hpp"

//again define proto_map variable.



//proto::_protoMap proto::protoMap;
proto::_protoMap proto::protoMap;



//register the protocol--new protocol will call this method to register that protocol information at run time.
bool proto::Proto::registerProto( int portNumber , proto::fpStruct *funcStructure , int noDissectr ){
    std::cout<<"FUNCTION:"<<__FUNCTION__<<'\n';
    proto::_protoMap::iterator protoMapIterator;
    protoMapIterator= proto::protoMap.find( portNumber ) ;
    if ( protoMapIterator == proto::protoMap.end() ){ // this port is not registered yet
        fieldInfo *temp;
        try{
            temp= new ( std::nothrow ) fieldInfo [ noDissectr ] ;
            mapkey k ( funcStructure , temp );
            protoMap.insert( std::make_pair ( portNumber , k ) );
            return true;
        }
        catch( std::bad_alloc &ba ){
            std::cerr<<__FUNCTION__<<ba.what()<<'\n';
            exit ( -1 );
        }
    }
    return true;
}

// register all field under new protocol.
bool proto::Proto::insertDissectorProto ( int port , int noDisectorProto , packetInfo * pInfo ){
    std::cout<<"FUNCTION:"<<__FUNCTION__<<'\n';
    //check that protocol/port is registered or not into the map
    _protoMap::iterator protoMapIterator = protoMap.find( port ) ;
    if ( protoMapIterator == protoMap.end() ){ // if port/protocol is not registered
        std::cerr<<__FUNCTION__<<"Protocol/port --"<<port<<"--has not been registerd\n";
        return false;
    }
    //port is registered
    else{
        //second element of the proto_map is a array od field_info
        //reffer this array pf field info in a field_info pointer;
        mapkey k=protoMapIterator->second;
        fieldInfo *reffer = k.second;
        for ( int i=0 ; i< noDisectorProto ; ++ i ){
            * ( pInfo [ i ].index ) = i;
            //now coppy the values from p_info->hf_info fields
            reffer [ i ] = pInfo [ i ].hfInfo;
            proto::Proto::printRegistrationData ( pInfo [ i ].hfInfo ) ;
        }
    }
    /*
            actRawDataStruct *packetSettingDataArray;// = new packetSettingDataArray();
            queryData * queryDataArray;// = new queryDataArray();

            boost::any_cast< bool ( * )( actRawDataStruct * , queryData *& )> ( boost::get < boost::any > (Proto::initDissect( 3306 , 1 ) ) )  ( packetSettingDataArray ,  queryDataArray );
*/
    return true;
	
}
//method to print registered protocol field information
void proto::Proto::printRegistrationData ( proto::fieldInfo fi ){
    std::cout<<"FUNCTION:"<<__FUNCTION__<<'\n';
    std::cout<<"packet INFO:: Name:"<<fi.name<<'\n';
}
//not sure--may be run time to find the approp dissector.
returnType proto::Proto::initDissect(int port , int choice ){

     std::cout<<"FUNCTION:"<<__FUNCTION__<<'\n';
     std::cout<<__FUNCTION__<<"[PORT]:"<<port<<'\n';
     proto::_protoMap::iterator protomapIterator;
     //check this port is registered or not
     protomapIterator= proto::protoMap.find( port );
     if ( protomapIterator == proto::protoMap.end() ){ std::cerr<<"Going to return false\n"; exit(0); return false;}
     else{
         mapkey k = protomapIterator->second;
         proto::fpStruct *func;
         func = k.first;
		 
         if ( choice !=1  ){
             std::cout<<"return:"<<"functionToInnitiateDissecton\n";
             return  func->functionToInnitiateDissecton;
         }
         else{
             std::cout<<"functionToGetClientRequest\n";
             return  func->functionToGetClientRequest ;
         }
		
        }
 }

//print all registeres protocols.
bool proto::Proto::logProtocols(){
    std::cout<<"FUNCTION:"<<__FUNCTION__<<'\n';
    //open a file to keep registered protocol's informations.
    std::fstream protocolFile;//("registeredProtocol.log", std::ios::out);
    protocolFile.open("../../CONFIG/registeredProtocol.log", std::ios::out );
    if ( !protocolFile.is_open() ){
        std::cerr<<__FUNCTION__<<"can't open registered prototcol log\n";
        return false;
        }
    // jSON file for keeping information of registered protocols
    Json::Value protocols;
    Json::Value dissectors;
    Json::Value dissectorsArray(Json::arrayValue);
    //   proto::_proto_map::iterator protomap_iterator;
    for ( proto::_protoMap::iterator protoMapIterator =protoMap.begin(); protoMapIterator != protoMap.end() ; ++protoMapIterator ){ // if port/protocol is not registered
        //second element of the proto_map is a array of field_info
        //reffer this array pf field info in a field_info pointer;
        mapkey k=protoMapIterator->second;
        //get the no f dissector
        fpStruct *no = k.first;
        fieldInfo *reffer = k.second;
        //this fied is not working properly
        std::cout<<__FUNCTION__<<"no of dissecto is"<<std::endl;
        // exit(0);
        //	std::size_t size =sizeof( reffer ) / sizeof( field_info );
        for ( int i=0 ; i<132 ; ++ i ){ // no of dissector given hardcoded // 132 if no. of field for mysql
            dissectors["fieldName"]= i;
            dissectorsArray.append(dissectors);
        //	dissectors["abbreviated name"]=reffer[ i ].;
            dissectorsArray.append(dissectors);
        }
        protocols ["ProtocolS"][ static_cast<std::ostringstream*>( &(std::ostringstream() << ( *protoMapIterator).first) )->str() ]["Dissector"]=dissectorsArray;
        protocolFile<<protocols<<std::endl;
    }
    //  protocolFile<<protocols<<std::endl;
    return true;
}

