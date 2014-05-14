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
#include "newproject.h"
#include "adddbserver.h"
#include "generatepacket.h"
#include "openproject.h"
#include "../SUPPORT/INTERFACE/sniffing.hpp"
#include "../DBLAYER/capture_packet_db.hpp"
#include "../DBLAYER/create_project_db.hpp"
#include "../DBLAYER/dummy_server_db.hpp"
#include "../STRUCTURE/database_structure.hpp"
#include "../STRUCTURE/rawdata_structure.hpp"
#include "../SUPPORT/STUB/server.hpp"
//#include "../SUPPORT/GENERATOR/packet_mysql.hpp"
#include "../SUPPORT/JSON/jsonHandler.hpp"
#include "projectopen.h"
extern int countForProgressBarPacketCapture;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow{
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
	void startDummyServerDataTransfer();
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
	char ** interfaceList;
	QSqlDatabase db;
	//TAB3
    bool genaralWorkForInsertUpdate( );
	bool writeDataFromQtextToFile();
	private:
	Ui::MainWindow *ui;
	int convserastionIdGlobal;
	QMessageBox errorMessageBox;
};

#endif // MAINWINDOW_H
