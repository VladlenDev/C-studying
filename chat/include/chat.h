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
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

//	message size
#define BUFFERSIZE 255

//	error function, prints error message and terminates application
void error(const char *err_msg);