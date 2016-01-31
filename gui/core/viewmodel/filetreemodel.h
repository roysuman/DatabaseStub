/*
 * =====================================================================================
 *
 *       Filename:  filetreemodel.h
 *
 *       Description:  file tree model for open dump
 *
 *       Version:  1.0
 *       Created:  Monday 25 January 2016 12:15:32  IST
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

#ifndef FILE_TREE_MODEL_H
#define FILE_TREE_MODEL_H
#include "treeitem.h"
#include <QAbstractItemModel>

class FileTreeModel: public QAbstractItemModel{
	Q_OBJECT
	public:
		FileTreeModel( QObject *parent = NULL );
		virtual ~FileTreeModel( void );
		bool setData( const QModelIndex& , const QVariant&, int role = Qt::EditRole ) override;

		int rowCount( const QModelIndex &parent= QModelIndex()) const override;

		int columnCount ( const QModelIndex &parent = QModelIndex())const override;
		void add_path( QString path  , uint64_t size );
		void add_full_path( QString path, uint64_t size);
		/* pure virtual function */
		QVariant data(const QModelIndex& index, int role) const;
		QModelIndex index(int row, int column,
				const QModelIndex& parent = QModelIndex()) const override;
		QModelIndex parent(const QModelIndex& index) const override;

		void update_children(const QModelIndex& _index, TreeItemFile* item, Qt::CheckState state);
		void update_parents(const QModelIndex& modelIndex, TreeItemFile* item);
		Qt::ItemFlags flags(const QModelIndex& index) const;
		QVariant headerData(int section, Qt::Orientation orientation,
				int role = Qt::DisplayRole) const override;
		int get_checked_path( QStringList*);/* not working */
	private:
		TreeItemFile * root_item;
		
};

#endif
