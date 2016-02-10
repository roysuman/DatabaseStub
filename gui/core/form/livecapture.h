/*
 * =====================================================================================
 *
 *       Filename:  livecapture.h
 *
 *       Description:  
 *
 *       Version:  1.0
 *       Created:  Tuesday 26 January 2016 08:37:51  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *       Author:  SIGCONT (suman roy), email.suman.roy@gmail.com
 *       Organization:  OPEN SOURCE
 *       LICENSE: GNU GPL
 *  
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
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
#include "capture/pcapinterface.h"

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
		void            fetch_available_interface( void);
		void set_style_sheet( void);
	private slots:
		void start_capture( void);
    signals:
		void start_processing( capture_opts* cap_options);


       // void on_pushButton_clicked();
};



#endif
