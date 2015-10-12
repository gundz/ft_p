/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgundlac <fgundlac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/08 20:33:56 by fgundlac          #+#    #+#             */
/*   Updated: 2015/10/08 20:33:57 by fgundlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <netdb.h>
#include <libft.h>
#include <libftsocket.h>
#include <client.h>

char					*prompt(t_socket *serv)
{
	char				*cinput;

	ft_putstr(serv->p->h_name);
	ft_putstr(" $>: ");
	get_next_line(STDIN_FILENO, &cinput);
	return (cinput);
}

void					client_commands(t_socket *serv, t_command *commands)
{
	char				*cinput;
	int					command_id;
	int					run;

	run = 1;
	while (run == 1)
	{
		cinput = prompt(serv);
		command_id = command_get_function_id(commands, cinput, NB_COMMANDS);
		if (ft_strcmp(cinput, "quit") == 0)
		{
			send_int32(serv->fd, MSG_CO_DISCO);
			run = 0;
		}
		else if (command_id == -1)
			show_msg(MSG_COMMAND_ERROR, NULL);
		else
			commands[command_id].f(serv->fd, cinput);
		free(cinput);
	}
}

int						main_client(t_data *data)
{
	int					msg;

	show_msg(MSG_CO_WAIT, data->serv.p->h_name);
	msg = get_int32(data->serv.fd);
	show_msg(msg, data->serv.p->h_name);
	client_commands(&data->serv, data->commands);
	close(data->serv.fd);
	show_msg(MSG_CO_DISCO, data->serv.p->h_name);
	return (EXIT_SUCCESS);
}

int						main(int argc, char **argv)
{
	t_data				data;

	if (argc != 3)
	{
		printf("Usage: ./client addr port\n");
		return (EXIT_FAILURE);
	}
	if ((data.serv.p = gethostbyname(argv[1])) == NULL)
	{
		printf("Error: Invalid hostname\n");
		return (EXIT_FAILURE);
	}
	data.addr = inet_ntoa(*((struct in_addr *)data.serv.p->h_addr));
	data.portno = ft_atoi(argv[2]);
	if (init_client(&data) == -1)
		return (EXIT_FAILURE);
	return (main_client(&data));
}
