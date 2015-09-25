#include <errno.h>
#include <stdio.h>

#include <libftsocket.h>
#include <server.h>

t_command				*init_commands(const int nb_commands)
{
	t_command			*commands;

	if (!(commands = (t_command *)malloc(sizeof(t_command) * nb_commands)))
		return (NULL);
	commands[0] = set_command("get", &command_send_file);
	return (commands);
}

int						init_server(t_data *data)
{
	static int			yes = 1;

	if (new_socket(&data->serv, AF_INET, INADDR_ANY, htons(data->portno)) == -1)
		return (-1);
	if(setsockopt(data->serv.fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) 
		return (-1);
	if (bind(data->serv.fd, (struct sockaddr *)&data->serv.addr, data->serv.socklen) == -1)
		perror("Error on binding");
	listen(data->serv.fd, 5);
	if ((data->commands = init_commands(NB_COMMANDS)) == NULL)
		return (-1);
	return (0);	
}