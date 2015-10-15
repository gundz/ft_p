/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftsocket.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgundlac <fgundlac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/08 20:37:21 by fgundlac          #+#    #+#             */
/*   Updated: 2015/10/08 20:37:22 by fgundlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTSOCKET_H
# define LIBFTSOCKET_H

# include <sys/socket.h>
# include <arpa/inet.h>
# include <unistd.h>
# include <stdlib.h>
# include <msg.h>

typedef struct			s_socket
{
	struct hostent		*p;
	int					fd;
	struct sockaddr_in	addr;
	socklen_t			socklen;
}						t_socket;

int						open_socket(void);
int						new_socket(t_socket *socket, short sin_family, \
	in_addr_t sin_addr, u_short sin_port);
int						get_client(t_socket *serv, t_socket *cli);
int32_t					safe_recv(int sockfd, void *buf, int buf_size);

int						send_int32(int fd, int32_t var);
int						get_int32(int fd);
int						send_char_string(int fd, char *msg);
char					*get_char_string(int fd);

int						open_file_read(char *path);
int						open_file_write(char *path);
int						send_file(int sockfd, int fd, void (*f)(off_t, off_t));
int						get_file(int sockfd, int fd, void (*f)(off_t, off_t));

void					show_msg(int msg, char *more);
void					show_percent(off_t i, off_t size);

char					*check_command_usage(char *command, \
	unsigned int nb_arg);

#endif
