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


#include "proto.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  register_protocol
 *  Description:  register all field information and protocol callback 
 *                methods to start dissection.
 *                @@protocol_name: name of the protocol.
 *                @@function_pointer: a structure that contains two callback method.
 *                @@f_info: array of all fields to register for a protocol.
 *                @@total_field_count: count of fields.
 *                @@return: true on success..false on error.
 * =====================================================================================
 */

VS_BOOL
Proto::register_protocol( std::string &protocol_name , 
		          disector_fun_pointer_str *function_pointer , 
			  field_info_str_map_str *f_info,
			  VS_ULONG total_field_count ){

	VS_BOOL          return_val;
	field_info_str   *field_information; 

#ifdef DEBUG
	std::cout<<PRINT<<"Register "<<protocol_name
		<<" with "<<total_field_count<<" no of fields\n";
#endif
	/* check whether protocol already registered or not */

	if ( proto_map.find ( protocol_name ) == proto_map.end() ){
		try{
			field_information = new field_info_str [ total_field_count ];
			/* store each field data */
			for ( VS_ULONG loop = 0; loop < total_field_count ; ++ loop ){
				*( field_information [loop ].index ) = loop;
				field_information [ loop ] = f_info[ loop].f_info;
#ifdef DEBUG
				(void)print_field_info_str( field_information [ loop ];
#endif

			}
			/* make pair of function point struct and field info struct */
			mapkey maping_var ( function_pointer , field_info_strrmation );
			
			if ( ( proto_map.insert( std::make_pair ( protocol_name , maped ) ).second )  ){
				return_val = true;
			}else {
				return_val = true;
			}
		}
		catch( const std::bad_alloc &ba ){
			std::cerr<<PRINT<<"Exception on registering \
				protocol information Error "
				<<ba.what()<<"\n";
			return_val = false;
		}
	}else{
		std::cout<<PRINT<<"Error on registering protocol\
			protocol "<<protocol_name<<" already registered\n";
		return_val = false;
	}
	return return_val;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  prient_field_info_str
 *  Description:  print the registered protocol field informations.
 *                @@field_info_str: structure of a field 
 *                @@return void.
 * =====================================================================================
 */
void
Proto::prient_field_info_str ( field_info_str field_info ){

	std::cout<<PRINT<<"Field Name [ "<<field_info->f_info.field_name
		<<" ] type [ "<<field_info->f_info.type<<" ] \n";
	return;	  

}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  get_function_to_disect
 *  Description:  return the appropriate disector method, depending on port
 *                @@protocol_name: the name of the protocol to dissect
 *                @@choice: there are two types of method recorded, 
 *                          depending on choice return the appropriate
 *                          dissector method.
 *                @@return: return the method to dissect.
 * =====================================================================================
 */
//FIXME return type...if protocol not registered
return_type
Proto::get_function_to_disect( std::string const &protocol_name , 
		               VS_INT32 choice ){

	disector_fun_pointer_str    *function;
	mapkey                      maping_var;
	proto_map_iterator          protomap_itr;

#ifdef 
	std::cout<<PRINT<<"Return disector function for" \
		"protocol [ "<<protocol_name<<" ] \n";
#endif
	/* check protocol registered or not */

	if (  ( protomap_itr = proto_map.find ( protocol_name ) ) == 
			proto_map.end() ){ 
		std::cerr<<PRINT<<"Protocol "<<protocol_name<<" not "\
			"registered\n";
		return false;//FIXME I am returning false.is it ok?
	}
	else{
		maping_var = protomap_itr->second;
		func = maped.first;
		/* depending on choice return the appropriate method */
		if ( choice !=1  ){
			return  func->fun_ptr_start_disection;
		}
		else{
			return func->fun_ptr_get_query_string;
		}
	}
}

