#ifndef LIBFTSOCKET_H
# define LIBFTSOCKET_H

# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <netdb.h>

# include <unistd.h>
# include <stdlib.h>

#include <libft.h>

typedef int SOCK;
typedef int SOCK_ERR;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

typedef struct		s_socket
{
	SOCKADDR_IN		sin;
	SOCK			sock;
	socklen_t		size;
}					t_socket;

# define PORT 80

#include <errno.h>
#include <stdio.h>

typedef struct s_file_data
{
	char		filename[255];
	uint32_t	filesize;
	uint32_t	block_size;
	uint32_t	nb_block;
}				t_file_data;

typedef struct	s_file_block
{
	uint32_t	block_id;
	char		*block;
}				t_file_block;

t_socket		*open_socket(void);
void			close_socket(t_socket *socket);

SOCK_ERR		send_msg(SOCK socket, char *msg);
SOCK_ERR		send_msg_input(SOCK socket, char **input);
char *			rec_msg(SOCK socket);

t_list			*list_dir(const char *path);
void			send_ls(t_socket *sock, const char *dir);
void			receive_ls(t_socket *socket);

#endif