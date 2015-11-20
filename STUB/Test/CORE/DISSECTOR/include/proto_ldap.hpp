
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
 *         Author:  Suman Roy(  )  (email.suman.roy@gmail.com), 
 *   Organization:  SELF
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
#include "../../../STRUCTURE/include/globalDatatypes.hpp"
#include "../../../STRUCTURE/include/rawdata_structure.hpp"
#include "ber.hpp"
#include <unordered_map>
#include "../../../SUPPORT/globalDatatypes.hpp"
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
		static  std::unordered_map< STUB_INT , std::string > resultCode;
	public:
        Ldap();
        ~Ldap();
	//this method will initilize ldap protocols into the mapping structure
	//by calling method defined at proto.hpp
	static bool initialize( void );
	static bool dissectLdap( actRawDataStruct * , STUB_INT );
        static STUB_INT dissectLdapProtocol( actRawDataStruct * , STUB_INT , STUB_INT );
	//for ldapbind request
        static STUB_INT dissectLdapBindRequest( const u_char * , STUB_INT , STUB_INT );
	
	static STUB_INT dissectLdapSearchRequest ( const u_char * , STUB_INT , STUB_INT );
	static STUB_INT dissectLdapFilter( const u_char * , STUB_INT , STUB_INT);
	static STUB_INT dissectAttributeDescAndLdapValue(const u_char * , STUB_INT , STUB_INT );
	static STUB_INT dissectLdapSubStringFilterItems( const u_char * , STUB_INT , STUB_INT);
	static STUB_INT dissectLdapSearchResultEntry( const u_char * , STUB_INT , STUB_INT );
	static STUB_INT dissectLdapPartialAttributes( const u_char * , STUB_INT , STUB_INT );
	static STUB_INT dissectLdapSearchResultDone( const u_char * , STUB_INT , STUB_INT );


};







#endif
