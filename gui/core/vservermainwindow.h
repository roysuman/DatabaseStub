
/*
 * =====================================================================================
 *
 *       Filename:  vservermainwindow.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Saturday 16 January 2016 09:06:20  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  SIGCONT (suman roy), email.suman.roy@gmail.com
 *   Organization:  OPEN SOURCE
 *
 * =====================================================================================
 */

#ifndef VSERVERMAIN_H
#define VSERVERMAIN_H

#include "gui/forms/CustomWindow.h"
#include "ui_CustomWindow.h"
#include <QTimer>

class VServerMainWindow : public BaseWindow<QWidget> , Ui::CustomWindow{
	Q_OBJECT


	public:
		VServerMainWindow(QWidget* parent = 0);
		void raise_window();
		virtual ~VServerMainWindow( void );
	protected:

	private:
		bool init_done;
		QTimer update_timer;
		QComboBox search_combo_box;
		QLabel *up_label_count , *up_label_text;
		QLabel *down_label_count,* down_label_text;
		void init_toolbar_icons( void )const;
		void init_status_bar_icons( void )const;
		void init_main_mennu_icons( void );
		void create_actions( void );
		void setup_toolbar( void );
		void setup_search_model( void );
		void setup_statusbar( void );
		void setup_custome_window( void );
		void save_window_state( void );
		virtual QPushButton* get_min_btn() override;
		virtual QPushButton* get_max_btn() override;
		virtual QPushButton* get_close_btn() override;
		virtual QWidget* get_title_bar() override;
		virtual QWidget* central_widget() override;
		virtual QLabel* get_title_label() override;
		virtual QLabel* get_title_icon() override;

	public slots:
		void show_open_tcp_dump( void );
		void show_interface_list( void );
		void show_start_server_dialog( void );
		void show_report_dialog(void);
		void show_about( void);
		void show_live_capture( void );

		void update_down_pack_count( int) const;
		void update_up_pack_count( int ) const;
		void update_statusbar( void );
		void update_tab_widgets( void );
		void perform_search( void );
		void maximize_btc_clicked( void );
		void process_minimize_btn_clicked( void );
		void on_quit( void);
		void toggle_info_tab_visibility( bool );
		void toggle_toolbar_visibility( bool );
		void toggle_statusbar_visibility( bool );
		void toggle_scenario_tree_visibility( bool );
		void check_updates( void);
		void open_configuration_dialog( void );
		void maximize_btn_clicked() override;
		void minimize_btn_clicked() override;


};

//Q_DECLARE_METATYPE(QHostAddress)
#endif // LTORRENT_H
