/*
 * =====================================================================================
 *
 *       Filename:  qtfilelock.h
 *
 *       Description:  
 *
 *       Version:  1.0
 *       Created:  Tuesday 19 January 2016 07:25:02  IST
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

#ifndef QTLOCKEDFILE_H
#define QTLOCKEDFILE_H

#include <QFile>
#include <QVector>

class QtLockedFile : public QFile
{
public:
        enum LockMode { NoLock = 0, ReadLock, WriteLock };

        QtLockedFile();
        QtLockedFile(const QString& name);
        ~QtLockedFile();

        bool open(OpenMode mode);

        bool lock(LockMode mode, bool block = true);
        bool unlock();
        bool isLocked() const;
        LockMode lockMode() const;

private:
        LockMode m_lock_mode;
};

#endif

