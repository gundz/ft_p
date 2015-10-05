#ifndef		SERVER_H
# define	SERVER_H

# include <libftsocket.h>
# include <limits.h>
# define NB_COMMANDS 5

typedef struct	s_command
{
	int			command;
	int			(*f)();
}				t_command;

typedef struct	s_data
{
	int			portno;
	t_socket	serv;
	t_socket	cli;
	t_command	*commands;
	char		root_path[PATH_MAX];
}				t_data;

int			init_server(t_data *data);

t_command	set_command(int command, int (*f)());
int			command_get_function_id(t_command *commands, int msg, const int nb_commands);

int			command_put_file(int sockfd);
int			command_get_file(int sockfd);
int			command_ls(const int sockfd);
int			command_pwd(const int sockfd);

int			command_cd(int sockfd, t_data *data);

#endif