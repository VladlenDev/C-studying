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
	if(argc < 3)
	{
		fprintf(stderr, "usage %s hostname port\n", argv[0]);
		exit(1);
	}

	pthread_t write, read;
	int status, status_addr;
	Message mes_args;
	int portnum;
	struct sockaddr_in serv_addr;
	struct hostent *server;
	
	//	opening socket
	portnum = atoi(argv[2]);
	mes_args.sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(mes_args.sockfd < 0)
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
	if(connect(mes_args.sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("Connection failed.");

	//	chatting
	status = pthread_create(&write, NULL, write_message, (void*)&mes_args);
	if(status != SUCCESS)
		error("Error on creating thread.");

	status = pthread_create(&read, NULL, read_message, (void*)&mes_args);
	if(status != SUCCESS)
		error("Error on creating thread.");

	status = pthread_join(write, (void**)&status_addr);
	if(status != SUCCESS)
		error("Error on joining thread.");

	status = pthread_join(read, (void**)&status_addr);
	if(status != SUCCESS)
		error("Error on joining thread.");

	//	closing
	close(mes_args.sockfd);
	return 0;
}