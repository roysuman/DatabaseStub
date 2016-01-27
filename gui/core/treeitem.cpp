/*
 * =====================================================================================
 *
 *       Filename:  treeitem.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Sunday 24 January 2016 11:48:26  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  SIGCONT (suman roy), email.suman.roy@gmail.com
 *   Organization:  OPEN SOURCE
 *
 * =====================================================================================
 */

#include "treeitem.h"

#include <QDebug>
#include <QDir>
TreeItemFile::TreeItemFile(  const file_data_type& file_data , TreeItemFile *parent){
	item_data = file_data;
	parent_file_item = parent;
	return;
}

TreeItemFile::~TreeItemFile( void ){
	qDeleteAll( items_container);
	return;
}
void
TreeItemFile::set_data( int index , QVariant data){
	if ( index > 1 ){
		qDebug() <<" Index greater thean( > ) 1.."
			<<" we have only two columns ";
		return;
	}
	if ( index == 0 ){
		item_data.first = data.toString();
	}else{
		item_data.second = data;
	}
	return;
}

QVariant
TreeItemFile::get_data( int column_number )const{
	if ( column_number > 2 ){
		qDebug() << " column_number greatee that 2 "
			<<" table has only two column";
		return QVariant();
	}
	return ( column_number == 0 ?  item_data.first :  item_data.second);
}

int
TreeItemFile::child_count( void ) const{
	return items_container.count();
}

int
TreeItemFile::row_count( void ) const{
	if ( parent_file_item ){
		return parent_file_item->items_container.indexOf( const_cast<TreeItemFile*>(this));
	}
	return 0;
}

void
TreeItemFile::append_child( TreeItemFile *item ){
	items_container.append( item );
	return;
}

TreeItemFile*
TreeItemFile::get_child( int row){
	return items_container.value( row);
}



Qt::CheckState 
TreeItemFile::checked()
{
	return checked_state;
}
void 
TreeItemFile::set_checked(Qt::CheckState _checked)
{
	checked_state = _checked;

	if(_checked != Qt::PartiallyChecked)
		for(int loop = 0; loop < items_container.count(); loop++)
		{
			items_container.at(loop)->set_checked(_checked);
		}
}


QString 
TreeItemFile::get_path( void ){
	QString res = get_data(0).toString();
	TreeItemFile* parrent = get_parent();
	while(parrent != NULL && parrent->get_parent() != NULL){
		res = parrent->get_data(0).toString() + QDir::separator() + res;
		parrent = parrent->get_parent();
	}
	return res;
}
