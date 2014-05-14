#include "newpacket.h"
#include "ui_newpacket.h"

newPacket::newPacket(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newPacket)
{
    ui->setupUi(this);
}

newPacket::~newPacket()
{
    delete ui;
}

//void newPacket::changeEvent(QEvent *e)
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
