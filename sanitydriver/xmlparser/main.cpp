/*
 * =====================================================================================
 *
 *       Filename:  main.cpp
 *
 *       Description:  
 *
 *       Version:  1.0
 *       Created:  Monday 01 February 2016 02:20:30  IST
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


#include <QCoreApplication>
#include <QDebug>
#include "/media/suman/7ef2db3a-45a7-43d5-9bad-189a525685f1/MY_PROJECT/git/DatabaseStub/core/xmlparser/parsermanager.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
qDebug()<<"SUMAN";
std::string path= "/home/suman/MY_PROJECT/git/DatabaseStub/config/vserver-util.xml";
ParserManager ins(path);
ins.parse_config();
    return a.exec();
}
