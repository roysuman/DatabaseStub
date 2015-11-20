/*
date: 25-april-2014
*/
#include "iostream"
#include <string.h>
#include <stdlib.h>
#include "../../STRUCTURE/sumanGtkmm.hpp"
#include"types.hpp"
#define DEBUG "debugon"
namespace ber{
	class Ber{
		private:
//			static gint8 lastBerClass;
//			static bool lastPrimFlag;
//			static gint32   lastTag;
		public:
			Ber();
			~Ber();
            static int getBerIdentifier( const u_char* , int , gint8 * ,bool * , gint32 *);
            static int getBerLength( const u_char * , int  , int *);
            static bool readBerInteger( const u_char * , int , int , int* );
	    static int readBerBlock( const u_char* , int , int , std::string );

	};
}

