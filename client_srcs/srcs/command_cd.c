/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgundlac <fgundlac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/13 11:54:43 by fgundlac          #+#    #+#             */
/*   Updated: 2015/10/13 11:54:44 by fgundlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftsocket.h>
#include <client.h>

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

int						command_lcd(int sockfd, char *command)
{
	char				*path;

	if ((path = check_command_usage(command, 1)) == NULL)
	{
		show_msg(MSG_CD_USAGE, NULL);
		return (error_handling(-1, MSG_CD_USAGE, NULL));
	}
	if (chdir(path) == -1)
	{
		free(path);
		return (error_handling(-1, MSG_NO_SUCH_FILE, NULL));
	}
	(void)sockfd;
	return (0);
}
