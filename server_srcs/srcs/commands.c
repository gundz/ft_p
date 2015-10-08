#include <stdio.h>
#include <sys/wait.h>
#include <limits.h>
#include <libft.h>
#include <libftsocket.h>
#include <server.h>

int						command_get_file(int sockfd)
{
	char				*path;
	int					fd;

	path = get_char_string(sockfd);
	if ((fd = open_file_read(path)) == -1)
		return (error_handling(-1, sockfd, MSG_NO_SUCH_FILE));
	error_handling(0, sockfd, MSG_FILE_GET_CONFIRM);
	if (send_file(sockfd, fd, NULL) == -1)
	{
		close(fd);
		return (error_handling(0, sockfd, MSG_FILE_GET_ERR));
	}
	close(fd);
	return (0);
}

int						command_put_file(int sockfd)
{
	char				*path;
	char				*filename;
	int					fd;

	if ((path = get_char_string(sockfd)) == NULL)
		return (-1);
	filename = ft_basename(path);
	free(path);
	if ((fd = open_file_write(filename)) == -1)
		return (error_handling(-1, sockfd, MSG_NO_SUCH_FILE));
	send_int32(sockfd, MSG_FILE_PUT_CONFIRM);
	if (get_file(sockfd, fd, NULL) == -1)
	{
		close(fd);
		return (error_handling(-1, -1, MSG_FILE_PUT_ERR));
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

int						command_cd(int sockfd, t_data *data)
{
	char				*new_path;
	char				*tmp;

	tmp = get_char_string(sockfd);
	new_path = ft_strijoin(3, getcwd(NULL, PATH_MAX), "/", tmp);
	free(tmp);
	if (chdir(new_path) == -1)
		return (error_handling(-1, sockfd, MSG_NO_SUCH_FILE));
	else
	{
		if (ft_strncmp(data->root_path, getcwd(NULL, PATH_MAX), ft_strlen(data->root_path)) != 0)
		{
			chdir(data->root_path);
			return (error_handling(-1, sockfd, MSG_CD_ACCESS_DENIED));
		}
		else
			return (error_handling(0, sockfd, MSG_CD_OK));
	}
	free(new_path);
	return (0);
}