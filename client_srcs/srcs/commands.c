#include <stdio.h>
#include <libft.h>
#include <libftsocket.h>
#include <client.h>

int						command_get_file(int sockfd, char *command)
{
	char				*path;
	char				*filename;
	int					msg;

	send_int32(sockfd, MSG_FILE_GET);
	send_char_string(sockfd, command);
	if ((msg = get_int32(sockfd)) != MSG_FILE_GET_CONFIRM)
	{
		show_msg(msg, NULL);
		return (-1);
	}
	if ((path = get_char_string(sockfd)) == NULL)
		return (-1);
	filename = ft_basename(path);
	if (get_file(sockfd, filename, &show_percent) == -1)
	{
		perror("Error get_file");
		return (-1);
	}
	return (0);
}

int						command_put_file(int sockfd, char *command)
{
	int					fd;
	char				*path;

	if ((path = check_command_usage(command, 1)) == NULL)
	{
		show_msg(MSG_FILE_PUT_USAGE, NULL);
		return (-1);
	}
	if ((fd = open_file_read(path)) == -1)
	{
		show_msg(MSG_FILE_NOT_EXISTS, NULL);
		return (-1);
	}
	send_int32(sockfd, MSG_FILE_PUT);
	send_char_string(sockfd, path);
	if (send_file(sockfd, path, &show_percent) == -1)
	{
		show_msg(MSG_FILE_PUT_ERR, NULL);
		return (-1);
	}
	return (0);
}

int						command_ls(const int sockfd, char *command)
{
	int					n;
	char				buf[DATA_BUF_SIZE + 1];
	char				*tmp;

	send_int32(sockfd, MSG_LS);
	while ((n = recv(sockfd, &buf, DATA_BUF_SIZE, 0)) > 0)
	{
		buf[n] = '\0';
		if ((tmp = ft_strchr(buf, EOF)) != NULL)
		{
			*tmp = '\0';
			printf("%s", buf);
			break ;
		}
		else
			printf("%s", buf);

	}
	(void)command;
	return (0);
}

int						command_pwd(const int sockfd, char *command)
{
	int					n;
	char				buf[DATA_BUF_SIZE + 1];
	char				*tmp;

	send_int32(sockfd, MSG_PWD);
	while ((n = recv(sockfd, &buf, DATA_BUF_SIZE, 0)) > 0)
	{
		buf[n] = '\0';
		if ((tmp = ft_strchr(buf, EOF)) != NULL)
		{
			*tmp = '\0';
			printf("%s", buf);
			break ;
		}
		else
			printf("%s", buf);

	}
	(void)command;
	return (0);
}

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