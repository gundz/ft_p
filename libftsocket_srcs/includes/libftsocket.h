#ifndef		LIBFTSOCKET_H
# define	LIBFTSOCKET_H

# include <sys/socket.h>

# include <arpa/inet.h>

# include <unistd.h>

# include <stdio.h>
# include <errno.h>

# include <stdlib.h>

typedef int SOCKET;

typedef struct			s_socket
{
	SOCKET				fd;
	struct sockaddr_in	addr;
	socklen_t			socklen;
}						t_socket;

typedef enum			e_msg_type
{
	MSG, UINT32
}						t_msg_type;

SOCKET					open_socket(void);
int						new_socket(t_socket *socket, const short sin_family, const in_addr_t sin_addr, const u_short sin_port);

int						send_msg_type(const int fd, const t_msg_type type);
t_msg_type				get_msg_type(const int fd);

#endif