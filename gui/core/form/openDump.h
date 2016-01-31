/*
 * =====================================================================================
 *
 *       Filename:  openDump.h
 *
 *       Description:  
 *
 *       Version:  1.0
 *       Created:  Sunday 24 January 2016 01:48:43  IST
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

#ifndef OPEN_DUMP_H
#define OPEN_DUMP_H
#pragma once
#include <QFile>
#include<QDialog>
#include<QFileDialog>
#include<QTreeWidgetItem>
#include<QString>
#include <QDir>
#include<cstring>
#include<iostream>
#include "gui/forms/CustomWindow.h"
#include "ui_OpenDumpFileDialog.h"
#include "./gui/core/viewmodel/filetreemodel.h"
#include "./gui/core/controls/messagebox.h"
class OpenDump: public BaseWindow<QDialog>, Ui::OpenDumpFileDialog {
	Q_OBJECT

	public:
		OpenDump( QWidget *parent= 0 );
		virtual ~OpenDump(void);
		int exec(void );
	private:
		QStringList      tcp_dump_files;
		QPushButton*     get_close_btn( void ) override;
		QWidget*         get_title_bar( void ) override;
		QWidget *        central_widget( void ) override;
		QLabel*          get_title_label( void) override;
		QLabel*          get_title_icon( void) override;
		void             setup_actions(void);
		FileTreeModel    *file_tree_model;
		void show_file_tree(  QStringList&);
	public slots:
	private slots:
		void browse_button( void);
	        void path_changed( void );
		void start_parsing(void);
	signals:
		void call_file_tree_model( QStringList& files);

};
#endif

	




