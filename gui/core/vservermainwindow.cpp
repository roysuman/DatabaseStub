/*
 * =====================================================================================
 *
 *       Filename:  vservermainwindow.cpp
 *
 *       Description:  
 *
 *       Version:  1.0
 *       Created:  Saturday 16 January 2016 09:06:20  IST
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


#include <stddef.h>
#include <QAbstractItemView>
#include <QClipboard>
#include <QComboBox>
#include <QDebug>
#include <QDesktopServices>
#include <QTreeWidgetItem>
#include"vservermainwindow.h"
#include "./gui/core/form/openDump.h"
#include "./gui/core/form/livecapture.h"


Q_DECLARE_METATYPE(QList<int>)

VServerMainWindow::VServerMainWindow(QWidget* parent)
    : BaseWindow( full_title,resize_allowed, parent)
     // , mw_init_finished(false)
{

	setWindowModality(Qt::NonModal);//QT method
	setup_custome_window();
    //update_timer = new QTimer(this);
    //update_timer->setInterval(400);
	setAcceptDrops(true);
	init_main_mennu_icons();
	create_actions();
//	pbMin->setIcon(QIcon(":/icons/button_minimize.ico"));
	
//	setup_status_bar();//done
//	setup_toolbar(); //done
//	setup_scenario_tree_widget();
//	setup_connections();
//	setup_view_menu_state();
//	QTimer::singleShot(10000, this, SLOT(CheckForUpdates()));
//	setup_tabel_widgets();
//	mw_update_timer->start();
//	mw_init_finished = true;
}




/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  init_statusbar_icons
 *  Description:  init the status bar icons..
 *  		  TODO setup the icon
 * =====================================================================================
 */
void 
VServerMainWindow::init_status_bar_icons(void) const{

    //TODO StyleENgine
    /*
    up_label_count->setPixmap(mw_style_eng->getIcon("status_bar_up_count").pixmap(16, 16));
    down_label_count->setPixmap(mw_style_eng->getIcon("status_bar_down_count").pixmap(16, 16));*/
}

/*
 * ===  FUNCTION  ======================================================================
 *         Name:  setup_status_bar
 *  Description:  create lebel for mainwindow status bar.
 * =====================================================================================
 */
void 
VServerMainWindow::setup_statusbar(){
	up_label_text = new QLabel( this);
	up_label_text->setToolTip("STATUS_UP_COUNT");
	up_label_text->setMinimumWidth( 140);
	up_label_count = new QLabel( this );
	up_label_count->setToolTip("STATUS_UP_COUNT");
	down_label_text = new QLabel( this );
	down_label_text->setToolTip( "STATUS_DOWN_COUNT");
	down_label_text->setMinimumWidth( 140 );
	down_label_count = new QLabel( this );
	down_label_count->setToolTip("STATUS_DOWN_COUNT");
	vServerStatusBar->addPermanentWidget( up_label_text);
	vServerStatusBar->addPermanentWidget( up_label_count);
	vServerStatusBar->addPermanentWidget( down_label_text);
	vServerStatusBar->addPermanentWidget( down_label_count);
	init_status_bar_icons();
	return;
}



void VServerMainWindow::init_toolbar_icons() const{
	/* 
    ACTION_TOOlBAR_SHOW_INTERFACE->setIcon( mw_style_eng->getIcon("toolbar_show_interface"));
    ACTION_TOOLBAR_START_SERVER->setIcon( mw_style_eng->getIcon("toolbar_start_server"));
    ACTION_TOOLBAR_SETTINGS->setIcon( mw_style_eng->getIcon("toolbar_settings"));*/
    /*
     * ACTION FOR
     * START LIVE CAPTURING
     * STOP live captur
     * save captured fiel`
     * */

}





VServerMainWindow::~VServerMainWindow()
{

}








/* setup custom window... understand */
void 
VServerMainWindow::setup_custome_window(){
    setupUi(this);
    BaseWindow::setup_custom_window();
    return;
}

QPushButton*
VServerMainWindow::get_min_btn( void ){
	return pbMin;
}

QPushButton *
VServerMainWindow::get_max_btn( void ){
	return pbMax;
}

QPushButton*
VServerMainWindow::get_close_btn( void ){
	return pbClose;
}

QWidget*
VServerMainWindow::get_title_bar( void ){
	return titleBar;
}

QWidget *
VServerMainWindow::central_widget( void ){
	return m_centralWidget;
}

QLabel*
VServerMainWindow::get_title_label(void ){
	return LTitle;
}

QLabel*
VServerMainWindow::get_title_icon( void ){
	return tbMenu;
}

void 
VServerMainWindow::init_main_mennu_icons( void ){
	BaseWindow::setup_window_icons();
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  create_actions
 *  Description:  register all actions
 * =====================================================================================
 */
void 
VServerMainWindow::create_actions( void ){
	connect ( ACTION_MENUFILE_OPEN_DUMP ,SIGNAL ( triggered () ) , this ,
			SLOT ( show_open_tcp_dump() ) );
	
	connect ( ACTION_MENUFILE_LIVE_CAPTURE ,SIGNAL ( triggered () ) , this ,
			SLOT ( show_live_capture() ) );

}
void VServerMainWindow::setup_toolbar( void){}
void VServerMainWindow::setup_search_model( void){}

void VServerMainWindow::save_window_state( void){}

//SLOTS


void VServerMainWindow::update_down_pack_count( int pack_count )const{}
void VServerMainWindow::update_up_pack_count( int pack_count ) const {}
void VServerMainWindow::show_about( void ){}
void VServerMainWindow::update_statusbar( void ){}
void VServerMainWindow::update_tab_widgets( void ){}
void VServerMainWindow::perform_search( void ){}
void VServerMainWindow::maximize_btc_clicked( void ){}
void VServerMainWindow::process_minimize_btn_clicked( void ){}
void VServerMainWindow::on_quit( void){}
void VServerMainWindow::toggle_info_tab_visibility( bool ){}
void VServerMainWindow::toggle_toolbar_visibility( bool ){}
void VServerMainWindow::toggle_statusbar_visibility( bool ){}
void VServerMainWindow::toggle_scenario_tree_visibility( bool ){}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  open_tcp_sump_file
 *  Description:  open the window of tcp dumo file
 * =====================================================================================
 */
void 
VServerMainWindow::show_open_tcp_dump( void ){
	OpenDump dumpIns(this);
	dumpIns.exec();
	return;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  show_live_capture
 *  Description:  show the livecapture setting dialog...configure setup 
 *  		  and start sniffing...
 * =====================================================================================
 */

void VServerMainWindow::show_live_capture( void ){
	LiveCapture live_capture(this);
	live_capture.exec();
	return;
}

void VServerMainWindow::show_interface_list( void){}
void VServerMainWindow::show_start_server_dialog( void ){}
void VServerMainWindow::show_report_dialog( void ){}
void VServerMainWindow::check_updates( void){}
void VServerMainWindow::open_configuration_dialog( void ){}

void VServerMainWindow::maximize_btn_clicked(){
    BaseWindow::maximize_btn_clicked();
}

void VServerMainWindow::minimize_btn_clicked(){
    BaseWindow::minimize_btn_clicked();
}

