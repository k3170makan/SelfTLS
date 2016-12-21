int main(int argc, char **argv){
	struct sockaddr_in socket_addr;
	struct hostent *host_addr;
	int port = 80;
	char *host = argv[1];
	client_connection = socket(AF_INET, SOCK_STREAM);
}
