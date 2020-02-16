//////////////////////////
//	File:	server.c
//	Author:	Zhelezov V. D.
//	Date:	02.02.2020
//	Type:	student code
//////////////////////////

#include "chat.h"

#define MAXCLIENTS 4

//	argument must be port number
int main(int argc, char *argv[])
{
	//	check for argument
	if(argc < 2)
	{
		fprintf(stderr, "Port number not provided. Program terminated.\n");
		exit(1);
	}

	pthread_t write, read;
	int status, status_addr;
	Message mes_args;
	int sockfd, portnum;
	struct sockaddr_in serv_addr, cli_addr;
	socklen_t clilen;

	//	opening socket on TCP
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0)
		error("Error opening socket.");

	//	adding server info
	bzero((char *) &serv_addr, sizeof(serv_addr));
	portnum = atoi(argv[1]);
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portnum);

	//	binding
	if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
		error("Binding failed.");

	//	listening and acceptions
	listen(sockfd, MAXCLIENTS);
	clilen = sizeof(cli_addr);
	mes_args.sockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if(mes_args.sockfd < 0)
		error("Error on accept.");

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
	close(sockfd);
	return 0;
}