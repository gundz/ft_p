/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgundlac <fgundlac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/08 20:37:56 by fgundlac          #+#    #+#             */
/*   Updated: 2015/10/08 20:37:58 by fgundlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libftsocket.h>
#include <stdio.h>

void				show_msg(int msg, char *more)
{
	if (msg == MSG_CO_WAIT)
		printf("%s: Waiting for server confirmation\n", more);
	if (msg == MSG_CO_CONFIRM)
		printf("%s: Connected to server\n", more);
	if (msg == MSG_CO_DISCO)
		printf("%s: Disconnected from server\n", more);
	if (msg == MSG_COMMAND_ERROR)
		printf("Error: Invalid command\n");
	if (msg == MSG_NO_SUCH_FILE)
		printf("Error: No such file or directory\n");
	if (msg == MSG_FILE_PUT_USAGE)
		printf("Error: Usage put __file__\n");
	if (msg == MSG_FILE_GET_USAGE)
		printf("Error: Usage get __file__\n");
	if (msg == MSG_FILE_GET_ERR)
		printf("Error: get error\n");
	if (msg == MSG_CD_ACCESS_DENIED)
		printf("Error: Access Denied\n");
	if (msg == MSG_CD_USAGE)
		printf("Error: Usage [cd][lcd] __path__\n");
	if (msg == MSG_LS_USAGE)
		printf("Error: Usage [ls][lls]\n");
	if (msg == MSG_PWD_USAGE)
		printf("Error: Usage [pwd][lpwd]\n");
}
