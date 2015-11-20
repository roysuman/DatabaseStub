#include "adddbserver.h"
#include "ui_adddbserver.h"

AddDbServer::AddDbServer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddDbServer)
{

    ui->setupUi(this);
   // ui->pshButtonSave->hide();
    ui->lnEditServerIp->setInputMask( "000.000.000.000 ; _" );
    ui->lnEditServerName->show();

    connect ( ui->pshButtonSave , SIGNAL ( clicked() ) ,SLOT ( save() ) );
    connect ( ui->pshButtonCancel , SIGNAL ( clicked () ) , SLOT ( cancel() ) );

}


void AddDbServer::save(){
    if (  ( ui->lnEditServerName->text() != "" ) || ( ui->lnEditServerType->text() != "" )  || ( ui->lnEditServerIp->text() != "") || ( ui->lnEditServerPort->text() != "")){
        errorMessageBox.setText(" PROVIDE ALL INFORMATION !");
        errorMessageBox.setWindowTitle("ERROR");

        if( errorMessageBox.exec() == QMessageBox::Yes){
          // do something
        }else {
          // do something else
        }

    }

}

void AddDbServer::cancel(){
    AddDbServer::close();
}


AddDbServer::~AddDbServer()
{
    delete ui;
}
