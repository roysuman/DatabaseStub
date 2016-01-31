/*
 * =====================================================================================
 *
 *       Filename:  messagebox.h
 *
 *       Description:  
 *
 *       Version:  1.0
 *       Created:  Monday 01 February 2016 02:13:26  IST
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

#pragma once

#include <QtGui>

#include <QMessageBox>
#include "ui_messagebox.h"
#include "gui/forms/CustomWindow.h"
#include "ui_CustomWindow.h"
class CustomMessageBox : public BaseWindow<QDialog>
{
	Q_OBJECT
	Q_DISABLE_COPY(CustomMessageBox)
private:

	QPixmap standard_icon(QMessageBox::Icon icon);
	QAbstractButton* button_clicked;
	QMessageBox::StandardButton _button_clicked();
	bool is_closed;
	QMessageBox::StandardButton button_cancel;
protected:
	void showEvent(QShowEvent* event) override;

public:
	explicit CustomMessageBox(QWidget* parent = 0);
	CustomMessageBox(QMessageBox::Icon icon, const QString& title, const QString& text,
	                 QMessageBox::StandardButtons buttons = QMessageBox::NoButton, QWidget* parent = 0,
	                 Qt::WindowFlags flags = Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
	~CustomMessageBox();

	static QMessageBox::StandardButton critical(QWidget* parent, const QString& title,
	        const QString& text, QMessageBox::StandardButtons buttons = QMessageBox::Ok);

	static QMessageBox::StandardButton information(QWidget* parent, const QString& title,
	        const QString& text, QMessageBox::StandardButtons buttons = QMessageBox::Ok);

	static QMessageBox::StandardButton question(QWidget* parent, const QString& title,
		const QString& text, QMessageBox::StandardButtons buttons = QMessageBox::Yes | QMessageBox::No);

	static QMessageBox::StandardButton warning(QWidget* parent, const QString& title, const QString& text,
	        QMessageBox::StandardButtons buttons = QMessageBox::Ok);

	static void about(QWidget* parent, const QString& title, const QString& text);

	static QMessageBox::StandardButton showNewMessageBox(QWidget* parent,
	        QMessageBox::Icon icon, const QString& title, const QString& text,
	        QMessageBox::StandardButtons buttons);

private:
	QMessageBox::Icon m_icon;
	Ui::CustomMessageBox* ui;
	QPushButton* get_close_btn() override;
	QWidget* get_title_bar() override;
	QLabel* get_title_label() override;
	QLabel* get_title_icon() override;
	QWidget* central_widget() override;
private slots:
	void slot_button_clicked(QAbstractButton*);
	void accept() override;
	void reject() override;



};
