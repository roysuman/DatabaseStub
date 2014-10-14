#include "generatepacket.h"
#include "ui_generatepacket.h"

GeneratePacket::GeneratePacket(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GeneratePacket){
   // ui->trWidgetDissectedValue->show();

    ui->setupUi(this);
    ui->trWidgetDissectedValue->setColumnCount(2);
    ui->trWidgetDissectedValue->show();

}

GeneratePacket::~GeneratePacket(){
    delete ui;
}



//function to add new packets at database
//it will show the packet at tree view and then you can edit items , and then you will be able to update
//new packet at db
//there we have used dissector.
void GeneratePacket::addNewpacket( STUB_INT conversationId ){
//     std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"conversation ID is"<<conversationId<<std::endl;

//     //after geting conversation ID read the whole conversatio and then dissect
//     //now only considered for mysql dissection.
//     createPacketDb::GenarateRawPacket *instance = new createPacketDb::GenarateRawPacket();
//     actSeriesStruct *tempConversationPackets =  instance->getChunkPackets( conversationId  ) ;
//     std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"no of packets = "<<tempConversationPackets->noOfPacket<<std::endl;
//     //now dissect all packets
//     for ( STUB_INT packetNo = 0 ; packetNo <=tempConversationPackets->noOfPacket ; ++packetNo ){
//         std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"*********DISSECT PACKET ******* " <<packetNo<<std::endl;
//          //now for each packet do dissection and create a new new table.
//         std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"APP_DB"<<tempConversationPackets->actRawData [ packetNo].appServer<<std::endl;
//         std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"DATA ="<<tempConversationPackets->actRawData [ packetNo].data<<"length ="<<tempConversationPackets->actRawData [ packetNo].length<<std::endl;
//          Mysql::dissect_mysql( &tempConversationPackets->actRawData[ packetNo ] , tempConversationPackets->actRawData [ packetNo].length );

//      }
 }


bool GeneratePacket::addRootRow( ){
    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"inside add root row"<<std::endl;
  //QThread::msleep(2);

    item = new QTreeWidgetItem();
    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"suman\n"<<std::endl;
    item->setText(0 , QString("Dissected Part PArt"));
    item->setText(1 , QString("Value"));
    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"roy\n";
   // ui->trWidgetDissectedValue->addTopLevelItem(item);
   // ui->trWidgetDissectedValue->show();

   // return item;
   // ui->trWidgetDissectedValue->show();

    std::cout<<" File Name ["<<__FILE__<<" ] Function [ "<<__FUNCTION__<<"] Line ["<<__LINE__<<"] DateTime ["<<__DATE__<<"_"<<__TIME__<<"]"<<"k";

    return true;

}

bool GeneratePacket::addChild ( QTreeWidgetItem *parrent ,QString column1, QString column2){
    QTreeWidgetItem * childItem = new QTreeWidgetItem();
    childItem->setText( 0 , column1 );
    childItem->setText( 1 , column2 );
    parrent->addChild( childItem );
    return true;
}
