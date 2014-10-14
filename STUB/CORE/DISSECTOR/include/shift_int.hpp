/*
 * =====================================================================================
 *
 *       Filename:  shif_STUB_INT.hpp
 *
 *    Description:  this file contains all shifting opeeration needed to transfer data from one format to another format
 *
 *        Version:  1.0
 *        Created:  Monday 23 September 2013 10:54:41  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy (), 
 *   Organization:  SELF
 *
 * =====================================================================================
 */

#ifndef SHIF_INT_HPP_
#define SHIF_INT_HPP_
#include "../../../SUPPORT/globalDatatypes.hpp"

/* PoSTUB_INTer versions of g_ntohs and g_ntohl.  Given a poSTUB_INTer to a member of a
 * byte array, returns the value of the two or four bytes at the poSTUB_INTer.
 * The pletoh[sl] versions return the little-endian representation.
 */
//thanks wireshark
#define ntohs16(p)   ((STUB_UINT16)                       \
                     ((STUB_UINT16)*((const STUB_UINT8 *)(p)+0)<<8|  \
                      (STUB_UINT16)*((const STUB_UINT8 *)(p)+1)<<0))

#define ntoh24(p)  ((STUB_UINT32)*((const STUB_UINT8 *)(p)+0)<<16|  \
                     (STUB_UINT32)*((const STUB_UINT8 *)(p)+1)<<8|   \
                     (STUB_UINT32)*((const STUB_UINT8 *)(p)+2)<<0)

#define ntohl32(p)   ((STUB_UINT32)*((const STUB_UINT8 *)(p)+0)<<24|  \
                     (STUB_UINT32)*((const STUB_UINT8 *)(p)+1)<<16|  \
                     (STUB_UINT32)*((const STUB_UINT8 *)(p)+2)<<8|   \
                     (STUB_UINT32)*((const STUB_UINT8 *)(p)+3)<<0)

#define ntoh40(p)  ((STUB_UINT64)*((const STUB_UINT8 *)(p)+0)<<32|  \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+1)<<24|  \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+2)<<16|  \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+3)<<8|   \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+4)<<0)

#define ntoh48(p)  ((STUB_UINT64)*((const STUB_UINT8 *)(p)+0)<<40|  \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+1)<<32|  \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+2)<<24|  \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+3)<<16|  \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+4)<<8|   \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+5)<<0)

#define ntoh56(p)  ((STUB_UINT64)*((const STUB_UINT8 *)(p)+0)<<48|  \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+1)<<40|  \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+2)<<32|  \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+3)<<24|  \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+4)<<16|  \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+5)<<8|   \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+6)<<0)

#define ntoh64(p)  ((STUB_UINT64)*((const STUB_UINT8 *)(p)+0)<<56|  \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+1)<<48|  \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+2)<<40|  \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+3)<<32|  \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+4)<<24|  \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+5)<<16|  \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+6)<<8|   \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+7)<<0)


#define letohs16(p)  ((STUB_UINT16)                       \
                     ((STUB_UINT16)*((const STUB_UINT8 *)(p)+1)<<8|  \
                      (STUB_UINT16)*((const STUB_UINT8 *)(p)+0)<<0))

#define letoh24(p) ((STUB_UINT32)*((const STUB_UINT8 *)(p)+2)<<16|  \
                     (STUB_UINT32)*((const STUB_UINT8 *)(p)+1)<<8|   \
                     (STUB_UINT32)*((const STUB_UINT8 *)(p)+0)<<0)

#define letohl32(p)  ((STUB_UINT32)*((const STUB_UINT8 *)(p)+3)<<24|  \
                     (STUB_UINT32)*((const STUB_UINT8 *)(p)+2)<<16|  \
                     (STUB_UINT32)*((const STUB_UINT8 *)(p)+1)<<8|   \
                     (STUB_UINT32)*((const STUB_UINT8 *)(p)+0)<<0)

#define letoh40(p) ((STUB_UINT64)*((const STUB_UINT8 *)(p)+4)<<32|  \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+3)<<24|  \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+2)<<16|  \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+1)<<8|   \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+0)<<0)

#define letoh48(p) ((STUB_UINT64)*((const STUB_UINT8 *)(p)+5)<<40|  \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+4)<<32|  \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+3)<<24|  \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+2)<<16|  \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+1)<<8|   \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+0)<<0)

