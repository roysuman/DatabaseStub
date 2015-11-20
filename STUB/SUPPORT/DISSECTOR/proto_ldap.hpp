
/*
 * =====================================================================================
 *
 *       Filename:  proto_ldap.hpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Thursday 23 April 2014 10:05:30  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Suman Roy( 346163 )  (roy.suman@cognizant.com), 
 *   Organization:  Cognizant Technological Solutions
 *
 * =====================================================================================
 */
#ifndef PROTO_LDAP_HPP_
#define PROTO_LDAP_HPP_

#include<iostream>
#include <sstream>
#include "proto.hpp"
#include "types.hpp"
#include "buffer.hpp"
#include "field.hpp"
#include "../../STRUCTURE/sumanGtkmm.hpp"
#include "../../STRUCTURE/rawdata_structure.hpp"
#include "ber.hpp"
#include <unordered_map>
#define noDissector 100 // no of ldap dissector
#define PORT_LDAP 389 // port dedicated for ldap
/* Initialize the protocol and registered fields */
/*
#define TCP_PORT_LDAP			389
#define TCP_PORT_LDAPS			636
#define UDP_PORT_CLDAP			389
#define TCP_PORT_GLOBALCAT_LDAP         3268 //Windows 2000 Global Catalog 
*/
//define class for ldap
class Ldap{
	private:
		static  std::unordered_map< int , std::string > resultCode;
	public:
        Ldap();
        ~Ldap();
	//this method will initilize ldap protocols into the mapping structure
	//by calling method defined at proto.hpp
	static bool initialize( void );
	static bool dissectLdap( actRawDataStruct * , int );
        static int dissectLdapProtocol( actRawDataStruct * , int , int );
	//for ldapbind request
        static int dissectLdapBindRequest( const u_char * , int , int );
	
	static int dissectLdapSearchRequest ( const u_char * , int , int );
	static int dissectLdapFilter( const u_char * , int , int);
	static int dissectAttributeDescAndLdapValue(const u_char * , int , int );
	static int dissectLdapSubStringFilterItems( const u_char * , int , int);
	static int dissectLdapSearchResultEntry( const u_char * , int , int );
	static int dissectLdapPartialAttributes( const u_char * , int , int );
	static int dissectLdapSearchResultDone( const u_char * , int , int );


};







#endif
