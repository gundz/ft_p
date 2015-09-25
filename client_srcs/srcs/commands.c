#include <libftsocket.h>

int						command_get_file(const int sockfd, char *command)
{
	(void)command;
	return (get_file(sockfd, &show_percent));
}