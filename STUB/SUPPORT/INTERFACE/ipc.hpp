/*
 * =====================================================================================
 *
 *       Filename:  ipc.hpp
 *
 *    Description:  this is for inter process communication, packets those are geting captured by sniffing.cpp need to be processed by capture_packet_db.cpp
 *    if these two tasks happen sequentially, packet loss may happen. Thus the concept of shared memory, it is a structure pool of circular queue.
 *    front to insert data and rar to get data one by one.
 *
 *        Version:  1.0
 *        Created:  Friday 21 March 2014 12:06:16  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy (), 
 *   Organization:  Cognizant Technological solutions
 *
 * =====================================================================================
 */

#ifndef IPC_HPP_
#define IPC_HPP_
#include "iostream"
#include <queue>
#include "../../STRUCTURE/rawdata_structure.hpp"
namespace ipc{
       extern std::queue < rawDataStruct * > rawDataQueue;
	  
	
	class IpcQueue{
		private:
                        int queueSize;
		public:
                        IpcQueue( );
			~IpcQueue();
			rawDataStruct * getData();
			bool insertData( rawDataStruct * );		
	};
     extern IpcQueue *ipcQueueInstance;


}



#endif

