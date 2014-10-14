/*me:  loghandle.cpp
 *
 *    Description:  this code to create a log file for TCP stub.
 *
 *        Version:  1.0
 *        Created:  01/06/2014 03:06:04 PM
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  SUMAN ROY (), email.suman.roy@gmail.com
 *   Organization:  SELF
 *
 * =====================================================================================
 */
#include "../include/loghandle.hpp"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  getTime
 *  Description:  get the current system time
 * =====================================================================================
 */
 std::string getTime(){


	 time_t         t;
	 struct tm      *now;
	 std::string    timeString;

     try{
         t  = time(0);   // get time now
         now = localtime( & t );
         timeString = timeString + static_cast<std::ostringstream*>(
			 &(std::ostringstream() << now->tm_year + 1900) )->str()+
		 "-"+ static_cast<std::ostringstream*>( &(std::ostringstream() 
					 << now->tm_mon + 1 ) )->str() +
		 "-"+static_cast<std::ostringstream*>( &(std::ostringstream() 
					 << now->tm_mday ) )->str()+" "+
		 static_cast<std::ostringstream*>( &(std::ostringstream() 
					 << now->tm_hour) )->str()+":"+
		 static_cast<std::ostringstream*>( &(std::ostringstream() 
					 << now->tm_min ) )->str()+":"+
		 static_cast<std::ostringstream*>( &(std::ostringstream() 
					 << now->tm_sec ) )->str() ;
     }
     catch ( std::exception &e ){
         std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		 <<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"
		 <<"exception"<<e.what()<<'\n';
     }
    return timeString;


}
//#################Stack Trace class##############################################

StackTrace::StackTrace(){}
StackTrace::~StackTrace(){}
STUB_UINT StackTrace::maxFrame = 64;

void StackTrace::printStackTrace( STUB_INT sigNum ){

    switch ( sigNum ) {
            case SIGABRT: case SIGTERM:
                        std::cout<<" File Name ["<<__FILE__<<" ] Function [ "
				<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["
				<<__DATE__<<"_"<<__TIME__<<"]"<<"Got signal SIGABRT/SIGTERM\n"
				<<"The SIGABRT signal is sent to a process to tell it to ab\
				ort, i.e. to terminate. The signal is usually initiated by t\
				he process itself when it calls abort function of the C Stand\
				ard Library, but it can be sent to the process from outside as\
			       	well as any other signal.\n";
                        break;

	    case SIGILL:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
				<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
				<<__TIME__<<"]"<<"got signal SIGILL\n"
				<<"The SIGILL signal is sent to a process when it attempts \
				to execute an illegal, malformed, unknown, or pri\
				vileged instruction.\n";
			break;
			
            case SIGSEGV:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
				<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
				<<__TIME__<<"]"<<"Got signal SIGSEGV\n"
				<<"The SIGSEGV signal is sent to a process when it makes \
				an invalid virtual memory reference, or segmentation fault,\
			       	i.e. when it performs a segmentation violation.";
			break;

			
	    case SIGURG:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
				<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
				<<__TIME__<<"]"<<"Got signal SIGURG\n"
				<<"The SIGURG signal is sent to a process when a socket ha\
				s urgent or out-of-band data available to read.\n";
			break;
			
	    case SIGUSR1: case SIGUSR2:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
				<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
				<<__TIME__<<"]"<<"Got signal SIGUSR1/SIGUSR2\n"
				<<"User-defined signal 1/2.\n";
			break;
			
	    default:
			std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
				<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
				<<__TIME__<<"]"<<"default signal\n";
			break;
            }

    StackTrace::printStackTrace();
}

void StackTrace::printStackTrace( ){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"stack Trace\n";
	
	STUB_CHAR    *ret;
	STUB_INT     status;
	STUB_INT     addrlen;
	STUB_CHAR    *funcname;
	STUB_CHAR    *end_offset;
	STUB_CHAR    *begin_name;
	STUB_CHAR    **symbollist;
	size_t       funcnamesize;
	STUB_CHAR    *begin_offset;
	void         *addrlist[maxFrame+1]; // storage array for stack trace address data

	begin_name = 0 ;
	begin_offset = 0;
	end_offset = 0;
	
	std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
	    <<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"stachTrace\n";

	// retrieve cturrent stack addresses
	addrlen = backtrace(addrlist, sizeof(addrlist) / sizeof(void*));
	if (addrlen == 0) {
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"]"<<"  <empty, possibly corrupt>\n";
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"]"<<" <empty, possibly corrupt\n";

		
	}
	// resolve addresses into strings containing "filename(function+address)",
	// this array must be free()-ed
	symbollist = backtrace_symbols(addrlist, addrlen);
	// allocate string which will be filled with the demangled function name
	funcnamesize = 256;
	funcname = (STUB_CHAR*)malloc(funcnamesize);
	// iterate over the returned symbol lines. skip the first, it is the
	// address of this function.
	for (STUB_INT i = 1; i < addrlen; i++){
		// find parentheses and +address offset surrounding the mangled name:
		// ./module(function+0x15c) [0x8048a6d]
		for (STUB_CHAR *p = symbollist[i]; *p; ++p){
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
			ret =abi::__cxa_demangle(begin_name, funcname, 
					&funcnamesize, &status);
			if (status == 0) {
				funcname = ret; // use possibly realloc()-ed string
                //fprintf(out, "  %s : %s+%s\n",
                    //	symbollist[i], funcname, begin_offset);
                std::cerr<<symbollist[ i ]<<funcname<<begin_offset<<std::endl;
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__
			<<"_"<<__TIME__<<"]"<<symbollist[ i ] 
			<< funcname << begin_offset<<std::endl;
            }else{

            //fprintf(out, "  %s\n", symbollist[i]);
                std::cerr<<symbollist[ i ]<<std::endl;
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__
			<<"_"<<__TIME__<<"]"<<symbollist [ i ]<<std::endl;
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

	std::string        logFile;
//	std::streambuf    *countbuf;
	std::string       errorLogFile;
	std::string       traceFileName;

	if ( configTcpFile.traceLog ){
		try{
			traceFileName = "../LOG/stdout"+getTime()+".log";
			traceLogHandler.open(traceFileName.c_str() );
//			countbuf = std::cout.rdbuf();
			std::cout.rdbuf ( traceLogHandler.rdbuf() ) ;
			AddTimeStamp ats( cout );

			
		}
		catch ( std::exception &e ){
			std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
				<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
				<<__TIME__<<"]"<<"exception caight\n";
			return false;
		}

    }else{
           std::cout.setstate(std::ios::failbit) ;
    }
    AddTimeStamp ats( cout );

    if( configTcpFile.errorLog ){


		try{
			errorLogFile = "../LOG/stdcerr"+getTime()+".log";
			errorLogHandler.open ( errorLogFile.c_str() );
//			countbuf = std::cerr.rdbuf();
			std::cerr.rdbuf( errorLogHandler.rdbuf () );
			AddTimeStamp ats2( cerr );
			
		}
		catch( std::exception &e ){
			std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
				<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
				<<__TIME__<<"]"<<"exception caught\n";
		}
	}
    else{

               std::cerr.setstate(std::ios::failbit) ;
        }

	if ( configTcpFile.log ){
		try{
            logFile = "../LOG/Tcp-stub-"+getTime() +".log";
            logHandler.open( logFile.c_str(), std::ios::out );
            logHandler<<"not activated this....\n";

		}
		catch ( std::exception &e ){
			std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
				<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
				<<__TIME__<<"]"<<"exception caught"<<e.what()<<std::endl;
		}
	}
return true;

}
