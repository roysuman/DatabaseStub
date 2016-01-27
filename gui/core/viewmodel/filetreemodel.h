/*
 * =====================================================================================
 *
 *       Filename:  filetreemodel.h
 *
 *    Description:  file tree model for open tcpdump
 *
 *        Version:  1.0
 *        Created:  Monday 25 January 2016 12:15:32  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  SIGCONT (suman roy), email.suman.roy@gmail.com
 *   Organization:  OPEN SOURCE
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
