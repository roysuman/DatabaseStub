/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed May 14 22:00:47 2014
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QFrame>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QScrollBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTableView>
#include <QtGui/QTextBrowser>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNewproject;
    QAction *actionOpenProject;
    QAction *actionQuit;
    QAction *action_New_Project;
    QAction *action_Save_Project;
    QAction *actionExit;
    QAction *action_Open_Project;
    QAction *actionAdd_Db_Server;
    QAction *actionAdd_App_Server;
    QWidget *centralWidget;
    QFrame *line_4;
    QTabWidget *tabWidget;
    QWidget *tab_3;
    QLabel *lblInterfaceList_2;
    QFrame *line_3;
    QFrame *line_5;
    QFrame *line_2;
    QFrame *line;
    QTextBrowser *txtBrowserInterface;
    QWidget *tab_4;
    QGroupBox *groupBox;
    QLabel *lblScenarioName;
    QLabel *lblCatagory;
    QLabel *lblProtocol;
    QLabel *lblServer;
    QLineEdit *lneEditScenarioName;
    QLineEdit *lneEditCatagory;
    QLineEdit *lneEditProtocol;
    QFrame *line_6;
    QLineEdit *lneEditServer;
    QLabel *lblPortNo;
    QLineEdit *lneEditPortNo;
    QFrame *line_7;
    QFrame *line_8;
    QFrame *line_9;
    QFrame *line_10;
    QFrame *line_11;
    QFrame *line_12;
    QPushButton *pshButtonSaveScenariocredentials;
    QPushButton *pshBtnGenDataFromTcpDump;
    QGroupBox *grpBoxStartSniffing;
    QLabel *label_6;
    QFrame *line_13;
    QFrame *line_14;
    QComboBox *cmbBoxInterfaces;
    QPushButton *pshButtonStartSniffing;
    QFrame *line_15;
    QFrame *line_16;
    QPushButton *pshButtonStopSniffing;
    QFrame *line_17;
    QFrame *line_18;
    QFrame *line_19;
    QFrame *frmPacketSetting;
    QTableView *tblViewShowPacketSettings;
    QScrollBar *horizontalScrollBar;
    QFrame *frmPacket;
    QTableView *tblViewPacket;
    QPushButton *pshButtonReturnPacketSetting;
    QPushButton *pushButton;
    QWidget *tab;
    QFrame *frmStartServer;
    QLabel *lblSelectScenario;
    QPushButton *pshButtonStartServer;
    QLabel *lblServerIp;
    QLabel *lblPOrt;
    QLineEdit *lnEditPort;
    QLineEdit *lnEditScenarioname;
    QLineEdit *lnEditServerIp;
    QFrame *line_20;
    QFrame *frmServerResult;
    QTableView *tblViewShowPacketSettingsNewPacket;
    QTextEdit *txtEditQuery;
    QPushButton *pshBttnCancelQuery;
    QPushButton *pshBttnUpdateQuery;
    QPushButton *pshButtnInsertQuery;
    QPushButton *pshBttnDelete;
    QFrame *frmStopServer;
    QPushButton *pshButtonSttopServer;
    QLabel *lblIncomingPacketNumbers;
    QLabel *lblOutgoingPacketsNumber;
    QLineEdit *lnEditIncomingPacketNumber;
    QLineEdit *lnEditOutgoingPacketNumber;
    QPushButton *pshButtonDissectPackets;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QMenuBar *menuBar;
    QMenu *menu_File;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1077, 687);
        actionNewproject = new QAction(MainWindow);
        actionNewproject->setObjectName(QString::fromUtf8("actionNewproject"));
        actionOpenProject = new QAction(MainWindow);
        actionOpenProject->setObjectName(QString::fromUtf8("actionOpenProject"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        action_New_Project = new QAction(MainWindow);
        action_New_Project->setObjectName(QString::fromUtf8("action_New_Project"));
        action_Save_Project = new QAction(MainWindow);
        action_Save_Project->setObjectName(QString::fromUtf8("action_Save_Project"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        action_Open_Project = new QAction(MainWindow);
        action_Open_Project->setObjectName(QString::fromUtf8("action_Open_Project"));
        actionAdd_Db_Server = new QAction(MainWindow);
        actionAdd_Db_Server->setObjectName(QString::fromUtf8("actionAdd_Db_Server"));
        actionAdd_App_Server = new QAction(MainWindow);
        actionAdd_App_Server->setObjectName(QString::fromUtf8("actionAdd_App_Server"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        line_4 = new QFrame(centralWidget);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setGeometry(QRect(0, -17, 761, 20));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 981, 581));
        tabWidget->setMaximumSize(QSize(981, 581));
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        lblInterfaceList_2 = new QLabel(tab_3);
        lblInterfaceList_2->setObjectName(QString::fromUtf8("lblInterfaceList_2"));
        lblInterfaceList_2->setGeometry(QRect(30, 10, 111, 21));
        lblInterfaceList_2->setMaximumSize(QSize(241, 16777215));
        lblInterfaceList_2->setFrameShape(QFrame::StyledPanel);
        lblInterfaceList_2->setTextFormat(Qt::LogText);
        line_3 = new QFrame(tab_3);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(0, 0, 761, 21));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);
        line_5 = new QFrame(tab_3);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setGeometry(QRect(413, 110, 20, 431));
        line_5->setFrameShape(QFrame::VLine);
        line_5->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(tab_3);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(0, 200, 751, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        line = new QFrame(tab_3);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(150, 10, 31, 411));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        txtBrowserInterface = new QTextBrowser(tab_3);
        txtBrowserInterface->setObjectName(QString::fromUtf8("txtBrowserInterface"));
        txtBrowserInterface->setGeometry(QRect(20, 40, 121, 151));
        txtBrowserInterface->setMouseTracking(false);
        txtBrowserInterface->setAutoFillBackground(true);
        txtBrowserInterface->setFrameShape(QFrame::Box);
        txtBrowserInterface->setLineWidth(2);
        txtBrowserInterface->setMidLineWidth(1);
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        groupBox = new QGroupBox(tab_4);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 261, 551));
        lblScenarioName = new QLabel(groupBox);
        lblScenarioName->setObjectName(QString::fromUtf8("lblScenarioName"));
        lblScenarioName->setGeometry(QRect(10, 30, 101, 41));
        lblCatagory = new QLabel(groupBox);
        lblCatagory->setObjectName(QString::fromUtf8("lblCatagory"));
        lblCatagory->setGeometry(QRect(10, 90, 111, 41));
        lblProtocol = new QLabel(groupBox);
        lblProtocol->setObjectName(QString::fromUtf8("lblProtocol"));
        lblProtocol->setGeometry(QRect(10, 160, 101, 41));
        lblServer = new QLabel(groupBox);
        lblServer->setObjectName(QString::fromUtf8("lblServer"));
        lblServer->setGeometry(QRect(10, 214, 91, 41));
        lneEditScenarioName = new QLineEdit(groupBox);
        lneEditScenarioName->setObjectName(QString::fromUtf8("lneEditScenarioName"));
        lneEditScenarioName->setGeometry(QRect(111, 37, 131, 31));
        lneEditCatagory = new QLineEdit(groupBox);
        lneEditCatagory->setObjectName(QString::fromUtf8("lneEditCatagory"));
        lneEditCatagory->setGeometry(QRect(113, 94, 131, 31));
        lneEditProtocol = new QLineEdit(groupBox);
        lneEditProtocol->setObjectName(QString::fromUtf8("lneEditProtocol"));
        lneEditProtocol->setGeometry(QRect(114, 160, 131, 31));
        line_6 = new QFrame(groupBox);
        line_6->setObjectName(QString::fromUtf8("line_6"));
        line_6->setGeometry(QRect(103, 30, 20, 311));
        line_6->setFrameShape(QFrame::VLine);
        line_6->setFrameShadow(QFrame::Sunken);
        lneEditServer = new QLineEdit(groupBox);
        lneEditServer->setObjectName(QString::fromUtf8("lneEditServer"));
        lneEditServer->setGeometry(QRect(113, 220, 131, 31));
        lblPortNo = new QLabel(groupBox);
        lblPortNo->setObjectName(QString::fromUtf8("lblPortNo"));
        lblPortNo->setGeometry(QRect(12, 272, 91, 41));
        lneEditPortNo = new QLineEdit(groupBox);
        lneEditPortNo->setObjectName(QString::fromUtf8("lneEditPortNo"));
        lneEditPortNo->setGeometry(QRect(112, 272, 131, 31));
        line_7 = new QFrame(groupBox);
        line_7->setObjectName(QString::fromUtf8("line_7"));
        line_7->setGeometry(QRect(10, 250, 241, 16));
        line_7->setFrameShape(QFrame::HLine);
        line_7->setFrameShadow(QFrame::Sunken);
        line_8 = new QFrame(groupBox);
        line_8->setObjectName(QString::fromUtf8("line_8"));
        line_8->setGeometry(QRect(10, 200, 241, 16));
        line_8->setFrameShape(QFrame::HLine);
        line_8->setFrameShadow(QFrame::Sunken);
        line_9 = new QFrame(groupBox);
        line_9->setObjectName(QString::fromUtf8("line_9"));
        line_9->setGeometry(QRect(0, 140, 241, 16));
        line_9->setFrameShape(QFrame::HLine);
        line_9->setFrameShadow(QFrame::Sunken);
        line_10 = new QFrame(groupBox);
        line_10->setObjectName(QString::fromUtf8("line_10"));
        line_10->setGeometry(QRect(10, 70, 241, 16));
        line_10->setFrameShape(QFrame::HLine);
        line_10->setFrameShadow(QFrame::Sunken);
        line_11 = new QFrame(groupBox);
        line_11->setObjectName(QString::fromUtf8("line_11"));
        line_11->setGeometry(QRect(0, 320, 241, 16));
        line_11->setFrameShape(QFrame::HLine);
        line_11->setFrameShadow(QFrame::Sunken);
        line_12 = new QFrame(groupBox);
        line_12->setObjectName(QString::fromUtf8("line_12"));
        line_12->setGeometry(QRect(10, 24, 251, 16));
        line_12->setFrameShape(QFrame::HLine);
        line_12->setFrameShadow(QFrame::Sunken);
        pshButtonSaveScenariocredentials = new QPushButton(groupBox);
        pshButtonSaveScenariocredentials->setObjectName(QString::fromUtf8("pshButtonSaveScenariocredentials"));
        pshButtonSaveScenariocredentials->setGeometry(QRect(60, 352, 111, 51));
        pshBtnGenDataFromTcpDump = new QPushButton(groupBox);
        pshBtnGenDataFromTcpDump->setObjectName(QString::fromUtf8("pshBtnGenDataFromTcpDump"));
        pshBtnGenDataFromTcpDump->setGeometry(QRect(30, 430, 221, 91));
        grpBoxStartSniffing = new QGroupBox(tab_4);
        grpBoxStartSniffing->setObjectName(QString::fromUtf8("grpBoxStartSniffing"));
        grpBoxStartSniffing->setGeometry(QRect(260, 0, 691, 531));
        label_6 = new QLabel(grpBoxStartSniffing);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 40, 91, 31));
        line_13 = new QFrame(grpBoxStartSniffing);
        line_13->setObjectName(QString::fromUtf8("line_13"));
        line_13->setGeometry(QRect(0, 20, 701, 16));
        line_13->setFrameShape(QFrame::HLine);
        line_13->setFrameShadow(QFrame::Sunken);
        line_14 = new QFrame(grpBoxStartSniffing);
        line_14->setObjectName(QString::fromUtf8("line_14"));
        line_14->setGeometry(QRect(0, 70, 701, 16));
        line_14->setFrameShape(QFrame::HLine);
        line_14->setFrameShadow(QFrame::Sunken);
        cmbBoxInterfaces = new QComboBox(grpBoxStartSniffing);
        cmbBoxInterfaces->setObjectName(QString::fromUtf8("cmbBoxInterfaces"));
        cmbBoxInterfaces->setGeometry(QRect(130, 32, 201, 41));
        pshButtonStartSniffing = new QPushButton(grpBoxStartSniffing);
        pshButtonStartSniffing->setObjectName(QString::fromUtf8("pshButtonStartSniffing"));
        pshButtonStartSniffing->setGeometry(QRect(380, 30, 141, 41));
        line_15 = new QFrame(grpBoxStartSniffing);
        line_15->setObjectName(QString::fromUtf8("line_15"));
        line_15->setGeometry(QRect(350, 20, 20, 61));
        line_15->setFrameShape(QFrame::VLine);
        line_15->setFrameShadow(QFrame::Sunken);
        line_16 = new QFrame(grpBoxStartSniffing);
        line_16->setObjectName(QString::fromUtf8("line_16"));
        line_16->setGeometry(QRect(523, 30, 20, 51));
        line_16->setFrameShape(QFrame::VLine);
        line_16->setFrameShadow(QFrame::Sunken);
        pshButtonStopSniffing = new QPushButton(grpBoxStartSniffing);
        pshButtonStopSniffing->setObjectName(QString::fromUtf8("pshButtonStopSniffing"));
        pshButtonStopSniffing->setGeometry(QRect(550, 30, 131, 41));
        line_17 = new QFrame(grpBoxStartSniffing);
        line_17->setObjectName(QString::fromUtf8("line_17"));
        line_17->setGeometry(QRect(0, 30, 20, 51));
        line_17->setFrameShape(QFrame::VLine);
        line_17->setFrameShadow(QFrame::Sunken);
        line_18 = new QFrame(grpBoxStartSniffing);
        line_18->setObjectName(QString::fromUtf8("line_18"));
        line_18->setGeometry(QRect(680, 30, 20, 51));
        line_18->setFrameShape(QFrame::VLine);
        line_18->setFrameShadow(QFrame::Sunken);
        line_19 = new QFrame(grpBoxStartSniffing);
        line_19->setObjectName(QString::fromUtf8("line_19"));
        line_19->setGeometry(QRect(0, 80, 701, 16));
        line_19->setFrameShape(QFrame::HLine);
        line_19->setFrameShadow(QFrame::Sunken);
        frmPacketSetting = new QFrame(grpBoxStartSniffing);
        frmPacketSetting->setObjectName(QString::fromUtf8("frmPacketSetting"));
        frmPacketSetting->setGeometry(QRect(10, 20, 691, 461));
        frmPacketSetting->setFrameShape(QFrame::StyledPanel);
        frmPacketSetting->setFrameShadow(QFrame::Raised);
        tblViewShowPacketSettings = new QTableView(frmPacketSetting);
        tblViewShowPacketSettings->setObjectName(QString::fromUtf8("tblViewShowPacketSettings"));
        tblViewShowPacketSettings->setGeometry(QRect(10, 10, 681, 481));
        horizontalScrollBar = new QScrollBar(frmPacketSetting);
        horizontalScrollBar->setObjectName(QString::fromUtf8("horizontalScrollBar"));
        horizontalScrollBar->setGeometry(QRect(210, 450, 160, 16));
        horizontalScrollBar->setOrientation(Qt::Horizontal);
        frmPacket = new QFrame(tab_4);
        frmPacket->setObjectName(QString::fromUtf8("frmPacket"));
        frmPacket->setGeometry(QRect(280, 30, 821, 501));
        frmPacket->setFrameShape(QFrame::StyledPanel);
        frmPacket->setFrameShadow(QFrame::Raised);
        tblViewPacket = new QTableView(frmPacket);
        tblViewPacket->setObjectName(QString::fromUtf8("tblViewPacket"));
        tblViewPacket->setGeometry(QRect(10, -10, 661, 471));
        pshButtonReturnPacketSetting = new QPushButton(frmPacket);
        pshButtonReturnPacketSetting->setObjectName(QString::fromUtf8("pshButtonReturnPacketSetting"));
        pshButtonReturnPacketSetting->setGeometry(QRect(210, 460, 93, 27));
        pushButton = new QPushButton(frmPacket);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(370, 460, 131, 27));
        tabWidget->addTab(tab_4, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        frmStartServer = new QFrame(tab);
        frmStartServer->setObjectName(QString::fromUtf8("frmStartServer"));
        frmStartServer->setGeometry(QRect(10, 10, 241, 221));
        frmStartServer->setFrameShape(QFrame::StyledPanel);
        frmStartServer->setFrameShadow(QFrame::Raised);
        lblSelectScenario = new QLabel(frmStartServer);
        lblSelectScenario->setObjectName(QString::fromUtf8("lblSelectScenario"));
        lblSelectScenario->setGeometry(QRect(10, 0, 121, 17));
        pshButtonStartServer = new QPushButton(frmStartServer);
        pshButtonStartServer->setObjectName(QString::fromUtf8("pshButtonStartServer"));
        pshButtonStartServer->setGeometry(QRect(30, 180, 161, 31));
        lblServerIp = new QLabel(frmStartServer);
        lblServerIp->setObjectName(QString::fromUtf8("lblServerIp"));
        lblServerIp->setGeometry(QRect(10, 70, 81, 17));
        lblPOrt = new QLabel(frmStartServer);
        lblPOrt->setObjectName(QString::fromUtf8("lblPOrt"));
        lblPOrt->setGeometry(QRect(10, 130, 71, 21));
        lnEditPort = new QLineEdit(frmStartServer);
        lnEditPort->setObjectName(QString::fromUtf8("lnEditPort"));
        lnEditPort->setGeometry(QRect(50, 140, 121, 27));
        lnEditScenarioname = new QLineEdit(frmStartServer);
        lnEditScenarioname->setObjectName(QString::fromUtf8("lnEditScenarioname"));
        lnEditScenarioname->setGeometry(QRect(40, 20, 131, 27));
        lnEditServerIp = new QLineEdit(frmStartServer);
        lnEditServerIp->setObjectName(QString::fromUtf8("lnEditServerIp"));
        lnEditServerIp->setGeometry(QRect(50, 90, 131, 27));
        line_20 = new QFrame(tab);
        line_20->setObjectName(QString::fromUtf8("line_20"));
        line_20->setGeometry(QRect(250, 0, 20, 551));
        line_20->setFrameShape(QFrame::VLine);
        line_20->setFrameShadow(QFrame::Sunken);
        frmServerResult = new QFrame(tab);
        frmServerResult->setObjectName(QString::fromUtf8("frmServerResult"));
        frmServerResult->setGeometry(QRect(280, 90, 681, 441));
        frmServerResult->setFrameShape(QFrame::StyledPanel);
        frmServerResult->setFrameShadow(QFrame::Raised);
        tblViewShowPacketSettingsNewPacket = new QTableView(frmServerResult);
        tblViewShowPacketSettingsNewPacket->setObjectName(QString::fromUtf8("tblViewShowPacketSettingsNewPacket"));
        tblViewShowPacketSettingsNewPacket->setGeometry(QRect(20, 31, 651, 401));
        txtEditQuery = new QTextEdit(frmServerResult);
        txtEditQuery->setObjectName(QString::fromUtf8("txtEditQuery"));
        txtEditQuery->setGeometry(QRect(90, 50, 531, 341));
        pshBttnCancelQuery = new QPushButton(frmServerResult);
        pshBttnCancelQuery->setObjectName(QString::fromUtf8("pshBttnCancelQuery"));
        pshBttnCancelQuery->setGeometry(QRect(240, 400, 93, 27));
        pshBttnUpdateQuery = new QPushButton(frmServerResult);
        pshBttnUpdateQuery->setObjectName(QString::fromUtf8("pshBttnUpdateQuery"));
        pshBttnUpdateQuery->setGeometry(QRect(390, 400, 93, 27));
        pshButtnInsertQuery = new QPushButton(frmServerResult);
        pshButtnInsertQuery->setObjectName(QString::fromUtf8("pshButtnInsertQuery"));
        pshButtnInsertQuery->setGeometry(QRect(530, 400, 93, 27));
        pshBttnDelete = new QPushButton(frmServerResult);
        pshBttnDelete->setObjectName(QString::fromUtf8("pshBttnDelete"));
        pshBttnDelete->setGeometry(QRect(110, 400, 93, 27));
        frmStopServer = new QFrame(tab);
        frmStopServer->setObjectName(QString::fromUtf8("frmStopServer"));
        frmStopServer->setGeometry(QRect(10, 240, 241, 271));
        frmStopServer->setFrameShape(QFrame::StyledPanel);
        frmStopServer->setFrameShadow(QFrame::Raised);
        pshButtonSttopServer = new QPushButton(frmStopServer);
        pshButtonSttopServer->setObjectName(QString::fromUtf8("pshButtonSttopServer"));
        pshButtonSttopServer->setGeometry(QRect(10, 190, 121, 71));
        lblIncomingPacketNumbers = new QLabel(frmStopServer);
        lblIncomingPacketNumbers->setObjectName(QString::fromUtf8("lblIncomingPacketNumbers"));
        lblIncomingPacketNumbers->setGeometry(QRect(10, 20, 121, 17));
        lblOutgoingPacketsNumber = new QLabel(frmStopServer);
        lblOutgoingPacketsNumber->setObjectName(QString::fromUtf8("lblOutgoingPacketsNumber"));
        lblOutgoingPacketsNumber->setGeometry(QRect(11, 80, 111, 17));
        lnEditIncomingPacketNumber = new QLineEdit(frmStopServer);
        lnEditIncomingPacketNumber->setObjectName(QString::fromUtf8("lnEditIncomingPacketNumber"));
        lnEditIncomingPacketNumber->setGeometry(QRect(152, 10, 61, 31));
        lnEditOutgoingPacketNumber = new QLineEdit(frmStopServer);
        lnEditOutgoingPacketNumber->setObjectName(QString::fromUtf8("lnEditOutgoingPacketNumber"));
        lnEditOutgoingPacketNumber->setGeometry(QRect(152, 70, 71, 31));
        pshButtonDissectPackets = new QPushButton(tab);
        pshButtonDissectPackets->setObjectName(QString::fromUtf8("pshButtonDissectPackets"));
        pshButtonDissectPackets->setGeometry(QRect(460, 2, 211, 41));
        tabWidget->addTab(tab, QString());
        MainWindow->setCentralWidget(centralWidget);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1077, 25));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        MainWindow->setMenuBar(menuBar);

        mainToolBar->addSeparator();
        mainToolBar->addAction(actionExit);
        menuBar->addAction(menu_File->menuAction());
        menu_File->addAction(action_New_Project);
        menu_File->addAction(action_Open_Project);
        menu_File->addSeparator();
        menu_File->addAction(actionExit);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "TCP STUB", 0, QApplication::UnicodeUTF8));
        actionNewproject->setText(QApplication::translate("MainWindow", "Newproject", 0, QApplication::UnicodeUTF8));
        actionOpenProject->setText(QApplication::translate("MainWindow", "OpenProject", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0, QApplication::UnicodeUTF8));
        action_New_Project->setText(QApplication::translate("MainWindow", "&New Project", 0, QApplication::UnicodeUTF8));
        action_Save_Project->setText(QApplication::translate("MainWindow", "&Save Project", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindow", "E&xit", 0, QApplication::UnicodeUTF8));
        action_Open_Project->setText(QApplication::translate("MainWindow", "&Open Project", 0, QApplication::UnicodeUTF8));
        actionAdd_Db_Server->setText(QApplication::translate("MainWindow", "Add Db Server", 0, QApplication::UnicodeUTF8));
        actionAdd_App_Server->setText(QApplication::translate("MainWindow", "Add App Server", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        tabWidget->setWhatsThis(QApplication::translate("MainWindow", "<html><head/><body><p>Setting</p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        lblInterfaceList_2->setText(QApplication::translate("MainWindow", "INTERFACE LIST", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Tab 1", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindow", "SETTING", 0, QApplication::UnicodeUTF8));
        lblScenarioName->setText(QApplication::translate("MainWindow", "SCENARIO NAME", 0, QApplication::UnicodeUTF8));
        lblCatagory->setText(QApplication::translate("MainWindow", "CATAGORY", 0, QApplication::UnicodeUTF8));
        lblProtocol->setText(QApplication::translate("MainWindow", "PROTOCOL", 0, QApplication::UnicodeUTF8));
        lblServer->setText(QApplication::translate("MainWindow", "SERVER", 0, QApplication::UnicodeUTF8));
        lblPortNo->setText(QApplication::translate("MainWindow", "PORT NO:", 0, QApplication::UnicodeUTF8));
        pshButtonSaveScenariocredentials->setText(QApplication::translate("MainWindow", "SAVE", 0, QApplication::UnicodeUTF8));
        pshBtnGenDataFromTcpDump->setText(QApplication::translate("MainWindow", "Gen From TCPDUMP", 0, QApplication::UnicodeUTF8));
        grpBoxStartSniffing->setTitle(QApplication::translate("MainWindow", "SNIFFING", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "INTERFACE :", 0, QApplication::UnicodeUTF8));
        pshButtonStartSniffing->setText(QApplication::translate("MainWindow", "START SNIFFING", 0, QApplication::UnicodeUTF8));
        pshButtonStopSniffing->setText(QApplication::translate("MainWindow", "STOP SNIFFING", 0, QApplication::UnicodeUTF8));
        pshButtonReturnPacketSetting->setText(QApplication::translate("MainWindow", "RETURN", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "ADD NEW DATA", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MainWindow", "Tab 2", 0, QApplication::UnicodeUTF8));
        lblSelectScenario->setText(QApplication::translate("MainWindow", "Select Scenario", 0, QApplication::UnicodeUTF8));
        pshButtonStartServer->setText(QApplication::translate("MainWindow", "START SERVER", 0, QApplication::UnicodeUTF8));
        lblServerIp->setText(QApplication::translate("MainWindow", "Server Ip", 0, QApplication::UnicodeUTF8));
        lblPOrt->setText(QApplication::translate("MainWindow", "Port", 0, QApplication::UnicodeUTF8));
        pshBttnCancelQuery->setText(QApplication::translate("MainWindow", "CANCEL", 0, QApplication::UnicodeUTF8));
        pshBttnUpdateQuery->setText(QApplication::translate("MainWindow", "UPDATE", 0, QApplication::UnicodeUTF8));
        pshButtnInsertQuery->setText(QApplication::translate("MainWindow", "INSERT", 0, QApplication::UnicodeUTF8));
        pshBttnDelete->setText(QApplication::translate("MainWindow", "DELETE", 0, QApplication::UnicodeUTF8));
        pshButtonSttopServer->setText(QApplication::translate("MainWindow", "STOP SERVER", 0, QApplication::UnicodeUTF8));
        lblIncomingPacketNumbers->setText(QApplication::translate("MainWindow", "Incoming Packet", 0, QApplication::UnicodeUTF8));
        lblOutgoingPacketsNumber->setText(QApplication::translate("MainWindow", "Outgoing Packet", 0, QApplication::UnicodeUTF8));
        pshButtonDissectPackets->setText(QApplication::translate("MainWindow", "DISSECT PACKET", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Page", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
