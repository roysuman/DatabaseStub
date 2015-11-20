/********************************************************************************
** Form generated from reading UI file 'openproject.ui'
**
** Created: Fri Mar 14 15:34:54 2014
**      by: Qt User Interface Compiler version 4.6.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPENPROJECT_H
#define UI_OPENPROJECT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_openProject
{
public:
    QLineEdit *lineEdit;
    QPushButton *pshBttnBrowse;
    QPushButton *pshBttnOk;
    QPushButton *pshBttnCancle;
    QLabel *label;

    void setupUi(QDialog *openProject)
    {
        if (openProject->objectName().isEmpty())
            openProject->setObjectName(QString::fromUtf8("openProject"));
        openProject->resize(400, 300);
        lineEdit = new QLineEdit(openProject);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(100, 110, 201, 27));
        pshBttnBrowse = new QPushButton(openProject);
        pshBttnBrowse->setObjectName(QString::fromUtf8("pshBttnBrowse"));
        pshBttnBrowse->setGeometry(QRect(300, 90, 100, 27));
        pshBttnOk = new QPushButton(openProject);
        pshBttnOk->setObjectName(QString::fromUtf8("pshBttnOk"));
        pshBttnOk->setGeometry(QRect(240, 150, 93, 27));
        pshBttnCancle = new QPushButton(openProject);
        pshBttnCancle->setObjectName(QString::fromUtf8("pshBttnCancle"));
        pshBttnCancle->setGeometry(QRect(80, 160, 93, 27));
        label = new QLabel(openProject);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 100, 100, 17));

        retranslateUi(openProject);

        QMetaObject::connectSlotsByName(openProject);
    } // setupUi

    void retranslateUi(QDialog *openProject)
    {
        openProject->setWindowTitle(QApplication::translate("openProject", "Dialog", 0, QApplication::UnicodeUTF8));
        pshBttnBrowse->setText(QApplication::translate("openProject", "Browse", 0, QApplication::UnicodeUTF8));
        pshBttnOk->setText(QApplication::translate("openProject", "Ok", 0, QApplication::UnicodeUTF8));
        pshBttnCancle->setText(QApplication::translate("openProject", "cancel", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("openProject", "Project Name:", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class openProject: public Ui_openProject {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPENPROJECT_H
