/*
 * =====================================================================================
 *
 *       Filename:  vserver_globals.h
 *
 *    Description:  this file contains all typedef dec regarding to GTKMM
 *
 *        Version:  1.0
 *        Created:  Monday 09 December 2013 10:16:44  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy (), 
 *   Organization:  SELF
 *
 * =====================================================================================
 */

#ifndef VSERVER_GLOBALS_H
#define VSERVER_GLOBALS_H

#define ZERO 0
#define IS_LESS_THAN(X,Y) ({    \
		bool    return_val;     \
		if ( X < Y ){ return_val= true;}        \
		else{ return_val= false;}       \
		return_val;     \
})


#define IS_LESS_THAN_EQUALITY(X,Y) ({    \
		bool    return_val;     \
		if ( X <= Y ){ return_val= true;}        \
		else{ return_val= false;}       \
		return_val;     \
})

#define IS_GREATER_THAN(X,Y) ({    \
		bool    return_val;     \
		if ( X > Y ){ return_val= true;}        \
		else{ return_val= false;}       \
		return_val;     \
})


#define IS_GREATER_THAN_EQUALITY(X,Y) ({    \
		bool    return_val;     \
		if ( X >= Y ){ return_val= true;}        \
		else{ return_val= false;}       \
		return_val;     \
})
/* customized datatype */
typedef signed long VS_LONG;
typedef unsigned long VS_ULONG;
typedef signed char VS_INT8;
typedef unsigned char VS_UINT8;
typedef signed short VS_INT16;
typedef unsigned short VS_UINT16;
typedef signed int VS_INT32;
typedef unsigned int VS_UINT32;
typedef signed long long VS_INT64;
typedef unsigned long long VS_UINT64;
typedef float VS_FLOAT;
typedef double VS_DOUBLE;
typedef bool VS_BOOL;

#endif

