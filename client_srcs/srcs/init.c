#include <errno.h>
#include <stdio.h>

#include <client.h>
#include <libftsocket.h>

t_command				*init_commands(const int nb_commands)
{
	t_command			*commands;

	if (!(commands = (t_command *)malloc(sizeof(t_command) * nb_commands)))
		return (NULL);
	commands[0] = set_command("put", &command_put_file);
	commands[1] = set_command("get", &command_get_file);
	commands[2] = set_command("ls", &command_ls);
	commands[3] = set_command("pwd", &command_pwd);
	return (commands);
}

int					init_client(t_data *data)
{
	if (new_socket(&data->serv, AF_INET, inet_addr(data->addr), htons(data->portno)) == -1)
		return (-1);
	if (connect(data->serv.fd, (struct sockaddr *)&data->serv.addr, data->serv.socklen) < 0)
	{
		perror("Error connecting 1");
		return (-1);
	}
	if ((data->commands = init_commands(NB_COMMANDS)) == NULL)
		return (-1);
	return (0);
}