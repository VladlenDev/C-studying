//////////////////////////
//	File:	error.c
//	Author:	Zhelezov V. D.
//	Date:	02.02.2020
//	Type:	student code
//////////////////////////

#include "chat.h"

//	error function
void error(const char *err_msg)
{
	//	print error message
	perror(err_msg);

	//	terminate process
	exit(1);
}