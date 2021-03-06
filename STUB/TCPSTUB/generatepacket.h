#ifndef GENERATEPACKET_H
#define GENERATEPACKET_H

#include <QDialog>
#include <QStandardItemModel>
#include <QTreeWidgetItem>

#include <QtSql/QtSql>
#include "../DBLAYER/capture_packet_db.hpp"
#include "../DBLAYER/create_project_db.hpp"
#include "../DBLAYER/dummy_server_db.hpp"
#include"../DBLAYER/newpacketDb.hpp"
#include "../STRUCTURE/include/database_structure.hpp"
#include "../CORE/STUB/include/server.hpp"
#include"../CORE/DISSECTOR/include/proto_mysql.hpp"


namespace Ui {
class GeneratePacket;
}

class GeneratePacket : public QDialog
{

    Q_OBJECT
   //  bool addRootRow( );

  //  bool addChild ( QTreeWidgetItem * ,QString , QString );




    
public:


  QTreeWidgetItem * item;
    void addNewpacket ( STUB_INT );
     bool addRootRow();
     bool addChild( QTreeWidgetItem *, QString , QString );


    explicit GeneratePacket(QWidget *parent = 0);
    ~GeneratePacket();



private:
         Ui::GeneratePacket *ui;





};

#endif // GENERATEPACKET_H
