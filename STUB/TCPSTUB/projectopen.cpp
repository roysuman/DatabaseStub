#include "projectopen.h"
#include "ui_projectopen.h"

projectOpen::projectOpen(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::projectOpen)
{
    ui->setupUi(this);
    ui->lneEdtBrowseProject->setReadOnly( true );
    connect ( ui->pshBttnBrowse , SIGNAL ( clicked () ) , SLOT ( browse () ));
    connect ( ui->pshBttnOpen, SIGNAL ( clicked ()) , SLOT ( ok() ) );
    connect ( ui->pshBttnCancel , SIGNAL ( clicked() ) , SLOT ( cancel() ));
}

projectOpen::~projectOpen()
{
    delete ui;
}

void projectOpen::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
void projectOpen::browse(){
    fileName =  QFileDialog::getOpenFileName( this ,"Open Directory" , "/media/D" );

    ui->lneEdtBrowseProject->setText( fileName);

}

void projectOpen::ok(){

     std::string filePath = ui->lneEdtBrowseProject->text().toStdString(); //ui->txtProjectName->text().toStdString();
     std::string valueTemp = ui->lneEdtBrowseProject->text().toStdString();
     std::string directoryPath;
     std::string databaseName ;
     int pos = 0;
     while ( ( pos = valueTemp.find( "/" ) )  != std::string::npos ){
         directoryPath  = directoryPath + valueTemp.substr ( 0, pos ) + "/";
         valueTemp.erase ( 0 , pos + 1 ) ;
     }
     databaseName = databaseName + valueTemp.substr ( 0, pos );
     dbCredentials.databaseName = databaseName.substr( 0 , databaseName.find("."));
     dbCredentials.databasePath = directoryPath;
     scenInfo.scenarioName = "q";


      if ( sqlite3_open( filePath.c_str() , &dbCredentials.db) != SQLITE_OK ){
          dbCredentials.databaseName = "";
           errorMessageBox.setWindowTitle("PROJECT ERROR");
          errorMessageBox.setText("DATABSE NOT opened !");


          if( errorMessageBox.exec() == QMessageBox::Yes){
            // do something
          }else {
            // do something else
          }
      }

      projectOpen::close();
      return ;
}

void projectOpen::cancel(){
    dbCredentials.databaseName = "";
    projectOpen::close();
    return;

}
