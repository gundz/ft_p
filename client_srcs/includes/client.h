#ifndef		CLIENT_H
# define	CLIENT_H

# include <libftsocket.h>
# define NB_COMMANDS 5

typedef struct	s_command
{
	char		*command;
	int			(*f)();
}				t_command;

typedef struct	s_data
{
	t_socket	serv;
	char		*addr;
	int			portno;
	t_command	*commands;
}				t_data;

int				init_client(t_data *data);

t_command		set_command(char *command, int (*f)());
int				command_get_function_id(t_command *commands, char *cinput, const int nb_commands);

int				command_put_file(int sockfd, char *command);
int				command_get_file(int sockfd, char *command);
int				command_ls(int sockfd);
int				command_pwd(int sockfd);
int				command_cd(int sockfd, char *command);

int					error_handling(int ret, int msg, char *more);

#endif