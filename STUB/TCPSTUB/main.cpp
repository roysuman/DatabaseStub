#include <QtGui/QApplication>
#include "mainwindow.h"
#include "../SUPPORT/LOG/loghandle.hpp"
#include<assert.h>
#include "iostream"
#include "fstream"
#include <signal.h>
#include "../SUPPORT/init.hpp"

int main(int argc, char *argv[]){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<'\n';
	//initialize the signal handling for all kind of signals to take stack trace.
	void (*prevHandler)(int);
	prevHandler = signal (SIGINT, StackTrace::printStackTrace);
	//read the configuration file tcpstub.configand init the logs
	LoadConfig::initConfig();
	//activate log files
	Log::activateLog();
	AddTimeStamp ats( cout );
	AddTimeStamp ats2( cerr );
	if( !configTcpFile.errorLog )
		std::cerr.setstate(std::ios::failbit) ;
	if ( !configTcpFile.traceLog )
		std::cout.setstate( std::ios::failbit );

	//initialize the inv
	init();
	QApplication a(argc, argv);
	MainWindow w;
	w.show();
	return a.exec();
}
