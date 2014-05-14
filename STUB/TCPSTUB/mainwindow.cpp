#include "mainwindow.h"
#include "ui_mainwindow.h"
int countForProgressBarPacketCapture = 0;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
	    std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;

	    // some initial work have to do before starting any process.
	    this->setWindowIconText("Tstub");
	    ui->setupUi(this);
	    ui->frmPacket->setVisible( false );
	    ui->frmPacketSetting->setVisible( false );
	    this->createActions();
	    this->createMenus();
	    //signal handleing for saving scenario
	    connect ( ui->pshButtonSaveScenariocredentials , SIGNAL ( clicked() ) , SLOT ( saveScenarioCredentials() ));
	    //signal handling for sto Sniffing
	    connect ( ui->pshButtonStopSniffing , SIGNAL ( clicked() ) , SLOT ( stopSniffing() ) );
	    connect ( ui->pshBtnGenDataFromTcpDump , SIGNAL(clicked() ), this, SLOT( genPacketFromTcpDump()));
	    //signal handling for start sniffing
	    connect ( ui->pshButtonStartSniffing , SIGNAL ( clicked () ) , SLOT ( startSniffing() ) );
	    //signal handling for show packets at table vies
	    connect ( ui->tblViewShowPacketSettings , SIGNAL(clicked( QModelIndex ) ), this, SLOT( showPackets( QModelIndex )));
	    //signal handling for returniong control from table view
	    connect ( ui->pshButtonReturnPacketSetting , SIGNAL ( clicked () ) , this , SLOT ( returnControl() ) );
	    //set window size fixed by code ( 1024 * 1024 )
	    setMinimumSize(1024, 1324);
	    setMaximumSize( 1024 , 1324 );
	    //function to show interfaces at first window.
	    this->showInterface(); // function called to display interface list
	    //group box start sniffing will be enable after saving a scenario.
	    ui->grpBoxStartSniffing->setDisabled( true );

	    //TAB 3
	    //signal to start the dummy server.
	    connect ( ui->pshButtonStartServer ,SIGNAL ( clicked () ) , this , SLOT ( startServer() ) );
	    //signal to show  packet after capturing scenario.
	    connect ( ui->pshButtonDissectPackets , SIGNAL ( clicked () ) , this , SLOT ( showPacketsAddNewPackets() ));
	    //signal to add new packet.
	    connect ( ui->tblViewShowPacketSettingsNewPacket , SIGNAL(clicked( QModelIndex ) ), this, SLOT( addNewpacket(QModelIndex)));
	    //signals for update, insert, cancel , delete query
	    connect ( ui->pshBttnCancelQuery , SIGNAL ( clicked () ) , this , SLOT ( cancelQuery() ) );
	    connect ( ui->pshBttnUpdateQuery , SIGNAL ( clicked() ), this , SLOT ( updateQuery() ) );
	    connect ( ui->pshButtnInsertQuery , SIGNAL ( clicked() ) , this , SLOT ( insertQuery() ) );
	    connect (ui->pshBttnDelete , SIGNAL ( clicked() ), this , SLOT (deleteQuery()));
	    //set some widget invisible
	    ui->txtEditQuery->setVisible( false );
	    ui->pshBttnCancelQuery->setVisible( false );
	    ui->pshBttnUpdateQuery->setVisible( false );
	    ui->pshButtnInsertQuery->setVisible( false );
	    ui->pshBttnDelete->setVisible(false);

	    //give name to tabs
	    ui->tabWidget->setTabText(0, "HOME");
	    ui->tabWidget->setTabText(1, "CAPTURE");
	    ui->tabWidget->setTabText(2, "STUB");


 }

//actions for menu items
void MainWindow::createActions(){

	ui->action_New_Project->setShortcut(QKeySequence::New);
	ui->action_Open_Project->setShortcut(QKeySequence::Open);
}
//all the menu items.

void MainWindow::createMenus(){
	connect(ui->action_New_Project,SIGNAL(triggered()),SLOT(newProject()));
	connect ( ui->actionExit , SIGNAL ( triggered() ) , SLOT ( close() ) );
	connect ( ui->action_Open_Project , SIGNAL ( triggered () ) ,SLOT ( openProject() ));
	
}




 //this functions describes the new project scenarios.
 
void MainWindow::newProject(){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	NewProject *newProjectObject = new NewProject();
	newProjectObject->setWindowTitle("Create New Project");
	newProjectObject->show();
	if (dbCredentials.databaseName.compare("") != 0 )//if database name is not empty.
		ui->tabWidget->setDisabled( false );
    return ;
}

