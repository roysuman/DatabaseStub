#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <stdlib.h>
#include <iostream>
#include <QTableView>
#include <QMessageBox>
#include <QtSql/QtSql>
#include <QDialog>
#include <QtSql/QtSql>
#include <pthread.h>
#include <fcntl.h>
#include <boost/any.hpp>
#include <boost/thread.hpp>
#include <boost/function.hpp>
#include "newproject.h"
#include "adddbserver.h"
#include "generatepacket.h"
#include "openproject.h"
#include "../CORE/INTERFACE/include/sniffing.hpp"
#include "../DBLAYER/capture_packet_db.hpp"
#include "../DBLAYER/create_project_db.hpp"
#include "../DBLAYER/dummy_server_db.hpp"
#include "../STRUCTURE/include/database_structure.hpp"
#include "../STRUCTURE/include/rawdata_structure.hpp"
#include "../CORE/STUB/include/server.hpp"
//#include "../SUPPORT/GENERATOR/packet_mysql.hpp"
#include "../SUPPORT/JSON/include/jsonHandler.hpp"
#include "projectopen.h"
#include "../SUPPORT/init.hpp"
#include "../SUPPORT/globalDatatypes.hpp"
#include "../Test/include/readFromJsonFile.hpp"
using namespace test;
extern STUB_INT countForProgressBarPacketCapture;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow , public TestStub {
	Q_OBJECT

	public slots:
		void newProject();
	void openProject();
	void saveProject();
	void addDbServer();
        void about();
	void startSniffing();
	void saveScenarioCredentials();
	void showPackets( const QModelIndex & );
	void showInterface ( );
	void showScenario();
	void returnControl();
	void genPacketFromTcpDump();


	//TAB 3
	void startServer();
//	void startDummyServerDataTransfer();
	void stopSniffing();
	void showPacketsAddNewPackets();
	void addNewpacket ( const QModelIndex & );
	bool cancelQuery();
	bool updateQuery();
	bool insertQuery();
	bool deleteQuery();
	public:
	// bool showButtonStartDataTransfer();
	void showResult(); // show results after clicking button stop sniffing
    pthread_t threadStartSniffing , threadDummyServer  , thread3 , threadPacket;
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	QMenu *fileMenu;
	QMenu *editMenu;
	QMenu *formatMenu;
	QMenu *helpMenu;
	QAction *newAct;
	QAction *openAct;
	QAction *saveAct;
	QAction *exitAct;
	QAction *aboutAct;
	QSqlTableModel *model;
	void createActions();
	void createMenus();
	void body();
	STUB_CHAR ** interfaceList;
	QSqlDatabase db;
	//TAB3
	bool genaralWorkForInsertUpdate( void );
	bool writeDataFromQtextToFile();
	private:
	Ui::MainWindow *ui;
	STUB_INT convserastionIdGlobal;
	QMessageBox errorMessageBox;

	public:
	boost::thread mainWindowThread;


};

#endif // MAINWINDOW_H
