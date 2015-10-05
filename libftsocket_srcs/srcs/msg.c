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
		printf("Error: Invalid command\n");
	if (msg == MSG_FILE_NOT_EXISTS)
		printf("Error file does not exists\n");
	if (msg == MSG_FILE_PUT_USAGE)
		printf("Error: Usage put __file__\n");
	if (msg == MSG_FILE_GET_USAGE)
		printf("Error: Usage get __file__\n");
	if (msg == MSG_CD_OK)
		printf("Success: new path = \n");
	if (msg == MSG_CD_ACCESS_DENIED)
		printf("Error: Access Denied\n");
	if (msg == MSG_CD_NO_SUCH_FILE)
		printf("Error: No such file or directory\n");
	if (msg == MSG_CD_USAGE)
		printf("Error: Usage cd __path__\n");
}