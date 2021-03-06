#define HTTP_TEST_PORT 31337
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
void process_http_request(int socket){
	return;	
}
int main(int argc, char**argv){
	int listen_sock, connect_sock;
	int on = 1;
	struct sockaddr_in local_addr;
	struct sockaddr_in client_addr;
	unsigned int client_addr_len = sizeof(client_addr);
	/*
		1. setup listening on given socket
		2. set socket options //not sure what this means yet
		3. setup socket address 
		4. bind the socket to a given port
		5. make the listen call
		6. enter accept/process loop
	*/
	//create listening socket - what actually happens when we make the socket call?
	if ( (listen_sock = socket( PF_INET, SOCK_STREAM, 0)) == -1){  //open a socket to listen on	
		perror("Unable to open listening socket");
		return 1;
	}
	//setup up options so the socket to be reused? need to read more about this
	if ( setsockopt( listen_sock, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on) ) == -1 ){
		perror("Setting socket option");
		return 2;
	}
	//setup the address for the socket
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons( HTTP_TEST_PORT );
	local_addr.sin_addr.s_addr = htonl( INADDR_ANY );
	//bind the socket 	
	if ( bind( listen_sock, (struct sockaddr *) &local_addr , sizeof(local_addr) )){
		perror("Unable to bind the socket");
		return 3; 
	}
	if ( listen( listen_sock, 5) == -1){
		perror("Unable to listen on the socket ");
		return 4;
	}	
	//connect-accept loop
	/*
			
	*/
	while ( ( connect_sock = accept( listen_sock, (struct sockaddr *) &client_addr, &client_addr_len ) ) != -1){
		process_http_request(connect_sock); //pass the connection sock to the request processor
		//this is boring, I'm gonna skip straight to the block cipher chapter
	}
	if ( connect_sock == -1){
		perror("Unable to accept socket");
		return 5;
		
	}
	return 0;
}

