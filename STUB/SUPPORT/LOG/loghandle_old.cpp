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
/*
std::fstream Loghandler::logfile;
Loghandler::Loghandler(){}
Loghandler::~Loghandler()
{
    logfile.close();
}

 bool Loghandler::openFile ( ){
    std::string fileName = "stdcout"+getTime()+".log";
    try{
        logfile.open ( fileName.c_str() , std::ios::out);
    }
    catch ( std::exception &e){
        std::cerr<<"exception caught"<<e.what()<<std::endl;
        return false;
    }
       if ( !logfile.is_open() ){
           std::cerr<<"can't open log file\n";
           return false;
       }
       return true;
}
bool Loghandler::closeFile(){
    try{
        logfile.close();
        return true;
    }
    catch ( std::exception &e ){
        std::cerr<<"exception caught"<<e.what()<<std::endl;
        return false;
    }


}
 bool Loghandler::writeLog ( std::string s){
     try{
         logfile <<getTime()<<"-"<< s<< std::endl;
     }
     catch ( std::exception &e ){
         std::cerr<<"exception caught"<<e.what()<<std::endl;
         return false;
     }
     return true;

}

bool Loghandler::writeLog( int n){
    try{
        logfile<<getTime()<<"-"<<  n << std::endl;
    }
    catch ( std::exception &e){
        std::cout<<"exception caught"<<e.what()<<std::endl;
        return false;
    }
    return true;

}

bool  Loghandler::writeLog( double d){
     try{
         logfile <<getTime()<<"-" << d << std::endl;
     }
     catch( std::exception &e){
         std::cerr<<"exception caught"<<e.what()<<std::endl;
         return false;
     }
     return true;
}

// #################################################################################### FOR Error Log  ###############################
//########################################################
std::fstream ErrorLog::errorLog;

ErrorLog::ErrorLog(){}
ErrorLog::~ErrorLog(){}

bool ErrorLog::openFile(){

    std::string fileName = "stdcerr"+getTime()+".log";
    try{
        errorLog.open ( fileName.c_str() , std::ios::out);
    }
    catch ( std::exception &e ){
        std::cerr<<"exception caught"<<e.what()<<std::endl;
        return false;
    }
    if ( !errorLog.is_open() ){
        std::cerr<<"can't open log file\n";
        return false;

    }
    return true;
}
bool ErrorLog::closeFile(){
    errorLog.close();
    return true;
}

bool ErrorLog::writeLog( std::string string ){
    try{
        errorLog<<getTime()<<"-"<<string<<std::endl;
    }
    catch( std::exception &e){
        std::cerr<<"exception caught"<<e.what();
        return false;
    }

    return true;
}
bool ErrorLog::writeLog ( int integer ){
    try{
        errorLog<<getTime()<<"-"<<integer<<std::endl;
    }
    catch ( std::exception &e ){
        std::cerr<<"exception caught\n";
        return false;
    }
    return true;
}
bool ErrorLog::writeLog ( double doubleValue ){
    try{
        errorLog<<getTime()<<"-"<<doubleValue<<std::endl;
    }
    catch ( std::exception &e ){
        std::cerr<<"exception caught"<<e.what()<<std::endl;
        return false;
    }
    return true;

}


bool ErrorLog::writeLog( float floatNumber ){
    try{
        errorLog<<getTime()<<"-"<<floatNumber<<std::endl;
    }
    catch ( std::exception &e){
        e.what();
        return false;
    }
    return true;
} */
//
//#################Stack Trace class##############################################

StackTrace::StackTrace(){}
StackTrace::~StackTrace(){}
std::fstream StackTrace::stackTrace;
bool StackTrace::openFile(){
	try{
		std::string traceLog="stackTrace"+getTime()+".log";
		stackTrace.open(traceLog.c_str(), std::ios::out );
		if ( !stackTrace.is_open() ){
			std::cerr<<"cant open Stack Trace Log\n";
			return false;
		}
	}
    catch ( std::exception &e ){
        std::cerr<<"exception caught\n"<<e.what();
		return false;
	}
	return true;
}

bool StackTrace::closeFile(){
	try{
		stackTrace.close();
	}
	catch ( std::exception &e ){
		std::cerr<<"exception caught\n";
		return false;
	}
	return true;
}
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
    //open file for stack trace
    StackTrace::openFile();
	stackTrace<<"stack Trace\n";
	// storage array for stack trace address data
    void* addrlist[maxFrame+1];

	// retrieve current stack addresses
	int addrlen = backtrace(addrlist, sizeof(addrlist) / sizeof(void*));
	if (addrlen == 0) {
		stackTrace<<"  <empty, possibly corrupt>\n";
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
                stackTrace<<symbollist[ i ]<<funcname<<begin_offset<<std::endl;
		std::cout<<symbollist[ i ] << funcname << begin_offset<<std::endl;
            }else{

            //fprintf(out, "  %s\n", symbollist[i]);
                stackTrace<<symbollist[ i ]<<std::endl;
		std::cout<<symbollist [ i ]<<std::endl;
            }
		}
	}
	free(funcname);
	free(symbollist);
        StackTrace::closeFile();
	out.close();
        exit ( 0);
	

}

/*########################## TRACE LOG#####################################*/
std::ofstream out;

bool TraceLog::activateTraceLog( bool isActive ){
	if ( isActive ){
        try{

            std::string traceFileName = "traceLog"+getTime()+".log";
            out.open(traceFileName.c_str() );
            std::streambuf *countbuf = std::cout.rdbuf();
            std::cout.rdbuf ( out.rdbuf() ) ;
            AddTimeStamp ats( cout );

            std::cout<<"buffer pointed\n";
                }
		catch ( std::exception &e ){
			std::cerr<<"exception caight\n";
			return false;
		}
		return true;

	}
	else{ //have to do some logic thus std::cout<<"print data\n" won;t print any thing to standard output.
    }
}


//int main(){
//    Loghandler::openFile();
//    Loghandler::writeLog(123);
////	Loghandler::writeLog("this is stdcout log");
//    Loghandler::closeFile();
//    ErrorLog::openFile();
//    ErrorLog::writeLog("this is error log");
//    return 0;

//}