//function open a project

void MainWindow::openProject(){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	projectOpen *openPro = new projectOpen();
	openPro->setWindowTitle("Open Project");
	openPro->show();
	if ( dbCredentials.databaseName !=""){
		std::cerr<<"can't open project\n";
		ui->tabWidget->setDisabled( false);
		
	}
    //    const char *filename ="/home/suman/test.db";
    //    db_credentials.databaseName="test";
    //    db_credentials.databasePath="/home/suman";
    //   scenInfo.scenarioName = "q";
    //
    //     int rc = sqlite3_open( filename , &db_credentials.db);
    //
    //     std::cout<<"opened"<<rc<<std::endl;

    return;
}

//for saving current project - yet to develop
void MainWindow::saveProject(){
    return ;

}

// about TCP STUB-- yet to develop
void MainWindow::about(){
    return ;

}
//body-- yet to develop
void MainWindow::body(){
   }

//method to add new server-- yet to modify and develop
void MainWindow::addDbServer(){
	std::cout<<__FUNCTION__<<std::endl;
	AddDbServer * dbServerInstance = new AddDbServer();
	dbServerInstance->show();
	delete dbServerInstance;
}

//#########################!TAB 2 !##############################
//####################!METHODS!################################

//method to save current scenario informations
 
void MainWindow::saveScenarioCredentials(){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	QString tempValue = ui->lneEditScenarioName->text();
	scenInfo.scenarioName = tempValue.toStdString() ;
	tempValue.clear();
	tempValue = ui->lneEditCatagory->text() ;
	scenInfo.catagory = tempValue.toStdString() ;
	tempValue.clear();
	tempValue = ui->lneEditProtocol->text();
	scenInfo.protocol =  tempValue.toStdString() ;
	tempValue.clear();
	tempValue = ui->lneEditServer->text() ;
	scenInfo.server = tempValue.toStdString();
	tempValue.clear();
	tempValue = ui->lneEditPortNo->text();
	scenInfo.portNo = tempValue.toStdString() ;
	tempValue.clear();
	//insert these inforation into database
	captureDb::CaptureDbSetting *captureInstance = new captureDb::CaptureDbSetting();
	if  ( captureInstance->insertCaptureConfiguration() ){
		// make edit lines non-editable
		ui->lneEditCatagory->setReadOnly( true );
		ui->lneEditCatagory->setDisabled( true );
		ui->lneEditPortNo->setReadOnly( true );
		ui->lneEditPortNo->setDisabled( true );
		ui->lneEditProtocol->setReadOnly( true );
		ui->lneEditProtocol->setDisabled( true );
		ui->lneEditScenarioName->setReadOnly( true );
		ui->lneEditScenarioName->setDisabled( true );
		ui->lneEditServer->setReadOnly( true );
		ui->lneEditServer->setDisabled( true );
		ui->pshButtonSaveScenariocredentials->setEnabled( false );
		//get all available interface list , to select the user which interface he wants to snif.
		ui->grpBoxStartSniffing->setDisabled( false );
		int i =1 ;
		ui->cmbBoxInterfaces->setDisabled( false );
		while ( strcmp ( interfaceList [ i ] , "NULL" ) ){
			ui->cmbBoxInterfaces->addItem( ( QString ) interfaceList [ i++ ] );
			
		}
		ui->cmbBoxInterfaces->show();
		
	}
	delete captureInstance;
}

//method that will display all available interface
void MainWindow::showInterface(){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	interfaceList = snif::giveInterface(); // get the interface list from snif::sniffing.cpp 
	int i = 1;
	ui->txtBrowserInterface->fontPointSize();
	while ( strcmp ( interfaceList [ i ] , "NULL" ) )
		ui->txtBrowserInterface->append( ( QString) interfaceList [ i++ ]);
	
}

//method to show all the available sceario under this project--yet to develop
void MainWindow::showScenario(){
    //code for displaying scenarios at tab1
}

//start the sniffing on the selected interface.This function wll be called after
//pressing btn startSniffing at TAB2
void MainWindow::startSniffing(){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	std::string interfaceName = ui->cmbBoxInterfaces->currentText().toStdString(); // take the interface name frim drop down box
	std::cout<<__FUNCTION__<<"Selected interface for sniffing is:"<<interfaceName<<std::endl;
	int i = 0;
	while ( strcmp ( interfaceList [ ++i ] , interfaceName.c_str() ) );
	pthread_create(&threadStartSniffing, NULL,
			snif::startSniffing, (void *)&i); // the function start sniffing to capture all the TCP level packets , it will be called through anew thread.
	
}


