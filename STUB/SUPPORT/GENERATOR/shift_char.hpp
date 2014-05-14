/*
 * =====================================================================================
 *
 *       Filename:  shift_char.hpp
 *
 *    Description:  this code to genarate raw data packet helper.
 *    		    to copy a int value to a char [] need some functions to implement shift operations.
 *
 *        Version:  1.0
 *        Created:  Thursday 19 December 2013 11:16:30  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy (), 
 *   Organization:  Cognizant Technological solutions
 *
 * =====================================================================================
 */

#ifndef SHIFT_CHAR_HPP_
#define SHIFT_CHAR_HPP_
#include "../../STRUCTURE/sumanGtkmm.hpp"
#include <iostream>
extern bool nths16 ( char *& , int , int );
extern bool nth24 ( char *& , int , int );
		
		// Shift each byte into the low-order position and mask it off
		// bytes[0] = msg & 0xff;
		// bytes[1] = (msg >> 8) & 0xff;
		// bytes[2] = (msg >> 16) & 0xff;{



/* #define ntohs16( p  )   ((guint16)                       \
                     ((guint16)*((const guint8 *)(p)+0)<<8|  \
                      (guint16)*((const guint8 *)(p)+1)<<0))

#define ntoh24(p)  ((guint32)*((const guint8 *)(p)+0)<<16|  \
                     (guint32)*((const guint8 *)(p)+1)<<8|   \
                     (guint32)*((const guint8 *)(p)+2)<<0)

#define ntohl32(p)   ((guint32)*((const guint8 *)(p)+0)<<24|  \
                     (guint32)*((const guint8 *)(p)+1)<<16|  \
                     (guint32)*((const guint8 *)(p)+2)<<8|   \
                     (guint32)*((const guint8 *)(p)+3)<<0)

#define ntoh40(p)  ((guint64)*((const guint8 *)(p)+0)<<32|  \
                     (guint64)*((const guint8 *)(p)+1)<<24|  \
                     (guint64)*((const guint8 *)(p)+2)<<16|  \
                     (guint64)*((const guint8 *)(p)+3)<<8|   \
                     (guint64)*((const guint8 *)(p)+4)<<0)

#define ntoh48(p)  ((guint64)*((const guint8 *)(p)+0)<<40|  \
                     (guint64)*((const guint8 *)(p)+1)<<32|  \
                     (guint64)*((const guint8 *)(p)+2)<<24|  \
                     (guint64)*((const guint8 *)(p)+3)<<16|  \
                     (guint64)*((const guint8 *)(p)+4)<<8|   \
                     (guint64)*((const guint8 *)(p)+5)<<0)

#define ntoh56(p)  ((guint64)*((const guint8 *)(p)+0)<<48|  \
                     (guint64)*((const guint8 *)(p)+1)<<40|  \
                     (guint64)*((const guint8 *)(p)+2)<<32|  \
                     (guint64)*((const guint8 *)(p)+3)<<24|  \
                     (guint64)*((const guint8 *)(p)+4)<<16|  \
                     (guint64)*((const guint8 *)(p)+5)<<8|   \
                     (guint64)*((const guint8 *)(p)+6)<<0)

#define ntoh64(p)  ((guint64)*((const guint8 *)(p)+0)<<56|  \
                     (guint64)*((const guint8 *)(p)+1)<<48|  \
                     (guint64)*((const guint8 *)(p)+2)<<40|  \
                     (guint64)*((const guint8 *)(p)+3)<<32|  \
                     (guint64)*((const guint8 *)(p)+4)<<24|  \
                     (guint64)*((const guint8 *)(p)+5)<<16|  \
                     (guint64)*((const guint8 *)(p)+6)<<8|   \
                     (guint64)*((const guint8 *)(p)+7)<<0)


#define letohs16(p)  ((guint16)                       \
                     ((guint16)*((const guint8 *)(p)+1)<<8|  \
                      (guint16)*((const guint8 *)(p)+0)<<0))

#define letoh24(p) ((guint32)*((const guint8 *)(p)+2)<<16|  \
                     (guint32)*((const guint8 *)(p)+1)<<8|   \
                     (guint32)*((const guint8 *)(p)+0)<<0)

#define letohl32(p)  ((guint32)*((const guint8 *)(p)+3)<<24|  \
                     (guint32)*((const guint8 *)(p)+2)<<16|  \
                     (guint32)*((const guint8 *)(p)+1)<<8|   \
                     (guint32)*((const guint8 *)(p)+0)<<0)

#define letoh40(p) ((guint64)*((const guint8 *)(p)+4)<<32|  \
                     (guint64)*((const guint8 *)(p)+3)<<24|  \
                     (guint64)*((const guint8 *)(p)+2)<<16|  \
                     (guint64)*((const guint8 *)(p)+1)<<8|   \
                     (guint64)*((const guint8 *)(p)+0)<<0)

#define letoh48(p) ((guint64)*((const guint8 *)(p)+5)<<40|  \
                     (guint64)*((const guint8 *)(p)+4)<<32|  \
                     (guint64)*((const guint8 *)(p)+3)<<24|  \
                     (guint64)*((const guint8 *)(p)+2)<<16|  \
                     (guint64)*((const guint8 *)(p)+1)<<8|   \
                     (guint64)*((const guint8 *)(p)+0)<<0)

#define letoh56(p) ((guint64)*((const guint8 *)(p)+6)<<48|  \
                     (guint64)*((const guint8 *)(p)+5)<<40|  \
                     (guint64)*((const guint8 *)(p)+4)<<32|  \
                     (guint64)*((const guint8 *)(p)+3)<<24|  \
                     (guint64)*((const guint8 *)(p)+2)<<16|  \
                     (guint64)*((const guint8 *)(p)+1)<<8|   \
                     (guint64)*((const guint8 *)(p)+0)<<0)

#define letoh64(p) ((guint64)*((const guint8 *)(p)+7)<<56|  \
                     (guint64)*((const guint8 *)(p)+6)<<48|  \
                     (guint64)*((const guint8 *)(p)+5)<<40|  \
                     (guint64)*((const guint8 *)(p)+4)<<32|  \
                     (guint64)*((const guint8 *)(p)+3)<<24|  \
                     (guint64)*((const guint8 *)(p)+2)<<16|  \
                     (guint64)*((const guint8 *)(p)+1)<<8|   \
                     (guint64)*((const guint8 *)(p)+0)<<0)
*/
#endif

