/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *       Description:  
 *
 *       Version:  1.0
 *       Created:  Monday 18 January 2016 11:08:54  IST
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


#include <QApplication>
#include "gui/forms/CustomWindow.h"
#include"core/vservermainwindow.h"
#include <QDesktopWidget>
#include "qtsingletonapplication.h"
#include "core/xmlparser/parsermanager.h"

void
data_output( QtMsgType msg_type , const char * msg ){
	std::fflush( stdout);
	std::fflush( stderr);
	switch ( msg_type){
		case QtDebugMsg:
			fprintf( stdout , "%s\n",msg);
			break;
		case QtWarningMsg:
			fprintf( stdout,"%s\n",msg);
			break;
		case QtCriticalMsg:
		       fprintf(stdout,"%s\n",msg);
		       break;
		case QtFatalMsg:
		       fprintf(stdout,"%s\n",msg);
		       abort();
	}
	std::fflush( stdout);
	std::fflush( stderr);
	return;
	
}

static bool
parse_config( void ){
	std::string path= "config/vserver-util.xml";
	ParserManager ins(path);
	return (  ins.parse_config() );
}
int 
main(int argc, char *argv[]){

    SingTonApp app(argc, argv);
    /* get all arguments */
    QStringList arguments = SingTonApp::arguments();
    QVariantMap arguments_map;
    FILE *file_ptr= nullptr;

    arguments_map["minimized"] = arguments.contains("-m")||
	    arguments.contains("--minimized");
    arguments.removeAll("-m");
    arguments.removeAll("--minimmized");
    
    arguments_map["debug"] =arguments.contains("-d") ||
	    arguments.contains("--debug");
    QString dir = QApplication::applicationDirPath() +
	    QDir::separator();
    if ( arguments_map["debug"].toBool()){
	    QString log_file_name = dir +"Vserver."+
		    QString::number(QApplication::applicationPid())+".log";
    }
    qDebug() << "Arguments "<< QApplication::arguments();
    qDebug() << "Parsed Values " << arguments_map;
    /* TODO set window icon */
//    app.setWindowIcon(QIcon(""));

    app.setWindowIcon(QIcon(":/icons/app.ico"));
    app.setDesktopSettingsAware( false);
    app.setEffectEnabled( Qt::UI_FadeMenu , true);
    app.setEffectEnabled( Qt::UI_AnimateCombo , true );

    VServerMainWindow w;
    app.set_activation_window(&w);
    if ( !parse_config() ){
	    qDebug()<<"Parsing config file failed";
	    return -1;
    }

    if ( arguments_map["minimized"].toBool() ){
        w.showMinimized();
    }
    else{
	    w.show();
    }
    bool res = app.exec();
    if ( arguments_map["debug"].toBool() && file_ptr ){
	    fclose( file_ptr );
    }
    return res;
}