//function to stop the snifing on aprticular interface
void MainWindow::stopSniffing(){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	snif::stopSniffing(); // stop the sniffing
	//now update the database table of PACKET_SETTING_ with the query string. Suppose a raw packet containg select query, so the following method
	//will updat the PACKET_SETTING_ table column with the query string body.
	//it will help to match the incoming query during stub mode.
	captureDb::StoreRawPacket pHandler;
	pHandler.updateQueryTypeQueryAtDatabase();
	this->showResult();
	
}
//this is for creating data from a tcpDump file.
//tcpDump mainly read the network packets using lpcap and store the packets
//into a file format

void MainWindow::genPacketFromTcpDump(){
    std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));


    char *fileName ="sample";
    pthread_create(&threadPacket, NULL,
            snif::analysisFromFile, (void *)fileName);
    pthread_join(threadPacket , NULL);


    //snif::analysisFromFile("sample1"); // file name that contains tcpDump file
	captureDb::StoreRawPacket pHandler;
	pHandler.updateQueryTypeQueryAtDatabase();

    QApplication::restoreOverrideCursor();

	this->showResult();
}



//after sniffing completed all the captured packets will be displayed into
//a tab;e widget

void MainWindow::showResult(){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	ui->frmPacketSetting->setVisible( true );
	ui->frmPacket->setVisible( false );
	db = QSqlDatabase::addDatabase( "QSQLITE" );
	db.setDatabaseName( ( QString) ( dbCredentials.databasePath+"/" + dbCredentials.databaseName + ".db").c_str());
	if( !db.open() ){
		qDebug() << db.lastError();
		qFatal( "Failed to connect." );
		
	}
	qDebug()<<db.databaseName();
	qDebug( "Connected!" );
	QSqlQuery qry;
	model = new QSqlTableModel( this , db );
	model->setTable( (QString)("PACKET_SETTING_"+scenInfo.scenarioName).c_str()) ; // replace by PACKET_SETTING + scen_info.scenarioname;
	model->select();
	model->setHeaderData(0, Qt::Horizontal, tr("CONVERSATION_ID"));
	model->setHeaderData(1, Qt::Horizontal, tr("PACKET_NO"));
	model->setHeaderData(2, Qt::Horizontal, tr("SEQUENCE_NO"));
	model->setHeaderData(3, Qt::Horizontal, tr("ACKNOWLEDGEMENT NO"));
	model->setHeaderData(4, Qt::Horizontal, tr("RAW_DATA"));
	model->setHeaderData(5, Qt::Horizontal, tr("STATUS"));
	ui->tblViewShowPacketSettings->setEditTriggers( QAbstractItemView::NoEditTriggers);
	ui->tblViewShowPacketSettings->setSelectionBehavior( QAbstractItemView::SelectRows );
	ui->tblViewShowPacketSettings->setModel( model );
	ui->tblViewShowPacketSettings->maximumSize();
	ui->tblViewShowPacketSettings->show();
	
}
//show the entire packet after selecting on the conversation id of PACKET_SETTING_
void MainWindow::showPackets( const QModelIndex &modelIndex ){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	QString conversationId = "not valid column";
	QVariant value = ui->tblViewShowPacketSettings->model()->data( modelIndex , 0 );
	if (!value.isValid()) return ;
	conversationId = value.toString();
	qDebug() << conversationId;
	ui->frmPacketSetting->setVisible( false);
	ui->frmPacket->setVisible ( true );
	QItemSelectionModel *selectionM = ui->tblViewShowPacketSettings->selectionModel();// tableView->selectionModel();
	QModelIndexList selectionL = selectionM->selectedIndexes();
	if( selectionL.size() < 1) return;
	QModelIndex previous = selectionL.first();// selectionL.first(); //indexes.first();
	QVariant data = model->data(previous);
	QString text = data.toString();
	//the following code for fetching information from PACKET table
	qDebug()<<db.databaseName();
	qDebug( "Connected!" );
	QSqlQuery qry;
	model->clear();
	model->setTable( (QString)("PACKET_"+scenInfo.scenarioName).c_str() ); // replace by PACKET_SETTING + scen_info.scenarioname;
	model->select();
	//modified on dec 7 - suman
	model->setFilter(" CONVERSATION_ID = "+ conversationId );
	model->setHeaderData(0, Qt::Horizontal, tr("CONVERSATION_ID"));
	model->setHeaderData(1, Qt::Horizontal, tr("PACKET_NO"));
	model->setHeaderData(2, Qt::Horizontal, tr("SEQ_NO"));
	model->setHeaderData(3, Qt::Horizontal, tr("ACK_NO"));
	model->setHeaderData(4, Qt::Horizontal, tr("APP_DATA"));
	model->setHeaderData(5, Qt::Horizontal, tr("DB_DATA"));
	ui->tblViewPacket->setEditTriggers( QAbstractItemView::NoEditTriggers);
	ui->tblViewPacket->setSelectionBehavior( QAbstractItemView::SelectRows );
	ui->tblViewPacket->setModel( model );
	ui->tblViewPacket->maximumSize();
	ui->tblViewPacket->show();
}
//return control after showing all packets under a particular conversation
void MainWindow::returnControl(){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	ui->frmPacket->setVisible ( false );
	ui->frmPacketSetting->setVisible( true );
	model->clear();
	this->showResult();
	
}

