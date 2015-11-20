/********************************************************************************
** Form generated from reading UI file 'projectopen.ui'
**
** Created: Wed May 14 22:00:47 2014
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECTOPEN_H
#define UI_PROJECTOPEN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_projectOpen
{
public:
    QPushButton *pshBttnBrowse;
    QPushButton *pshBttnOpen;
    QLineEdit *lneEdtBrowseProject;
    QPushButton *pshBttnCancel;

    void setupUi(QDialog *projectOpen)
    {
        if (projectOpen->objectName().isEmpty())
            projectOpen->setObjectName(QString::fromUtf8("projectOpen"));
        projectOpen->resize(485, 300);
        pshBttnBrowse = new QPushButton(projectOpen);
        pshBttnBrowse->setObjectName(QString::fromUtf8("pshBttnBrowse"));
        pshBttnBrowse->setGeometry(QRect(390, 90, 93, 27));
        pshBttnOpen = new QPushButton(projectOpen);
        pshBttnOpen->setObjectName(QString::fromUtf8("pshBttnOpen"));
        pshBttnOpen->setGeometry(QRect(290, 140, 93, 27));
        lneEdtBrowseProject = new QLineEdit(projectOpen);
        lneEdtBrowseProject->setObjectName(QString::fromUtf8("lneEdtBrowseProject"));
        lneEdtBrowseProject->setGeometry(QRect(130, 90, 261, 27));
        pshBttnCancel = new QPushButton(projectOpen);
        pshBttnCancel->setObjectName(QString::fromUtf8("pshBttnCancel"));
        pshBttnCancel->setGeometry(QRect(150, 140, 93, 27));

        retranslateUi(projectOpen);

        QMetaObject::connectSlotsByName(projectOpen);
    } // setupUi

    void retranslateUi(QDialog *projectOpen)
    {
        projectOpen->setWindowTitle(QApplication::translate("projectOpen", "Dialog", 0, QApplication::UnicodeUTF8));
        pshBttnBrowse->setText(QApplication::translate("projectOpen", "Browse", 0, QApplication::UnicodeUTF8));
        pshBttnOpen->setText(QApplication::translate("projectOpen", "Open", 0, QApplication::UnicodeUTF8));
        pshBttnCancel->setText(QApplication::translate("projectOpen", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class projectOpen: public Ui_projectOpen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECTOPEN_H
