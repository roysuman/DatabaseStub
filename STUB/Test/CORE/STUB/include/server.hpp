#ifndef SERVER_HPP
#define SERVER_HPP
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<fstream>
#include <boost/thread.hpp>
//#include <boost/thread/future.hpp>
#include "../../../TCPSTUB/mainwindow.h"
#include "../STRUCTURE/include/rawdata_structure.hpp"
#include "../DBLAYER/dummy_server_db.hpp"
#include"../CORE/DISSECTOR/include/proto_mysql.hpp"
#include "../../../SUPPORT/globalDatatypes.hpp"
namespace server{

    //a structure to contain current converastion chunk packets
    extern actSeriesStruct *currentConversationChunk;
    extern  pthread_t thread;
    extern STUB_INT serverSockFd , clientSockFd;
    extern STUB_INT globalDynamicInt;
    class DummyServer{
        public:
        DummyServer();
        ~DummyServer();
	STUB_INT dynamicValueGlobal; //statement id for mysql
        STUB_INT createServer( std::string , STUB_INT  );
        bool stopServer ( std::string , STUB_INT );
	static void acceptClient(  );
	bool actWithData( void  );
	
    };
}


#endif

