/********************************************************************************
** Form generated from reading UI file 'newpacket.ui'
**
** Created: Mon Dec 9 13:07:26 2013
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWPACKET_H
#define UI_NEWPACKET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QTreeWidget>

QT_BEGIN_NAMESPACE

class Ui_newPacket
{
public:
    QFrame *frmNewPacketAdd;
    QTreeWidget *trWidgetAddPacket;

    void setupUi(QDialog *newPacket)
    {
        if (newPacket->objectName().isEmpty())
            newPacket->setObjectName(QString::fromUtf8("newPacket"));
        newPacket->resize(400, 300);
        frmNewPacketAdd = new QFrame(newPacket);
        frmNewPacketAdd->setObjectName(QString::fromUtf8("frmNewPacketAdd"));
        frmNewPacketAdd->setGeometry(QRect(30, 30, 331, 241));
        frmNewPacketAdd->setFrameShape(QFrame::StyledPanel);
        frmNewPacketAdd->setFrameShadow(QFrame::Raised);
        trWidgetAddPacket = new QTreeWidget(frmNewPacketAdd);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        trWidgetAddPacket->setHeaderItem(__qtreewidgetitem);
        trWidgetAddPacket->setObjectName(QString::fromUtf8("trWidgetAddPacket"));
        trWidgetAddPacket->setGeometry(QRect(10, 10, 301, 201));

        retranslateUi(newPacket);

        QMetaObject::connectSlotsByName(newPacket);
    } // setupUi

    void retranslateUi(QDialog *newPacket)
    {
        newPacket->setWindowTitle(QApplication::translate("newPacket", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class newPacket: public Ui_newPacket {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWPACKET_H
