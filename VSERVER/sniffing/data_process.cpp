/*
 * =====================================================================================
 *
 *       Filename:  dat_process.cpp
 *
 *    Description:  process the tcp_dump data
 *
 *        Version:  1.0
 *        Created:  Saturday 10 October 2015 08:20:28  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  ROY (), email.suman.roy@gmail.com
 *   Organization:  NA
 *
 * =====================================================================================
 */

#include "data_process.h"


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  start_process_dump_file
 *  Description:  process the tcp dump file
 *              @@file_name: the fullpath of the file
 *              Return: -1 ==> environment not ready
 *                      0 ==> failed on processing
 *                      >0  ==> No of packet processed
 * =====================================================================================
 */
const VS_INT32
ProcessData::start_processing_dump_file( std::string const file_name,
		                      std::string const ip_address,
				      VS_UINT32    const port){
	VS_INT32    return_val;
#ifdef DEBUG
	std::cout<<PRINT<<"Process file name [ "<<file_name<<" ]\n";
#endif
	/* check whether the class Buffer,GroupPacket and Snif created successfully or not  */
	if ( !is_init ){
		return_val = -1; 
	}else{
		/* if port is not 0 then set the filter */
		if ( port !=0 ){
			snif->set_filter( file_name , ip_address , port );
		}
		/* ceate a pthread for sniffing and call analysis_from_file */

		pthread_create(&file_process_thread , nullptr , &Snif::analysis_from_file,(VS_VOID*)snif);
		/* create a pthread and call start_grouping */
		pthread_create(&group_packet_thread,nullptr,&GroupPacket::start_grouping,(VS_VOID*)grp_pack);
		/* wait for thread joining */

		pthread_join ( file_process_thread, NULL );
		pthread_join( group_packet_thread , NULL );
		return_val = 1;//FIXME return no of processed packets.
	}
	
	return return_val;
}
