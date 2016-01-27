/*
 * =====================================================================================
 *
 *       Filename:  proto.h
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

#ifndef PROTO_H_
#define PROTO_H_

#include<iostream>
#include<unordered_map>
#include <boost/any.hpp>
#include <boost/variant.hpp>
#include<stdlib.h>
#include <fstream>
#include <map>

#include "types.h"

#define ENC_NA 0
#define ENC_LITTLE_INDIAN 1

/* Structure to hold the field information of each protocol*/

typedef struct _field_info_str field_info_str;

struct _field_info_str {
	VS_UINT8 const    field_name; /* name of thefield */
	enum ftenum       type;       /* field data tyypes.. header types.h */
	VS_INT32          display;    /* bitmask */  
};

/* structure for indexing each field info */
//FIXME Am I important?
//
typedef struct _field_info_map_str field_info_map_str;

struct _field_info_map_str{
	VS_ULONG     *index;     /* index in the array */
	field_info_str   f_info; /* field info variable */
};
/* structure to hold function pointer to init the dissection
 * each dissector routuine will register the init functions. */

//TODO think whether to use boost of normal function pointer

typedef struct _disector_fun_pointer_str disector_fun_pointer_str;

struct _disector_fun_pointer_str{
	boost::any fun_ptr_start_disection; /* disect all */
	boost::any fun_ptr_get_query_string; /* disect only incoming querry */
	VS_ULONG noDissecto;                 //FIXME am I importanat?
}

/* std::pir to hold both disector_fun_pointer_str and field_info_str. It's easy to maintain a single variable */

typedef std::pair < disector_fun_pointer_str * , field_info_str* > pair_dis_fun_info;

/* hash map to map protocol name and corresponding helper structure & method..to dissect corresponding protocol packet */

typedef std::unordered_map < std::string , pair_dis_fun_info > _proto_map;

/* iterator for _proto_map */

typedef _proto_map::iterator    proto_map_iterator;

//FIXME the following maping not important.. this time will use Nmae rather than port no.
//
typedef std::map < STUB_INT , std::string  > _ports;

//extern _ports ports;

//------------------------------


class Proto{
	public:
		Proto(){} //FIXME Am I just formality?
		virtual ~Proto(){} //FIXME what to clean ?
	private:
		static 	_proto_map   proto_map; /* to hold all protocol information */
	protected:
		/* register a protocol */
		bool register_protocol( std::string &, disector_fun_pointer_str * , field_info_map_str * , VS_ULONG );
#ifdef DEBUG
		/* helper method..print the values related to a sp
		 * ecific field.. needed during debug */
		void print_field_info_str ( field_info_str );
#endif
		/* get the appropriate disector method */
		return_type get_function_to_disect( std::string const &, VS_INT32 );
		/* dump all registered protocol values into a dump file
		 * helper method in debug mode */
//		VS_BOOL logProtocols( );//FIXME suman you have deleted me.. Are you sure that I have no use?
};

#endif
