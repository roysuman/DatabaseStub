/*
 * =====================================================================================
 *
 *       Filename:  senario_struct.hpp
 *
 *    Description:  all the structure required for scenario handel
 *
 *        Version:  1.0
 *        Created:  Wednesday 06 November 2013 12:41:07  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy (), 
 *   Organization:  SELF
 *
 * =====================================================================================
 */
//needed by DBLAYER/create_project.hpp  DB/ctreate_project_db.hpp GUI/main_call.cp
#ifndef SCENARIO_STRUCT_HPP_
#define SCENARIO_STRUCT_HPP_
#include<iostream>
#include "../../SUPPORT/globalDatatypes.hpp"

//under a project there may be different scenarios--this structure for storing scenario information
typedef struct _scenarioInformation scenarioInformation;

struct _scenarioInformation{
	std::string scenarioName;
	std::string catagory;
	std::string protocol;
	std::string server;
	std::string portNo;
};
//one global variable for holding scenario information
extern scenarioInformation scenInfo;

#endif

