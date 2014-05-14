/*
 * =====================================================================================
 *
 *       Filename:  ipc.cpp
 *
 *    Description:  implementation of ipc.hpp
 *
 *        Version:  1.0
 *        Created:  Friday 21 March 2014 12:15:39  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy (), 
 *   Organization:  Cognizant Technological solutions
 *
 * =====================================================================================
 */

#include "ipc.hpp"
using namespace ipc;
std::queue < rawDataStruct * > ipc::rawDataQueue;

IpcQueue::IpcQueue ( ){
//	queueSize = size;


}

IpcQueue::~IpcQueue(){

}

rawDataStruct * IpcQueue::getData( ){
        if (!rawDataQueue.empty()){
                rawDataStruct *tempPointer = rawDataQueue.front();
		rawDataQueue.pop();
		return tempPointer;

	}else return NULL;
}
bool IpcQueue::insertData ( rawDataStruct *rawData ){
	rawDataQueue.push ( rawData );
	return true;
}

IpcQueue *ipcQueueInstance;
