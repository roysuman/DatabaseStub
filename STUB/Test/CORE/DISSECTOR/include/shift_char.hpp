/*
 * =====================================================================================
 *
 *       Filename:  shift_char.hpp
 *
 *    Description:  this code to genarate raw data packet helper.
 *    		    to copy a STUB_INT value to a STUB_CHAR [] need some functions to implement shift operations.
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

#ifndef SHIFT_CHAR_HPP_
#define SHIFT_CHAR_HPP_

#include <iostream>
#include "../../../SUPPORT/globalDatatypes.hpp"
extern bool nths16 ( STUB_CHAR *& , STUB_INT , STUB_INT );
extern bool nth24 ( STUB_CHAR *& , STUB_INT , STUB_INT );
extern bool nth32 ( STUB_CHAR * , STUB_INT , STUB_INT );
extern bool lths16 ( STUB_CHAR * , STUB_INT , STUB_INT );
		
		// Shift each byte into the low-order position and mask it off
		// bytes[0] = msg & 0xff;
		// bytes[1] = (msg >> 8) & 0xff;
		// bytes[2] = (msg >> 16) & 0xff;{



/* #define ntohs16( p  )   ((STUB_UINT16)                       \
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
*/
#endif

