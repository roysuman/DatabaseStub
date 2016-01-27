
/*
 * =====================================================================================
 *
 *       Filename:  CustomWindow.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Tuesday 19 January 2016 03:37:42  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  SIGCONT (suman roy), email.suman.roy@gmail.com
 *   Organization:  OPEN SOURCE
 *
 * =====================================================================================
 */
#ifndef CUSTOM_WINDOW_H
#define CUSTOM_WINDOW_H
#pragma once

#define PIXELS_TO_ACT 3
#include <QtGui>
#include <QHBoxLayout>
#include <QApplication> // Qt includes
#include <QPushButton>
#include <QLabel>
#include <QDesktopWidget> //QDesktopWidget.h
#include<iostream>
template <class T>
class BaseWindow : public T{

	/* disable copy */
	Q_DISABLE_COPY(BaseWindow)

	public:
		enum mode_resize {resize_not_allowed , resize_allowed};
		enum mode_title { full_title = 0 , maximize_mode_off =1,
			minimize_mode_off = 2, 
			max_min_off = maximize_mode_off | minimize_mode_off ,
			only_close_btn = max_min_off, full_screen_mode = 4};
		BaseWindow( mode_title mode_title_var , mode_resize mode_resize_var , QWidget* parent = NULL);
		/* public methods  */
		void show_maximized( void );
		void show_normal( void );
		void set_geometry( QRect geom);
		void set_title(QString title);
		void do_hide();
		bool is_window_maximized( void );

	protected:
		
		bool is_maximized;
        bool allow_to_resize ;
		QRect pre_maximize_geomentry;
		QHBoxLayout* central_layout;

        mode_resize m_mode_resize;
		mode_title  m_mode_title;

		/* mouseDoubleClickEvent: overload method that maximize/restore
		 * the window if double clicked and the position of the mouse is not
		 * in the menu zone
		 * */
		virtual void mouseDoubleClickEvent( QMouseEvent *e );

		virtual void setup_custom_window();
		virtual void setup_window_icons();
		virtual QPushButton* get_min_btn();
		virtual QPushButton* get_max_btn();
		virtual QPushButton* get_close_btn();
		virtual QWidget* get_title_bar();
		virtual QWidget* central_widget();
		virtual QLabel* get_title_label();
		virtual QLabel* get_title_icon();

	public slots:
		virtual void maximize_btn_clicked();
		virtual void minimize_btn_clicked();

};



/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  set_title
 *  Description:  set the title of the window
 * =====================================================================================
 */
