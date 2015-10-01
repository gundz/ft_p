#include <stdio.h>
#include <sys/wait.h>
#include <libft.h>
#include <libftsocket.h>
#include <server.h>

int						command_get_file(int sockfd, char *command)
{
	int					fd;
	char				*path;
	char				**tmp;
	int					ret;

	tmp = ft_strsplit(command, ' ');
	if (ft_ctablen(tmp) != 2)
	{
		send_int32(sockfd, MSG_FILE_GET_USAGE);
		ft_freectab(tmp);
		return (-1);
	}
	path = tmp[1];
	if ((fd = open_file_read(path)) == -1)
	{
		send_int32(sockfd, MSG_FILE_NOT_EXISTS);
		ft_freectab(tmp);
		return (-1);
	}
	send_int32(sockfd, MSG_FILE_GET_CONFIRM);
	send_char_string(sockfd, path);
	ret = send_file(sockfd, path, NULL);
	ft_freectab(tmp);
	if (ret == -1)
		perror("Error: send_file");
	return (ret);
}

int						command_put_file(int sockfd, char *command)
{
	char				*path;
	char				*filename;
	int					msg;

	if ((msg = get_int32(sockfd)) != MSG_FILE_PUT_CONFIRM)
		return (-1);
	if ((path = get_char_string(sockfd)) == NULL)
		return (-1);
	filename = ft_basename(path);
	if (get_file(sockfd, filename, NULL) == -1)
	{
		perror("Error get_file");
		return (-1);
	}
	return (0);
	(void)command;
}

int						command_ls(const int sockfd, char *command)
{
	pid_t				pid;
	const int			eof = EOF;

	pid = fork();
	if (pid > 0)
	{
		wait(NULL);
		send(sockfd, &eof, sizeof(eof), 0);

	}
	else
	{
		dup2(sockfd, STDOUT_FILENO);
		if (execl("/bin/ls", "ls", "-l", NULL) == -1)
		{
			perror("execl: ls");
			send(sockfd, &eof, sizeof(eof), 0);
		}
	}
	return (0);
	(void)command;
}