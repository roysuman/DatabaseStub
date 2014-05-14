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
 *   Organization:  Cognizant Technological solutions
 *
 * =====================================================================================
 */
#include "function.hpp"

std::string func::quotesql( const std::string& s ) {
        return std::string("'") + s + std::string("'");
}

bool func::executeStatus ( int status , char * zErrMsg ){


         if ( status != SQLITE_OK ){
             std::cerr<<"DB/function.cpp::executeStatus -> error"<<std::endl;
             sqlite3_free ( zErrMsg );

             return false;
         }
         else {
             std::cout<<"DB/function.cpp::executeStatus- > ok"<<std::endl;
             sqlite3_free ( zErrMsg );

             return true;
         }
     }

int func::callback(void *NotUsed, int argc, char **argv, char **azColName){
        int i;
          for(i=0; i<argc; i++){
                printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");

               }
          //  printf("\n");
              return 0;

              }




