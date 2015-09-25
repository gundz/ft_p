#include <errno.h>
#include <stdio.h>

#include <libft.h>
#include <libftsocket.h>
#include <server.h>

void					server_commands(t_socket *cli, t_command *commands, int *run)
{
	char				*cinput;
	int					command_id;

	cinput = get_char_string(cli->fd);
	command_id = command_get_function_id(commands, cinput, NB_COMMANDS);
	if (ft_strcmp(cinput, "quit") == 0)
	{
		send_int32(cli->fd, MSG_CO_DISCO);
		*run = 0;
	}
	else if (command_id == -1)
		send_int32(cli->fd, MSG_COMMAND_ERROR);
	else
		commands[command_id].f(cli->fd, cinput);
	free(cinput);
}

int						main_server(t_data *data)
{
	int					run;

	run = 1;
	//FORK
	if (get_client(&data->serv, &data->cli) == -1)
		return (EXIT_FAILURE);
	while (run == 1)
		server_commands(&data->cli, data->commands, &run);
	close(data->cli.fd);
	//END FORK
	free(data->commands);
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
	data.portno = ft_atoi(argv[1]);
	if (init_server(&data) == -1)
		return (EXIT_FAILURE);
	return (main_server(&data));
}