//###########################################!TAB 3!######################
//##########################################!METHODS!####################

//method to start the summy server - all the information like server ip port
//must be taken fro the GUI
void MainWindow::startServer(){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	server::DummyServer *instance;
       try{
	       instance = new server::DummyServer(); //create an object of dummy server
       }
       catch ( std::exception &e ){
	       std::cerr<<__FUNCTION__<<"exception cgt \n";
	       exit ( -1 );
       }
	int socket_fd = instance->createServer( ui->lnEditServerIp->text().toStdString() , ui->lnEditPort->text().toInt()  );
	std::cout<<__FUNCTION__<<":server created sock_fd = "<<socket_fd<<std::endl;
	if ( socket_fd < -1 ){
		std::cerr<<__FUNCTION__<<":cant create server\n";

		// ADD A MSG BOX
		return ;
		
	}
	try{
		delete instance;
	}
	catch ( std::exception &e ){
		std::cerr<<__FUNCTION__<<"exception cgt\n";
		exit ( -1 );
	}
	//after creating server on specified port and IP server must wait for a client ping
	//all of these lofics are written in the following method
	//and a new thread has been assigned for handling the client part
	pthread_create(&thread3, NULL, server::DummyServer::acceptClient, (void * )&thread3 );

}

// function to transfer data from DB
// have ? on the usability of this method
void MainWindow::startDummyServerDataTransfer(){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
//	initServer (); -- saw this method at rawdatastructure.cpp--it was empty--so deltd
	pthread_create(&threadDummyServer, NULL, server::playWithData, (void * )&threadDummyServer );
	
}
//add new packet-- add new packet similar to capterd packet type
//this method will show all the packets from PACKET_SETTING_scenarioName
void MainWindow::showPacketsAddNewPackets(){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	db = QSqlDatabase::addDatabase( "QSQLITE" );
	db.setDatabaseName( ( QString) ( dbCredentials.databasePath+"/" + dbCredentials.databaseName + ".db").c_str());
	if( !db.open() ){
		qDebug() << db.lastError();
		qFatal( "Failed to connect." );
		
	}
	qDebug()<<db.databaseName();
	qDebug( "Connected!" );
	QSqlQuery qry;
	std::cout<<__FUNCTION__<<"db.is_open :" <<db.isOpen()<<std::endl;
	try{
		model = new QSqlTableModel( this , db );
		
	}
	catch ( std::exception &ba){
        std::cerr<<__FUNCTION__<<"exception cgt:"<<ba.what()<<std::endl;
	
	}
	 model->setTable( (QString)("PACKET_SETTING_"+scenInfo.scenarioName).c_str()) ; // replace by PACKET_SETTING + scen_info.scenarioname;
	 model->select();
	 model->setHeaderData(0, Qt::Horizontal, tr("CONVERSATION_ID"));
        //model->setHeaderData(1, Qt::Horizontal, tr("PACKET_NO"));
        //model->setHeaderData(2, Qt::Horizontal, tr("SEQUENCE_NO"));
        //model->setHeaderData(3, Qt::Horizontal, tr("ACKNOWLEDGEMENT NO"));
        //model->setHeaderData(4, Qt::Horizontal, tr("RAW_DATA"));
        //model->setHeaderData(5, Qt::Horizontal, tr("STATUS"));
	 ui->tblViewShowPacketSettingsNewPacket->setEditTriggers( QAbstractItemView::NoEditTriggers);
	 ui->tblViewShowPacketSettingsNewPacket->setSelectionBehavior( QAbstractItemView::SelectRows );
	 ui->tblViewShowPacketSettingsNewPacket->setModel( model );
	 ui->tblViewShowPacketSettingsNewPacket->maximumSize();
	 ui->tblViewShowPacketSettingsNewPacket->show();
	 
}
//gload variable that must be destroied at dissector---hopefully
createPacketDb::GenarateRawPacket *instance;
actSeriesStruct *tempConversationPackets;
//Method to display all the packets under a particular conversation ID
//the dissected packet information will be displayed in a JSON file
//where user can edit the new query
void MainWindow::addNewpacket( const QModelIndex &modelIndex ){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	QVariant value = ui->tblViewShowPacketSettingsNewPacket->model()->data( modelIndex , 0 );
	if (!value.isValid()) return ;
	int conversationId = value.toInt();
	convserastionIdGlobal = conversationId; // store the conversation id into a global variable for inter method communication
	try {
		instance = new createPacketDb::GenarateRawPacket(); // variable defined gloabally
	}
	catch ( std::bad_alloc &ba ){
		std::cerr<<__FUNCTION__<<"cgt exception:"<<ba.what()<<std::endl;
		exit ( -1 );
	}
	tempConversationPackets =  instance->getChunkPackets( conversationId  ) ; // variable declared gloabally
	//now dissect all packets
        for ( int packetNo = 0 ; packetNo <=tempConversationPackets->noOfPacket ; ++packetNo ){
		std::cout<<__FUNCTION__<<"*********DISSECT PACKET ******* " <<packetNo<<'\n';
		///now get the method for dissection
//		boost::any_cast< bool ( * )( actRawDataStruct * , int , actSeriesStruct *)> ( boost::get< boost::any >(proto::Proto::initDissect( 3306 , 0 )) )  ( &tempConversationPackets->actRawData [ packetNo ] , tempConversationPackets->actRawData [ packetNo ].length , tempConversationPackets );
		// Mysql::dissectMysql( &tempConversationPackets->actRawData[ packetNo ] , tempConversationPackets->actRawData [ packetNo].length );
		
	}
	//write all dissected query for a particular conversation into a JSON file
            Json::JsonHandler::writeDataJson ( &QueryPacket , "../LOG/json.js");
	    //show the JSON file information into the textEditor
	    QFile myFile("../LOG/json.js");
	    myFile.open(QIODevice::ReadOnly);
	    QTextStream textStream(&myFile);
	    QString line = textStream.readAll();
	    myFile.close();
	    ui->tblViewShowPacketSettingsNewPacket->setVisible( false );
	    ui->txtEditQuery->setPlainText( line );
	    ui->tblViewShowPacketSettings->setVisible( false);
	    ui->txtEditQuery->setVisible( true );
	    ui->pshBttnCancelQuery->setVisible( true );
	    ui->pshBttnUpdateQuery->setVisible( true );
	    ui->pshButtnInsertQuery->setVisible( true );
	    ui->pshBttnDelete->setVisible(true);
	    return ;
	    
}

