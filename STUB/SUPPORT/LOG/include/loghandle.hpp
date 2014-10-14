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
#include "../STRUCTURE/include/configStruct.hpp"
#include "../../globalDatatypes.hpp"
using namespace std;
 std::string getTime();
class StackTrace{
public:
    static STUB_UINT  maxFrame;
    StackTrace();
    ~StackTrace();
        static void printStackTrace( );
        static void printStackTrace( STUB_INT );

};


class AddTimeStamp : public std::streambuf
{
public:
    AddTimeStamp( std::basic_ios< STUB_CHAR >& out )
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
       // const STUB_CHAR_type c =
        traits_type::to_char_type( m );
        newline_ = traits_type::to_char_type( m ) == '\n';
        return sink_->sputc( m );
    }
private:
    AddTimeStamp( const AddTimeStamp& );
    AddTimeStamp& operator=( const AddTimeStamp& ); // not copyable
    // --   Members
    std::basic_ios< STUB_CHAR >& out_;
    std::streambuf* sink_;
    bool newline_;
};

extern std::ofstream traceLogHandler;
extern std::ofstream errorLogHandler;
extern std::ofstream logHandler;
class Log{
	public:
		Log(){}
		~Log(){}

		static bool activateLog();
		
};



    //AddTimeStamp ats( cout ); // timestamp is active
#endif
