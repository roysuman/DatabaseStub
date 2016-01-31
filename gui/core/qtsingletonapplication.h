/*
 * =====================================================================================
 *
 *       Filename:  qtsingletonapplication.h
 *
 *       Description:  
 *
 *       Version:  1.0
 *       Created:  Saturday 16 January 2016 07:44:47  IST
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
