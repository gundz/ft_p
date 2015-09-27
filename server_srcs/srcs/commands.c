#include <libft.h>
#include <libftsocket.h>
#include <server.h>

int						command_send_file(const int sockfd, char *path)
{
	int					fd;
	char				**tmp;

	tmp = ft_strsplit(path, ' ');
	if (ft_ctablen(tmp) != 2)
	{
		send_int32(sockfd, MSG_FILE_SEND_USAGE);
		ft_freectab(tmp);
		return (-1);
	}
	path = tmp[1];
	if ((fd = open_file_read(path)) == -1)
	{
		send_int32(sockfd, MSG_FILE_SEND_NOT_EXISTS);
		return (-1);
	}
	send_int32(sockfd, MSG_FILE_GET_CONFIRM);
	send_file(sockfd, path, fd, NULL);
	close(fd);
	ft_freectab(tmp);
	return (0);
}

int						command_get_file(const int sockfd, char *command)
{
	int					msg;

	msg = get_int32(sockfd);
	if (msg != MSG_FILE_GET_CONFIRM)
	{
		show_msg(msg, NULL);
		return (-1);
	}
	return (get_file(sockfd, NULL));
	(void)command;
}