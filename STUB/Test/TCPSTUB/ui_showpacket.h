/********************************************************************************
** Form generated from reading UI file 'showpacket.ui'
**
** Created: Thu Nov 28 12:57:07 2013
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWPACKET_H
#define UI_SHOWPACKET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QTableView>

QT_BEGIN_NAMESPACE

class Ui_showPacket
{
public:
    QTableView *tblViewPacket;

    void setupUi(QDialog *showPacket)
    {
        if (showPacket->objectName().isEmpty())
            showPacket->setObjectName(QString::fromUtf8("showPacket"));
        showPacket->resize(446, 321);
        tblViewPacket = new QTableView(showPacket);
        tblViewPacket->setObjectName(QString::fromUtf8("tblViewPacket"));
        tblViewPacket->setGeometry(QRect(40, 40, 351, 251));

        retranslateUi(showPacket);

        QMetaObject::connectSlotsByName(showPacket);
    } // setupUi

    void retranslateUi(QDialog *showPacket)
    {
        showPacket->setWindowTitle(QApplication::translate("showPacket", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class showPacket: public Ui_showPacket {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWPACKET_H
