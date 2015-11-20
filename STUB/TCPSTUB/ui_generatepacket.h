/********************************************************************************
** Form generated from reading UI file 'generatepacket.ui'
**
** Created: Mon Mar 10 09:18:04 2014
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERATEPACKET_H
#define UI_GENERATEPACKET_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QFrame>
#include <QtGui/QHeaderView>
#include <QtGui/QTreeWidget>

QT_BEGIN_NAMESPACE

class Ui_GeneratePacket
{
public:
    QFrame *frmAddPacket;
    QTreeWidget *trWidgetDissectedValue;

    void setupUi(QDialog *GeneratePacket)
    {
        if (GeneratePacket->objectName().isEmpty())
            GeneratePacket->setObjectName(QString::fromUtf8("GeneratePacket"));
        GeneratePacket->resize(736, 475);
        frmAddPacket = new QFrame(GeneratePacket);
        frmAddPacket->setObjectName(QString::fromUtf8("frmAddPacket"));
        frmAddPacket->setGeometry(QRect(40, 30, 351, 431));
        frmAddPacket->setFrameShape(QFrame::StyledPanel);
        frmAddPacket->setFrameShadow(QFrame::Raised);
        trWidgetDissectedValue = new QTreeWidget(frmAddPacket);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QString::fromUtf8("1"));
        trWidgetDissectedValue->setHeaderItem(__qtreewidgetitem);
        trWidgetDissectedValue->setObjectName(QString::fromUtf8("trWidgetDissectedValue"));
        trWidgetDissectedValue->setGeometry(QRect(20, 10, 321, 331));

        retranslateUi(GeneratePacket);

        QMetaObject::connectSlotsByName(GeneratePacket);
    } // setupUi

    void retranslateUi(QDialog *GeneratePacket)
    {
        GeneratePacket->setWindowTitle(QApplication::translate("GeneratePacket", "Dialog", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class GeneratePacket: public Ui_GeneratePacket {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATEPACKET_H
