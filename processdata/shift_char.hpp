/*
 * =====================================================================================
 *
 *       Filename:  shift_char.h
 *
 *    Description:  read and create lthos & nthos data
 *
 *        Version:  1.0
 *        Created:  Thursday 19 December 2013 11:16:30  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy (), 
 *   Organization:  SELF
 *
 * =====================================================================================
 */

#ifndef SHIFT_CHAR_H_
#define SHIFT_CHAR_H_

#include <iostream>

#include "../common/vserver_globals.h"

inline void
nths16 ( VS_UINT8 *&tvb , VS_ULONG offset , VS_INT32 data ) {

	tvb [ offset  ] = data & 0xff;
	tvb [ ++offset ] = ( data >> 8 ) & 0xff ;
	return;
}

inline void
nth24 ( VS_UINT8  *&tvb , VS_ULONG offset , VS_INT32  data ){

	tvb [ offset ] = data & 0xff;
	tvb [ ++offset ] = ( data >> 8 ) & 0xff ;
	tvb [ ++offset ] = ( data >>16 ) & 0xff ;
	return;
}

inline void
nth32( VS_UINT8 *&tvb , VS_ULONG offset , VS_INT32 data ){

	tvb [ offset ] = data & 0xff;
	tvb [ ++offset ] = ( data >> 8 ) & 0xff ;
	tvb [ ++offset ] = ( data >>16 ) & 0xff ;
	tvb [ ++offset ] = ( data >>32 ) & 0xff ;
	return;
}

inline void
lths16( VS_UINT8 *&tvb , VS_ULONG  offset , VS_INT32  value ){

	tvb [ offset ] = value & 0xff;
	tvb [ ++offset ] =( value >> 8 ) & 0xff;
	return;
}
#define ntohs16(p)  ((VS_UINT16)                       \
                     ((VS_UINT16)*((const VS_UINT8 *)(p)+0)<<8|  \
                      (VS_UINT16)*((const VS_UINT8 *)(p)+1)<<0))

#define ntoh24(p)   ((VS_UINT32)*((const VS_UINT8 *)(p)+0)<<16|  \
                     (VS_UINT32)*((const VS_UINT8 *)(p)+1)<<8|   \
                     (VS_UINT32)*((const VS_UINT8 *)(p)+2)<<0)

#define ntohl32(p)  ((VS_UINT32)*((const VS_UINT8 *)(p)+0)<<24|  \
                     (VS_UINT32)*((const VS_UINT8 *)(p)+1)<<16|  \
                     (VS_UINT32)*((const VS_UINT8 *)(p)+2)<<8|   \
                     (VS_UINT32)*((const VS_UINT8 *)(p)+3)<<0)

#define ntoh40(p)  ((VS_UINT64)*((const VS_UINT8 *)(p)+0)<<32|  \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+1)<<24|  \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+2)<<16|  \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+3)<<8|   \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+4)<<0)

#define ntoh48(p)  ((VS_UINT64)*((const VS_UINT8 *)(p)+0)<<40|  \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+1)<<32|  \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+2)<<24|  \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+3)<<16|  \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+4)<<8|   \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+5)<<0)

#define ntoh56(p)  ((VS_UINT64)*((const VS_UINT8 *)(p)+0)<<48|  \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+1)<<40|  \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+2)<<32|  \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+3)<<24|  \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+4)<<16|  \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+5)<<8|   \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+6)<<0)

#define ntoh64(p)  ((VS_UINT64)*((const VS_UINT8 *)(p)+0)<<56|  \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+1)<<48|  \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+2)<<40|  \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+3)<<32|  \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+4)<<24|  \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+5)<<16|  \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+6)<<8|   \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+7)<<0)


#define letohs16(p) ((VS_UINT16)                       \
                     ((VS_UINT16)*((const VS_UINT8 *)(p)+1)<<8|  \
                      (VS_UINT16)*((const VS_UINT8 *)(p)+0)<<0))

#define letoh24(p) ((VS_UINT32)*((const VS_UINT8 *)(p)+2)<<16|  \
                     (VS_UINT32)*((const VS_UINT8 *)(p)+1)<<8|   \
                     (VS_UINT32)*((const VS_UINT8 *)(p)+0)<<0)

#define letohl32(p) ((VS_UINT32)*((const VS_UINT8 *)(p)+3)<<24|  \
                     (VS_UINT32)*((const VS_UINT8 *)(p)+2)<<16|  \
                     (VS_UINT32)*((const VS_UINT8 *)(p)+1)<<8|   \
                     (VS_UINT32)*((const VS_UINT8 *)(p)+0)<<0)

#define letoh40(p) ((VS_UINT64)*((const VS_UINT8 *)(p)+4)<<32|  \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+3)<<24|  \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+2)<<16|  \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+1)<<8|   \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+0)<<0)

#define letoh48(p) ((VS_UINT64)*((const VS_UINT8 *)(p)+5)<<40|  \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+4)<<32|  \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+3)<<24|  \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+2)<<16|  \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+1)<<8|   \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+0)<<0)

#define letoh56(p) ((VS_UINT64)*((const VS_UINT8 *)(p)+6)<<48|  \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+5)<<40|  \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+4)<<32|  \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+3)<<24|  \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+2)<<16|  \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+1)<<8|   \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+0)<<0)

#define letoh64(p) ((VS_UINT64)*((const VS_UINT8 *)(p)+7)<<56|  \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+6)<<48|  \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+5)<<40|  \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+4)<<32|  \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+3)<<24|  \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+2)<<16|  \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+1)<<8|   \
                     (VS_UINT64)*((const VS_UINT8 *)(p)+0)<<0)

#endif

