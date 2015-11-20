#include <QtGui/QApplication>
#include "mainwindow.h"
#include "../SUPPORT/LOG/include/loghandle.hpp"
#include<assert.h>
#include "iostream"
#include "fstream"
#include <signal.h>
#include "../SUPPORT/init.hpp"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  main function, all initial init will be done hear,
 *  
 * =====================================================================================
 */
STUB_INT main(STUB_INT argc, STUB_CHAR *argv[]){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	/*-----------------------------------------------------------------------------
	 *  initializethe signal handling for all kind of signals--totake stack trace
	 *-----------------------------------------------------------------------------*/
	void (*prevHandler)(STUB_INT);
	prevHandler = signal (SIGINT, StackTrace::printStackTrace);

	/*-----------------------------------------------------------------------------
	 *  read the configuration file tcpstub.config--to load all configurations
	 *-----------------------------------------------------------------------------*/
	LoadConfig::initConfig();
	/*-----------------------------------------------------------------------------
	 *  activate the log files
	 *-----------------------------------------------------------------------------*/
	Log::activateLog();
	AddTimeStamp ats( cout );
	AddTimeStamp ats2( cerr );
	if( !configTcpFile.errorLog )
		std::cerr.setstate(std::ios::failbit) ;
	if ( !configTcpFile.traceLog )
		std::cout.setstate( std::ios::failbit );

	/*-----------------------------------------------------------------------------
	 *  init the env...
	 *-----------------------------------------------------------------------------*/
	init();
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
