#ifndef INIT_HPP_
#define INIT_HPP_
#include "iostream"
#include "fstream"
#include "../SUPPORT/LOG/loghandle.hpp"
#include "../STRUCTURE/rawdata_structure.hpp"
#include "../STRUCTURE/configStruct.hpp"
#include "DISSECTOR/proto_mysql.hpp"
#include "DISSECTOR/proto_ldap.hpp"
#include "DISSECTOR/proto.hpp"
#include "LOG/loghandle.hpp"
#include "jsoncpp/json.h"

// written by suman roy on 6th jan 2014
// all the init part will be handled by this peace of code, when the application is being launched.

extern bool init();
class LoadConfig{
	public:
		LoadConfig();
		~LoadConfig();
		static std::ifstream configFileHandler;
		//		bool openFile();
		//		bool clodeFile();
		static void initConfig();

};

#endif
