/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgundlac <fgundlac@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/10/08 20:35:51 by fgundlac          #+#    #+#             */
/*   Updated: 2015/10/08 20:35:53 by fgundlac         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

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
	t_command	commands[NB_COMMANDS];
	char		root_path[PATH_MAX];
}				t_data;

int				init_server(t_data *data);

void			init_commands(t_command *commands);
int				command_get_function_id(t_command *commands, int msg, \
	const int nb_commands);

int				command_put_file(int sockfd);
int				command_get_file(int sockfd);
int				command_ls(const int sockfd);
int				command_pwd(const int sockfd);
int				command_cd(int sockfd, t_data *data);

int				error_handling(int ret, int sockfd, int msg);

#endif
