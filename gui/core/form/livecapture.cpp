/*
 * =====================================================================================
 *
 *       Filename:  livecapture.cpp
 *
 *    Description:  cpp file of live cpture
 *
 *        Version:  1.0
 *        Created:  Tuesday 26 January 2016 08:43:34  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  SIGCONT (suman roy), email.suman.roy@gmail.com
 *   Organization:  OPEN SOURCE
 *
 * =====================================================================================
 */
#include "livecapture.h"
LiveCapture::LiveCapture( QWidget* parent):BaseWindow( BaseWindow::only_close_btn , BaseWindow::resize_not_allowed, parent){
	setupUi( this);
	setup_custom_window( );
	setup_window_icons();
	setup_actions();
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
}

LiveCapture::~LiveCapture( void){
}

void
LiveCapture::start_capture( void){
}

