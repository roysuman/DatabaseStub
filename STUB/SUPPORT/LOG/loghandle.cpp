/*me:  loghandle.cpp
 *
 *    Description:  this code to create a log file for TCP stub.
 *
 *        Version:  1.0
 *        Created:  01/06/2014 03:06:04 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  SUMAN ROY (), suman.roy@cognizant.com
 *   Organization:  COGNIZANT TECHNOLOGICAL SOLUTIONS
 *
 * =====================================================================================
 */
#include "loghandle.hpp"
 std::string getTime(){
     std::string timeString;
     try{
         time_t t = time(0);   // get time now
         struct tm *now = localtime( & t );
         timeString = timeString + static_cast<std::ostringstream*>( &(std::ostringstream() << now->tm_year + 1900) )->str()+"-"+ static_cast<std::ostringstream*>( &(std::ostringstream() << now->tm_mon + 1 ) )->str() +"-"+static_cast<std::ostringstream*>( &(std::ostringstream() << now->tm_mday ) )->str()+" "+static_cast<std::ostringstream*>( &(std::ostringstream() << now->tm_hour) )->str()+":"+static_cast<std::ostringstream*>( &(std::ostringstream() << now->tm_min ) )->str()+":"+static_cast<std::ostringstream*>( &(std::ostringstream() << now->tm_sec ) )->str() ;
     }
     catch ( std::exception &e ){
         std::cerr<<"exception cgt\n";
     }
    return timeString;


}
//#################Stack Trace class##############################################

StackTrace::StackTrace(){}
StackTrace::~StackTrace(){}
unsigned int StackTrace::maxFrame = 64;
void StackTrace::printStackTrace( int sigNum ){
    switch ( sigNum ) {
            case SIGABRT: case SIGTERM:
                        std::cout<<"Got signal SIGABRT/SIGTERM\n"
				<<"The SIGABRT signal is sent to a process to tell it to abort, i.e. to terminate. The signal is usually initiated by the process itself when it calls abort function of the C Standard Library, but it can be sent to the process from outside as well as any other signal.\n";
                        break;

	    case SIGILL:
			std::cout<<"got signal SIGILL\n"
				<<"The SIGILL signal is sent to a process when it attempts to execute an illegal, malformed, unknown, or privileged instruction.\n";
			break;
			
            case SIGSEGV:
			std::cout<<"Got signal SIGSEGV\n"
				<<"The SIGSEGV signal is sent to a process when it makes an invalid virtual memory reference, or segmentation fault, i.e. when it performs a segmentation violation.";
			break;

			
	    case SIGURG:
			std::cout<<"Got signal SIGURG\n"
				<<"The SIGURG signal is sent to a process when a socket has urgent or out-of-band data available to read.\n";
			break;
			
	    case SIGUSR1: case SIGUSR2:
			std::cout<<"Got signal SIGUSR1/SIGUSR2\n"
				<<"User-defined signal 1/2.\n";
			break;
			
	    default:
			std::cout<<"default signal\n";
			break;
            }

    StackTrace::printStackTrace();
}

void StackTrace::printStackTrace( ){
	std::cout<<"stack Trace\n";
    std::cerr<<"stachTrace\n";
	// storage array for stack trace address data
    void* addrlist[maxFrame+1];

	// retrieve current stack addresses
	int addrlen = backtrace(addrlist, sizeof(addrlist) / sizeof(void*));
	if (addrlen == 0) {
		std::cerr<<"  <empty, possibly corrupt>\n";
		std::cout<<" <empty, possibly corrupt\n";

		
	}
	// resolve addresses into strings containing "filename(function+address)",
	// this array must be free()-ed
	char** symbollist = backtrace_symbols(addrlist, addrlen);
	// allocate string which will be filled with the demangled function name
	size_t funcnamesize = 256;
	char* funcname = (char*)malloc(funcnamesize);
	// iterate over the returned symbol lines. skip the first, it is the
	// address of this function.
	for (int i = 1; i < addrlen; i++){
		char *begin_name = 0, *begin_offset = 0, *end_offset = 0;
		// find parentheses and +address offset surrounding the mangled name:
		// ./module(function+0x15c) [0x8048a6d]
		for (char *p = symbollist[i]; *p; ++p){
			if (*p == '(')
				begin_name = p;
			else if (*p == '+')
				begin_offset = p;
			else if (*p == ')' && begin_offset) {
				end_offset = p;
				break;
				
			}
		}
		if (begin_name && begin_offset && end_offset
				&& begin_name < begin_offset){
			*begin_name++ = '\0';
			*begin_offset++ = '\0';
			*end_offset = '\0';
			// mangled name is now in [begin_name, begin_offset) and caller
			// offset in [begin_offset, end_offset). now apply
			// __cxa_demangle():
			int status;
                        char* ret =abi::__cxa_demangle(begin_name, funcname, &funcnamesize, &status);
			if (status == 0) {
				funcname = ret; // use possibly realloc()-ed string
                //fprintf(out, "  %s : %s+%s\n",
                    //	symbollist[i], funcname, begin_offset);
                std::cerr<<symbollist[ i ]<<funcname<<begin_offset<<std::endl;
		std::cout<<symbollist[ i ] << funcname << begin_offset<<std::endl;
            }else{

            //fprintf(out, "  %s\n", symbollist[i]);
                std::cerr<<symbollist[ i ]<<std::endl;
		std::cout<<symbollist [ i ]<<std::endl;
            }
		}
	}
	free(funcname);
	free(symbollist);
        exit ( 0);
	

}

//class Log

std::ofstream errorLogHandler;
std::ofstream logHandler;
std::ofstream traceLogHandler;
bool Log::activateLog(){

	if ( configTcpFile.traceLog ){
		try{
                        std::string traceFileName = "../LOG/stdout"+getTime()+".log";
            traceLogHandler.open(traceFileName.c_str() );
            std::streambuf *countbuf = std::cout.rdbuf();
            std::cout.rdbuf ( traceLogHandler.rdbuf() ) ;
			AddTimeStamp ats( cout );

			
		}
		catch ( std::exception &e ){
			std::cerr<<"exception caight\n";
			return false;
		}

    }else{
           std::cout.setstate(std::ios::failbit) ;
    }
    AddTimeStamp ats( cout );

    if( configTcpFile.errorLog ){


		try{
            std::string errorLogFile = "../LOG/stdcerr"+getTime()+".log";
            errorLogHandler.open ( errorLogFile.c_str() );
            std::streambuf *countbuf = std::cerr.rdbuf();
            std::cerr.rdbuf( errorLogHandler.rdbuf () );
			AddTimeStamp ats2( cerr );
			
		}
		catch( std::exception &e ){
			std::cout<<"exception caught\n";
			std::cerr<<"exception caught\n";
		}
	}
    else{

               std::cerr.setstate(std::ios::failbit) ;
        }

	if ( configTcpFile.log ){
		try{
            std::string logFile = "../LOG/Tcp-stub-"+getTime() +".log";
            logHandler.open( logFile.c_str(), std::ios::out );
            logHandler<<"not activated this....\n";

		}
		catch ( std::exception &e ){
			std::cerr<<"exception caught"<<e.what()<<std::endl;
		}
	}
return true;

}
