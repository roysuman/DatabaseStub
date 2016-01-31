/*
 * =====================================================================================
 *
 *       Filename:  openDump.cpp
 *
 *       Description:  
 *
 *       Version:  1.0
 *       Created:  Sunday 24 January 2016 02:05:28  IST
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



#include "openDump.h"

OpenDump::OpenDump( QWidget *parent):BaseWindow( BaseWindow::only_close_btn,BaseWindow::resize_not_allowed, parent){
	setupUi( this);
	setup_custom_window();
	setup_window_icons();
	setup_actions();
	file_tree_model = new FileTreeModel();
	tcp_dump_files = { "suman", "suman/Roy",};
	return;
}


QPushButton*
OpenDump::get_close_btn( void){
	return pbClose;
}


QWidget*
OpenDump::get_title_bar( void){
	return titleBar;
}

QWidget*
OpenDump::central_widget( void ){
	return centralWidget;
}
QLabel*
OpenDump::get_title_label( void ){
	return LTitle;
}
QLabel*
OpenDump::get_title_icon( void ){
	return tbMenu;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  browse_button
 *  Description:  action browse button clicked.
 * =====================================================================================
 */
void 
OpenDump::browse_button(  void ){
	
	QString last_dir = pathEdit->text();
	QStringList files = QFileDialog::getOpenFileNames(
			this,"Select tcp dumo files",
			last_dir,"All(*.*)");
	
	QStringList list = files;
	/*
	 * check whether any file has been selectd or not..
	 * and next time browse will start from selectedfiles-dir
	 */
	if ( !files.isEmpty() ){
		files.append(QDir::separator());
		files[0] = QDir::toNativeSeparators(files[0]);
		pathEdit->setText( files[0]);
		/* show selected files in treeView */
		show_file_tree( list);
	}else{
		qDebug()<< "No file selected for parsing";
	}
	return;
}
void 
OpenDump::path_changed( void){
}

int
OpenDump::exec( void){
	QDialog::exec();
	//TODO check error
	return 1;
	//return 0;

}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  setup_actions
 *  Description:  register all actions
 * =====================================================================================
 */
void
OpenDump::setup_actions( void ){
	

	connect ( browseButton ,SIGNAL ( clicked () ) , this ,
			SLOT ( browse_button() ) );
	connect ( parseButton , SIGNAL( clicked() ), this,
			SLOT( start_parsing()));
}
OpenDump::~OpenDump(){
	if ( file_tree_model != NULL)delete file_tree_model;
}

void
OpenDump::show_file_tree( QStringList& files ){
	std::cout<<"signal handler"<<std::endl;

	QStringList::Iterator it = files.begin();
	while(it != files.end()) {
		QString str = *it;
		tcp_dump_files.append( *it);
		qDebug () << *it;

//		file_tree_model->add_path(QString::fromUtf8( str),10);
		file_tree_model->add_path(QString( str),1);
		++it;
	}
	dumpFilesTreeView->setModel( file_tree_model);
	dumpFilesTreeView->expandToDepth(0);
	dumpFilesTreeView->setColumnWidth(0, 300);
	dumpFilesTreeView->setColumnWidth(1, 60); 
	return;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  start_parsing
 *  Description:  all data validation is done hear...
 *  		  whether environment has enough data to start parsing or
 *  		  or not. If all OK then control returns @MainWindow and
 *  		  start processing dump files
 * =====================================================================================
 */
void
OpenDump::start_parsing( void ){
	//TODO validation
	CustomMessageBox::critical(this, "WARNING_VALIDATION", "SCENARIO: NO_NAME");
	QStringList::Iterator it;
	for( it = tcp_dump_files.begin() ; it != tcp_dump_files.end(); ++it ){
		qDebug()<<*it;
	}
	return;
}

