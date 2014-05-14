#include "openproject.h"
#include "ui_openproject.h"

openProject::openProject(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::openProject)
{
    ui->setupUi(this);
    ui->setupUi(this);
    //ui->txtLocation->setReadOnly( true );
    connect ( ui->pshBttnBrowse , SIGNAL ( clicked () ) , SLOT ( browse () ));
    connect ( ui->pshBttnOk , SIGNAL ( clicked ()) , SLOT ( ok() ) );
    connect ( ui->pshBttnCancle , SIGNAL ( clicked() ) , SLOT ( cancel() ));

return ;

}

openProject::~openProject()
{
    delete ui;
}



void openProject::browse()
{

    projectName = QFileDialog::getOpenFileName( this ,"Open Project" , "/media/D"   );
    ui->lineEdit->setText(projectName);


}
//
//void openProject::changeEvent(QEvent *e)
//{
//    QDialog::changeEvent(e);
//    switch (e->type()) {
//    case QEvent::LanguageChange:
//        ui->retranslateUi(this);
//        break;
//    default:
//        break;
//    }
//}

void openProject::ok()
{
    dbCreateProject::CreateProject *initializedatabase = new dbCreateProject::CreateProject();
    std::string filePath = ui->lineEdit->text().toStdString(); //ui->txtProjectName->text().toStdString();
   std::string valueTemp = ui->lineEdit->text().toStdString();
   std::string directoryPath;
   std::string databaseName ;
   int pos = 0;
   while ( ( pos = valueTemp.find( "/" ) )  != std::string::npos ){
       directoryPath  = directoryPath + valueTemp.substr ( 0, pos );
       valueTemp.erase ( 0 , pos + 1 ) ;
   }
   databaseName = databaseName + valueTemp.substr ( 0, pos );
   db_credentials.databaseName = databaseName;
   db_credentials.databasePath = directoryPath;
    int rc = sqlite3_open( filePath.c_str() , &db_credentials.db);
    if ( !sqlite3_open( filePath.c_str() , &db_credentials.db) ){
         errorMessageBox.setWindowTitle("PROJECT ERROR");
        errorMessageBox.setText("DATABSE NOT opened !");


        if( errorMessageBox.exec() == QMessageBox::Yes){
          // do something
        }else {
          // do something else
        }
    }
    openProject::close();
    return ;
}

void openProject::cancel()
{
    db_credentials.databaseName = "";
    openProject::close( );
    return ;
}

