/*
date: 25-april-2014
*/
#include "iostream"
#include <string.h>
#include <stdlib.h>
#include "../../../STRUCTURE/include/globalDatatypes.hpp"
#include"types.hpp"
#include "../../../SUPPORT/globalDatatypes.hpp"
//#define DEBUG "debugon"
namespace ber{
	class Ber{
		private:
//			static STUB_INT8 lastBerClass;
//			static bool lastPrimFlag;
//			static STUB_INT32   lastTag;
		public:
			Ber();
			~Ber();
            static STUB_INT getBerIdentifier( const u_char* , STUB_INT , STUB_INT8 * ,bool * , STUB_INT32 *);
            static STUB_INT getBerLength( const u_char * , STUB_INT  , STUB_INT *);
            static bool readBerInteger( const u_char * , STUB_INT , STUB_INT , STUB_INT* );
	    static STUB_INT readBerBlock( const u_char* , STUB_INT , STUB_INT , std::string );

	};
}

