#include <stdio.h>
#include <sys/wait.h>
#include <libft.h>
#include <libftsocket.h>
#include <server.h>

int						command_get_file(int sockfd)
{
	int					fd;
	char				*path;
	char				*tmp;

	tmp = get_char_string(sockfd);
	if ((path = check_command_usage(tmp, 1)) == NULL)
	{
		send_int32(sockfd, MSG_FILE_GET_USAGE);
		free(tmp);
		return (-1);
	}
	if ((fd = open_file_read(path)) == -1)
	{
		send_int32(sockfd, MSG_FILE_NOT_EXISTS);
		free(tmp);
		return (-1);
	}
	send_int32(sockfd, MSG_FILE_GET_CONFIRM);
	send_char_string(sockfd, path);
	send_file(sockfd, path, NULL);
	free(tmp);
	return (0);
}

int						command_put_file(int sockfd)
{
	char				*path;
	char				*filename;

	if ((path = get_char_string(sockfd)) == NULL)
		return (-1);
	filename = ft_basename(path);
	if (get_file(sockfd, filename, NULL) == -1)
	{
		perror("Error get_file");
		return (-1);
	}
	return (0);
}

int						command_ls(const int sockfd)
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
}

int						command_pwd(const int sockfd)
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
		if (execl("/bin/pwd", "pwd", NULL) == -1)
		{
			perror("execl: pwd");
			send(sockfd, &eof, sizeof(eof), 0);
		}
	}
	return (0);
}