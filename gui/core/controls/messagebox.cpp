#include <QDebug>
#include "messagebox.h"
#ifdef Q_WS_WIN
#include "Windows.h"
#endif
void CustomMessageBox::showEvent(QShowEvent* p_event)
{
	/* 
#ifndef QT_NO_ACCESSIBILITY

	if (m_icon == QMessageBox::Critical || m_icon == QMessageBox::Warning)
	{
		QAccessible::updateAccessibility(this, 0, QAccessible::Alert);
	}

#endif
*/
	QDialog::showEvent(p_event);
}

CustomMessageBox::CustomMessageBox(QWidget* /*parent*/) :
	BaseWindow<QDialog> (BaseWindow::only_close_btn, BaseWindow::resize_not_allowed),
	ui(new Ui::CustomMessageBox)
{
	ui->setupUi(this);
}

CustomMessageBox::CustomMessageBox(QMessageBox::Icon icon, const QString& title, const QString& text,
                                   QMessageBox::StandardButtons buttons, QWidget* parent, Qt::WindowFlags /*flags*/) :
	BaseWindow<QDialog>(BaseWindow::only_close_btn,BaseWindow::resize_not_allowed, parent),
	ui(new Ui::CustomMessageBox),
	m_icon(icon)
{
	ui->setupUi(this);
	setup_custom_window();
	setup_window_icons();
	ui->icon->setPixmap(standard_icon(icon));
	ui->LTitle->setText(title);
	ui->text->setText(text);

	if (parent != NULL)
	{
	//	parent->showNormal();
		parent->setWindowState((windowState() & ~Qt::WindowMinimized) | Qt::WindowActive);
		parent->raise();
		parent->activateWindow();
	}

	if(buttons == QMessageBox::NoButton)
	{
		buttons = QMessageBox::Ok | QMessageBox::Cancel;
	}

	button_clicked = NULL;
	uint mask = QMessageBox::FirstButton;
	bool isFirst = true;

	while(mask <= QMessageBox::LastButton)
	{
		uint sb = buttons & mask;
		mask <<= 1;

		if(!sb)
		{
			continue;
		}

		QPushButton* button = ui->buttonBox->addButton(static_cast<QDialogButtonBox::StandardButton>(sb));

		if (isFirst)
		{
			isFirst = false;
			button->setFocus();
		}

		QMessageBox::ButtonRole  role = static_cast<QMessageBox::ButtonRole>(ui->buttonBox->buttonRole(button));

		if(role == QMessageBox::RejectRole || role == QMessageBox::NoRole)
		{
			button_cancel = static_cast<QMessageBox::StandardButton>(ui->buttonBox->standardButton(button));
		}
	}

	setWindowModality(Qt::ApplicationModal);
	connect(ui->buttonBox, SIGNAL(clicked(QAbstractButton*)), this, SLOT(slot_button_clicked(QAbstractButton*)));
}


QPixmap CustomMessageBox::standard_icon(QMessageBox::Icon icon)
{
	QStyle* style = this->style();
	int icon_size = style->pixelMetric(QStyle::PM_MessageBoxIconSize, NULL, this);
	QIcon tmp_icon;

	switch(icon)
	{
		case QMessageBox::Information:
			tmp_icon = style->standardIcon(QStyle::SP_MessageBoxInformation, NULL , this);
			break;

		case QMessageBox::Warning:
			tmp_icon = style->standardIcon(QStyle::SP_MessageBoxWarning, NULL, this);
			break;

		case QMessageBox::Critical:
			tmp_icon = style->standardIcon(QStyle::SP_MessageBoxCritical, NULL, this);
			break;

		case QMessageBox::Question:
			tmp_icon = style->standardIcon(QStyle::SP_MessageBoxQuestion, NULL, this);
			break;

		case QMessageBox::NoIcon:
			return ui->tbMenu->pixmap()->scaled(icon_size, icon_size);

		default:
			break;
	}

	if(!tmp_icon.isNull())
	{
		return tmp_icon.pixmap(icon_size);
	}

	return QPixmap();
}

QMessageBox::StandardButton CustomMessageBox::_button_clicked()
{
	return  button_clicked != NULL ? static_cast<QMessageBox::StandardButton>(ui->buttonBox->standardButton(button_clicked)) : button_cancel;
}

CustomMessageBox::~CustomMessageBox()
{
	delete ui;
}

QMessageBox::StandardButton CustomMessageBox::critical(QWidget* parent, const QString& title, const QString& text, QMessageBox::StandardButtons buttons)
{
	return showNewMessageBox(parent, QMessageBox::Critical, title, text, buttons);
}

QMessageBox::StandardButton CustomMessageBox::information(QWidget* parent, const QString& title, const QString& text, QMessageBox::StandardButtons buttons)
{
	return showNewMessageBox(parent, QMessageBox::Information, title, text, buttons);
}

QMessageBox::StandardButton CustomMessageBox::question(QWidget* parent, const QString& title, const QString& text, QMessageBox::StandardButtons buttons)
{
	return showNewMessageBox(parent, QMessageBox::Question, title, text, buttons);
}

QMessageBox::StandardButton CustomMessageBox::warning(QWidget* parent, const QString& title, const QString& text, QMessageBox::StandardButtons buttons)
{
	return showNewMessageBox(parent, QMessageBox::Warning, title, text, buttons);
}

void CustomMessageBox::about(QWidget* parent, const QString& title, const QString& text)
{
	showNewMessageBox(parent, QMessageBox::NoIcon, title, text, QMessageBox::Ok);
}

QMessageBox::StandardButton CustomMessageBox::showNewMessageBox(QWidget* parent, QMessageBox::Icon icon,
        const QString& title, const QString& text,
        QMessageBox::StandardButtons buttons)
{
	//CustomMessageBox msgBox = CustomMessageBox(icon, title, text, buttons, parent);
	CustomMessageBox msgBox(icon, title, text, buttons, parent);
	msgBox.exec();
	return msgBox._button_clicked();
}

void CustomMessageBox::slot_button_clicked(QAbstractButton* button)
{
	button_clicked = button;
}

void CustomMessageBox::accept()
{
	is_closed = true;
	done(QDialog::Accepted);
}

void CustomMessageBox::reject()
{
	is_closed = true;
	done(QDialog::Rejected);
}

QWidget* CustomMessageBox::get_title_bar()
{
	return ui->titleBar;
}

QLabel* CustomMessageBox::get_title_label()
{
	return ui->LTitle;
}

QLabel* CustomMessageBox::get_title_icon()
{
	return ui->tbMenu;
}

QPushButton* CustomMessageBox::get_close_btn()
{
	return ui->pbClose;
}

QWidget* CustomMessageBox::central_widget()
{
	return ui->m_centralWidget;
}
