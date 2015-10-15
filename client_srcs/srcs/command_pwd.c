/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgundlac <fgundlac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/13 11:54:54 by fgundlac          #+#    #+#             */
/*   Updated: 2015/10/13 11:54:55 by fgundlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/wait.h>
#include <libft.h>
#include <libftsocket.h>
#include <client.h>

int						command_pwd(int sockfd, char *command)
{
	int					n;
	char				buf[BUFSIZ + 1];
	char				*tmp;

	if (check_command_usage(command, 0) == NULL)
		return (error_handling(-1, MSG_PWD_USAGE, NULL));
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
	(void)sockfd;
	return (0);
}

int						command_lpwd(int sockfd, char *command)
{
	pid_t				pid;

	if (check_command_usage(command, 0) == NULL)
		return (error_handling(-1, MSG_PWD_USAGE, NULL));
	pid = fork();
	if (pid == -1)
		printf("Error: lpwd\n");
	if (pid > 0)
		wait(NULL);
	else
	{
		if (execl("/bin/pwd", "pwd", NULL) == -1)
			printf("Error: lpwd\n");
	}
	(void)sockfd;
	return (0);
}
