/********************************************************************************
** Form generated from reading UI file 'newproject.ui'
**
** Created: Wed May 14 22:00:47 2014
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWPROJECT_H
#define UI_NEWPROJECT_H

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

class Ui_NewProject
{
public:
    QLabel *lblProjectName;
    QLineEdit *txtProjectName;
    QPushButton *btnOk;
    QPushButton *btnCancel;
    QPushButton *btnBrowse;
    QLineEdit *txtLocation;
    QLabel *LblSaveLocation;

    void setupUi(QDialog *NewProject)
    {
        if (NewProject->objectName().isEmpty())
            NewProject->setObjectName(QString::fromUtf8("NewProject"));
        NewProject->resize(540, 197);
        lblProjectName = new QLabel(NewProject);
        lblProjectName->setObjectName(QString::fromUtf8("lblProjectName"));
        lblProjectName->setGeometry(QRect(10, 40, 91, 16));
        txtProjectName = new QLineEdit(NewProject);
        txtProjectName->setObjectName(QString::fromUtf8("txtProjectName"));
        txtProjectName->setGeometry(QRect(100, 31, 311, 31));
        btnOk = new QPushButton(NewProject);
        btnOk->setObjectName(QString::fromUtf8("btnOk"));
        btnOk->setGeometry(QRect(430, 10, 91, 41));
        btnCancel = new QPushButton(NewProject);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setGeometry(QRect(430, 130, 95, 41));
        btnBrowse = new QPushButton(NewProject);
        btnBrowse->setObjectName(QString::fromUtf8("btnBrowse"));
        btnBrowse->setGeometry(QRect(430, 70, 95, 41));
        txtLocation = new QLineEdit(NewProject);
        txtLocation->setObjectName(QString::fromUtf8("txtLocation"));
        txtLocation->setGeometry(QRect(100, 71, 311, 31));
        LblSaveLocation = new QLabel(NewProject);
        LblSaveLocation->setObjectName(QString::fromUtf8("LblSaveLocation"));
        LblSaveLocation->setGeometry(QRect(10, 80, 91, 16));

        retranslateUi(NewProject);

        QMetaObject::connectSlotsByName(NewProject);
    } // setupUi

    void retranslateUi(QDialog *NewProject)
    {
        NewProject->setWindowTitle(QApplication::translate("NewProject", "Dialog", 0, QApplication::UnicodeUTF8));
        lblProjectName->setText(QApplication::translate("NewProject", "Project Name: ", 0, QApplication::UnicodeUTF8));
        btnOk->setText(QApplication::translate("NewProject", "Ok", 0, QApplication::UnicodeUTF8));
        btnCancel->setText(QApplication::translate("NewProject", "Cancel", 0, QApplication::UnicodeUTF8));
        btnBrowse->setText(QApplication::translate("NewProject", "Browse", 0, QApplication::UnicodeUTF8));
        LblSaveLocation->setText(QApplication::translate("NewProject", "Save Location", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class NewProject: public Ui_NewProject {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWPROJECT_H
