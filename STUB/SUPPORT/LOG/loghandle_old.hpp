#ifndef LOGHANDLE_HPP_
#define LOGHANDLE_HPP_

#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <execinfo.h>
#include <cxxabi.h>
#include <assert.h>
#include<sstream>
#include <signal.h>
using namespace std;
 std::string getTime();
/*
class Loghandler
{
    private:

    public:
        static   std::fstream logfile;
            Loghandler();
            ~Loghandler();
        static bool openFile();
        static bool closeFile();

            static bool writeLog(std::string );
            static bool writeLog(int );
            static bool writeLog(double );
        static bool writeLog ( float );
};
class ErrorLog{
    public:
        static std::fstream errorLog;
        ErrorLog();
        ~ErrorLog();
        static bool openFile();
        static bool closeFile();
        static bool writeLog( std::string );
        static bool writeLog( int  );
        static bool writeLog ( double  );
        static bool writeLog ( float );
};
*/
class StackTrace{
public:
	static unsigned int maxFrame;
    StackTrace();
    ~StackTrace();
	static std::fstream stackTrace;
	static bool openFile();
	static bool closeFile();
        static void printStackTrace( );
        static void printStackTrace( int );

};


class AddTimeStamp : public std::streambuf
{
public:
    AddTimeStamp( std::basic_ios< char >& out )
        : out_( out )
        , sink_()
        , newline_( true )
    {
        sink_ = out_.rdbuf( this );
        assert( sink_ );
    }
    ~AddTimeStamp()
    {
        out_.rdbuf( sink_ );
    }
protected:
    int_type overflow( int_type m = traits_type::eof() )
    {
        if( traits_type::eq_int_type( m, traits_type::eof() ) )
            return sink_->sputc( m );
        if( newline_ )
        {   // --   add timestamp here
            std::stringstream buf;
            buf << getTime(); // add perhaps a seperator " "
            if( !(buf >> sink_) )
                return traits_type::eof(); // Error
        }
        const char_type c = traits_type::to_char_type( m );
        newline_ = traits_type::to_char_type( m ) == '\n';
        return sink_->sputc( m );
    }
private:
    AddTimeStamp( const AddTimeStamp& );
    AddTimeStamp& operator=( const AddTimeStamp& ); // not copyable
    // --   Members
    std::basic_ios< char >& out_;
    std::streambuf* sink_;
    bool newline_;
};
extern std::ofstream out;

class TraceLog {
    public:
         TraceLog(){}
        ~TraceLog(){}
		static bool activateTraceLog( bool  ); 
};


    //AddTimeStamp ats( cout ); // timestamp is active
#endif
