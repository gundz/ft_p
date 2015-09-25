#ifndef		SERVER_H
# define	SERVER_H

# include <libftsocket.h>
# define NB_COMMANDS 1

typedef struct	s_data
{
	int			portno;
	t_socket	serv;
	t_socket	cli;
	t_command	*commands;
}				t_data;

int			init_server(t_data *data);

int			command_send_file(const int sockfd, char *path);

#endif