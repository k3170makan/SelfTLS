#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#define MAX_URI 100
#define MAX_PORT 65535
#define SCHEME "http"


#define HTTP_PORT 80
#define HTTPS_PORT 443

#define GET "GET"
#define POST "POST"
#define PUT "PUT"
#define DELETE "DELETE"
#define MOVE "MOVE"
#define DEFAULT_GET "GET / HTTP/1.1\r\n"
//define the rest of the commands later

/*
	
	parse_url parse a uri in its host and port portions in place so we can feed these details to
	the socket calls

		INPUT char * uri - uri to parse
			   char * host - host portion of the uri 
				int port - port portion of the uri
				char * path - path portion of uri
		OUTPUT
				*host - (in place) host portion of uri
				*path - (in place) path portion of uri
			   *port - (in place) port portion of uri
				int - success 
*/
int parse_url( char *uri,  
				   char **host, 
					int *port,
					char **path){
	/*
		uri ~ http[s]://[host]:[port]/[path]
		1. check that the first part of the string is 'http'
			if not there - fail
		2. skip over additional 's' if is included
		3. check that the next part of the string is '://'
			if not there - fail
		4. fill the host portion of the string until a ':' is encountered or the end of the string is reached
		5. if a ':' is encounted fill a temporary char for the port value until a '/' is encounted or the end of the string is reached
	*/
		char *pos;
		int is_https = 1;
		if (strlen(uri) < 8){
			return 1;
		}
		int i =0;
		for ( ;i < 3;i++){
			if (SCHEME[i] != uri[i] ){
				return 2;
			}
		}
		#ifdef DEBUG
		printf("[i] = %d\n", i);
		#endif
		if ( uri[i+1] == 's'){
			is_https = 0;
			i++;
		}
		//we should be at the host portion of the string now, point host to the host portion of the string and chop it off where the host ends
		if (uri[i+1] == ':' && uri[i+2] == '/' && uri[i+3] == '/'){
			*host = &(uri[i+4]); 	
		}
		else{
			return 3;
		}
		#ifdef DEBUG
			printf("[i] parsing port...\n");
		#endif
		pos = strchr(*host,':');	
		#ifdef DEBUG
			printf("[i] check (pos = %s) ...\n",pos);
		#endif
		if (!pos){
			pos = strchr(*host,'/');
		#ifdef DEBUG
			printf("[i] pos = %s\n",pos);
		#endif
			if (!pos){
				*path = NULL;
				if (is_https == 0){
					 *port = HTTPS_PORT;
				} else{ *port = HTTP_PORT; } //does this work in c?
				return 0;
			}
			*pos = '\0';
		}	
		else{
		#ifdef DEBUG
			printf("[i] check 2...\n");
		#endif
			
			char *temp_port = NULL;
			temp_port = pos+1;
			*pos = '\0';
		#ifdef DEBUG
			printf("[i] check 3 (temp_port = %s)...\n",temp_port);
		#endif
			pos = strchr(temp_port,'/');
			if (pos){
				*path = pos+1;
				*pos = '\0';

		#ifdef DEBUG
			printf("[i] check 4 (temp_port = %s)...\n",temp_port);
		#endif
				*port = atoi(temp_port);	
			}
			else{
				*port = atoi(temp_port);	
				*path = NULL;
				return 0;
			}
		}
		#ifdef DEBUG
			printf("[i] parsing path...\n");
		#endif
		//we should now be at the path portion of the string
		pos = strchr(*host,'/');
		#ifdef DEBUG
			printf("[i] check 5 path (path = %s)...\n",pos);
		#endif
		if (!pos){
			*path = NULL;
		}
		else{
			*path = pos+1;
		}
		return 0;	
}
#define MAX_GET_COMMAND 255
int http_get( int connection, char *host, char *path, int port){
		//using a static get here, should fix this up later
		static char get_command[MAX_GET_COMMAND];
		sprintf(get_command,"GET / HTTP/1.1\r\n");
		#ifdef DEBUG
		printf("[*] sending get command to '%s' on port '%d'...\n",host,port);
		printf("%s",get_command);
		#endif
		if ( send( connection, get_command, strlen(get_command),0) == -1){
			perror("Unable to send GET command:");
			return 1;
		}
		sprintf(get_command,"Host: %s\r\n",host);

		#ifdef DEBUG
		printf("%s",get_command);
		#endif
		if ( send( connection, get_command, strlen(get_command),0)  == -1){
			return 2;
		}
		sprintf(get_command,"Connection: close\r\n\r\n");
		#ifdef DEBUG
		printf("%s",get_command);
		printf("\n");
		#endif
		if ( send( connection, get_command, strlen(get_command),0)  == -1){
			return 3;
		}
		return 0;
}
int http_move( int connection, char *host, char *path, int port){
		return 0;
}
int http_post( int connection, char *host, char *path, int port){
		return 0;
}
int http_delete( int connection, char *host, char *path, int port){
		return 0;
}
int http_put( int connection, char *host, char *path, int port){
		return 0;
}
#define BUFFER_SIZE 255
void display_result(int connection){
	int received = 0;
	static char recv_buf[BUFFER_SIZE];
	while ( (received = recv(connection,recv_buf,BUFFER_SIZE,0) ) > 0 ){
		recv_buf[received] = '\0';
		printf("%s",recv_buf);
	}
	printf("\n");
}
int main(int argc, char **argv){
	/*this is not complete we should fix the path parsing, but it requires a major change in approache, so I'll do that later*/
	int client_connection;
	struct hostent *host_name;
	struct sockaddr_in host_address;
	char *host, *path;
	int port;	
	int ret = parse_url(argv[1],&host,&port,&path);
	/*
	if (ret == 0){
		printf("[*] host: %s\n",host);
		printf("[*] port: %d\n",port);
		//printf("[*] path: %s\n",path);
		return 0;
	}
	else{
	
		printf("[x] error : %d\n",ret);
	}
	*/
	if (ret != 0){
	return ret;
	}
	//connect to host
	#ifdef DEBUG
	printf("connecting to host '%s' on port '%d'...\n",host,port);
	#endif
	/**
			its straight forward
			1. create a hostent and sockaddr_in structs
			2. lookup the ip address using 'gethostbyname' which returns a pointer hostent
			3. copy the first entry in the h_addr_list array filled in by 'gethostbyname' into the sockaddr_in struct
			4. use the sockaddr_in struct to make the connect call
		 	 so the rub is, connect only accepts sockaddr_in structs, and gethostbyname on returns hostent structs 
			 
		*/	
	client_connection = socket(PF_INET,SOCK_STREAM,0); 	
	if ( !client_connection){
		perror("unable to create socket");
		return 2;
	}
	host_name = gethostbyname(host);
	if (!host_name){
		herror("unable to get hostname");
		return 3;
	}
	host_address.sin_family = AF_INET;
	host_address.sin_port = htons(HTTP_PORT);
	memcpy(&host_address.sin_addr,host_name->h_addr_list[0],sizeof(struct in_addr)); //why are we getting the first address? what happens if more than one is returned?
	#ifdef DEBUG
		printf("[*] host address = '%s' [%lu]\n",host_name->h_addr_list[0],strlen(host_name->h_addr_list[0]));
	#endif	
	if (connect(client_connection, (struct sockaddr *) &host_address, sizeof(host_address)) == -1){
		perror("could not connect to host");
		return 4;
	}
	//connection went through without a hitch :)
	#ifdef DEBUG
	printf("[*] connection succeeded!\n");
	#endif
	ret = http_get(client_connection,host,path,port); //issue the get command
	#ifdef DEBUG
	if (ret == 0){
		printf("[*] get worked!\n");
	}
	else{
		printf("[x] error sending get '%d'\n",ret);
	}
	#endif
	display_result(client_connection);
}
