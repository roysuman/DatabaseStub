/*
 *
 * =====================================================================================
 *
 *       Filename:  main_call.cpp
 *
 *    Description:  this is the testing environment 
 *
 *        Version:  1.0
 *        Created:  Wednesday 06 November 2013 09:23:24  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy (), 
 *   Organization:  Cognizant Technological solutions
 *
 * =====================================================================================
 */

#include <iostream>
#include <cstdlib>
#include "../SUPPORT/INTERFACE/sniffing.hpp"
#include "../DBLAYER/create_project_db.hpp"
#include "../DBLAYER/capture_packet_db.hpp"
#include "../STRUCTURE/scenario_struct.hpp"
#include "../STRUCTURE/database_structure.hpp"
#include "../STRUCTURE/rawdata_structure.hpp"


bool showInterface ( ){

	//display the available interfae list
	char **interface = snif::give_interface ( );
	
	std::cout <<" Interface List\n";
	int i = 0;
	while ( strcmp ( interface [ ++i ] , "NULL" ) ) {
		std::cout<<i<<"::"<<interface [ i ]<<std::endl;
	}
	return true;
}
//------------------------------------- ALL TOOLBAR----------------------------------------
//------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------

bool getServerInfo(  ){
	std::cout<<" ENTER -- SERVER NAME \n "
		<<"--------- SERVER TYPE ( LINUX | WINDOWS | IAM )\n"
		<<"--------- SERVER IP ( ----.----.----.---- )\n"
		<<"SERVER PORT\n";
	std::cin>>serverCredentials.serverName
		>>serverCredentials.serverType
		>>serverCredentials.serverIp
		>>serverCredentials.serverPort;

	return true;



}


bool addServer(){
	captureDb::RemoteServer remoteServer;
	
	if ( getServerInfo() & remoteServer.addNewServerInfo () ){
		std::cout<<" new server info added\n";
		return true;
	}

}

bool menuBar(){
	int choice;
	std::cout<<"1 for FILE ---\n"
		<<"2 for SETTINGS - NOW NOT EXIST\n";

	std::cout<<" Enter choice \t";
	std::cin>>choice;
	switch ( choice ){
		case 1:{
			choice = 0;
			std::cout<<" 1 for NEW PROJECT\n"
				<<" 2 FOR OPEN PROJECT\n";
			std::cout<<"enter choice \t";
			std::cin>>choice;
			switch ( choice ){
				case 1:{//create new project		
					       dbCreateProject::CreateProject  initializeDatabase;     // instance for create_project_db.hpp for accessing db 
					       std::string projectName , project_path;
					       std::cout<<"Enter project name\n";
					     //  std::cin>>projectName;
					     	std::cin>>db_credentials.databaseName;
					       std::cout<<std::endl;
					       std::cout<<"Enter path\n";
					      // std::cin>>project_path;
					      	std::cin>>db_credentials.databasePath;
					       //have to create a DB of the name if project
					       if ( initializeDatabase.createInitDb(  ) ){
						       std::cout<<"DB "<<projectName<< " created successfully \n";
						       
					       }

					       else {
						       std::cout<<" can't crate DB "<<projectName<<"\n";
						       
					       }

					       break;
					       
				       }

				       case 2:{// open project
                                  std::string projectName;
                                  std::cout<<"Enter project name\n";
                                  std::cin>>projectName;
                                  break;

						      
					      }
				       default: std::cout<<"---------Wrong CHOICE---------\n";
						exit ( EXIT_FAILURE );
						break;
					      
			}
			break ;
			
		       }

		       
		case 2:
		       break;

		default:
		       std::cout<<"-------------WRONG CHOICE--------------\n";
		       exit ( EXIT_FAILURE );
		       break;



		       

		       
	}
}


bool captureScenarioSetting(  ){
	int choice;
	std::cout<<"----------------___CAPTURE SCENARIO---------------------\n";
	std::cout<<"enter the scenario name\n "
		<<"-----------Catagory\n"
		<<"------------protocol\n"
		<<"------------Server\n"
		<<"------------Server Port\n";

	std::cin>>scenInfo.scenarioName
		>>scenInfo.catagory
		>>scenInfo.protocol
		>>scenInfo.server
		>>scenInfo.portNo;



	return true;

}
bool captureScenario( void ){
//	scenarioInformation scenInfo; // variable for scenario detail information
	captureScenarioSetting(  );
	//call function for inserting capture setting info into DB - scenario
	captureDb::CaptureDbSetting  capSetting; //  ::insertCaptureConfiguration
	capSetting.insertCaptureConfiguration(  );
	
}

bool startupProject(){
	showInterface();
	menuBar();  // for creating or opening PROJECT


	return true;
}

bool toolbar(){
	int choice;
	std::cout<<" 1 For ADD SERVER \n"
		<<" 10 for not choice \n";
	std::cin>>choice;
	switch ( choice ){
		case 1:{
			        return ( addServer() ); // this function to add new server information
				break;

		       }
		case 10:
		       break;
		default: std::cout<<" wrong chose\n";
			 return false;
			 break;

	}

	return true;
}
bool capture(){
	int choice;
	int interface_index;
	
	captureScenario ( );  // for capture data for a scenario
	std::cout<<" Do you want to start capture press 1 - tp start capture \n"
		<<"-------------------------------------NO - for nothing\n";
	std::cin>>choice;
	if ( choice == 1 ){
		showInterface();
		std::cout<<"select your interface\n";
		std::cin>>interface_index;
		snif::start_sniffing ( interface_index );

		}
	
}

int main(){

	init ();

	startupProject (); //when the sw is geting laiunch.
	toolbar();
	capture();
	return 0;
}
