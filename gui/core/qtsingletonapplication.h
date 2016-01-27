
/*
 * =====================================================================================
 *
 *       Filename:  a.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Saturday 16 January 2016 07:44:47  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  SIGCONT (suman roy), email.suman.roy@gmail.com
 *   Organization:  OPEN SOURCE
 *
 * =====================================================================================
 */

#ifndef QTSINGLEAPPLICATION_H
#define QTSINGLEAPPLICATION_H

#include <QApplication>
#include <QLatin1Char>
#include "core/qtfilelock.h"


class QtInstance: public QObject{
	Q_OBJECT
	public:
		QtInstance( QObject *parent = nullptr );
         ~QtInstance();
		bool is_active();
		QString get_app_file() const{
			return name;
		}

	private:
		QString name;
		QtLockedFile locked_file;
};

class SingTonApp : public QApplication
{
	Q_OBJECT

public:
	SingTonApp(int& argc, char** argv, bool GUIenabled = true);

	bool is_running();
	QString id() const;

	void set_activation_window(QWidget* aw);
	QWidget* activation_window() const;
    QString get_identifier() const;

	// Obsolete:
	void initialize(bool dummy = true)
	{
		peer->is_active();
		Q_UNUSED(dummy)
	}

public Q_SLOTS:
	void activate_window();


Q_SIGNALS:


private:
	void init(void );
	QtInstance* peer;
	QWidget* active_window;
};

#endif // QTSINGLEAPPLICATION_H
