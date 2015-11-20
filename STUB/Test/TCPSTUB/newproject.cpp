#include "newproject.h"
#include "ui_newproject.h"
#include <QFileDialog>

NewProject::NewProject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewProject){
	    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	    ui->setupUi(this);
	    ui->txtLocation->setReadOnly( true );
	    connect ( ui->btnBrowse , SIGNAL ( clicked () ) , SLOT ( browse () ));
	    connect ( ui->btnOk , SIGNAL ( clicked ()) , SLOT ( ok() ) );
	    connect ( ui->btnCancel , SIGNAL ( clicked() ) , SLOT ( cancel() ));
	    return ;
    
    }

NewProject::~NewProject(){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	delete ui;
}

void NewProject::browse(){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"Browse:"<<__FUNCTION__<<std::endl;
	//QFileDialog::getSaveFileName(this,"Create New File",".");
	directoryName = QFileDialog::getExistingDirectory( this ,"Open Directory" , "/media/D" , QFileDialog::ShowDirsOnly  );
	ui->txtLocation->setText( directoryName );

}

void NewProject::ok(){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"FUNCTION:"<<__FUNCTION__<<std::endl;
	dbCreateProject::CreateProject *initializedatabase = new dbCreateProject::CreateProject();
	// dbCredentials.databaseName="test";
	//dbCredentials.databasePath="/home/suman";
	dbCredentials.databaseName = ui->txtProjectName->text().toStdString();
	//    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"Databse name ="<<dbCredentials.databaseName<<std::endl;
	dbCredentials.databasePath = directoryName.toStdString() ;
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<__FUNCTION__<<"Path "<<dbCredentials.databasePath<<std::endl;
	if ( !initializedatabase->createInitDb() ){
		errorMessageBox.setText("DATABSE NOT CREATED !");
		errorMessageBox.setWindowTitle("PROJECT ERROR");
		if( errorMessageBox.exec() == QMessageBox::Yes){
			// do something
			
		}else {
			// do something else
			
		}
		
	}
	delete initializedatabase ;
	NewProject::close();
	return ;
	
}

void NewProject::cancel(){
	std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"Function:"<<__FUNCTION__<<std::endl;
	dbCredentials.databaseName = "";
	NewProject::close( );
	return ;
	
}

