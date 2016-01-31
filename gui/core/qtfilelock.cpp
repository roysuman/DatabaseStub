/*
 * =====================================================================================
 *
 *       Filename:  qtfilelock.cpp
 *
 *       Description:  
 *
 *       Version:  1.0
 *       Created:  Tuesday 19 January 2016 07:25:43  IST
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


#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#include "qtfilelock.h"

QtLockedFile::QtLockedFile(): QFile(){
	m_lock_mode = NoLock;
}


QtLockedFile::QtLockedFile(const QString& name): QFile(name){
	m_lock_mode = NoLock;
}

bool 
QtLockedFile::open(OpenMode mode){
	if(mode & QIODevice::Truncate){
		qWarning("QtLockedFile::open(): Truncate mode not allowed.");
		return false;
	}
	return QFile::open(mode);
}


bool 
QtLockedFile::isLocked() const{
	return m_lock_mode != NoLock;
}

QtLockedFile::LockMode QtLockedFile::lockMode() const{
	return m_lock_mode;
}

bool QtLockedFile::lock(LockMode mode, bool block)
{
	if(!isOpen())
	{
		qWarning("QtLockedFile::lock(): file is not opened");
		return false;
	}

	if(mode == NoLock)
	{
		return unlock();
	}

	if(mode == m_lock_mode)
	{
		return true;
	}

	if(m_lock_mode != NoLock)
	{
		unlock();
	}

	struct flock fl;

	fl.l_whence = SEEK_SET;

	fl.l_start = 0;

	fl.l_len = 0;

	fl.l_type = (mode == ReadLock) ? F_RDLCK : F_WRLCK;

	int cmd = block ? F_SETLKW : F_SETLK;

	int ret = fcntl(handle(), cmd, &fl);

	if(ret == -1)
	{
		if(errno != EINTR && errno != EAGAIN)
		{
			qWarning("QtLockedFile::lock(): fcntl: %s", strerror(errno));
		}

		return false;
	}

	m_lock_mode = mode;
	return true;
}


bool QtLockedFile::unlock()
{
	if(!isOpen())
	{
		qWarning("QtLockedFile::unlock(): file is not opened");
		return false;
	}

	if(!isLocked())
	{
		return true;
	}

	struct flock fl;

	fl.l_whence = SEEK_SET;

	fl.l_start = 0;

	fl.l_len = 0;

	fl.l_type = F_UNLCK;

	int ret = fcntl(handle(), F_SETLKW, &fl);

	if(ret == -1)
	{
		qWarning("QtLockedFile::lock(): fcntl: %s", strerror(errno));
		return false;
	}

	m_lock_mode = NoLock;
	return true;
}

QtLockedFile::~QtLockedFile()
{
	if(isOpen())
	{
		unlock();
	}
}

