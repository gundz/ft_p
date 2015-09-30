#ifndef		LIBFTSOCKET_H
# define	LIBFTSOCKET_H

# include <sys/socket.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <stdlib.h>

# include <msg.h>

# define DATA_BUF_SIZE 4096

typedef struct	s_command
{
	char		*command;
	int			(*f)(int, char *);
}				t_command;

typedef int SOCKET;

typedef struct			s_socket
{
	SOCKET				fd;
	struct sockaddr_in	addr;
	socklen_t			socklen;
}						t_socket;

SOCKET					open_socket(void);
int						new_socket(t_socket *socket, const short sin_family, const in_addr_t sin_addr, const u_short sin_port);
int						get_client(t_socket *serv, t_socket *cli);

int						send_int32(const int fd, const int32_t var);
int						get_int32(const int fd);
int						send_char_string(const int fd, char *msg);
char					*get_char_string(const int fd);
int						send_data(const int fd, void *data, int size);
int						get_data(const int fd, void **data);

int						send_file(const int sockfd, char *path, \
	void (*f)(off_t, off_t));
int						get_file(int sockfd, char *path, void (*f)(off_t, off_t));

int						open_file_read(char *path);
int						open_file_write(char *path);

void					show_msg(const int msg, char *more);

void					show_percent(const off_t i, const off_t size);

t_command				set_command(char *command, int (*f)(int, char *));
int						command_get_function_id(t_command *commands, char *cinput, const int nb_commands);

#endif