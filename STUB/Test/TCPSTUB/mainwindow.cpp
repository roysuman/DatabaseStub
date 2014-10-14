#include "mainwindow.h"
#include "ui_mainwindow.h"
STUB_INT countForProgressBarPacketCapture = 0;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){

	    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		    <<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		    <<__TIME__<<"]\n";

	    // some initial work have to do before starting any process.
	    this->setWindowIconText("Tstub");
	    ui->setupUi(this);
	    ui->frmPacket->setVisible( false );
	    ui->frmPacketSetting->setVisible( false );
	    this->createActions();
	    this->createMenus();
	    //signal handleing for saving scenario
	    connect ( ui->pshButtonSaveScenariocredentials , SIGNAL ( clicked() ) , 
			    SLOT ( saveScenarioCredentials() ));
	    //signal handling for sto Sniffing
	    connect ( ui->pshButtonStopSniffing , SIGNAL ( clicked() ) , 
			    SLOT ( stopSniffing() ) );
	    connect ( ui->pshBtnGenDataFromTcpDump , SIGNAL(clicked() ), this,
			    SLOT( genPacketFromTcpDump()));
	    //signal handling for start sniffing
	    connect ( ui->pshButtonStartSniffing , SIGNAL ( clicked () ) ,
			    SLOT ( startSniffing() ) );
	    //signal handling for show packets at table vies
	    connect ( ui->tblViewShowPacketSettings , SIGNAL(clicked( QModelIndex ) ), 
			    this, SLOT( showPackets( QModelIndex )));
	    //signal handling for returniong control from table view
	    connect ( ui->pshButtonReturnPacketSetting , SIGNAL ( clicked () ) , 
			    this , SLOT ( returnControl() ) );
	    //set window size fixed by code ( 1024 * 1024 )
	    setMinimumSize(1024, 1324);
	    setMaximumSize( 1024 , 1324 );
	    //function to show STUB_INTerfaces at first window.
	    this->showInterface(); // function called to display STUB_INTerface list
	    //group box start sniffing will be enable after saving a scenario.
	    ui->grpBoxStartSniffing->setDisabled( true );

	    //TAB 3
	    //signal to start the dummy server.
	    connect ( ui->pshButtonStartServer ,SIGNAL ( clicked () ) , this , 
			    SLOT ( startServer() ) );
	    //signal to show  packet after capturing scenario.
	    connect ( ui->pshButtonDissectPackets , SIGNAL ( clicked () ) , this , 
			    SLOT ( showPacketsAddNewPackets() ));
	    //signal to add new packet.
	    connect ( ui->tblViewShowPacketSettingsNewPacket , 
			    SIGNAL(clicked( QModelIndex ) ), this, 
			    SLOT( addNewpacket(QModelIndex)));
	    //signals for update, insert, cancel , delete query
	    connect ( ui->pshBttnCancelQuery , SIGNAL ( clicked () ) , this , 
			    SLOT ( cancelQuery() ) );
	    connect ( ui->pshBttnUpdateQuery , SIGNAL ( clicked() ), this , 
			    SLOT ( updateQuery() ) );
	    connect ( ui->pshButtnInsertQuery , SIGNAL ( clicked() ) , this , 
			    SLOT ( insertQuery() ) );
	    connect (ui->pshBttnDelete , SIGNAL ( clicked() ), this , 
			    SLOT (deleteQuery()));
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

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  createActions
 *  Description:  actions for menu items
 * =====================================================================================
 */
void MainWindow::createActions(){

	ui->action_New_Project->setShortcut(QKeySequence::New);
	ui->action_Open_Project->setShortcut(QKeySequence::Open);
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  createMenus
 *  Description:  create all menus
 * =====================================================================================
 */
void MainWindow::createMenus(){
	connect(ui->action_New_Project,SIGNAL(triggered()),SLOT(newProject()));
	connect ( ui->actionExit , SIGNAL ( triggered() ) , SLOT ( close() ) );
	connect ( ui->action_Open_Project , SIGNAL ( triggered () ) ,
			SLOT ( openProject() ));
	
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  newProject
 *  Description:  function for creating a new project
 * =====================================================================================
 */
void MainWindow::newProject(){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"]\n";

        NewProject                        *newProjectObject;


#ifdef TESTMODE
	dbCreateProject::CreateProject    *initDatabase;

	/*-----------------------------------------------------------------------------
	 *  for testing perpouse no need to browse for creating new project
	 *-----------------------------------------------------------------------------*/
	try{
		initDatabase = new dbCreateProject::CreateProject();
	}
	catch ( std::exception &ea ){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"] Exception: "<<ea.what()<<'\n';
		exit(0);
	}
	dbCredentials.databaseName.assign(testParameters.databaseName ) ;
	dbCredentials.databasePath.assign( testParameters.path ) ;
	if ( !initDatabase->createInitDb() ){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"]"<<"databse not created\n";
		exit(0);
	}

	saveScenarioCredentials();
#else
	

	try{
		newProjectObject = new NewProject();
		newProjectObject->setWindowTitle("Create New Project");
		newProjectObject->show();
		if (dbCredentials.databaseName.compare("") != 0 )//if database name is not empty.
			ui->tabWidget->setDisabled( false );
		
	}
	catch( std::exception e ) {
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"] EXCEPTION"<<e.what()<<'\n';
		exit ( 0 );
	}
#endif
    return ;
}
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  openProject
 *  Description:  open an existing project
 * =====================================================================================
 */

void MainWindow::openProject(){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	projectOpen    *openPro;
	std::string    filename;

#ifdef TESTMODE
	STUB_INT      rc;
        filename = testParameters.path + testParameters.databaseName+".db";

	dbCredentials.databaseName.assign(testParameters.databaseName
			);
	dbCredentials.databasePath.assign( testParameters.path );
	scenInfo.scenarioName.assign(testParameters.scenarioName );
	
	rc = sqlite3_open( filename.c_str()  , &dbCredentials.db);
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"
		<<"opened"<<rc<<'\n';
#else
	
	openPro = new projectOpen();
	openPro->setWindowTitle("Open Project");
	openPro->show();
	if ( dbCredentials.databaseName !=""){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"]"<<"can't open project\n";
		ui->tabWidget->setDisabled( false);
		
	}
#endif
    return;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  saveProject
 *  Description:  save the current project snap--- have to implement
 * =====================================================================================
 */
void MainWindow::saveProject(){
    return ;

}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  about
 *  Description:  about this tool
 * =====================================================================================
 */
void MainWindow::about(){
    return ;

}
//body-- yet to develop
void MainWindow::body(){
   }

//method to add new server-- yet to modify and develop
void MainWindow::addDbServer(){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"]\n";

	AddDbServer    *dbServerInstance;
	try {
		dbServerInstance = new AddDbServer();
		dbServerInstance->show();
		delete dbServerInstance;
	}
	catch ( std::exception e ){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"] EXCEPTION"<<e.what()<<'\n';
		exit ( 0 );
	}
}

//#########################!TAB 2 !##############################
//####################!METHODS!################################

//method to save current scenario informations
 
void MainWindow::saveScenarioCredentials(){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"]\n";
	STUB_INT                       loop; 
	QString                        tempValue;
	captureDb::CaptureDbSetting    *captureInstance;
#ifdef TESTMODE

        scenInfo.scenarioName.assign( testParameters.scenarioName );//	= "q";
	scenInfo.catagory.assign( testParameters.catagory ) ;// = "q";
	scenInfo.protocol.assign( testParameters.protocol );// =  "MySQL" ;
	scenInfo.server.assign( testParameters.filterIp );// = "127.0.0.1";
        scenInfo.portNo.assign( testParameters.portNo );// = "3306";
        ui->lneEditScenarioName->setText( QString::fromStdString(testParameters.scenarioName ));
	ui->lneEditCatagory->setText( QString::fromStdString( testParameters.catagory ) );
	ui->lneEditProtocol->setText ( QString::fromStdString ( testParameters.protocol ) );
	ui->lneEditServer->setText ( QString::fromStdString ( testParameters.filterIp ) );
	ui->lneEditPortNo->setText( QString::fromStdString( scenInfo.portNo ) );			
#else
		tempValue = ui->lneEditScenarioName->text();
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
#endif
	try {
		//insert these inforation into database
		captureInstance =
			new captureDb::CaptureDbSetting();
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
			//get all available STUB_INTerface list , to select the user which STUB_INTerface he wants to snif.
			ui->grpBoxStartSniffing->setDisabled( false );
			loop =1 ;
			ui->cmbBoxInterfaces->setDisabled( false );
			while ( strcmp ( interfaceList [ loop ] , "NULL" ) ){
				ui->cmbBoxInterfaces->addItem( ( QString ) interfaceList [ loop++ ] );
				
			}
			ui->cmbBoxInterfaces->show();
			
		}
		delete captureInstance;
	}
	catch ( std::exception e){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
			<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
			<<"]Exception "<<e.what()<<'\n';
		exit ( 0 );
	}
#ifdef TESTMODE
	
	/*-----------------------------------------------------------------------------
	 *  check wheather read from tcpstub or not---
	 *-----------------------------------------------------------------------------*/
	if ( testParameters.readFromTcpDump == "1") {
		genPacketFromTcpDump();
		
	}
	else {
		startSniffing();
		
	}
#endif

}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  showInterface
 *  Description:  will show all available interfaces
 * =====================================================================================
 */
void MainWindow::showInterface(){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	STUB_INT    loop; 

	interfaceList = snif::giveInterface(); // get the STUB_INTerface list from snif::sniffing.cpp 

	loop = 1;
	ui->txtBrowserInterface->fontPointSize();

	while ( strcmp ( interfaceList [ loop ] , "NULL" ) )

		ui->txtBrowserInterface->append( ( QString) interfaceList [ loop++ ]);
	
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  showScenario
 *  Description:  method to show all availablescenarios, under this project--yet
 *  to develop
 * =====================================================================================
 */
void MainWindow::showScenario(){
    //code for displaying scenarios at tab1
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  startSniffing
 *  Description:  start the sniff -- read network packets under the selected interface
 * =====================================================================================
 */

void MainWindow::startSniffing(){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"]\n";
	
	STUB_INT       loop;
	std::string    interfaceName;

#ifdef TESTMODE
	interfaceName = testParameters.interface;
#else
	interfaceName=
	      ui->cmbBoxInterfaces->currentText().toStdString(); // take the STUB_INTerface name frim drop down box
#endif
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"] Selected STUB_INTerface for sniffing is:"
		<<interfaceName<<std::endl;
	loop = 0;
	while ( strcmp ( interfaceList [ ++loop ] , interfaceName.c_str() ) );
	mainWindowThread = boost::thread ( &snif::startSniffing, loop );
	

	//pthread_create(&threadStartSniffing, NULL,
	//		snif::startSniffing, (void *)&i); // the function start sniffing to capture all the TCP level packets , it will be called through anew thread.
	
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  stopSniffing
 *  Description:  stop the sniffing
 * =====================================================================================
 */
void MainWindow::stopSniffing(){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"]\n";

	captureDb::StoreRawPacket    pHandler;

	snif::stopSniffing( ); // stop the sniffing
	mainWindowThread.join();

	/*-----------------------------------------------------------------------------
	 *  update the database table of PACKET_SETTING_ with the query string.
	 *  suppose a raw binary data contains select query, the following codes
	 *  will update the PACKET_SETTING_ table column with the query string.
	 *  it will help to match the incoming query during STUB mode
	 *-----------------------------------------------------------------------------*/
	
	pHandler.updateQueryTypeQueryAtDatabase();
	this->showResult();
	
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  gnPacketFromTcpDump
 *  Description:  if already a TCP dump is available, this method will train the tool
 *  with the help of that dump file's data.
 * =====================================================================================
 */

void MainWindow::genPacketFromTcpDump(){
    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
	    <<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
	    <<__TIME__<<"]\n";

    captureDb::StoreRawPacket    pHandler;
    std::string                  fileName;


    QApplication::setOverrideCursor( QCursor ( Qt::WaitCursor ) );


    fileName = testParameters.tcpDumpFile;
    mainWindowThread = boost::thread( &snif::analysisFromFile , 
		    fileName );
    mainWindowThread.join();

	boost::function<bool()> th_func = 
		boost::bind(&captureDb::StoreRawPacket::updateQueryTypeQueryAtDatabase, 
				&pHandler);
	boost::thread th(th_func);
	th.join();
	mainWindowThread= 
		boost::thread( &QApplication::restoreOverrideCursor);//();
	mainWindowThread.join();

	this->showResult();
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  showResult
 *  Description:  after completion of capturing network packets and storing into database
 *  all the packets will be displaied into a Qt table widget.
 * =====================================================================================
 */

void MainWindow::showResult(){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"]\n";

	ui->frmPacketSetting->setVisible( true );
	ui->frmPacket->setVisible( false );
	db = QSqlDatabase::addDatabase( "QSQLITE" );
	db.setDatabaseName( ( QString) ( dbCredentials.databasePath+"/" + 
				dbCredentials.databaseName + ".db").c_str());
	if( !db.open() ){
		qDebug() << db.lastError();
		qFatal( "Failed to connect." );
		
	}
	qDebug()<<db.databaseName();
	qDebug( "Connected!" );
	QSqlQuery qry;
	model = new QSqlTableModel( this , db );
	model->setTable( (QString)
			("PACKET_SETTING_"+scenInfo.scenarioName).c_str()) ; // replace by PACKET_SETTING + scen_info.scenarioname;
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


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  showPackets
 *  Description:  show all conversations after selecting a conversation id
 * =====================================================================================
 */
void MainWindow::showPackets( const QModelIndex &modelIndex ){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"]\n";
	
	QSqlQuery          qry;
	QVariant           data;
	QString            text;
	QVariant           value;
	QModelIndex        previous;
	QModelIndexList    selectionL; 
	QString            conversationId; 
	
	conversationId	= "not valid column";
	value = 
		ui->tblViewShowPacketSettings->model()->data( modelIndex , 0 );
	if (!value.isValid()) return ;
	conversationId = value.toString();
	qDebug() << conversationId;
	ui->frmPacketSetting->setVisible( false);
	ui->frmPacket->setVisible ( true );
	QItemSelectionModel *selectionM = 
		ui->tblViewShowPacketSettings->selectionModel();// tableView->selectionModel();
        selectionL = selectionM->selectedIndexes();
	if( selectionL.size() < 1) return;
	previous = selectionL.first();// selectionL.first(); //indexes.first();
	data = model->data(previous);
	text = data.toString();
	//the following code for fetching information from PACKET table
	qDebug()<<db.databaseName();
	qDebug( "Connected!" );
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


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  returnControl
 *  Description:  return control after showing all packets under a particular 
 *                conversation
 * =====================================================================================
 */

void MainWindow::returnControl(){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"]\n";

	ui->frmPacket->setVisible ( false );
	ui->frmPacketSetting->setVisible( true );
	model->clear();
	this->showResult();
	
}

//###########################################!TAB 3!######################
//##########################################!METHODS!####################

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  startServer
 *  Description:  start the dummy server, all the information those are needed 
 *                like IP , PORT must be taken from the GUI.
 * =====================================================================================
 */

void MainWindow::startServer(){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"]\n";

	STUB_INT                sockFd;
	server::DummyServer    *instance;

       try{
	       instance = new server::DummyServer(); //create an object of dummy server
       }
       catch ( std::exception &e ){
	       std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		       <<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		       <<__TIME__<<"] Exception :"<<e.what();
	       exit ( -1 );
       }
       mainWindowThread = boost::thread(boost::bind( &server::DummyServer::createServer, 
			       instance ,ui->lnEditServerIp->text().toStdString() ,
			       ui->lnEditPort->text().toInt()));
       mainWindowThread.join();
       
	sockFd = 0;
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"] :server created sockFdd = "<<sockFd<<std::endl;
	if ( sockFd < -1 ){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"] :cant create server\n";

		// ADD A MSG BOX
		return ;
		
	}
	try{
		delete instance;
	}
	catch ( std::exception &e ){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"] Exception "<<e.what();
		exit ( -1 );
	}

	/*-----------------------------------------------------------------------------
	 *  after creating server on specified port and IP, server must wait for a 
	 *  client to send connection request. A new thred for handling this.
	 *-----------------------------------------------------------------------------*/
	mainWindowThread = boost::thread ( &server::DummyServer::acceptClient );
	mainWindowThread.join();

}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  showPacketsAddNewPackets
 *  Description:  add new packt similar to captured packet type-- this method shows all
 *               packets from PACKET_SETTING_scenarioName
 * =====================================================================================
 */

void MainWindow::showPacketsAddNewPackets(){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
		<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
		<<__TIME__<<"]\n";

	QSqlQuery    qry;

	db = QSqlDatabase::addDatabase( "QSQLITE" );
	db.setDatabaseName( ( QString) ( dbCredentials.databasePath+"/" + 
				dbCredentials.databaseName + ".db").c_str());
	if( !db.open() ){
		qDebug() << db.lastError();
		qFatal( "Failed to connect." );
		
	}
	qDebug()<<db.databaseName();
	qDebug( "Connected!" );
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
		<<"] db.is_open :" <<db.isOpen()<<std::endl;
	try{
		model = new QSqlTableModel( this , db );
		
	}
	catch ( std::exception &e){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"] EXCEPTION:"<<e.what()<<'\n';
	
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


/*-----------------------------------------------------------------------------
 *  global variable-- significance of bad coding ... must be destroid if created.
 *-----------------------------------------------------------------------------*/
createPacketDb::GenarateRawPacket *instance;
actSeriesStruct *tempConversationPackets;


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  addNewpacket
 *  Description:  display all dissected packet information of a conversation in a Json
 *  file... edit that file to insert ,update query & response
 * =====================================================================================
 */

void MainWindow::addNewpacket( const QModelIndex &modelIndex ){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	QString     line;
	QVariant    value;
	STUB_INT    conversationId;

	value 	= 
		ui->tblViewShowPacketSettingsNewPacket->model()->data( modelIndex , 0 );
	if (!value.isValid()) return ;
	conversationId = value.toInt();
	// store the conversation id into a global variable for STUB_INTer method communication
	convserastionIdGlobal = conversationId; 
	try {
		instance = new createPacketDb::GenarateRawPacket(); // variable defined gloabally
	}
	catch ( std::bad_alloc &ba ){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
			<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
			<<__TIME__<<"] Exception:"<<ba.what()<<std::endl;
		exit ( -1 );
	}
	tempConversationPackets =  instance->getChunkPackets( conversationId  ) ; // variable declared gloabally
	//now dissect all packets
        for ( STUB_INT packetNo = 0 ; packetNo <=tempConversationPackets->noOfPacket ; 
			++packetNo ){
		std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
			<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
			<<"] *********DISSECT PACKET ******* " <<packetNo<<'\n';
		///now get the method for dissection
		boost::any_cast< bool ( * )( actRawDataStruct * , STUB_INT , actSeriesStruct *)> 
			( boost::get< boost::any >(proto::Proto::initDissect( "MYSQL" , 0 )) )  
			( &tempConversationPackets->actRawData [ packetNo ] , 
			  tempConversationPackets->actRawData [ packetNo ].length , 
			  tempConversationPackets );
		// Mysql::dissectMysql( &tempConversationPackets->actRawData[ packetNo ] , 
		// tempConversationPackets->actRawData [ packetNo].length );
		
	}
	//write all dissected query for a particular conversation into a JSON file
            Json::JsonHandler::writeDataJson ( &QueryPacket , "../LOG/json.js");
	    //show the JSON file information into the textEditor
	    QFile myFile("../LOG/json.js");
	    myFile.open(QIODevice::ReadOnly);
	    QTextStream textStream(&myFile);
	    line = textStream.readAll();
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

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  generalWorkForInsertUpdate
 *  Description:  some basic work required for insert/update query
 * =====================================================================================
 */

bool MainWindow::genaralWorkForInsertUpdate( void ){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	bool         returnValue;
        queryData    *queryDataArray ;

	writeDataFromQtextToFile();
	Json::JsonHandler::readDataJson ("../LOG/json.js");
	Json::JsonHandler::generateColByColData ( &QueryPacket );

	/*-----------------------------------------------------------------------------
	 *  now dissect all packets, this dissection is for testing--no need in future.
	 *-----------------------------------------------------------------------------*/
//	MAKE JSON TRUE TO INDICATE THAT IT'S NEW PACKET CREATION
	Json::flagForGenerateQuery = true;

	for ( STUB_INT packetNo = 0 ; packetNo <=tempConversationPackets->noOfPacket ;
		       	++packetNo ){
		tempConversationPackets->actRawData [ packetNo].packetNumber = 
			packetNo ; 

		boost::any_cast< bool ( * )( actRawDataStruct * , STUB_INT , 
				actSeriesStruct*)> ( boost::get < boost::any > 
					( proto::Proto::initDissect( "MYSQL" , 0 ) ) ) 
				       	( &tempConversationPackets->actRawData [ packetNo ] , 
					  tempConversationPackets->actRawData [ packetNo ].length ,
					  tempConversationPackets );
	}

	Json::flagForGenerateQuery = false;

	/*-----------------------------------------------------------------------------
	 *  get only the query part and perform insert generated packet
	 *-----------------------------------------------------------------------------*/
        try{
            queryDataArray = new queryData [ 1 ];
            
            }
        catch ( std::bad_alloc &ba ){
		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
			<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"] Exception "
			<<ba.what()<<std::endl;
		exit ( -1 );
        }
	try{
		boost::any_cast< STUB_INT ( * )( actRawDataStruct * , queryData *& , STUB_INT , STUB_INT )> 
			( boost::get < boost::any > ( proto::Proto::initDissect( "MYSQL" , 1 ) ) )  
			( newConversationPack->actRawData ,  queryDataArray , 0 , 0);
		}
		catch ( std::exception &e ){

			std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
				<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
				<<__TIME__<<"]"<<"EXCEPTION:"<<e.what()<<'\n';
			exit ( 0 );
			
		}
		returnValue =  
			instance->insertGeneratedPacket ( newConversationPack ,
			       	queryDataArray  );// && deleteActSeriesStruct ( newConversationPack ) ;-- note was getting segpipe error
		try {
			delete []queryDataArray ;
		}
		catch ( std::exception e ){

			std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__
				<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"
				<<__TIME__<<"] EXCEPTION"<<e.what()<<'\n';
			exit ( 0 );
		}
		return returnValue ;
		
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  cancelQuery
 *  Description:  cancel a query -- no need this query so clean the testWidget
 * =====================================================================================
 */
bool MainWindow::cancelQuery(){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";
	ui->tblViewShowPacketSettings->setVisible( true);
	ui->txtEditQuery->setVisible( false );
	ui->pshBttnCancelQuery->setVisible( false );
	ui->pshBttnUpdateQuery->setVisible( false );
	ui->pshButtnInsertQuery->setVisible( false );
	ui->pshBttnDelete->setVisible( false );
	try{
		delete instance;
		delete []tempConversationPackets;
	}
	catch ( std::exception &e ){

		std::cerr<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
			<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__
			<<"] EXCEPTION:"<<e.what()<<'\n';
		exit ( 0 );
	}
	return true;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  insertQuery
 *  Description:  insert a new created query into sqlite2 database
 * =====================================================================================
 */
bool MainWindow::insertQuery(){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";
    if ( genaralWorkForInsertUpdate( ) )
		errorMessageBox.setText("NEW DATA INSERTED");
	else errorMessageBox.setWindowTitle("ERROR\n");
	if( errorMessageBox.exec() == QMessageBox::Yes){
		//do smthing
		
	}
	MainWindow::cancelQuery(); // to clear the textWidget
	return true;
	
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  updateQuery
 *  Description:  update the existing query with edited reply data.
 * =====================================================================================
 */
bool MainWindow::updateQuery(){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	if ( genaralWorkForInsertUpdate(  ) & 
			instance->deletePacketRegardingConversationId( convserastionIdGlobal) )
		errorMessageBox.setText("NEW DATA UPDATED");
	else 
		errorMessageBox.setWindowTitle("ERROR\n");
	if( errorMessageBox.exec() == QMessageBox::Yes){
		//do smthing
		
	}
	MainWindow::cancelQuery();
	return true;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  writeDataFromQtextToFile
 *  Description:  write data from QText to the json file
 * =====================================================================================
 */
bool MainWindow::writeDataFromQtextToFile(){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

	std::string   fileName;   

	fileName ="../LOG/json.js";
	if ( fileName != "") {
		QFile file( fileName.c_str());
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

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  deleteQuery
 *  Description:  permanently delete the query packets.
 * =====================================================================================
 */
bool MainWindow::deleteQuery(){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

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


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ~MainWindow
 *  Description:  dissector
 * =====================================================================================
 */
MainWindow::~MainWindow(){

	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["
		<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]\n";

//	mainWindowThread = boost::thread ( &finishingTouch );// a methd to deallocate memory when exiting the programm
//	mainWindowThread.join();
	

	 delete ui;
//	 delete instance;
	 
}

