//////////////////////////
//	File:	client.c
//	Author:	Zhelezov V. D.
//	Date:	02.02.2020
//	Type:	student code
//////////////////////////

#include <netdb.h>
#include "chat.h"

//	first argument must be server host (ipv4), second - port number
int main(int argc, char *argv[])
{
	//	check for arguments
	if(argc < 3) {
		fprintf(stderr, "usage %s hostname port\n", argv[0]);
		exit(1);
	}

	int sockfd, portnum, n;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	char buffer[BUFFERSIZE];
	
	//	opening socket
	portnum = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
		error("Error opening socket.");

	//	check for server adress
	server = gethostbyname(argv[1]);
	if(server == NULL)
		fprintf(stderr, "Error, no such host.");

	//	adding server info
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(portnum);

	//	connection
	if(connect(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("Connection failed.");

	//	chatting
	while(1)
	{
		//	writing
		bzero(buffer, BUFFERSIZE);
		fgets(buffer, BUFFERSIZE, stdin);
		n = write(sockfd, buffer, strlen(buffer));
		if(n < 0)
			error("Error on writing.");

		//	reading
		bzero(buffer, BUFFERSIZE);
		n = read(sockfd, buffer, BUFFERSIZE);
		if(n < 0)
			error("Error on reading.");
		printf("Server : %s", buffer);

		//	stop chatting message
		int i = strncmp("Bye", buffer, 3);
		if(i == 0)
			break;
	}

	//	closing
	close(sockfd);
	return 0;
}