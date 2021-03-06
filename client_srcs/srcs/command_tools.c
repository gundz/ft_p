/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgundlac <fgundlac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/08 20:33:34 by fgundlac          #+#    #+#             */
/*   Updated: 2015/10/08 20:33:36 by fgundlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <client.h>

static void		set_command(t_command *commands, char *command, int (*f)())
{
	commands->command = command;
	commands->f = f;
}

void			init_commands(t_command *commands)
{
	set_command(&commands[0], "put", &command_put_file);
	set_command(&commands[1], "get", &command_get_file);
	set_command(&commands[2], "lls", &command_lls);
	set_command(&commands[3], "ls", &command_ls);
	set_command(&commands[4], "lpwd", &command_lpwd);
	set_command(&commands[5], "pwd", &command_pwd);
	set_command(&commands[6], "lcd", &command_lcd);
	set_command(&commands[7], "cd", &command_cd);
}

int				command_get_function_id(t_command *commands, char *cinput, \
	const int nb_commands)
{
	int					i;
	int					j;

	i = 0;
	while (i < nb_commands)
	{
		j = 0;
		while (cinput[j] == commands[i].command[j])
		{
			if (cinput[j] == '\0' || commands[i].command[j] == '\0')
				break ;
			j++;
		}
		if (cinput[j] == '\0' && commands[i].command[j] == '\0')
			return (i);
		if (cinput[j] == ' ' && commands[i].command[j] == '\0')
			return (i);
		i++;
	}
	return (-1);
}
