#include <server.h>

t_command				set_command(int command, int (*f)(int))
{
	t_command			commands;

	commands.command = command;
	commands.f = f;
	return (commands);
}

int						command_get_function_id(t_command *commands, int msg, const int nb_commands)
{
	int					i;

	i = 0;
	while (i < nb_commands)
	{
		if (msg == commands[i].command)
			return (i);
		i++;
	}
	return (-1);
}