//some basic work, that is required for insert new query/update query.

bool MainWindow::genaralWorkForInsertUpdate(){
	std::cout<<"METHOD:"<<__FUNCTION__<<std::endl;
	writeDataFromQtextToFile();
	Json::JsonHandler::readDataJson ("../LOG/json.js");
	Json::JsonHandler::generateColByColData ( &QueryPacket );
	//now dissect all packets
	//thinf this dissection is for testing no need in future--not sure
	//
//	MAKE JSON TRUE TO INDICATE THAT IT'S NEW PACKET CREATION
	Json::flagForGenerateQuery = true;

	for ( int packetNo = 0 ; packetNo <=tempConversationPackets->noOfPacket ; ++packetNo )
//		boost::any_cast< bool ( * )( actRawDataStruct * , int , actSeriesStruct*)> ( boost::get < boost::any > ( proto::Proto::initDissect( 3306 , 0 ) ) )  ( &tempConversationPackets->actRawData [ packetNo ] , tempConversationPackets->actRawData [ packetNo ].length , tempConversationPackets );
	Json::flagForGenerateQuery = false;
	return ( instance->insertGeneratedPacket ( newConversationPack ) && deleteActSeriesStruct ( newConversationPack ) );
       // Mysql::dissectMysql( &tempConversationPackets->actRawData[ packetNo ] , tempConversationPackets->actRawData [ packetNo].length );
	//std::cerr<<__FUNCTION__<<"Printing the real data\n";
	//std::cerr<<__FUNCTION__<<"lrngth==="<<tempConversationPackets->actRawData[1].length<<std::endl;
	//for( int i = 0; i< tempConversationPackets->actRawData[1].length ; ++i)	std::cerr<<__FUNCTION__<<tempConversationPackets->actRawData[1].data[i]<<'\n';
    /*CreatePacketMysql *createPacket;
	try{
		createPacket = new CreatePacketMysql ();
        createPacket->conversationPackets = tempConversationPackets;
		}
	catch ( std::bad_alloc &ba ){
		std::cerr<<__FUNCTION__<<"caught exception :"<<ba.what()<<std::endl;
		
	}

	//now add the new value-- beter analysis needed
	for ( int packetNo = 0 ; packetNo <=tempConversationPackets->noOfPacket ; ++packetNo )
		createPacket->dissectMysql( &tempConversationPackets->actRawData [ packetNo ] , tempConversationPackets->actRawData [ packetNo ].length , packetNo );
		
	std::cout<<__FUNCTION__<<"now insert the new query into database\n";
	if( instance->insertGeneratedPacket( createPacket->newConversation) ) {
	       delete createPacket;
	       return true;
	}
	else{
		
		delete createPacket;
		return false;
	}
    */
    return true;
}

