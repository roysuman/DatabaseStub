/*
 * =====================================================================================
 *
 *       Filename:  filetreemodel.cpp
 *
 *       Description:  
 *
 *       Version:  1.0
 *       Created:  Monday 25 January 2016 12:26:31  IST
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



#include "filetreemodel.h"

#include <QDebug>
#include <QDir>
#include <QCheckBox>
#include <QFileIconProvider>
#include <QFileInfo>
#include <QTemporaryFile>
#include <QQueue>
#include <QDesktopServices>

FileTreeModel::FileTreeModel(QObject *parent ):QAbstractItemModel( parent){
	QString d="FILE";
	QString count="COUNT";
	file_data_type root_data = qMakePair( d, QVariant::fromValue(count ) );
	root_item = new TreeItemFile( root_data);
	return;
}
FileTreeModel::~FileTreeModel( void ){
	delete root_item;
}


int
FileTreeModel::rowCount( const QModelIndex &parent ) const {
	TreeItemFile * parent_item;
	if ( parent.column() > 0 ){
		return 0;
	}
	if ( !parent.isValid()){
		parent_item = root_item; 
	}else{
		parent_item = static_cast< TreeItemFile*>(parent.internalPointer());
	}
	return parent_item->child_count();

}


int
FileTreeModel::columnCount( const QModelIndex& parent ) const {
	if(parent.isValid()){
		return static_cast<TreeItemFile*>(parent.internalPointer())->column_count();
	}else{
		return root_item->column_count();
	}
}

void
FileTreeModel::add_path( QString path , uint64_t size ){
	qDebug() <<" add the path to file tree view model"
		<<" Path "<<path<<"of size "<< size;

	path = QDir::toNativeSeparators( path );
	QStringList path_parts = path.split( QDir::separator());
	TreeItemFile *iterator = root_item;
	qDebug()<<"path_parts coont "<<path_parts.count()
		<<"child count "<<iterator->child_count();
	TreeItemFile *save = root_item;
	if ( root_item->child_count()  == 0){
		TreeItemFile *curr_item = root_item;
		for ( int loop =0 ; loop<path_parts.count() ; ++loop){
			curr_item->append_child(new TreeItemFile ( qMakePair( path_parts.at(loop), QVariant::fromValue(size)),curr_item));
			curr_item= curr_item->get_child( iterator->child_count() - 1);
		}
		root_item = save;
		return;
	}
	for ( int outer_loop = 0 ; outer_loop < path_parts.count(); outer_loop++){
		int found_index = -1;
		for ( int inner_loop = 0 ; inner_loop < iterator->child_count(); ++inner_loop){
			if ( iterator->get_child( inner_loop)->get_data(0).toString().compare(path_parts.at(outer_loop))== 0){
				found_index = inner_loop;

				break;
			}
		}
		if ( found_index >= 0 ){
			iterator = iterator->get_child( found_index);
			iterator->set_data( 1, QVariant::fromValue( iterator->get_data(1).toULongLong() + size));
		}else{
			iterator->append_child(new TreeItemFile ( qMakePair(path_parts.at(outer_loop),QVariant::fromValue(size)),iterator));
			iterator= iterator->get_child( iterator->child_count() - 1);
		}
	}
	root_item = save;
	return;
}

bool
FileTreeModel::setData( const QModelIndex& model_index, const QVariant& value, int role){
	if ( !model_index.isValid() ){
		return false;
	}
	TreeItemFile* item= static_cast<TreeItemFile*>(model_index.internalPointer());
	if ( role == Qt::CheckStateRole && model_index.column() == 0){
		Qt::CheckState state = static_cast<Qt::CheckState>(value.toInt());
		item->set_checked( state);
		update_children( model_index, item, state );
		update_parents( model_index, item );
		return true;
	}
	return QAbstractItemModel::setData( model_index, value, role);
}

void 
FileTreeModel::update_children(const QModelIndex& model_index, TreeItemFile* item, Qt::CheckState state)
{
	int child_count = item->child_count();

	if (child_count > 0)
	{
		for (int i = 0; i < child_count; i++)
		{
			TreeItemFile* child = item->get_child(i);
			child->set_checked(state);
			int sub_children_count = child->child_count();

			if (sub_children_count > 0)
			{
				update_children(index(i, 0, model_index), child, state);
			}
		}

		emit dataChanged(index(0, 0, model_index), index(child_count - 1, 0 , model_index));
	}
}

void 
FileTreeModel::update_parents(const QModelIndex& model_index, TreeItemFile* item){
	TreeItemFile* parent = item->get_parent();

	if (parent == NULL)
	{
		return;
	}

	bool all_unchecked = true, all_checked = true;

	for(int i = 0; i < parent->child_count(); i++){
		all_unchecked = all_unchecked && (parent->get_child(i)->checked() == Qt::Unchecked);
		all_checked = all_checked && (parent->get_child(i)->checked() == Qt::Checked);
	}

	QModelIndex parent_index = model_index.parent();

	if(all_unchecked)
	{
		parent->set_checked(Qt::Unchecked);
		emit dataChanged(parent_index, parent_index);
		parent = parent->get_parent();

		if (parent != NULL)
		{
			parent->set_checked(Qt::Checked);
			update_parents(parent_index, parent);
		}
	}
	else if(all_checked)
	{
		parent->set_checked(Qt::Checked);
		emit dataChanged(parent_index, parent_index);
		parent = parent->get_parent();

		if(parent != NULL)
		{
			parent->set_checked(Qt::Checked);
			update_parents(parent_index, parent);
		}
	}
	else
	{
		while (parent != root_item && parent_index.isValid()){
			parent->set_checked(Qt::PartiallyChecked);
			emit dataChanged(parent_index, parent_index);
			parent = parent->get_parent();
			parent_index = parent_index.parent();
		}
	}
}

QVariant 
FileTreeModel::data(const QModelIndex& index, int role) const{
	if ( !index.isValid()){
		return QVariant();
	}
	TreeItemFile *item = static_cast<TreeItemFile*>(index.internalPointer());
 	if ( role == Qt::CheckStateRole && index.column() == 0 ){
	//	return item->checked();
	}
	if ( role == Qt::DecorationRole && index.column() == 0 ){
		QString curr_path = item->get_path();
		QIcon icon;
		QFileInfo info(curr_path);
		QFileIconProvider icon_provider;
		QString suffix = info.suffix();
		if ( !suffix.isEmpty() && item->child_count() == 0){
			icon =icon_provider.icon( QFileIconProvider::File);

		}else{
			icon = icon_provider.icon(QFileIconProvider::Folder);
		}
		return icon;;
	}
	if ( role != Qt::DisplayRole){
		return QVariant();
	}
	return item->get_data(index.column());
}
	
	QModelIndex 
FileTreeModel::index(int row, int column,
		const QModelIndex& parent) const {
	if(!hasIndex(row, column, parent)){
		return QModelIndex();
	}
	TreeItemFile* parent_item;

	if(!parent.isValid()){
		parent_item = root_item;
	}else{
		parent_item = static_cast<TreeItemFile*>(parent.internalPointer());
	}

	TreeItemFile* child_item = parent_item->get_child(row);

	if(child_item)
	{
		return createIndex(row, column, child_item);
	}
	else
	{
		return QModelIndex();
	}
}
QModelIndex 
FileTreeModel::parent(const QModelIndex& index) const {
	if(!index.isValid()){
		return QModelIndex();
	}
	TreeItemFile* child_item = static_cast<TreeItemFile*>(index.internalPointer());
	TreeItemFile* parent_item = child_item->get_parent();

	if(parent_item == root_item)
	{
		return QModelIndex();
	}

	return createIndex(parent_item->row_count(), 0, parent_item);
}
		
Qt::ItemFlags 
FileTreeModel::flags(const QModelIndex& index) const{
	if(!index.isValid())
	{
		return 0;
	}

	return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable ;
}

QVariant 
FileTreeModel::headerData(int section, Qt::Orientation orientation,
                                   int role) const
{
	if (role == Qt::InitialSortOrderRole)
	{
		return Qt::DescendingOrder;
	}

	if(orientation == Qt::Horizontal && role == Qt::DisplayRole)
	{
		return root_item->get_data(section);
	}

	return QVariant();
}




void
FileTreeModel::add_full_path( QString full_path , uint64_t size ){
	qDebug() <<" add the path to file tree view model"
		<<" Path "<<full_path<<"of size "<< size;

//	path = QDir::toNativeSeparators( path );
//	QStringList path_parts = path.split( QDir::separator());
	TreeItemFile *iterator = root_item;
	TreeItemFile *save = root_item;
	if ( root_item->child_count()  == 0){
		TreeItemFile *curr_item = root_item;
		curr_item->append_child( new TreeItemFile( qMakePair( full_path, QVariant::fromValue( size)),curr_item));
		/*
		for ( int loop =0 ; loop<path_parts.count() ; ++loop){
			curr_item->append_child(new TreeItemFile ( qMakePair( path_parts.at(loop), QVariant::fromValue(size)),curr_item));
			curr_item= curr_item->get_child( iterator->child_count() - 1);
		}*/
		root_item = save;
		return;
	}

	int found_index = -1;
	for ( int loop = 0 ; loop < iterator->child_count(); ++loop){
		if ( iterator->get_child( loop)->get_data(0).toString().compare(full_path)== 0){
			found_index = loop;
			break;
		}
	}
	if ( found_index >= 0 ) {
		qDebug()<<" File path aready registered";
	 }else{
		 iterator->append_child( new TreeItemFile( qMakePair( full_path, QVariant::fromValue( size)),iterator));
		 iterator= iterator->get_child( iterator->child_count() - 1);
	 }
	root_item = save;
	return;
}
int
FileTreeModel::get_checked_path( QStringList *paths){
	TreeItemFile* iterator = root_item;
	int count = 0;
	QString path;
	for ( int loop =0; loop < iterator->child_count(); ++loop){
		if( iterator->get_child( loop )->checked() == Qt::Checked){
			qDebug()<<"Matched checked"
				<<"Child count "
				<<iterator->get_child( loop )->child_count()
				<<"Path "<<iterator->get_path();
		}
		if ( ( iterator->get_child( loop )->checked() == Qt::Checked) && (iterator->get_child(loop)->child_count() == 0 ) ){
			paths->append (iterator->get_path());
		}
		
	}
	QStringList::Iterator it;
	for ( it = paths->begin(); it != paths->end();++it){
		qDebug()<<*it;
	}
	return count;
}
