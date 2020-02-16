//////////////////////////
//	File:	error.c
//	Author:	Zhelezov V. D.
//	Date:	02.02.2020
//	Type:	student code
//////////////////////////

#include "chat.h"

//static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//	error function
void error(const char *err_msg)
{
	//	print error message
	perror(err_msg);

	//	terminate process
	exit(1);
}

//	thread function, send messages
void * write_message(void *args)
{
	Message *mes_args = (Message*) args;

	while(1)
	{
		//pthread_mutex_lock(&mutex);

		bzero(mes_args->buffer, BUFFERSIZE);
		fgets(mes_args->buffer, BUFFERSIZE, stdin);
		mes_args->n = write(mes_args->sockfd, mes_args->buffer, strlen(mes_args->buffer));
		if(mes_args->n < 0)
			error("Error on writing.");

		//pthread_mutex_unlock(&mutex);

		int i = strncmp("Bye", mes_args->buffer, 3);
		if(i == 0)
			break;
	}

	return SUCCESS;
}

//	thread function, recieve messages
void * read_message(void *args)
{
	Message *mes_args = (Message*) args;

	while(1)
	{
		//pthread_mutex_lock(&mutex);

		bzero(mes_args->buffer, BUFFERSIZE);
		mes_args->n = read(mes_args->sockfd, mes_args->buffer, BUFFERSIZE);
		if(mes_args->n < 0)
			error("Error on reading.");
		printf("Server : %s", mes_args->buffer);

		//pthread_mutex_unlock(&mutex);

		int i = strncmp("Bye", mes_args->buffer, 3);
		if(i == 0)
			break;
	}

	return SUCCESS;
}