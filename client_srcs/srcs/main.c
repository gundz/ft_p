#include <errno.h>
#include <stdio.h>

#include <libft.h>
#include <libftsocket.h>
#include <client.h>

char					*prompt(t_socket *serv)
{
	char				*cinput;

	ft_putstr(inet_ntoa(serv->addr.sin_addr));
	ft_putstr(" $>: ");
	get_next_line(0, &cinput);
	send_char_string(serv->fd, cinput);
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
			run = 0;
		else if (command_id == -1)
			show_msg(get_int32(serv->fd), NULL);
		else
			commands[command_id].f(serv->fd, cinput);
		free(cinput);
	}
}

int						main_client(t_data *data)
{
	int					msg;

	show_msg(MSG_CO_WAIT, inet_ntoa(data->serv.addr.sin_addr));
	msg = get_int32(data->serv.fd);
	show_msg(msg, inet_ntoa(data->serv.addr.sin_addr));
	client_commands(&data->serv, data->commands);
	close(data->serv.fd);
	show_msg(MSG_CO_DISCO, inet_ntoa(data->serv.addr.sin_addr));
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
	data.addr = argv[1];
	data.portno = ft_atoi(argv[2]);
	if (init_client(&data) == -1)
		return (EXIT_FAILURE);
	return (main_client(&data));
}
