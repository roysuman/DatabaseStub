/*
 * =====================================================================================
 *
 *       Filename:  qtsingletonapplication.cpp
 *
 *       Description:  
 *
 *       Version:  1.0
 *       Created:  Saturday 16 January 2016 08:04:15  IST
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





#include "qtsingletonapplication.h"
#include <QWidget>

/* all function defination of class QtInstance */
//class QtLockedFile;
QtInstance::QtInstance( QObject *parent )
	:QObject( parent){
		/* get the exe file path */
		name = QCoreApplication::applicationFilePath();
       // QString file_prefix = name.section( QLatin1Char('/',-1));
		/* set lock */
        locked_file.setFileName( name);
		locked_file.open( QIODevice::ReadWrite);
		return;
	}
bool QtInstance::is_active(){
	bool    return_val;
	if ( locked_file.isLocked() ){
		return_val= false;
	}
	if ( !locked_file.lock(QtLockedFile::WriteLock,false) ){
		return_val =  true;
	}
	return return_val;
}

QtInstance::~QtInstance(){
    locked_file.unlock();
	return;
}


/*-----------------------------------------------------------------------------
 *  all method defination for SingTonApp...
 *-----------------------------------------------------------------------------*/


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  init
 *  Description:  init the lock , thus only one instance of this 
 *  	 	   application can get active at a time
 * =====================================================================================
 */
void SingTonApp::init()
{
//	actWin = 0;
	peer = new QtInstance(this);
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  SingTonApp
 *  Description:  constructor of singletomapplication.
 *   		  Initializing the QApplication.
 *   		  GUIenabled is true for GUI based app.
 * =====================================================================================
 */
SingTonApp::SingTonApp(int& argc, char** argv, bool GUIenabled)
	: QApplication(argc, argv, GUIenabled)
{
	init();
}



/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  is_running
 *  Description:  returns true if another instance of this app is running
 *                else returns false.
 * =====================================================================================
 */
bool SingTonApp::is_running()
{
	return peer->is_active();
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  get_identifier
 *  Description:  returns the identifier for this instance. 
 *  		  Which is generaly exe file path.
 * =====================================================================================
 */
QString SingTonApp::get_identifier() const
{
	/* return the lock file name */
	return peer->get_app_file();
}



/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  set_activation_window
 *  Description:  set the activation windiw of this application.
 * =====================================================================================
 */
void SingTonApp::set_activation_window(QWidget* aw){

	active_window = aw;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  activation_window
 *  Description:  return the activation window of this appliation is set else return 0/
 * =====================================================================================
 */
QWidget* SingTonApp::activation_window() const
{
	return active_window;
}


/*!
  De-minimizes, raises, and activates this application's activation window.
  This function does nothing if no activation window has been set.

  This is a convenience function to show the user that this
  application instance has been activated when he has tried to start
  another instance.

  This function should typically be called in response to the
  messageReceived() signal. By default, that will happen
  automatically, if an activation window has been set.

  \sa setActivationWindow(), messageReceived(), initialize()
*/
/* set the active window */
void SingTonApp::activate_window()
{
	if(active_window)
	{
		active_window->setWindowState(active_window->windowState() & ~Qt::WindowMinimized);
		active_window->raise();
		active_window->activateWindow();
	}
}


/*!
    \fn void SingTonApp::messageReceived(const QString& message)

    This signal is emitted when the current instance receives a \a
    message from another instance of this application.

    \sa sendMessage(), setActivationWindow(), activateWindow()
*/


/*!
    \fn void SingTonApp::initialize(bool dummy = true)

    \obsolete
*/
