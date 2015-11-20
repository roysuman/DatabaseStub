/*
 * =====================================================================================
 *
 *       Filename:  function.cpp
 *
 *    Description:  implementation of function.hpp
 *
 *        Version:  1.0
 *        Created:  Wednesday 06 November 2013 03:59:19  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy (),
 *   Organization:  SELF
 *
 * =====================================================================================
 */
#include "function.hpp"

std::string func::quotesql( const std::string& s ) {
        return std::string("\"") + s + std::string("\"");
}

bool func::executeStatus ( STUB_INT status , STUB_CHAR * zErrMsg ){


         if ( status != SQLITE_OK ){
             std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<
		     __FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["
		     <<__DATE__<<"_"<<__TIME__<<"]"<<"DB/function.cpp::\
		     executeStatus -> error"<<std::endl;
             sqlite3_free ( zErrMsg );

             return false;
         }
         else {

             std::cout<<" File Name ["<<__FILE__<<" ] Function [ "
		     <<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["
		     <<__DATE__<<"_"<<__TIME__<<"]"<<"DB/function.cpp::ex\
		     ecuteStatus- > ok\n";
             sqlite3_free ( zErrMsg );

             return true;
         }
     }

STUB_INT func::callback(void *temp,  STUB_INT argc, STUB_CHAR **argv, STUB_CHAR **azColName){
        STUB_INT    i;




          for(i=0; i<argc; i++){
                printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

               }
          //  printf("\n");
              return 0;

              }




