/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgundlac <fgundlac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/08 20:36:08 by fgundlac          #+#    #+#             */
/*   Updated: 2015/10/08 20:36:09 by fgundlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <libft.h>
#include <libftsocket.h>
#include <server.h>

void					server_commands(t_data *data, int *run)
{
	int					msg;
	int					command_id;

	msg = get_int32(data->cli.fd);
	command_id = command_get_function_id(data->commands, msg, NB_COMMANDS);
	if (msg == MSG_CO_DISCO)
	{
		error_handling(0, -1, MSG_CO_DISCO);
		*run = 0;
	}
	else if (command_id == -1)
		error_handling(0, data->cli.fd, MSG_COMMAND_ERROR);
	else
		data->commands[command_id].f(data->cli.fd, data);
}

int						main_server(t_data *data)
{
	int					run;
	pid_t				pid;

	run = 1;
	printf("Server launched on port: %d\n", data->portno);
	while (1)
	{
		if (get_client(&data->serv, &data->cli) == -1)
		{
			printf("FORK ERROR\n");
			return (EXIT_FAILURE);
		}
		pid = fork();
		if (pid == -1)
			return (EXIT_FAILURE);
		if (pid == 0)
		{
			while (run == 1)
				server_commands(data, &run);
			close(data->cli.fd);
			return (EXIT_SUCCESS);
		}
	}
	close(data->serv.fd);
	return (EXIT_SUCCESS);
}

int						main(int argc, char **argv)
{
	t_data				data;

	if (argc != 2)
	{
		printf("Usage: ./server port\n");
		return (EXIT_FAILURE);
	}
	if (ft_isnumbers(argv[1]) != 1)
	{
		printf("Usage: ./client addr port\n");
		return (EXIT_FAILURE);
	}
	data.portno = ft_atoi(argv[1]);
	if (init_server(&data) == -1)
		return (EXIT_FAILURE);
	return (main_server(&data));
}
