#include <libftsocket.h>

int						command_cd(int sockfd, char *command)
{
	char				*path;
	int					msg;

	if ((path = check_command_usage(command, 1)) == NULL)
	{
		show_msg(MSG_CD_USAGE, NULL);
		return (-1);
	}
	send_int32(sockfd, MSG_CD);
	send_char_string(sockfd, path);
	msg = get_int32(sockfd);
	show_msg(msg, NULL);
	return (0);
}
