#include <libftsocket.h>
#include <stdio.h>

void				show_msg(const int msg, char *more)
{
	if (msg == MSG_CO_WAIT)
		printf("%s: Waiting for server confirmation\n", more);
	if (msg == MSG_CO_CONFIRM)
		printf("%s: Connected to server\n", more);
	if (msg == MSG_CO_DISCO)
		printf("%s: Disconnected from server\n", more);
	if (msg == MSG_COMMAND_ERROR)
		printf("Invalid command\n");
}