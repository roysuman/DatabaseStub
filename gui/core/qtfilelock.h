/*
 * =====================================================================================
 *
 *       Filename:  qtfilelock.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Tuesday 19 January 2016 07:25:02  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  SIGCONT (suman roy), email.suman.roy@gmail.com
 *   Organization:  OPEN SOURCE
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

