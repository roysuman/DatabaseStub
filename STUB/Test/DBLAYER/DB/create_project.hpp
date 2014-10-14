#ifndef CREATE_PROJECT_HPP_
#define CREATE_PROJECT_HPP_
#include <iostream>
#include <sqlite3.h>
#include <cstdlib>
#include "../../STRUCTURE/include/database_structure.hpp" // for variable db_credentials;
#include "../../SUPPORT/globalDatatypes.hpp"
namespace initProject{





  //  extern sqlite3 *db;
    extern STUB_INT rc;
    extern STUB_CHAR *sql;
    extern STUB_CHAR *zErrMsg;
    
    class Project  {
        private:
       // static STUB_CHAR *zErrMsg ;
       // static STUB_INT rc;
       // static STUB_CHAR *sql;

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
