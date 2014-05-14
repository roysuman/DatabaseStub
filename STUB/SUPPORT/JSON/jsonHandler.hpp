/*
 * =====================================================================================
 *
 *       Filename:  jsonHandler.hpp
 *
 *    Description:  for handling data to write and read from a json
 *
 *        Version:  1.0
 *        Created:  Tuesday 04 March 2014 04:38:14  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy (), 
 *   Organization:  Cognizant Technological solutions
 *
 * =====================================================================================
 */

#ifndef JSONHANDLER_HPP_
#define JSONHANDLER_HPP_
#include "iostream"
#include "jsoncpp/json.h"
#include "jsoncpp/writer.h"
#include "fstream"
#include "../../STRUCTURE/rawdata_structure.hpp"
#include <sstream>
namespace Json{
	extern bool flagForGenerateQuery;
	class JsonHandler{

		public:
			static std::fstream fileHandler;
			JsonHandler(){}
			~JsonHandler(){}
			static bool writeDataJson( queryPacketJson * , std::string );
			static bool readDataJson ( std::string  );
			static int generateColByColData( queryPacketJson * );
	};
}

#endif

