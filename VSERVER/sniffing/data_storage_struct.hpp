/*
 * =====================================================================================
 *
 *       Filename:  data_storage_struct.h
 *
 *    Description:  structure to transfer data between different method
 *
 *        Version:  1.0
 *        Created:  Sunday 11 October 2015 07:23:28  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  ROY (), email.suman.roy@gmail.com
 *   Organization:  NA
 *
 * =====================================================================================
 */
#ifndef DATA_STORAGE_STRUCT_H
#define DATA_STORAGE_STRUCT_H
#include "../common/vserver_datatype.h"
/*-----------------------------------------------------------------------------
 *  structure to hold information of a querry_string along with querry type
 *  this structure is required to get the dissected querry information from 
 *  discetors.
 *-----------------------------------------------------------------------------*/
typedef struct _query_data_info query_data_info;

struct _query_data_info {
	VS_INT32 packet_seq_no;           /* unque sequence number of packet */
	std::string query_type;      /* type of the querry..if needed to define */
	std::string query_string;    /* disected querry string */
};

/*-----------------------------------------------------------------------------
 *  structure to hold the non-disected query. This structure is helpful to 
 *  send the non-disected data to the disector. We can use the huge structure 
 *  that has been used for sniffing and grouping packet. 
 *FIXME : which struct to use..need to think
 *-----------------------------------------------------------------------------*/
typedef struct raw_data_struct_ raw_data_struct;

struct raw_data_struct_{
	bool application_or_server ; /* to differentiate between application or server packet */
	VS_UINT64 packet_seq_number;    /*unique sequence number of packet */
	VS_UINT8 *data;         /* raw packet data */
	VS_UINT64  length ;             /* length of the data */
};

#endif
