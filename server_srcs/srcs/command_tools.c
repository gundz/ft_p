#include <server.h>

static void				set_command(t_command *commands, int command, int (*f)())
{
	commands->command = command;
	commands->f = f;
}

void					init_commands(t_command *commands)
{
	set_command(&commands[0], MSG_FILE_PUT, &command_put_file);
	set_command(&commands[1], MSG_FILE_GET, &command_get_file);
	set_command(&commands[2], MSG_LS, &command_ls);
	set_command(&commands[3], MSG_PWD, &command_pwd);
	set_command(&commands[4], MSG_CD, &command_cd);
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