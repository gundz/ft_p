#include <libft.h>
#include <libftsocket.h>
#include <server.h>

int						command_send_file(const int sockfd, char *path)
{
	int					fd;

	path = ft_strdup("/mnt/FCB83109B830C3C4/tmp/test.wav");
	if ((fd = open_file_read(path)) == -1)
	{
		send_int32(sockfd, MSG_FILE_SEND_NOT_EXISTS);
		return (-1);
	}
	send_int32(sockfd, MSG_FILE_GET_CONFIRM);
	send_file(sockfd, path, fd);
	close(fd);
	return (0);
}