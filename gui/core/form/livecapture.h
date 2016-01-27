/*
 * =====================================================================================
 *
 *       Filename:  livecapture.h
 *
 *    Description:  live capture window
 *
 *        Version:  1.0
 *        Created:  Tuesday 26 January 2016 08:37:51  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  SIGCONT (suman roy), email.suman.roy@gmail.com
 *   Organization:  OPEN SOURCE
 *
 * =====================================================================================
 */
#ifndef LIVE_CAPTURE_H
#define LIVE_CAPTURE_H

#include <QFile>
#include<QDialog>
#include<QFileDialog>
#include<QTreeWidgetItem>
#include<QString>
#include <QDir>
#include<cstring>
#include<iostream>
#include "gui/forms/CustomWindow.h"
#include "./gui/core/controls/messagebox.h"
//#include "ui_liveCaptureDialog.h"
#include "ui_livecapture.h"

class LiveCapture: public BaseWindow<QDialog>, Ui::liveCaptureDialog{
	Q_OBJECT
	public:
		LiveCapture( QWidget* parent=0);
		virtual ~LiveCapture( void);
		int exec( void);
	private:
		QPushButton*    get_close_btn( void) override;
		QWidget*        get_title_bar( void) override;
		QWidget*	central_widget( void) override;
		QLabel*		get_title_label( void) override;
		QLabel*		get_title_icon( void) override;
		void 		setup_actions( void);
	private slots:
		void start_capture( void);
        void on_pushButton_clicked();
};



#endif