//cancel a query--no need to insert/update/delete the query shown at textWidget
bool MainWindow::cancelQuery(){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	ui->tblViewShowPacketSettings->setVisible( true);
	ui->txtEditQuery->setVisible( false );
	ui->pshBttnCancelQuery->setVisible( false );
	ui->pshBttnUpdateQuery->setVisible( false );
	ui->pshButtnInsertQuery->setVisible( false );
	ui->pshBttnDelete->setVisible( false );
	return true;
}

//insert a new query
bool MainWindow::insertQuery(){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
    if ( genaralWorkForInsertUpdate( ) )
		errorMessageBox.setText("NEW DATA INSERTED");
	else errorMessageBox.setWindowTitle("ERROR\n");
	if( errorMessageBox.exec() == QMessageBox::Yes){
		//do smthing
		
	}
	MainWindow::cancelQuery(); // to clear the textWidget
	return true;
	
}

//update the already available query--mainly it used to update the query
//with many reply data
bool MainWindow::updateQuery(){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
    if ( genaralWorkForInsertUpdate( ) & instance->deletePacketRegardingConversationId( convserastionIdGlobal) )
		errorMessageBox.setText("NEW DATA UPDATED");
	else 
		errorMessageBox.setWindowTitle("ERROR\n");
	if( errorMessageBox.exec() == QMessageBox::Yes){
		//do smthing
		
	}
	MainWindow::cancelQuery();
	return true;
}

//write the data from QText to the json file
bool MainWindow::writeDataFromQtextToFile(){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	std::string nomeFile ="../LOG/json.js";
	if (nomeFile != "") {
		QFile file(nomeFile.c_str());
		if (file.open( QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
			QTextStream stream(&file );
			stream << ui->txtEditQuery->toPlainText();//  ui->editaTesto->toPlainText();
			file.flush();
			file.close();
			return true;
			
		}
		else {
			QMessageBox::critical(this, tr("Errore"), tr("Non posso salvare il file"));
			return false;
			
		}
		
	}else return false;
}

//delete the query permanently from DB
bool MainWindow::deleteQuery(){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	if (instance->deletePacketRegardingConversationId( convserastionIdGlobal) ){
		errorMessageBox.setText("DELETED");
		ui->txtEditQuery->clear();
	}
	else errorMessageBox.setWindowTitle("ERROR\n");
	if( errorMessageBox.exec() == QMessageBox::Yes){
		//do smthing
	}
	MainWindow::cancelQuery(); // clear text
	return true;
}
//dissector for mainwindow--all the object that has been created must be freed
//
MainWindow::~MainWindow(){
	std::cout<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	void *status;
	//join threads
	int rc = pthread_join(threadStartSniffing, &status); // thread which was created to read raw packet have to be joined.
	if (rc){
		std::cerr<<__FUNCTION__<<"Error:unable to join\n";
		exit(-1);
		
	}
	std::cout <<__FUNCTION__<< "completed thread id :" << threadStartSniffing<<std::endl;
         std::cout << "  exiting with status :" << status << std::endl;
	 delete ui;
	 delete instance;
	 
}

