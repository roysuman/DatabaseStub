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
 *   Organization:  Cognizant Technological solutions
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
#include "../../STRUCTURE/sumanGtkmm.hpp"
#include "../../STRUCTURE/rawdata_structure.hpp"
#include<stdlib.h>
#include <fstream>

#include "jsoncpp/json.h"
#include "jsoncpp/writer.h"


#include "types.hpp"
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
         const char *name;           // name of this field
         enum types::ftenum type;           //field type, one of FT_ (from ftypes.h)
         int display;        // one of BASE_, or field bit-width if FT_BOOLEAN and non-zero bitmask
        };
     //another structure that will contains a int part for indexinng and referrenc of field_info structure
     typedef struct _packetFieldInfo packetInfo;
     struct _packetFieldInfo{
         int *index;
        fieldInfo hfInfo;
        };
     //one structure that will hold two function pointer 1. dissector 2. genr..
     typedef struct _fpStruct fpStruct;
     struct _fpStruct{
         boost::any functionToInnitiateDissecton;
         boost::any functionToGetClientRequest;
         int noDissecto;

         };
     //pair for holding two different structure
     typedef std::pair < fpStruct * , fieldInfo* > mapkey;
     //this unordered_map/ hash contains portno and mapkey values
     typedef std::unordered_map < gint , mapkey > _protoMap;
     extern _protoMap protoMap; // only one global variable for entire project.
	 class Proto{
		 public:
			 Proto(){}
			 ~Proto(){}
			 //this functionn will be called from sniffing code to initialize dissection
			 static returnType initDissect( int  , int );
			 //function to register a protocol/port no  bool ( *)( void )
             static bool registerProto( int , fpStruct * , int );
			 //function to insert disector elements/variables/datatypes information in to the structure field_info
			 static bool insertDissectorProto( int , int , packetInfo * );
			 //print the dat of field info of a protocol being registered
			 static void printRegistrationData ( fieldInfo );
			 //method to print all registered protocols in theprotocol file
			 static bool logProtocols( );
        };
	 
 }

#endif
