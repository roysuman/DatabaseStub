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

#include "../../TCPSTUB/mainwindow.h"
#include"../../STRUCTURE/rawdata_structure.hpp"
#include "../../DBLAYER/dummy_server_db.hpp"
#include"../SUPPORT/DISSECTOR/proto_mysql.hpp"
namespace server{

    //a structure to contain current converastion chunk packets
    extern actSeriesStruct *currentConversationChunk;
    extern  pthread_t thread;
    extern int serverSockFd , clientSockFd;
    extern void * playWithData ( void *);
    class DummyServer{
        public:
        DummyServer();
        ~DummyServer();
        int createServer( std::string , int  );
        bool stopServer ( std::string , int );
       // int acceptClient ( int );
         static void * acceptClient( void *  );
         bool actWithData( void  );

    };
}


#endif

