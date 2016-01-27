
/*
 * =====================================================================================
 *
 *       Filename:  a.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Monday 18 January 2016 11:08:54  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  SIGCONT (suman roy), email.suman.roy@gmail.com
 *   Organization:  OPEN SOURCE
 *
 * =====================================================================================
 */


#include <QApplication>
#include "gui/forms/CustomWindow.h"
#include"core/vservermainwindow.h"
#include <QDesktopWidget>
#include "qtsingletonapplication.h"

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
int main(int argc, char *argv[])
{
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
