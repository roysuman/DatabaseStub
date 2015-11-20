/*
 * =====================================================================================
 *
 *       Filename:  proto.hpp
 *
 *    Description:  This header file contains all structures required to store store
 *    		   informatiopn about the protocols.
 *
 *        Version:  1.0
 *        Created:  Thursday 19 September 2013 12:38:12  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy (), 
 *   Organization:  SELF
 *
 * =====================================================================================
 */

#ifndef PROTO_HPP_
#define PROTO_HPP_

//header files
#include<iostream>
#include<unordered_map>
#include <boost/any.hpp>
#include <boost/variant.hpp>
#include "types.hpp"
#include "../STRUCTURE/include/globalDatatypes.hpp"
#include "../STRUCTURE/include/rawdata_structure.hpp"
#include<stdlib.h>
#include <fstream>

#include "jsoncpp/json.h"
#include "jsoncpp/writer.h"
#include <map>

#include "types.hpp"
#include "../../../SUPPORT/globalDatatypes.hpp"
//#include "proto_mysql.hpp"
#define ENC_NA 0
#define ENC_LITTLE_INDIAN 1

//for storing information regarding protocol--example mysql protocol
//thanks wireshark for their open source code.
 namespace proto{
      // information describing a header field
     typedef struct _fieldInfo fieldInfo;
     // information describing a header field
     struct _fieldInfo {
         const STUB_CHAR *name;           // name of this field
         enum types::ftenum type;           //field type, one of FT_ (from ftypes.h)
         STUB_INT display;        // one of BASE_, or field bit-width if FT_BOOLEAN and non-zero bitmask
        };
     //another structure that will contains a STUB_INT part for indexinng and referrenc of field_info structure
     typedef struct _packetFieldInfo packetInfo;
     struct _packetFieldInfo{
         STUB_INT *index;
        fieldInfo hfInfo;
        };
     //one structure that will hold two function poSTUB_INTer 1. dissector 2. genr..
     typedef struct _fpStruct fpStruct;
     struct _fpStruct{
         boost::any functionToInnitiateDissecton;
         boost::any functionToGetClientRequest;
         STUB_INT noDissecto;

         };
     //pair for holding two different structure
     typedef std::pair < fpStruct * , fieldInfo* > mapkey;
     //this unordered_map/ hash contains portno and mapkey values
     typedef std::unordered_map < std::string , mapkey > _protoMap;
     typedef std::map < STUB_INT , std::string  > _ports;
     extern _ports ports;

     extern _protoMap protoMap; // only one global variable for entire project.
	 class Proto{
		 public:
			 Proto(){}
			 ~Proto(){}
			 //this functionn will be called from sniffing code to initialize dissection
			 static returnType initDissect( std::string  , STUB_INT );

			 //function to register a protocol/port no  bool ( *)( void )
			 static bool registerProto( std::string , fpStruct * , STUB_INT );
			 //function to insert disector elements/variables/datatypes 
			 //information in to the structure field_info
			 static bool insertDissectorProto( std::string , STUB_INT , packetInfo * );
			 //print the dat of field info of a protocol being registered
			 static void printRegistrationData ( fieldInfo );
			 //method to print all registered protocols in theprotocol file
			 static bool logProtocols( );
        };
	 
 }

#endif
