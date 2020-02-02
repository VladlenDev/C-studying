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

	int sockfd, newsockfd, portnum, n;
	char buffer[BUFFERSIZE];
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
	newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	if(newsockfd < 0)
		error("Error on accept.");

	//	chatting
	while(1)
	{
		//	reading
		bzero(buffer, BUFFERSIZE);
		n = read(newsockfd, buffer, BUFFERSIZE);
		if(n < 0)
			error("Error on reading.");
		printf("Client : %s", buffer);

		//	writing
		bzero(buffer, BUFFERSIZE);
		fgets(buffer, BUFFERSIZE, stdin);
		n = write(newsockfd, buffer, strlen(buffer));
		if(n < 0)
			error("Error on writing.");

		//	stop chatting message
		int i = strncmp("Bye", buffer, 3);
		if(i == 0)
			break;
	}

	//	closing
	close(newsockfd);
	close(sockfd);
	return 0;
}