#ifndef CREATE_PROJECT_HPP_
#define CREATE_PROJECT_HPP_
#include <iostream>
#include <sqlite3.h>
#include <cstdlib>
#include "../../STRUCTURE/database_structure.hpp" // for variable db_credentials;
namespace initProject{





  //  extern sqlite3 *db;
    extern int rc;
    extern char *sql;
    extern char *zErrMsg;
    
    class Project  {
        private:
       // static char *zErrMsg ;
       // static int rc;
       // static char *sql;

        public:

        Project();
        ~Project () ;
        bool createDb ( void );
        bool createTableScenario ( void );

//        bool initializeSettings ( std::string , std::string , std::string );
	bool createTableServerInfo( void ); 


    };
}

#endif
