/*
 * =====================================================================================
 *
 *       Filename:  livecapture.cpp
 *
 *       Description:  
 *
 *       Version:  1.0
 *       Created:  Tuesday 26 January 2016 08:43:34  IST
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


#include "livecapture.h"
#include "./capture/pcapinterface.h"


LiveCapture::LiveCapture( QWidget* parent):BaseWindow( BaseWindow::only_close_btn , BaseWindow::resize_not_allowed, parent){
	setupUi( this);
	set_style_sheet();
	setup_custom_window( );
	setup_window_icons();
	setup_actions();
	fetch_available_interface( );
	return;
}

QPushButton*
LiveCapture::get_close_btn( void){
	return pbClose;
}


QWidget*
LiveCapture::get_title_bar( void){
	return titleBar;
}

QWidget*
LiveCapture::central_widget( void ){
	return centralWidget;
}
QLabel*
LiveCapture::get_title_label( void ){
	return LTitle;
}
QLabel*
LiveCapture::get_title_icon( void ){
	return tbMenu;
}

int
LiveCapture::exec( void){
	QDialog::exec();
	//TODO check error
	return 1;
}

void
LiveCapture::setup_actions( void){
	connect( pb_StartSniffing , SIGNAL( clicked() ),this,SLOT( start_capture()) ); 


}

LiveCapture::~LiveCapture( void){
}

void
LiveCapture::start_capture( void){
	qDebug()<<"start capture";
	capture_opts *cap= new capture_opts();
	cap->device_name = "wlan0";
	std::string name="suman";

	cap->save_file = false;
	cap->ring_buffer_handle = nullptr;
	cap->stop_packet_set = false;
	cap->stop_byte_set = false;
	cap->stop_time_duration = false;
	cap->do_dissect = false;
	std::cout<<cap->device_name<<std::endl;

	emit start_processing( cap);

	

	//TODO save values into cap_opts variable
	//and emit start_processing signal
}
void
LiveCapture::set_style_sheet( void ){
	interfaceListWidget->setAlternatingRowColors(true);
//	interfaceListWidget->setStyleSheet("alternate-background-color: green;background-color: blue;");
	interfaceListWidget->setStyleSheet( 
			"QListWidget::item {"
			"border-style: solid;" 
			"border-width:1px;" 
		//	"border-color:black;" 
			"border-color: rgba(255,255,255,200);"
		//	"background-color: green;"
			"background-color: qlineargradient(x1:0, y1:0, x2:1,y2:1, stop: 1 rgba(228, 41, 81, 100), stop: 0 rgba(234, 107, 101, 100));"
			"padding: 1px 0px 1px 3px;"
			"}"
			"QListWidget::item:selected {"
			 "background-color: green;"
			 "}");
	interfaceCombobx->setStyleSheet(
			"QComboBox {"
			"color:black;"
			"background-color: qlineargradient(x1:0, y1:0, x2:1,y2:1, stop: 1 rgba(228, 41, 81, 100), stop: 0 rgba(234, 107, 101, 100));"
			"border-color: rgba(255,255,255,200);"
			"border-width: 1px;"
			"border-style: solid;"
			"padding: 1px 0px 1px 3px;"
			"}");
	/*
	interfaceCombobx->setStyleSheet(
			"QComboBox::drop-down{"
			"width: 20px;"
			"border: 1px;"
			"border-color:white;"
			"border-left-style:solid;"
			"border-top-style: none;"
			"border-bottom-style: none;"
			"border-right-style: none;"
			"}");
	interfaceCombobx->setStyleSheet(
			"QComboBox QListView{"
			"border-style: none;"
			"background-color: qlineargradient(x1:0, y1:0, x2:1,y2:0, stop: 1 rgba(228, 41, 81, 100), stop: 0 rgba(234, 107, 101, 100));"
			"}");

	QComboBox::down-arrow
	{
		    image: url(:/ArrowImages/images/whitearrowdown16.png);
			       width: 16px;
				          height: 16px;
	}
	*/
	

}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  fetch_available_interface
 *  Description:  call the pcap api to provide interface list available in 
 *  		  current system.
 * =====================================================================================
 */
void
LiveCapture::fetch_available_interface( void){
	int error;
	char str_err[ERRBUFF_SIZE];
	/* read the interface list */
	std::vector<interface_info*> interfaces =
		InterfaceHandler::get_available_interface_list( &error , str_err );
	if ( error != 0 ){
		//TODO show the error 
	}

	std::vector<interface_info*>::iterator it;

	/* display interface list @GUI(interfaceListWidget &
	 * interfaceCombobx  */

    for ( it= interfaces.begin(); it!= interfaces.end(); ++it ){
        QListWidgetItem* item = new QListWidgetItem(QString(((*it)->name).c_str()));
		/* TODO: use checkbox when you are planning to
		 * capture from multiple device..simultaniously */
//		item->setCheckState(Qt::Unchecked);
		//TODO setup icon
        //item->setIcon(pIconDownloader->getFavicon(pFeed->url().toString()));

	interfaceListWidget->addItem(item);
	interfaceCombobx->addItem(QString(((*it)->name).c_str()));
	}
	return;
}
