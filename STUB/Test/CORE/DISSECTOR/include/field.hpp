/*
 * =====================================================================================
 *
 *       Filename:  field.hpp
 *
 *    Description:  this contains field info regarding to dassect packet that requires for future use.
 *
 *        Version:  1.0
 *        Created:  Tuesday 24 September 2013 03:09:40  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy (), 
 *   Organization:  SELF
 *
 * =====================================================================================
 */

#ifndef FIELD_HPP
#define FIELD_HPP
#include "../STRUCTURE/include/globalDatatypes.hpp"
#include "../../../SUPPORT/globalDatatypes.hpp"

//have to dete this... too many struct for the same info
namespace field{
	//all are needed for dissecting.
	//one structure for holding source and destination port
	typedef struct _ipHeader ipHeader;
	struct _ipHeader{
		STUB_INT sourcePort ;
		STUB_INT destiPort;
		STUB_UINT32 packetLength ;
		STUB_UINT32 packetNumber;
	};
	extern ipHeader ipInfo;
	//for storing prev field info
	typedef struct _prevQueryType prevQueryType ;
	struct _prevQueryType{
		STUB_INT prevQueryState;
	};
	extern prevQueryType prevQuery;
}

#endif

