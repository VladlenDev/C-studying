//////////////////////////
//	File:	chat.h
//	Author:	Zhelezov V. D.
//	Date:	02.02.2020
//	Type:	student code
//////////////////////////

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define ERROR_CREATE_THREAD -11		//	error result of pthread_create()
#define ERROR_CJOIN_THREAD -12		//	error result of pthread_join()
#define SUCCESS 0					//	correct function result
#define BUFFERSIZE 255				//	message max size

//	data for thread functions operating messages
typedef struct Message
{
	char buffer[BUFFERSIZE];
	int sockfd;
	int n;
} Message;

void error(const char *err_msg);	//	error function, prints error message and terminates application
void * write_message(void *args);	//	thread function, send messages
void * read_message(void *args);	//	thread function, recieve messages