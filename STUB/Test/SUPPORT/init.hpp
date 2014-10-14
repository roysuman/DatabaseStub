#ifndef INIT_HPP_
#define INIT_HPP_
#include "iostream"
#include "fstream"
#include "../SUPPORT/LOG/include/loghandle.hpp"
#include "../STRUCTURE/include/rawdata_structure.hpp"
#include "../STRUCTURE/include/configStruct.hpp"
#include "../CORE/DISSECTOR/include/proto_mysql.hpp"
#include "../CORE/DISSECTOR/include/proto_ldap.hpp"
#include "../CORE/DISSECTOR/include/proto.hpp"
#include "../CORE/DISSECTOR/include/types.hpp"
#include "LOG/include/loghandle.hpp"
#include "jsoncpp/json.h"

// written by suman roy on 6th jan 2014
// all the init part will be handled by this peace of code, when the application is being launched.

extern bool init();
extern void finishingTouch();
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
