/*
 * =====================================================================================
 *
 *       Filename:  treeitem.h
 *
 *       Description:  
 *
 *       Version:  1.0
 *       Created:  Sunday 24 January 2016 11:37:53  IST
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

#ifndef TREE_ITEM_H
#define TREE_ITEM_H

#include<QPair>
#include<QVariant>
#include<cstdint>
typedef QPair< QString , QVariant > file_data_type;
class TreeItemFile{
	public:
		TreeItemFile( const file_data_type& file_data , TreeItemFile * parent = 0);
		virtual ~TreeItemFile();
		void append_child( TreeItemFile *child_item);
		TreeItemFile* get_child( int row );

		int child_count() const;
		inline int column_count(void) const{
			return 2;
		}
		int row_count( void) const;
		QVariant get_data( int column_number) const;
		void set_data( int index , QVariant data);
		void set_checked( Qt::CheckState checked);
		Qt::CheckState checked( void );
		inline TreeItemFile* get_parent( void ) {
			return parent_file_item;
		}
		QString get_path( void );
		int row() const;
	private:
		QList< TreeItemFile *>items_container;
		TreeItemFile * parent_file_item;
		file_data_type item_data;
		Qt::CheckState checked_state;
};
#endif
