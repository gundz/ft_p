#include <libft.h>
#include <libftsocket.h>

t_command				set_command(char *command, int (*f)(int, char *))
{
	t_command			commands;

	commands.command = command;
	commands.f = f;
	return (commands);
}

int						command_get_function_id(t_command *commands, char *cinput, const int nb_commands)
{
	int					i;

	i = 0;
	while (i < nb_commands)
	{
		if (ft_strcmp(commands[i].command, cinput) == 0)
			return (i);
		i++;
	}
	return (-1);
}