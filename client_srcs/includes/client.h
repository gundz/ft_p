#ifndef		CLIENT_H
# define	CLIENT_H

# include <libftsocket.h>
# define NB_COMMANDS 3

typedef struct	s_data
{
	t_socket	serv;
	char		*addr;
	int			portno;
	t_command	*commands;
}				t_data;

int				init_client(t_data *data);

int				command_put_file(int sockfd, char *command);
int				command_get_file(int sockfd, char *command);

int				command_ls(const int sockfd, char *command);

#endif