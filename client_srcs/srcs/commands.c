/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgundlac <fgundlac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/08 20:34:07 by fgundlac          #+#    #+#             */
/*   Updated: 2015/10/08 20:34:08 by fgundlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <libft.h>
#include <libftsocket.h>
#include <client.h>

int						command_get_file(int sockfd, char *command)
{
	int					fd;
	char				*path;
	char				*filename;
	int					msg;

	if ((path = check_command_usage(command, 1)) == NULL)
		return (error_handling(-1, MSG_FILE_GET_USAGE, NULL));
	if ((fd = open_file_write(path)) == -1)
		return (error_handling(-1, MSG_NO_SUCH_FILE, NULL));
	send_int32(sockfd, MSG_FILE_GET);
	send_char_string(sockfd, path);
	if ((msg = get_int32(sockfd)) != MSG_FILE_GET_CONFIRM)
		return (error_handling(-1, msg, NULL));
	filename = ft_basename(path);
	if (get_file(sockfd, fd, &show_percent) == -1)
		return (error_handling(-1, MSG_FILE_GET_ERR, NULL));
	return (0);
}

int						command_put_file(int sockfd, char *command)
{
	int					fd;
	char				*path;
	int					msg;

	if ((path = check_command_usage(command, 1)) == NULL)
		return (error_handling(-1, MSG_FILE_PUT_USAGE, NULL));
	if ((fd = open_file_read(path)) == -1)
		return (error_handling(-1, MSG_NO_SUCH_FILE, NULL));
	send_int32(sockfd, MSG_FILE_PUT);
	send_char_string(sockfd, path);
	if ((msg = get_int32(sockfd)) != MSG_FILE_PUT_CONFIRM)
		return (error_handling(-1, msg, NULL));
	if (send_file(sockfd, fd, &show_percent) == -1)
	{
		close(fd);
		return (error_handling(-1, MSG_FILE_PUT_ERR, NULL));
	}
	close(fd);
	return (0);
}

int						command_ls(int sockfd)
{
	int					n;
	char				buf[BUFSIZ + 1];
	char				*tmp;

	send_int32(sockfd, MSG_LS);
	while ((n = recv(sockfd, &buf, BUFSIZ, 0)) > 0)
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
	return (0);
}

int						command_pwd(int sockfd)
{
	int					n;
	char				buf[BUFSIZ + 1];
	char				*tmp;

	send_int32(sockfd, MSG_PWD);
	while ((n = recv(sockfd, &buf, BUFSIZ, 0)) > 0)
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
