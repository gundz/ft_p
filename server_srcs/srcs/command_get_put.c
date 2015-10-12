/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgundlac <fgundlac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/08 20:36:13 by fgundlac          #+#    #+#             */
/*   Updated: 2015/10/08 20:36:14 by fgundlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <libftsocket.h>
#include <server.h>

int						command_get_file(int sockfd)
{
	char				*path;
	int					fd;

	path = get_char_string(sockfd);
	if ((fd = open_file_read(path)) == -1)
	{
		free(path);
		return (error_handling(-1, sockfd, MSG_NO_SUCH_FILE));
	}
	error_handling(0, sockfd, MSG_FILE_GET_CONFIRM);
	if (send_file(sockfd, fd, NULL) == -1)
	{
		free(path);
		close(fd);
		return (error_handling(0, sockfd, MSG_FILE_GET_ERR));
	}
	free(path);
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
	if ((fd = open_file_write(filename)) == -1)
	{
		free(path);
		return (error_handling(-1, sockfd, MSG_NO_SUCH_FILE));
	}
	send_int32(sockfd, MSG_FILE_PUT_CONFIRM);
	if (get_file(sockfd, fd, NULL) == -1)
	{
		free(path);
		close(fd);
		return (error_handling(-1, -1, MSG_FILE_PUT_ERR));
	}
	free(path);
	return (0);
}
