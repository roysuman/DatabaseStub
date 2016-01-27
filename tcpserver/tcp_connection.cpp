/*
 * =====================================================================================
 *
 *       Filename:  tcp_connection.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  Wednesday 07 October 2015 12:15:01  IST
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  ROY (), email.suman.roy@gmail.com
 *   Organization:  NA
 *
 * =====================================================================================
 */

#include "tcp_connection.h"

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  TcpConnection
 *  Description:  construiction of TcpConnection class. create an instance of connection
 *                with accepted sochet descriptor number and port. This is the one and only way to
 *                keep tracjk of connection
 *                @@connection_id: a id to identify each connection
 *                @@socket: acceoted connection socket fd
 *                @@port: port of connected socket
 * =====================================================================================
 */
TcpConnection::TcpConnection( uint32_t connection_id , int socket ,
		              uint32_t port):connection_id(connection_id),
	                      socket_id(socket),bind_port(port){
	send_buffer = nullptr;
	recv_buffer = nullptr;
	tcp_con_state = connection_open;/* connected */
	connection_is_active = true;
	/* this thread will process all incoming and outgoing packets on this connection */
	pthread_create( &loop_thread , nullptr,&TcpConnection::run_loop_process_connection,this);
	return;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  ~TcpConneection
 *  Description:  deconstructor of TcpConnection free memory and disconnect the connection
 *                When one connection is getting closed or the proces is getting terminated
 * =====================================================================================
 */
TcpConnection::~TcpConnection(){
#ifdef INFO
	std::cout<< "Deconstrutor of tcp connection\n";
	//TODO wait for the run thread
	pthread_join( loop_thread , NULL );
	buffer_make_empty();
//	disconnect_connection();
	safe_delete(recv_buffer);//TODO implement safe_delete
	safe_delete(send_buffer);
	return;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  send_data
 *  Description:  it's public function.. veasible from outside. Outsider will call it to
 *                send data. Actually it will coppy the data tnto the send buffer
 *                @@dat: data to send
 *                @@length: no of bytes to send
 * =====================================================================================
 */
bool
TcpConnection::send_data( const unsigned char* data, size_t length){
#ifdef INFO
	std::cout<<"send data of size [ "<<length<<"  \n";
#endif
	if ( !is_connected() )
		return false;
	if ( !length){
		return true;
	}
	return  send_buffer_push( data , length );
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  send_buffer_push
 *  Description:  insert the send data into the end of the send buffer
 *                ::send method will read data from this send buffer and will 
 *                forward to kernel buffer
 *                @@data: the data
 *                @@length: bytes count of data
 * =====================================================================================
 */
void
TcpConnection::send_buffer_push( const unsigned char* data, size_t length ){
	unsigned char    *temp ;

	return_val = true;

	if ( send_buffer == nullptr ){
		send_buffer = new unsigned char [ length ];
		send_buffer_used  = 0;
		send_buffer_capacity = length;
	}else if ( ( send_buffer_capacity - send_buffer_used ) <  length ){
		send_buffer_capacity += length + 1024;
		temp = new unsigned char [ send_buffer_capacity ];
		memcpy(temp , send_buffer , send_buffer_used);
		safe_delete(send_buffer);
		send_buffer = temp;
	}
	memcpy ( &( send_buffer + send_buffer_used ), data , length );
	send_buffer_used += length;
	return;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  send_buffer_push_front
 *  Description:  push the data infront of the send buffer
 *                when sending is getting failed due to kernel buffer full.
 *                This method will coppy the extra bytes infront of the send buffer
 * =====================================================================================
 */

void
TcpConnection::send_buffer_push_front( unsigned char*data, size_t length){
	unsigned char    *temp_buff;
	if ( send_buffer == 0 ){
		send_buffer = new unsigned char [ length ];
		send_buffer_capacity = length;
		send_buffer_used = 0;
	}
	else if ( length > ( send_buffer_capacity - send_buffer_used ) ){
		send_buffer_capacity += length;
		temp_buff = new unsigned char[ send_buffer_capacity];
		memcpy(&temp[length],send_buffer,send_buffer_used);
		safe_delete_array(send_buffer);
		send_buffer = temp_buff;
	}
	memcpy(send_buffer,data,length);
	send_buffer_used += length;
	return;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  send_buffer_pop
 *  Description:  pop data from the send buffer and ::send to kernel buffer
 *               @@data: pointer reference to hold the data
 *               @@length: no of byte read from local send buffer                
 * =====================================================================================
 */
bool
TcpConnection::send_buffer_pop( unsigned char **data, size_t *length){
	bool    return_val;
	if ( send_buffer ){
		*data = send_buffer;
		*length = send_buffer_used;
		send_buffer = 0;
		return_val = true;
	}else return_val = false;
	return return_val;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  disconnect_connection
 *  Description:  close the opened connection
 * =====================================================================================
 */
void
TcpConnection::disconnect_connection( void){
	if ( socket_id != 0 && socket_id != SOCKET_INVALID ){
		if ( tcp_con_state == connection_open){
			/* empty the send buffer before clossing the connection */
			//TODO send_data(
		}
		buffer_make_empty();
		f ( close( socket_id) == 0 )
			tcp_con_state = connection_closed;
		else tcp_con_state = connection_error;
	}else {
		tcp_con_state = connection_closed;
	}
	connection_is_active = false;/* connection is no more active */
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  disconnect
 *  Description:  a public method to disconnect the connection./
 *                It will change the connection state to closing.
 *                Thus the process loop can send the extra data and close the 
 *                connection
 *   =====================================================================================
 */

void
TcpConnection::disconnect(){
	if ( tcp_con_state == connection_open ){
		tcp_con_state  = connection_closing ;
	}
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  buffer_make_empty
 *  Description:  both send and recive buffers delete
 * =====================================================================================
 */
void
TcpConnection::buffer_make_empty(void){
	safe_delete_array( recv_buffer);
	safe_delete_array( send_buffer );
	return;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  recv_data
 *  Description:  recive data from the kernel buffer and call processing the data
 *                //FIXME there might be scenario when a full request/response packet
 *                is not present into the kernel buffer(when packet size is large)
 *                ... we are calling process_data but don't know the whole packet is
 *                 present or not. Need to think some logic for this
 * =====================================================================================
 */
bool
TcpConnection::recv_data( void ){
	bool             return_val;
	unsigned char    *temp_buff;
	ssize_t          recv_status;
	if ( !is_connected() ){
		return_val = false;
	}else{
		if ( recv_buffer == 0 ){
			recv_buffer = new unsigned char[5120];
			recv_buffer_capacity = 5120;
			recv_buffer_used = 0;
		}
		else if	( ( recv_buffer_capacity - recv_buffer_used ) < 2048 ){
			temp_buff = new unsigned char [ recv_buffer_capacity + 5120 ];
			memcpy( temp_buff , recv_buffer, recv_buffer_used );
			recv_buffer_capacity += 5120;
			safe_delete_array( recv_buffer);
			recv_buffer = temp_buff;
		}
		return_val = true;
	}
	recv_status = ::recv( socket_id , (char*)&recv_buffer[recv_buffer_used],
			    (recvbuf_size - recvbuf_used ), 0 );
	if ( recv_status < 0 ){ /* recv error */  
		std::cerr<<"TcpConnection::recv_data() : Error\n";
		return_val = false;;
	}else if(recv_status == 0 ){
		std::cerr<<"TcpConnection::recv_buffer() : connection closed\n";
		return_val = false;
	}else{/* success on data recv */
		std::cout<<"Recv [ "<<recv_status <<"] bytes from recv_buffer\
		       	location [ " <<recv_buffer_used<<" ] \n";
		recv_buffer_used += (size_t)recv_status;
		process_receive_data();
	}
	return return_val;
}


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  send_data
 *  Description:  pop data from send buffer and forward to kernel buffer
 *                When the total data length is not able to placed into 
 *                kernel buffer. Need to push at send buffer front.
 * =====================================================================================
 */
bool 
TcpConnection::send_data( void ){
	unsigned char *data;
	size_t         length;
	ssize_t        send_status;

	data = nullptr;
	length = 0;
	send_status = 0;
	if ( send_buffer_pop( &data , &length ) ){
		send_status = ::send( socket_id,(const char*)data,length,0);
		if ( errno == EPIPE ) send_status = -1;
	}
	if( send_status > 0 ){/* send  data  success*/
		std::cout<<" Send [ "<<send_status<<" bytes to network buffer\n";
		/* need to resend skipped bytes.. add to the front of send buffer */
		if ( (size_t)send_status < length ){
#ifdef DBUG
			std::cout<<"Not able to send all bytes to the network buffer\
			       	need to push data infront of send buffer\n";
#endif
			(void)send_buffer_push_front( &data[send_status],length - (size_t)send_status);
		}
		else if( (size_t)send_status > length ){/* wrote extra */
			return_val = false;
		}else return_val = true;
	}
	else{/* send failed */
		(void)send_buffer_push_front(data, length);
	}
	/* delete the array */
	safe_delete_array(data);
	if ( send_status <0 ){
		if ( errno != EWOULDBLOCK ) {
			tcp_con_state = connection_error; //TODO connection_closed
			return_val = false;
		}
	}
	return return_val;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  process_data
 *  Description:  process the recived data. 
 * =====================================================================================
 */
//TODO impl
bool
TcpConnection::process_receive_data(){
	//TODO process the recv data and create response and update into the send buffer queue

}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  run_loop_process_connection
 *  Description:  loop untill the connection is getting closed or some error occured
 *                 during send || recv || processing data
 * =====================================================================================
 */

void* TcpConnection::run_loop_process_connection( void* temp){
	if ( temp == NULL ){
		return nullptr;
	}
	TcpConnection *tcp_con = (TcpConnection*)temp;
	while(tcp_con->connection_is_active){
		thread_sleep( LOOP_GRANULARITY);
		if ( !tcp_con->process() )
			return nullptr;
	}
	return nullptr;
}

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  process
 *  Description:  process the data
 * =====================================================================================
 */
void
TcpConnection::process( void){

	/* process the data depending on the state of connection */

	switch(get_state()){
		case connection_open:
			/* receive data */
			if ( !recv_data() ){
				return false;
			}
			break;
		case connection_closing:
		       if ( send_buffer ){
			       if ( send_buffer_used > 0 ){
				       /* there are some data to send */
				       break;
			       }
			       safe_delete_array(send_buffer);
		       }
		case connection_closed:
		case connection_error:
		       connection_is_active = false;
		       return true;
	}
	/* send data */
	if( !send_data() ){
		return false;
	}
	return true;
}

