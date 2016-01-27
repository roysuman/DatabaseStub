/*
 * =====================================================================================
 *
 *       Filename:  openDump.h
 *
 *    Description:  open the dump file
 *
 *        Version:  1.0
 *        Created:  Sunday 24 January 2016 01:48:43  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  SIGCONT (suman roy), email.suman.roy@gmail.com
 *   Organization:  OPEN SOURCE
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

	