template <class T> 
void 
BaseWindow<T>::set_title(QString title){
	QLabel *label = get_title_label();
	if ( (label = get_title_label()) != NULL){
		label->setText(title);
	}
	return;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  do_hide
 *  Description:  hide the window
 * =====================================================================================
 */
template<class T>
void
BaseWindow<T>::do_hide( void ){
	if ( !is_maximized ){
		pre_maximize_geomentry = T::geometry();
	}
	T::hide();
	return;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  is_window_maximized
 *  Description:  whether window is maximized or not
 * =====================================================================================
 */
template< class T>
bool
BaseWindow<T>::is_window_maximized( void ){
	return is_maximized;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  set_geometry
 *  Description:  set the window geo.. if window is not maximized
 *  		  then save the geo. 
 * =====================================================================================
 */
template< class T>
void
BaseWindow<T>::set_geometry( QRect geo ){
	if ( !is_maximized ){
		pre_maximize_geomentry = geo;
	}
	T::setGeometry( geo );
	return;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  show_normal
 *  Description:  show normal desktop
 * =====================================================================================
 */
template< class T>
void
BaseWindow<T>::show_normal( void ){
	set_geometry( pre_maximize_geomentry);
	T::showNormal();
	is_maximized = false;
	return;
}

/*-----------------------------------------------------------------------------
 *  defination of virtual methods...dummy defination
 *-----------------------------------------------------------------------------*/
template<class T>
QLabel * 
BaseWindow<T>::get_title_icon( void ){
	return NULL;
}

template < class T>
QLabel*
BaseWindow<T>::get_title_label( void ){
	return NULL;
}

template<class T>
QWidget * 
BaseWindow<T>::central_widget( void ){
	return NULL;
}

template< class T>
QWidget *
BaseWindow<T>::get_title_bar( void ){
	return NULL;
}

template < class T>
QPushButton *
BaseWindow<T>::get_close_btn( void ){
	return NULL;
}

template< class T>
QPushButton *
BaseWindow<T>::get_min_btn( void ){
	return NULL;
}

template < class T>
QPushButton *
BaseWindow< T>::get_max_btn ( void ){
	return NULL;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  BaseWindow
 *  Description:  constructor.
 * =====================================================================================
 */

template <class T>
BaseWindow<T>::BaseWindow( mode_title var_mode_title , 
	       		   mode_resize var_mode_resize,
			   QWidget *parent) : T(), is_maximized(false){
	m_mode_title = var_mode_title;
	m_mode_resize = var_mode_resize;
	return;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  setup_window_icons
 *  Description:  set up mainwindow icons.. minimizw,maximize,reset,close
 * =====================================================================================
 */
template< class T>
void
BaseWindow<T>::setup_window_icons(){

//	get_min_btn()->setIcon(QIcon(":/icons/button_minimize.ico"));
//	get_max_btn()->setIcon(QIcon(":/icons/button_maximize.ico"));

	 
	if  (  ( m_mode_title & minimize_mode_off ) == 0 &&
			get_min_btn()!= NULL){
		get_min_btn()->setIcon(QIcon(":/icons/button_minimize.ico"));

	}
	if ( ( m_mode_title & maximize_mode_off ) == 0 &&
			get_max_btn() != NULL){
		if ( is_maximized){
			get_max_btn()->setIcon(QIcon(":/icons/button_maximize.ico"));
		}
		else{
			get_max_btn()->setIcon(QIcon(":/icons/button_maximize.ico"));
		}
	}
	
	get_close_btn()->setIcon(QIcon(":/icons/button_close.ico"));

	return;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  setup_custom_window
 *  Description:  set up the custom window... this is the method
 *  		  which init the window environemnt
 * =====================================================================================
 */

template <class T>
void 
BaseWindow<T>::setup_custom_window()
{
	T::setWindowFlags(Qt::FramelessWindowHint);
	T::setMouseTracking(true);
	
	get_title_bar()->setMouseTracking(true);
	get_title_label()->setMouseTracking(true);
	get_title_icon()->setMouseTracking(true);
	get_close_btn()->setMouseTracking(true);

	if(central_widget() == NULL)
	{
		qCritical() << "Central widget is null";
	}
	else
	{
		central_widget()->setMouseTracking(true);
	}

	if ( ( (m_mode_title & minimize_mode_off) == 0 ) && ( get_min_btn() != NULL) )
	{
		get_min_btn()->setMouseTracking(true);
		T::connect(get_min_btn(), SIGNAL(clicked()), this, SLOT(minimize_btn_clicked()));
	}
	else if(get_min_btn() != NULL)
	{
		get_min_btn()->hide();
	}

	if ( ( ( m_mode_title & maximize_mode_off) == 0) && (get_max_btn() != NULL ))
	{
		get_max_btn()->setMouseTracking(true);
		T::connect(get_max_btn(), SIGNAL(clicked()), this, SLOT(maximize_btn_clicked()));
	}
	else if(get_max_btn() != NULL)
	{
		get_max_btn()->hide();
	}

	T::connect(get_close_btn(), SIGNAL(clicked()), this, SLOT(close()));
	allow_to_resize = false;
	
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  minimize_btn_clicked
 *  Description:  slot for minimize button clicked
 * =====================================================================================
 */
template< class T>
void
BaseWindow<T>::minimize_btn_clicked( void ){
	if ( T::isMaximized()){
		T::setWindowState(T::windowState() & ~Qt::WindowMinimized);
	}
	else{
		T::setWindowState(T::windowState() | Qt::WindowMinimized );
	}
	return;
}

template<class T>
void
BaseWindow<T>::mouseDoubleClickEvent( QMouseEvent *event ){
	QPoint pos = event->globalPos();
	QRect  title_geo = get_title_bar()->geometry();
	title_geo.moveTopLeft(get_title_bar()->parentWidget()->mapToGlobal( title_geo.topLeft()));
	if ( title_geo.contains( pos , true ) &&
			m_mode_title != full_screen_mode){
		maximize_btn_clicked();
	}
	event->accept();
	return;

}
template<class T>
void BaseWindow<T>::maximize_btn_clicked(void){
    if (get_max_btn() != NULL)
      {
              if (T::isFullScreen() || is_window_maximized())
              {
                    //  getMaxBtn()->setIcon(styleEngine->getIcon("app_max"));
                  show_normal();

              }
              else
              {
                  //    getMaxBtn()->setIcon(styleEngine->getIcon("app_reset"));
                  show_maximized();

              }
      }
}

template <class T>
void BaseWindow<T>::show_maximized()
{
        QDesktopWidget* desktop = QApplication::desktop();
        pre_maximize_geomentry = T::geometry();
        is_maximized = true;
        set_geometry(desktop->availableGeometry(this));
        T::showNormal();
}
#endif