#define letoh56(p) ((STUB_UINT64)*((const STUB_UINT8 *)(p)+6)<<48|  \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+5)<<40|  \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+4)<<32|  \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+3)<<24|  \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+2)<<16|  \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+1)<<8|   \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+0)<<0)

#define letoh64(p) ((STUB_UINT64)*((const STUB_UINT8 *)(p)+7)<<56|  \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+6)<<48|  \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+5)<<40|  \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+4)<<32|  \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+3)<<24|  \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+2)<<16|  \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+1)<<8|   \
                     (STUB_UINT64)*((const STUB_UINT8 *)(p)+0)<<0)

#define pletohll(p) ((unsigned long long)*((const unsigned STUB_CHAR *)(p)+7)<<56|  \
                     (unsigned long long)*((const unsigned STUB_CHAR *)(p)+6)<<48|  \
                      (unsigned long long)*((const unsigned STUB_CHAR *)(p)+5)<<40|  \
                      (unsigned long long)*((const unsigned STUB_CHAR *)(p)+4)<<32|  \
                      (unsigned long long)*((const unsigned STUB_CHAR *)(p)+3)<<24|  \
                      (unsigned long long)*((const unsigned STUB_CHAR *)(p)+2)<<16|  \
                      (unsigned long long)*((const unsigned STUB_CHAR *)(p)+1)<<8|   \
                      (unsigned long long)*((const unsigned STUB_CHAR *)(p)+0)<<0)

#define pletohss(p) ((unsigned long long)*((const unsigned STUB_CHAR *)(p)+0)<<56|  \
                     (unsigned long long)*((const unsigned STUB_CHAR *)(p)+1)<<48|  \
                      (unsigned long long)*((const unsigned STUB_CHAR *)(p)+2)<<40|  \
                      (unsigned long long)*((const unsigned STUB_CHAR *)(p)+3)<<32|  \
                      (unsigned long long)*((const unsigned STUB_CHAR *)(p)+4)<<24|  \
                      (unsigned long long)*((const unsigned STUB_CHAR *)(p)+5)<<16|  \
                      (unsigned long long)*((const unsigned STUB_CHAR *)(p)+6)<<8|   \
                      (unsigned long long)*((const unsigned STUB_CHAR *)(p)+7)<<0)


#define pletohl(p)  ((unsigned long)*((const unsigned STUB_CHAR *)(p)+3)<<24|  \
                      (unsigned long)*((const unsigned STUB_CHAR *)(p)+2)<<16|  \
                      (unsigned long)*((const unsigned STUB_CHAR *)(p)+1)<<8|   \
                      (unsigned long)*((const unsigned STUB_CHAR *)(p)+0)<<0)

#define pletohs(p)  ((unsigned long)*((const unsigned STUB_CHAR *)(p)+0)<<24|  \
                      (unsigned long)*((const unsigned STUB_CHAR *)(p)+1)<<16|  \
                      (unsigned long)*((const unsigned STUB_CHAR *)(p)+2)<<8|   \
                      (unsigned long)*((const unsigned STUB_CHAR *)(p)+3)<<0)

/* PoSTUB_INTer routines to put items out in a particular byte order.
 * These will work regardless of the byte alignment of the poSTUB_INTer.

//needed
//#define Htons(p, v) \
//	{ 				\
//	((STUB_UINT8*)(p))[0] = (STUB_UINT8)((v) >> 8);	\
//	((STUB_UINT8*)(p))[1] = (STUB_UINT8)((v) >> 0);	\
//	}
*/
#define Htonl(p, v) \
	{ 				\
	((STUB_UINT8*)(p))[0] = (STUB_UINT8)((v) >> 24);	\
	((STUB_UINT8*)(p))[1] = (STUB_UINT8)((v) >> 16);	\
	((STUB_UINT8*)(p))[2] = (STUB_UINT8)((v) >> 8);	\
	((STUB_UINT8*)(p))[3] = (STUB_UINT8)((v) >> 0);	\
	}


/* Macros to byte-swap 32-bit and 16-bit quantities. */
#define	BSWAP32(x) \
	((((x)&0xFF000000)>>24) | \
	 (((x)&0x00FF0000)>>8) | \
	 (((x)&0x0000FF00)<<8) | \
	 (((x)&0x000000FF)<<24))
#define	BSWAP16(x) \
	 ((((x)&0xFF00)>>8) | \
	  (((x)&0x00FF)<<8))

/* Turn host-byte-order values into little-endian values. */
#define htoles(s) GUINT16_TO_LE(s)
#define htolel(l) GUINT32_TO_LE(l)


#endif

