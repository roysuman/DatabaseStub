/********************************************************************************
** Form generated from reading UI file 'adddbserver.ui'
**
** Created: Wed May 14 22:00:47 2014
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDDBSERVER_H
#define UI_ADDDBSERVER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTreeView>

QT_BEGIN_NAMESPACE

class Ui_AddDbServer
{
public:
    QPushButton *pshButtonSave;
    QPushButton *pshButtonCancel;
    QLineEdit *lnEditServerName;
    QLineEdit *lnEditServerType;
    QLineEdit *lnEditServerIp;
    QLineEdit *lnEditServerPort;
    QLabel *lblServername;
    QLabel *lblServerType;
    QLabel *lblServerIp;
    QLabel *LblServerPort;
    QTreeView *treeView;

    void setupUi(QDialog *AddDbServer)
    {
        if (AddDbServer->objectName().isEmpty())
            AddDbServer->setObjectName(QString::fromUtf8("AddDbServer"));
        AddDbServer->resize(469, 300);
        pshButtonSave = new QPushButton(AddDbServer);
        pshButtonSave->setObjectName(QString::fromUtf8("pshButtonSave"));
        pshButtonSave->setGeometry(QRect(170, 240, 95, 23));
        pshButtonCancel = new QPushButton(AddDbServer);
        pshButtonCancel->setObjectName(QString::fromUtf8("pshButtonCancel"));
        pshButtonCancel->setGeometry(QRect(300, 240, 95, 23));
        lnEditServerName = new QLineEdit(AddDbServer);
        lnEditServerName->setObjectName(QString::fromUtf8("lnEditServerName"));
        lnEditServerName->setGeometry(QRect(200, 30, 113, 22));
        lnEditServerType = new QLineEdit(AddDbServer);
        lnEditServerType->setObjectName(QString::fromUtf8("lnEditServerType"));
        lnEditServerType->setGeometry(QRect(200, 70, 113, 22));
        lnEditServerIp = new QLineEdit(AddDbServer);
        lnEditServerIp->setObjectName(QString::fromUtf8("lnEditServerIp"));
        lnEditServerIp->setGeometry(QRect(200, 130, 113, 22));
        lnEditServerPort = new QLineEdit(AddDbServer);
        lnEditServerPort->setObjectName(QString::fromUtf8("lnEditServerPort"));
        lnEditServerPort->setGeometry(QRect(200, 190, 113, 22));
        lblServername = new QLabel(AddDbServer);
        lblServername->setObjectName(QString::fromUtf8("lblServername"));
        lblServername->setGeometry(QRect(60, 30, 91, 16));
        lblServerType = new QLabel(AddDbServer);
        lblServerType->setObjectName(QString::fromUtf8("lblServerType"));
        lblServerType->setGeometry(QRect(60, 70, 101, 20));
        lblServerIp = new QLabel(AddDbServer);
        lblServerIp->setObjectName(QString::fromUtf8("lblServerIp"));
        lblServerIp->setGeometry(QRect(60, 130, 81, 16));
        LblServerPort = new QLabel(AddDbServer);
        LblServerPort->setObjectName(QString::fromUtf8("LblServerPort"));
        LblServerPort->setGeometry(QRect(60, 190, 111, 16));
        treeView = new QTreeView(AddDbServer);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        treeView->setGeometry(QRect(180, 60, 256, 192));

        retranslateUi(AddDbServer);

        QMetaObject::connectSlotsByName(AddDbServer);
    } // setupUi

    void retranslateUi(QDialog *AddDbServer)
    {
        AddDbServer->setWindowTitle(QApplication::translate("AddDbServer", "ADD DB SERVER ITEM", 0, QApplication::UnicodeUTF8));
        pshButtonSave->setText(QApplication::translate("AddDbServer", "SAVE", 0, QApplication::UnicodeUTF8));
        pshButtonCancel->setText(QApplication::translate("AddDbServer", "CANCEL", 0, QApplication::UnicodeUTF8));
        lblServername->setText(QApplication::translate("AddDbServer", "Server Name", 0, QApplication::UnicodeUTF8));
        lblServerType->setText(QApplication::translate("AddDbServer", "Server Type", 0, QApplication::UnicodeUTF8));
        lblServerIp->setText(QApplication::translate("AddDbServer", "Server Ip ", 0, QApplication::UnicodeUTF8));
        LblServerPort->setText(QApplication::translate("AddDbServer", "Server Port", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AddDbServer: public Ui_AddDbServer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDDBSERVER_H
